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

# Ignore warning 158: overflow in implicit constant conversion because of SDCC bug
SDCCFLAGS = --disable-warning 158 -mmcs51 --model-large -o$(OUTPUTDIR)/ -I$(CURDIR)
SDLDFLAGS = --xram-loc 0xFB00 --xram-size 640

GCCCFLAGS = -o$(DBGOUTPUTDIR)/ -I$(CURDIR) -DDEBUG
GCLDFLAGS =

PROGRAMMER 	= cmd \/C ROVATool.lnk -d2660 -ppparallel -w

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

# First create dependency files
# Then create object files
# Use sdcc -ooutput/ -IC:\test\ -MD -c ./main/main.c
$(OUTPUTDIR)/%.rel: %.c
	sdcc $(SDCCFLAGS) -MMD -MP -c $<
	$(fix_d_files)
	sdcc $(SDCCFLAGS) -c $<

# SDCC requires the main file to be passed first
$(OUTPUTDIR)/firmware.hex: $(OUTPUTDIR)/$(MAINFILE).rel $(filter-out $(OUTPUTDIR)/$(MAINFILE).rel, $(RELFILES))
	sdcc $(SDCCFLAGS) $(SDLDFLAGS) -o$(OUTPUTDIR)/firmware.hex $^

$(OUTPUTDIR)/firmware.bin: $(OUTPUTDIR)/firmware.hex
	makebin $(OUTPUTDIR)/firmware.hex $(OUTPUTDIR)/firmware.bin


$(DBGOUTPUTDIR):
	mkdir $(DBGOUTPUTDIR)

$(DBGOUTPUTDIR)/%.o: %.c %.h
	gcc $(GCCCFLAGS) -c $<

$(DBGOUTPUTDIR)/debug$(EXE): $(DBGOUTPUTDIR)/$(MAINFILE).o $(filter-out $(DBGOUTPUTDIR)/$(MAINFILE).o, $(OFILES))
	gcc $(GCCCFLAGS) $(GCLDFLAGS) -o$(DBGOUTPUTDIR)/debug$(EXE) $^

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DFILES)