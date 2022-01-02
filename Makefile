# Compatability with Windows command line tools
ifeq ($(OS),Windows_NT)
	fwd_to_back  = $(subst /,\,$1)
	remove_file  = cmd /C del /Q /F $1
	remove_files = cmd /C rmdir /Q /S $1
	list_paths   = cmd /C dir /s /b /o:n /ad $1
	EXEC = .exe
    # SDCC Bug, Replace backslash with forward slash, in dependency files, if on windows # Proper regex \\*(?=.*:)
	fix_d_files  = cscript //NoLogo scripts\\substitute.vbs s:$(OUTPUTDIR)\\:$(OUTPUTDIR)/: < $(basename $@).d > $(basename $@).d.tmp && cmd /C move $(call fwd_to_back,$(CURDIR)/$(basename $@).d.tmp $(CURDIR)/$(basename $@).d) > nul
else # Other POSIX
	remove_file  = rm -f $1
	remove_files = rm -f -r $1/*
	space :=
	space +=
	list_paths  = $(subst $(space),:,$(shell find $1 -type d))
	fix_d_files =
	EXEC =
endif


MAINFILE      = main
RLSOUTPUTDIR  = output
DBGOUTPUTDIR  = output-debug

DEBUG_FLAGS   = -D DEBUG --debug

SDCC_CFLAGS   = -mmcs51 --model-large -I$(CURDIR)
SDCC_LDFLAGS  = --xram-loc 0xFB00 --xram-size 640

PROGRAMMER    = cmd \/C rtdmultiprog.lnk -i lpt_old -d 888 -w


ifeq ($(DEBUG),1)
	SDCC_CFLAGS  += $(DEBUG_FLAGS)
	SDCC_LDFLAGS += $(DEBUG_FLAGS)
	OUTPUTDIR     = $(DBGOUTPUTDIR)
else
	OUTPUTDIR 	  = $(RLSOUTPUTDIR)
endif


# Add all subdirectories 1 level deep into make search path
VPATH =  $(wildcard ./*/)

SRCFILES = $(filter-out $(MAINFILE), $(wildcard */*.c))
RELFILES = $(patsubst %.c, $(OUTPUTDIR)/%.rel, $(notdir $(SRCFILES)))
DFILES   = $(RELFILES:.rel=.d)


all: firmware

firmware: $(OUTPUTDIR) $(OUTPUTDIR)/firmware.hex

programm: $(OUTPUTDIR)/firmware.bin
	$(PROGRAMMER) "$(CURDIR)/$(OUTPUTDIR)/firmware.bin"

memory: firmware.mem
	python scripts/print_memory_usage.py

clean: $(OUTPUTDIR)
	$(call remove_files,$(OUTPUTDIR))

$(OUTPUTDIR):
	mkdir $(OUTPUTDIR)

# Create dependency files and object files
$(OUTPUTDIR)/%.rel: %.c
	sdcc $(SDCC_CFLAGS) -o$(OUTPUTDIR)/ -MMD -c $<
	@$(fix_d_files)

# SDCC requires the main file to be passed first
$(OUTPUTDIR)/firmware.hex: $(OUTPUTDIR)/$(MAINFILE).rel $(filter-out $(OUTPUTDIR)/$(MAINFILE).rel, $(RELFILES))
	sdcc $(SDCC_CFLAGS) $(SDCC_LDFLAGS) -o$(OUTPUTDIR)/firmware.hex $^

$(OUTPUTDIR)/firmware.bin: $(OUTPUTDIR)/firmware.hex
	makebin $(OUTPUTDIR)/firmware.hex $(OUTPUTDIR)/firmware.bin

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DFILES)