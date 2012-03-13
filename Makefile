-include Config.mk

################ Source files ##########################################

EXE	:= ${NAME}
SRCS	:= $(wildcard *.c)
OBJS	:= $(addprefix $O,$(SRCS:.c=.o))

################ Compilation ###########################################

.PHONY: all clean dist distclean maintainer-clean

all:	Config.mk config.h ${EXE}

run:	${EXE}
	@./${EXE}

${EXE}:	${OBJS}
	@echo "Linking $@ ..."
	@${CXX} ${LDFLAGS} -o $@ ${OBJS} ${LIBS}

tools/crypt:	$Otools/crypt.o
	@echo "Linking $@ ..."
	@${CXX} ${LDFLAGS} -o $@ $<

tools/decrypt:	$Otools/decrypt.o
	@echo "Linking $@ ..."
	@${CXX} ${LDFLAGS} -o $@ $<

$O%.o:	%.c
	@echo "    Compiling $< ..."
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	@${CXX} ${CXXFLAGS} -MMD -MT "$(<:.c=.s) $@" -o $@ -c $<

%.s:	%.c
	@echo "    Compiling $< to assembly ..."
	@${CXX} ${CXXFLAGS} -S -o $@ -c $<

################ Installation ##########################################

.PHONY:	install uninstall

ifdef BINDIR
EXEI	:= $(addprefix ${BINDIR}/,${EXE})

install:	${EXEI}
${EXEI}:	${EXE}
	@echo "Installing $< as $@ ..."
	@${INSTALLEXE} $< $@

uninstall:
	@echo "Removing ${EXEI} ..."
	@rm -f ${EXEI}
endif

################ Maintenance ###########################################

clean:
	@[ ! -d ./$O ] || rm -rf ./$O

distclean:	clean
	@rm -f Config.mk config.h config.status

maintainer-clean: distclean

${OBJS}:		Makefile Config.mk config.h
Config.mk:		Config.mk.in
config.h:		config.h.in
Config.mk config.h:	configure
	@if [ -x config.status ]; then echo "Reconfiguring ..."; ./config.status; \
	else echo "Running configure ..."; ./configure; fi

-include ${OBJS:.o=.d}
