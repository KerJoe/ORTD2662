# Add all subdirectories 1 level deep into make search path
VPATH += $(wildcard ./*/)
# Compile all .c files in directories
SRCFILES := $(wildcard */*.c)
# folderA/file1.c -> file1.d
DFILES   := $(notdir $(SRCFILES:.c=.d))
# folderA/file1.c -> file1.o
OBJFILES := $(notdir $(SRCFILES:.c=.o))
# File that has the main() function
MAINFILE := core/main.c


# Native compiler
NATIVE_CC        = gcc
NATIVE_CFLAGS 	 = -I. -MMD -g $(shell pkg-config --cflags python3-embed)
NATIVE_LDFLAGS   = $(shell pkg-config --libs python3-embed)
NATIVE_OUTPUTDIR = output-native

NATIVE_OBJFILES := $(addprefix $(NATIVE_OUTPUTDIR)/, $(OBJFILES))
NATIVE_DFILES   := $(addprefix $(NATIVE_OUTPUTDIR)/, $(DFILES))

native: $(NATIVE_OUTPUTDIR) $(NATIVE_OUTPUTDIR)/native

$(NATIVE_OUTPUTDIR):
	mkdir $(NATIVE_OUTPUTDIR)

$(NATIVE_OUTPUTDIR)/native: $(addprefix $(NATIVE_OUTPUTDIR)/, $(OBJFILES))
	$(NATIVE_CC) $^ $(NATIVE_CFLAGS) $(NATIVE_LDFLAGS) -o $@

$(NATIVE_OUTPUTDIR)/%.o: %.c
	$(NATIVE_CC) $< $(NATIVE_CFLAGS) -o $@ -c


# Firmware compiler
SDCC_CC        = sdcc
SDCC_CFLAGS    = -I. -MMD
SDCC_LDFLAGS   =
SDCC_OUTPUTDIR = output

SDCC_OBJFILES := $(addprefix $(SDCC_OUTPUTDIR)/, $(OBJFILES))
SDCC_DFILES   := $(addprefix $(SDCC_OUTPUTDIR)/, $(DFILES))

firmware: $(SDCC_OUTPUTDIR) $(SDCC_OUTPUTDIR)/firmware.bin

$(SDCC_OUTPUTDIR):
	mkdir $(SDCC_OUTPUTDIR)

$(SDCC_OUTPUTDIR)/firmware.hex: $(addprefix $(SDCC_OUTPUTDIR)/, $(OBJFILES))
	$(SDCC_CC) $^ $(SDCC_CFLAGS) $(SDCC_LDFLAGS) -o $@

$(SDCC_OUTPUTDIR)/firmware.bin: $(SDCC_OUTPUTDIR)/firmware.hex
	makebin $(SDCC_OUTPUTDIR)/firmware.hex $(SDCC_OUTPUTDIR)/firmware.bin

$(SDCC_OUTPUTDIR)/%.o: %.c
	$(SDCC_CFLAGS) -o $@ -c $(SDCC_CFLAGS) $<


all: native firmware

clean:
	rm -rf $(NATIVE_OUTPUTDIR)
	rm -rf $(SDCC_OUTPUTDIR)


-include $(NATIVE_DFILES)