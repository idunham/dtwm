include config.Mk
INSTDIR=${DESTDIR}${PREFIX}

all: dtwm
	
dtwm: 
	make -C src/dtwm

clean: dtwm-clean

dtwm-clean:
	make -C src/dtwm clean

install: all
	mkdir -p ${INSTDIR}/bin ${INSTDIR}/share/dtwm ${DESTDIR}/etc/X11/dtwm ${DESTDIR}/etc/X11/app-defaults
	install -s -m 0755 bin/dtwm ${INSTDIR}/bin/
	install -m 0644 conf/dtwm/Dtwm ${DESTDIR}/etc/X11/app-defaults/Dtwm
	install -m 0644 conf/dtwm/system.dtwmrc ${DESTDIR}/etc/X11/mwm/system.dtwmrc
	install -m 0644 COPYRIGHT.MOTIF ${DESTDIR}${PREFIX}/share/dtwm/
