all: checkmakefiles
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile

makefiles:
	cd src && opp_makemake -f --deep --make-so -o openflow -O out -I../../inet/src/transport/tcp/queues -I../../inet/src/transport/tcp_common -I../../inet/src/base -I../../inet/src/util -I../../inet/src/linklayer/ieee80211/mac -I../../inet/src/transport/udp -I../../inet/src/transport/tcp -I../../inet/src/linklayer/ieee80211/radio/errormodel -I../../inet/src/util/headerserializers -I../../inet/src/linklayer/ieee80211/radio -I../../inet/src/status -I../../inet/src/transport/sctp -I../../inet/src/networklayer/icmpv6 -I../../inet/src/linklayer/radio/propagation -I../../inet/src/transport/contract -I../../inet/src/networklayer/ipv6tunneling -I../../inet/src/world/radio -I../../inet/src/linklayer/contract -I../../inet/src/util/headerserializers/udp -I../../inet/src/util/headerserializers/tcp -I../../inet/src/linklayer/radio -I../../inet/src/world/obstacles -I../../inet/src/networklayer/common -I../../inet/src/linklayer/ethernet -I../../inet/src/networklayer/arp -I../../inet/src/networklayer/ipv6 -I../../inet/src/networklayer/routing/aodv -I../../inet/src/networklayer/contract -I../../inet/src -I../../inet/src/networklayer/xmipv6 -I../../inet/src/util/headerserializers/sctp -I../../inet/src/util/headerserializers/ipv6 -I../../inet/src/battery/models -I../../inet/src/networklayer/autorouting/ipv4 -I../../inet/src/applications/tcpapp -I../../inet/src/networklayer/ipv4 -I../../inet/src/mobility/contract -I../../inet/src/applications/pingapp -I../../inet/src/linklayer/common -I../../inet/src/util/headerserializers/ipv4 -L../../inet/out/$$\(CONFIGNAME\)/src -linet -DINET_IMPORT -KINET_PROJ=../../inet

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi
