#Try to detect INET if variable is not set
ifndef INET_PROJ
    ifneq ($(wildcard ../inet),)
        INET_PROJ=../../inet
    else
        $(error "Cannot find INET framework in the usual location. You have to set the PATH to INET in the INET_PROJ variable")
    endif
endif
all: checkmakefiles
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile

makefiles:
	cd src && opp_makemake --make-so -f --deep --no-deep-includes -O out -KINET_PROJ=../../inet -I. -I$$\(INET_PROJ\)/src -L$$\(INET_PROJ\)/src -lINET$$\(D\)

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi
	