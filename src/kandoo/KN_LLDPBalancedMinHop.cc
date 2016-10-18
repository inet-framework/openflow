#include <KN_LLDPBalancedMinHop.h>
#include <algorithm>
#include <string>


Define_Module(KN_LLDPBalancedMinHop);


KN_LLDPBalancedMinHop::KN_LLDPBalancedMinHop(){

}

KN_LLDPBalancedMinHop::~KN_LLDPBalancedMinHop(){

}

void KN_LLDPBalancedMinHop::initialize(){
    LLDPBalancedMinHop::initialize();


    knAgent = NULL;
    appName="KN_LLDPBalancedMinHop";

    //register signals
    kandooEventSignalId =registerSignal("KandooEvent");
    getParentModule()->subscribe("KandooEvent",this);

}



void KN_LLDPBalancedMinHop::handlePacketIn(OFP_Packet_In * packet_in_msg){
    //get some details
    CommonHeaderFields headerFields = extractCommonHeaderFields(packet_in_msg);

    //ignore lldp packets
    if(headerFields.eth_type == 0x88CC){
        return;
    }

    //ignore arp requests
    if(ignoreArpRequests && headerFields.eth_type == ETHERTYPE_ARP && packet_in_msg->getMatch().OFB_ARP_OP == ARP_REQUEST){
        return;
    }


    //compute path for non arps
    std::list<LLDPPathSegment> route = computeBalancedMinHopPath(headerFields.swInfo->getMacAddress(),headerFields.dst_mac.str());

    //if route empty flood
    if(route.empty()){
        if(!knAgent->getIsRootController()){
            //ask our root controller for instructions
            KandooEntry entry = KandooEntry();
            entry.trgApp = "KN_LLDPBalancedMinHop";
            entry.srcApp = "KN_LLDPBalancedMinHop";
            entry.trgController = "RootController";
            entry.trgSwitch = "";
            entry.srcSwitch = headerFields.swInfo->getMacAddress();
            entry.type=1;
            entry.srcController = controller->getFullPath();
            entry.payload = packet_in_msg->dup();

            knAgent->sendRequest(entry);

        } else {
            if(dropIfNoRouteFound && headerFields.eth_type != ETHERTYPE_ARP){
                dropPacket(packet_in_msg);
            } else {
                floodPacket(packet_in_msg);
            }
        }

    }else {
        std::string computedRoute = "";
        //send packet to next hop
        LLDPPathSegment seg = route.front();
        route.pop_front();
        sendPacket(packet_in_msg,seg.outport);

        //set flow mods for all switches under my controller's command
        oxm_basic_match match = oxm_basic_match();
        match.OFB_ETH_DST = headerFields.dst_mac;
        match.OFB_ETH_SRC = headerFields.src_mac;

        match.wildcards= 0;
        match.wildcards |= OFPFW_IN_PORT;
        match.wildcards |= OFPFW_DL_TYPE;

        TCPSocket * socket = controller->findSocketFor(packet_in_msg);
        sendFlowModMessage(OFPFC_ADD, match, seg.outport, socket,idleTimeout,hardTimeout);

        //concatenate route
       computedRoute += seg.chassisId + " -> ";

        //iterate the rest of the route and set flow mods for switches under my control
        while(!route.empty()){
            seg = route.front();
            route.pop_front();
            oxm_basic_match match = oxm_basic_match();
            match.OFB_ETH_DST = headerFields.dst_mac;
            match.OFB_ETH_SRC = headerFields.src_mac;

            match.wildcards= 0;
            match.wildcards |= OFPFW_IN_PORT;
            match.wildcards |= OFPFW_DL_TYPE;

            computedRoute += seg.chassisId + " -> ";

            TCPSocket * socket = controller->findSocketForChassisId(seg.chassisId);
            //is switch under our control
            if(socket != NULL){
                sendFlowModMessage(OFPFC_ADD, match, seg.outport, socket,idleTimeout,hardTimeout);
            }
        }

        //clean up route
        computedRoute.erase(computedRoute.length()-4);
        EV << "Route:" << computedRoute << endl;
    }

}




