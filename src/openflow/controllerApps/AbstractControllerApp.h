
#ifndef ABSTRACTCONTROLLERAPP_H_
#define ABSTRACTCONTROLLERAPP_H_

#include <list>
#include <map>
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "openflow/openflow/controller/OF_Controller.h"
#include "inet/transportlayer/contract/tcp/TcpSocket.h"
#include "openflow/openflow/protocol/OpenFlow.h"
#include "openflow/messages/Open_Flow_Message_m.h"
#include "openflow/messages/OFP_Packet_In_m.h"
#include "openflow/messages/OFP_Packet_Out_m.h"
#include "openflow/messages/OFP_Flow_Mod_m.h"
#include "inet/networklayer/arp/ipv4/ArpPacket_m.h"
#include "inet/networklayer/common/InterfaceTable.h"

namespace openflow{

struct CommonHeaderFields{
    uint32_t buffer_id;
    Switch_Info * swInfo;
    int inport;
    MacAddress src_mac;
    MacAddress dst_mac;
    int eth_type;
    Ipv4Address arp_src_adr;
    Ipv4Address arp_dst_adr;
    int arp_op;
};

class AbstractControllerApp: public OperationalBase, public cListener {


    std::map<int, int> ifaceIndex;

protected:
    virtual int getIndexFromId(int id);

    static simsignal_t PacketInSignalId;
    static simsignal_t PacketOutSignalId;
    static simsignal_t PacketFeatureRequestSignalId;
    static simsignal_t PacketFeatureReplySignalId;
    static simsignal_t PacketExperimenterSignalId;
    static simsignal_t BootedSignalId;

    long packetsFlooded = 0;
    long packetsDropped = 0;
    long numPacketOut = 0;
    long numFlowMod = 0;
    int priority = 0;

    OF_Controller * controller = nullptr;

    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void finish(cComponent *component, simsignal_t signalID) override {}
    //using cIListener::finish;
    virtual void handleParameterChange(const char *parname) override;

    virtual void handleMessageWhenUp(cMessage *msg) override {
        throw cRuntimeError("Received message, this module should not receive a message");
    }


    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;

    virtual Packet * createFloodPacketFromPacketIn(Packet *packet_in_msg);
    virtual Packet * createDropPacketFromPacketIn(Packet *packet_in_msg);
    virtual Packet * createPacketOutFromPacketIn(Packet *packet_in_msg, uint32_t outport);
    virtual Packet * createFlowMod(ofp_flow_mod_command mod_com,const oxm_basic_match &match, uint32_t outport, int idleTimeOut, int hardTimeOut);
    virtual Packet * createFlowMod(ofp_flow_mod_command mod_com,const oxm_basic_match &match, uint32_t outport, int priority, int idleTimeOut, int hardTimeOut);

    bool chekIcmpEchoRequest(Packet *pkt, int &seqNumber, int &identifier);
    virtual CommonHeaderFields extractCommonHeaderFields(Packet *packet_in_msg);

    virtual void floodPacket(Packet *packet_in_msg);
    virtual void dropPacket(Packet *packet_in_msg);
    virtual void sendPacket(Packet *packet_in_msg, uint32_t outport);
    virtual void sendFlowModMessage(ofp_flow_mod_command mod_com,const oxm_basic_match &match, uint32_t outport, TcpSocket *socket,int idleTimeOut, int hardTimeOut);

    // Lifecycle methods
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

#if INET_VERSION >= 0x0404
    virtual bool isInitializeStage(int stage) const override { return stage == INITSTAGE_APPLICATION_LAYER; }
    virtual bool isModuleStartStage(int stage) const override { return stage == ModuleStartOperation::STAGE_APPLICATION_LAYER; }
    virtual bool isModuleStopStage(int stage) const override { return stage == ModuleStopOperation::STAGE_APPLICATION_LAYER; }
#else
    virtual bool isInitializeStage(int stage) override { return stage == INITSTAGE_APPLICATION_LAYER; }
    virtual bool isModuleStartStage(int stage) override { return stage == ModuleStartOperation::STAGE_APPLICATION_LAYER; }
    virtual bool isModuleStopStage(int stage) override { return stage == ModuleStopOperation::STAGE_APPLICATION_LAYER; }
#endif

public:
    AbstractControllerApp();
    ~AbstractControllerApp();

};

} /*end namespace openflow*/

#endif
