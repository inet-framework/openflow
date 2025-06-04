Notes about the INET-3.x to INET-4.x Migration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Regression testing was done by comparing network-level (~tNl) fingerprints
before and after the migration, i.e. the fingerprints produced with INET-3.x and
INET-4.x. Exact fingerprint match was achieved in all but 24 simulations; the
cause of fingerprint mismatch for the remaining simulations was not investigated
due to lack of time.

INET-3.x and INET-4.x operation differs in subtle ways, so the simulations
needed certain tweaks to achieve identical fingerprints with both versions.
These tweaks include:

  - Fixing some issues in Openflow
  - Turning off Nagle's algorithm in TCP due to differences in the two versions
  - Modifying TCP's sendData() function to behave the same way
  - Tweaking certain cable lengths to make them different, to reduce the frequency
    of unrelated events occurring at exactly the same simulation times.
  - Setting csmacdSupport=false for Ethernet MACs.
  - Etc.

For re-running the fingerprint tests, use the following versions/branches:

In OpenFlow (these changes disable Nagle's algorithm, modify cable lengths, etc.):

1. `topic/bz/inet4version_for_migration_test` – modifies migrated version (INET 4.x)
2. `topic/bz/inet3version_for_migration_test` – modifies `v20250602`  (INET 3.x)

Apply the following patches to INET. They reduce the differences between INET 3.x and 4.x
versions so that identical fingerprints can be achieved:

1. `inet3patch_for_openflow_migration_test.patch`: patch for inet-3.8.5
2. `inet4patch_for_openflow_migration_test.patch`: patch for inet-4.5.4

The list of mismatching simulations:

  scenarios/hyperflow/usa/,   -f Scenario_USA_ARP_HF_Ping_2C.ini -c General -r 0,                 101s,  106a-08f4/tplx;3d6c-df22/~tNl, PASS,
  scenarios/hyperflow/usa/,   -f Scenario_USA_ARP_HF_Ping_3C.ini -c General -r 0,                 101s,  daaf-a5e2/tplx;a11f-7a9c/~tNl, PASS,
  scenarios/hyperflow/usa/,   -f Scenario_USA_ARP_HF_Ping_4C.ini -c General -r 0,                 101s,  879f-d835/tplx;e4a0-c34a/~tNl, PASS,
  scenarios/hyperflow/usa/,   -f Scenario_USA_ARP_HF_Ping_5C.ini -c General -r 0,                 101s,  52e1-3edd/tplx;f077-fdd4/~tNl, PASS,
  scenarios/kandoo/fattree/,  -f Scenario_DynamicFatTree_ARP_KN_Ping_2C.ini -c General -r 0,      101s,  ab9a-66e8/tplx;3d71-1518/~tNl, PASS,
  scenarios/kandoo/fattree/,  -f Scenario_DynamicFatTree_ARP_KN_Ping_3C.ini -c General -r 0,      101s,  f4ba-bd9e/tplx;b4c6-1187/~tNl, PASS,
  scenarios/kandoo/fattree/,  -f Scenario_DynamicFatTree_ARP_KN_Ping_4C.ini -c General -r 0,      101s,  0c98-9200/tplx;61f8-ddfe/~tNl, PASS,
  scenarios/kandoo/fattree/,  -f Scenario_DynamicFatTree_ARP_KN_Ping_5C.ini -c General -r 0,      101s,  53c5-6de8/tplx;0100-c9e2/~tNl, PASS,
  scenarios/kandoo/fattree/,  -f TestScenario_DynamicFatTree_ARP_KN_Ping_4C.ini -c General -r 0,  101s,  9f58-d91e/tplx;7222-69c6/~tNl, PASS,
  scenarios/kandoo/usa/,      -f Scenario_USA_ARP_KN_Ping_2C.ini -c General -r 0,                 101s,  ea0e-2a48/tplx;6a29-b700/~tNl, PASS,
  scenarios/kandoo/usa/,      -f Scenario_USA_ARP_KN_Ping_3C.ini -c General -r 0,                 101s,  466d-254a/tplx;01a0-33c5/~tNl, PASS,
  scenarios/kandoo/usa/,      -f Scenario_USA_ARP_KN_Ping_4C.ini -c General -r 0,                 101s,  8d06-9a73/tplx;7938-ff2d/~tNl, PASS,
  scenarios/kandoo/usa/,      -f Scenario_USA_ARP_KN_Ping_5C.ini -c General -r 0,                 101s,  51b8-e5d3/tplx;4124-5ff8/~tNl, PASS,
  scenarios/topologyzoo/,     -f BtNorthAmerica.ini -c cfg1 -r 0,                                 101s,  4a51-e349/tplx;1f1e-f23e/~tNl, PASS,
  scenarios/topologyzoo/,     -f BtNorthAmerica_KN.ini -c cfg1 -r 0,                              101s,  e408-5cf5/tplx;4b23-54e2/~tNl, PASS,
  scenarios/topologyzoo/,     -f Cernet.ini -c cfg1 -r 0,                                         101s,  332c-6333/tplx;33d4-9310/~tNl, PASS,
  scenarios/topologyzoo/,     -f Cernet_KN.ini -c cfg1 -r 0,                                      101s,  e183-49fa/tplx;43d7-cda0/~tNl, PASS,
  scenarios/topologyzoo/,     -f Geant2009.ini -c cfg1 -r 0,                                      101s,  0f8b-e005/tplx;e6af-3ef5/~tNl, PASS,
  scenarios/topologyzoo/,     -f Geant2009_KN.ini -c cfg1 -r 0,                                   101s,  56fe-efd3/tplx;2a18-4625/~tNl, PASS,
  scenarios/topologyzoo/,     -f Iij.ini -c cfg1 -r 0,                                            101s,  ce2a-e153/tplx;931e-6268/~tNl, PASS,
  scenarios/topologyzoo/,     -f Iij_KN.ini -c cfg1 -r 0,                                         101s,  ad80-ea94/tplx;e0ee-a55a/~tNl, PASS,
  scenarios/usa/,             -f Scenario_USA_ARP_Ping_Drop.ini -c General -r 0,                  101s,  950d-cc8e/tplx;fec9-dcdf/~tNl, PASS,
  scenarios/usa/,             -f Scenario_USA_ARP_Ping_Drop_Load.ini -c General -r 0,             101s,  83e7-8bfc/tplx;0594-bd62/~tNl, PASS,
  scenarios/usa/,             -f Scenario_USA_ARP_Ping_Drop_Load_Refined.ini -c General -r 0,     101s,  5dbe-25fe/tplx;9d95-9eeb/~tNl, PASS,
