include ../../Makefile.cfg

all:
	mkdir -p cd_root
	$(CC) $(CCFLAGS)-DEXAMPLES_VMODE=VMODE_PAL rps1.c -o rps1.elf
	elf2exe rps1.elf rps1.exe
	cp rps1.exe cd_root
	systemcnf rps1.exe > cd_root/system.cnf
	mkisofs.exe -o rps1.hsf -V RPSv1 -sysid PLAYSTATION cd_root
	mkpsxiso rps1.hsf rps1.bin $(CDLIC_FILE)