void KN_LLDPBalancedMinHop::receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
    LLDPBalancedMinHop::receiveSignal(src,id,obj);

    //set knagent link
    if(knAgent == NULL && controller != NULL){
        auto appList = controller->getAppList();

        for(auto iterApp=appList->begin();iterApp!=appList->end();++iterApp){
            if(dynamic_cast<KandooAgent *>(*iterApp) != NULL) {
                KandooAgent *kn = (KandooAgent *) *iterApp;
                knAgent = kn;
                break;
            }
        }
    }



    //check kandoo events
    if(id == kandooEventSignalId){
        if(dynamic_cast<KN_Packet *>(obj) != NULL) {
            KN_Packet *knpck = (KN_Packet *) obj;
            if(strcmp(knpck->getKnEntry().trgApp.c_str(),appName.c_str())==0){
                //this is a received inform
                if(knpck->getKnEntry().type == 0){
                    //not used by this app
                } else if(knpck->getKnEntry().type == 1) {
                    //this is a received request
                    if (dynamic_cast<OFP_Packet_In *>(knpck->getKnEntry().payload) != NULL) {
                        OFP_Packet_In *pckin = (OFP_Packet_In *) knpck->getKnEntry().payload;
                        CommonHeaderFields headerFields = extractCommonHeaderFields(pckin);

                        //check if we can find a route

                        //ignore lldp packets
                        if(headerFields.eth_type == 0x88CC){
                            return;
                        }

                        //ignore arp requests
                        if(ignoreArpRequests && headerFields.eth_type == ETHERTYPE_ARP && pckin->getMatch().OFB_ARP_OP == ARP_REQUEST){
                            return;
                        }


                        //compute path for non arps
                        std::list<LLDPPathSegment> route = computeBalancedMinHopPath(knpck->getKnEntry().srcSwitch,headerFields.dst_mac.str());

                        //if route empty flood
                        if(route.empty()){
                            if(dropIfNoRouteFound && headerFields.eth_type != ETHERTYPE_ARP){
                                //respond with a drop packet
                                KandooEntry entry2 = KandooEntry();
                                entry2.trgApp = "KN_LLDPBalancedMinHop";
                                entry2.srcApp = "KN_LLDPBalancedMinHop";
                                entry2.trgController = knpck->getKnEntry().srcController;
                                entry2.trgSwitch = knpck->getKnEntry().srcSwitch;
                                entry2.srcSwitch = "";
                                entry2.type=2;
                                entry2.srcController = knpck->getKnEntry().trgController;
                                entry2.payload = createDropPacketFromPacketIn(pckin);

                                knAgent->sendReply(knpck,entry2);
                            } else {
                                //respond with flood packet
                                KandooEntry entry = KandooEntry();
                                entry.trgApp = "KN_LLDPBalancedMinHop";
                                entry.srcApp = "KN_LLDPBalancedMinHop";
                                entry.trgController = knpck->getKnEntry().srcController;
                                entry.trgSwitch = knpck->getKnEntry().srcSwitch;
                                entry.srcSwitch = "";
                                entry.type=2;
                                entry.srcController = knpck->getKnEntry().trgController;
                                entry.payload = createFloodPacketFromPacketIn(pckin);

                                knAgent->sendReply(knpck,entry);
                            }
                        } else {
                            //send packet to next hop
                            LLDPPathSegment seg = route.front();
                            route.pop_front();
                            std::string computedRoute = "";

                            //packet out
                            KandooEntry entry = KandooEntry();
                            entry.trgApp = "KN_LLDPBalancedMinHop";
                            entry.srcApp = "KN_LLDPBalancedMinHop";
                            entry.trgController = knpck->getKnEntry().srcController;
                            entry.trgSwitch = knpck->getKnEntry().srcSwitch;
                            entry.srcSwitch = "";
                            entry.type=2;
                            entry.srcController = knpck->getKnEntry().trgController;
                            entry.payload = createPacketOutFromPacketIn(pckin,seg.outport);

                            knAgent->sendReply(knpck,entry);

                            //set flow mods for all switches under my controller's command
                            oxm_basic_match match = oxm_basic_match();
                            match.OFB_ETH_DST = headerFields.dst_mac;
                            match.OFB_ETH_SRC = headerFields.src_mac;

                            match.wildcards= 0;
                            match.wildcards |= OFPFW_IN_PORT;
                            match.wildcards |= OFPFW_DL_TYPE;


                            entry = KandooEntry();
                            entry.trgApp = "KN_LLDPBalancedMinHop";
                            entry.srcApp = "KN_LLDPBalancedMinHop";
                            entry.trgController = knpck->getKnEntry().srcController;
                            entry.trgSwitch = knpck->getKnEntry().srcSwitch;
                            entry.srcSwitch = "";
                            entry.type=2;
                            entry.srcController = knpck->getKnEntry().trgController;
                            entry.payload = createFlowMod(OFPFC_ADD, match, seg.outport,idleTimeout,hardTimeout);

                            knAgent->sendReply(knpck,entry);
                            computedRoute += seg.chassisId + ":" + std::to_string(seg.outport) + " -> ";

                            //iterate the rest of the route and set flow mods for switches under my control
                            while(!route.empty()){
                                seg = route.front();
                                route.pop_front();
                                oxm_basic_match match = oxm_basic_match();
                                match.OFB_ETH_DST = headerFields.dst_mac;
                                match.OFB_ETH_SRC = headerFields.src_mac;

                                match.wildcards= 0;
                                match.wildcards |= OFPFW_IN_PORT;
                                match.wildcards |= OFPFW_DL_TYPE;

                                computedRoute += seg.chassisId + ":" + std::to_string(seg.outport) + " -> ";

                                entry = KandooEntry();
                                entry.trgApp = "KN_LLDPBalancedMinHop";
                                entry.srcApp = "KN_LLDPBalancedMinHop";
                                entry.trgController = knpck->getKnEntry().srcController;
                                entry.trgSwitch = seg.chassisId;
                                entry.srcSwitch = "";
                                entry.type=2;
                                entry.srcController = knpck->getKnEntry().trgController;
                                entry.payload = createFlowMod(OFPFC_ADD, match, seg.outport,idleTimeout,hardTimeout);

                                knAgent->sendReplyToSwitchAuthoritive(seg.chassisId,entry);
                            }

                            //clean up route
                            computedRoute.erase(computedRoute.length()-4);
                            EV << "Route:" << computedRoute << endl;
                        }

                    }

                } else if(knpck->getKnEntry().type == 2) {
                    //this is a received reply
                    if(dynamic_cast<OFP_Packet_Out *>(knpck->getKnEntry().payload) != NULL){
                        OFP_Packet_Out *pckout = (OFP_Packet_Out *) knpck->getKnEntry().payload;
                        controller->sendPacketOut(pckout->dup(),controller->findSocketForChassisId(knpck->getKnEntry().trgSwitch));
                    } else if (dynamic_cast<OFP_Flow_Mod *>(knpck->getKnEntry().payload) != NULL){
                        OFP_Flow_Mod *pckout = (OFP_Flow_Mod *) knpck->getKnEntry().payload;
                        controller->sendPacketOut(pckout->dup(),controller->findSocketForChassisId(knpck->getKnEntry().trgSwitch));
                    }
                }
            }
        }
    }
}





