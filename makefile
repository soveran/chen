PREFIX?=/usr/local
MANPREFIX?=${PREFIX}/share/man
STRIP?=strip

default: chen

chen: chen.c
	$(CC) -Wall -Os -o chen chen.c

clean:
	@echo cleaning
	@rm -f chen

install: chen
	@echo stripping executable
	@${STRIP} chen
	@echo installing executable to ${PREFIX}/bin
	@mkdir -p ${PREFIX}/bin
	@cp -f chen ${PREFIX}/bin/chen
	@chmod 755 ${PREFIX}/bin/chen

	@echo installing manual pages to ${MANPREFIX}/man1
	@mkdir -p ${MANPREFIX}/man1
	@cp -f chen.1 ${MANPREFIX}/man1/chen.1
	@chmod 644 ${MANPREFIX}/man1/chen.1

uninstall:
	@echo removing executable from ${PREFIX}/bin
	@rm ${PREFIX}/bin/chen
	@echo removing manual pages from ${MANPREFIX}/man1
	@rm ${MANPREFIX}/man1/chen.1

test:
	@sh test/tests.sh

.PHONY: clean install uninstall test
