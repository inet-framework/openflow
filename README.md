# OpenFlow
OpenFlow framework is an open source extension to the [INET-Framework](https://inet.omnetpp.org/) for the event-based simulation of real-time Ethernet in the [OMNEST/OMNeT++](https://omnetpp.org/) simulation system. It provides implementations for network devices, controllers and controller applications supporting the [OpenFlow protocol](https://www.opennetworking.org/software-defined-standards/specifications/). It was originally created by the University of Würzburg, Germany and is now managed within the [INET frameworks](https://github.com/inet-framework/openflow).

This fork contains modified sources to increase compatibility to the other frameworks developed at the [CoRE (Communication over Realtime Ethernet)](https://core-researchgroup.de/) research group at the [HAW-Hamburg (Hamburg University of Applied Sciences)](https://www.haw-hamburg.de/english.html).

<img src="/doc/images/OpenFlow.png" alt="OpenFlow Environment" width="35%">

## Quick Start
1. Download OMNeT++ 5.5.1
    * [https://omnetpp.org/download/old](https://omnetpp.org/download/old)
2. Install OMNeT++
    * [https://doc.omnetpp.org/omnetpp/InstallGuide.pdf](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf)
3. Get INET framework 3.6.6
    * [https://inet.omnetpp.org/Download.html](https://inet.omnetpp.org/Download.html)
6. Get OpenFlow framework
    * GitHub: Clone framework and import it in OMNEST/OMNeT++
6. Select at least the following INET Project Features TCP Common, TCP(INET), IPv4 protocol, IPv6 protocol, Multi network layer, UDP protocol, SCTP, Ethernet, PPP, MPLS support (incl. LDP and RSVP-TE), HTTPTools, IEEE802.1d

## Continuous Integration
The build state of the master branch is monitored:
* Building:
<a><img src="https://jenkins.core-rg.de/buildStatus/icon?job=OpenFlow/OpenFlow"></a>

<table>
  <tr>
    <th></th>
    <th>Ubuntu 18.04</th>
    <th>Windows 10</th>
  </tr>
  <tr>
    <td>Building</td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=OpenFlow/OpenFlow/Nodes=Ubuntu_18.04"></td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=OpenFlow/OpenFlow/Nodes=Windows_10"></td>
  </tr>
</table>

## IMPORTANT
The OpenFlow model is our original fork to improve compatibility with CoRE4INET for SDN4CoRE. Our simulation models are under continuous development: new parts are added, bugs are corrected, and so on. We cannot assert that the implementation will work fully according to the specifications. YOU ARE RESPONSIBLE YOURSELF TO MAKE SURE THAT THE MODELS YOU USE IN YOUR SIMULATIONS WORK CORRECTLY, AND YOU'RE GETTING VALID RESULTS. 
