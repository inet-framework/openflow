OpenFlow-20250605
-----------------

* Ported to INET-4.x. See `inet4-migration-notes/` for details. Incorporates migration work by Alfonso Ariza Quintana.
* Renamed `AbstractControllerApp` NED type to `IControllerApp`
* Added NED documentation for several undocumented modules
* Tested with omnetpp-6.1 and inet-4.5.4 and 4.4.2.


OpenFlow-20250602
-----------------

Patch release for OpenFlow 20240124.

* Added `setenv` script
* Updated `fingerprinttest` script, added network-level (~tNl) fingerprints
* ARPResponder: fix: do not add preamble and SFD to frame length
* StaticSpanningTree: fixed wrong numInitStages
* Fill in OFB_IN_PORT in internal messages
* More assertions in the code
* Compatible with omnetpp-6.1 and inet-3.8.5


OpenFlow-20240124
-----------------

This repo started as a fork of the CoRE research group's OpenFlow fork, and this release represents their last version.

* Identical to [CoRE-RG/OpenFlow's nightly/2024-01-24_15-05-30](https://github.com/CoRE-RG/OpenFlow/releases/tag/nightly%2F2024-01-24_15-05-30).
* Compatible with omnetpp-6.0.3 and inet-3.8.3