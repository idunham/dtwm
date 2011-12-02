include config.Mk
INSTDIR=${DESTDIR}${PREFIX}

all: dtwm
	
dtwm: 
	make -C src/dtwm

clean: dtwm-clean

dtwm-clean:
	make -C src/dtwm clean

install: all
	install -s -m 0755 bin/dtwm ${INSTDIR}/bin/
	#install -s -m 0644 -d conf/ ${DESTDIR}/etc/X11/
	install -s -m 0644 COPYING.MOTIF ${INSTDIR}/share/dtwm/
