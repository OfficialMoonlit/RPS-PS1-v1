include ../../Makefile.cfg

all:
	mkdir -p cd_root
	$(CC) $(CCFLAGS)-DCOMPILE_VMODE=VMODE_PAL rps.c -o rps.elf
	elf2exe rps.elf rps.exe
	cp rps.exe cd_root
	systemcnf rps.exe > cd_root/system.cnf
	mkisofs.exe -o rps.hsf -V RockPaperScissors -sysid PLAYSTATION cd_root
	mkpsxiso rps.hsf rps.bin $(CDLIC_FILE)