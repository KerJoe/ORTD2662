# Compatability with Windows command line tools
ifeq ($(OS),Windows_NT)
	fwd_to_back  = $(subst /,\,$1)
	remove_file  = cmd /C del /Q /F $1
	remove_files = cmd /C rmdir /Q /S $1
	list_paths   = cmd /C dir /s /b /o:n /ad $1
	EXEC = .exe
    # SDCC Bug, Replace backslash with forward slash, in dependency files, if on windows # Proper regex \\*(?=.*:)
	fix_d_files = cscript //NoLogo scripts\\substitute.vbs s:$(OUTPUTDIR)\\:$(OUTPUTDIR)/: < $(basename $@).d > $(basename $@).d.tmp && cmd /C move $(call fwd_to_back,$(CURDIR)/$(basename $@).d.tmp $(CURDIR)/$(basename $@).d) > nul
else # Other POSIX
	remove_file  = rm -f $1
	remove_files = rm -f -r $1/*
	space :=
	space +=
	list_paths  = $(subst $(space),:,$(shell find $1 -type d))
	fix_d_files =
	EXEC =
endif

OUTPUTDIR    = output
DBGOUTPUTDIR = $(OUTPUTDIR)-debug
MAINFILE     = main

# Ignore warning 158: "overflow in implicit constant conversion" because of SDCC bug where unisgned integers are treates as signed
SDCC_CFLAGS  = --disable-warning 158 -mmcs51 --model-large -o$(OUTPUTDIR)/ -I$(CURDIR)
SDCC_LDFLAGS = --xram-loc 0xFB00 --xram-size 640

GCC_CFLAGS   = -o$(DBGOUTPUTDIR)/ -I$(CURDIR) -DDEBUG
GCC_LDFLAGS  =

#PROGRAMMER 	= cmd \/C ROVATool.lnk -d2660 -ppparallel -w
PROGRAMMER	= cmd \/C rtdmultiprog.lnk -i lpt_old -d 888 -w

# Add all subdirectories 1 level deep into make search path
VPATH =  $(wildcard ./*/)

SRCFILES = $(filter-out $(MAINFILE), $(wildcard */*.c))
RELFILES = $(patsubst %.c, $(OUTPUTDIR)/%.rel, $(notdir $(SRCFILES)))
OFILES   = $(patsubst %.c, $(DBGOUTPUTDIR)/%.o, $(notdir $(SRCFILES)))
DFILES   = $(RELFILES:.rel=.d)


all: firmware #debug

firmware: $(OUTPUTDIR) $(OUTPUTDIR)/firmware.hex

debug: $(DBGOUTPUTDIR) $(DBGOUTPUTDIR)/debug$(EXE)

programm: $(OUTPUTDIR)/firmware.bin
	$(PROGRAMMER) "$(CURDIR)/$(OUTPUTDIR)/firmware.bin"

memory: firmware.mem
	python scripts/print_memory_usage.py

clean: $(OUTPUTDIR) $(DBGOUTPUTDIR)
	$(call remove_files,$(OUTPUTDIR))
	$(call remove_files,$(DBGOUTPUTDIR))

$(OUTPUTDIR):
	mkdir $(OUTPUTDIR)

# Create dependency files and object files
$(OUTPUTDIR)/%.rel: %.c
	@echo Compiling $<...
	@sdcc $(SDCC_CFLAGS) -MMD -c $<
	@$(fix_d_files)

# SDCC requires the main file to be passed first
$(OUTPUTDIR)/firmware.hex: $(OUTPUTDIR)/$(MAINFILE).rel $(filter-out $(OUTPUTDIR)/$(MAINFILE).rel, $(RELFILES))
	@echo Linking...
	@sdcc $(SDCC_CFLAGS) $(SDCC_LDFLAGS) -o$(OUTPUTDIR)/firmware.hex $^

$(OUTPUTDIR)/firmware.bin: $(OUTPUTDIR)/firmware.hex
	makebin $(OUTPUTDIR)/firmware.hex $(OUTPUTDIR)/firmware.bin


$(DBGOUTPUTDIR):
	mkdir $(DBGOUTPUTDIR)

$(DBGOUTPUTDIR)/%.o: %.c %.h
	gcc $(GCC_CFLAGS) -c $<

$(DBGOUTPUTDIR)/debug$(EXE): $(DBGOUTPUTDIR)/$(MAINFILE).o $(filter-out $(DBGOUTPUTDIR)/$(MAINFILE).o, $(OFILES))
	gcc $(GCC_CFLAGS) $(GCC_LDFLAGS) -o$(DBGOUTPUTDIR)/debug$(EXE) $^

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DFILES)