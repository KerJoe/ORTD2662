ifeq ($(OS),Windows_NT) # Windows tools
RMDIR = -cmd /C rd /S /Q # Ignore "cannot find the file" error
EXEC = .exe
else # POSIX tools
RMDIR = rm -r
EXEC =
endif

# Add all subdirectories 1 level deep into make search path
VPATH =  $(wildcard ./*/)
# Compile all .c files in directories
SRCFILES := $(wildcard ./*/*.c)
# File that has the main() function
MAINFILE := core/main.c
#
PROGRAMMER := python3 ../RTDMultiProg/rtdmultiprog.py -i mcp2221_c -w


# Native compiler
NATIVE_CC        = gcc
NATIVE_CFLAGS 	 = -I. -MMD -g $(shell pkg-config --cflags python3-embed)
NATIVE_LDFLAGS   = $(shell pkg-config --libs python3-embed)
NATIVE_OUTPUTDIR = output_native

NATIVE_OBJFILES := $(addprefix $(NATIVE_OUTPUTDIR)/, $(notdir $(SRCFILES:.c=.o)))
NATIVE_DFILES   := $(addprefix $(NATIVE_OUTPUTDIR)/, $(notdir $(SRCFILES:.c=.d)))

native: $(NATIVE_OUTPUTDIR) $(NATIVE_OUTPUTDIR)/native$(EXEC)

$(NATIVE_OUTPUTDIR):
	mkdir $(NATIVE_OUTPUTDIR)

$(NATIVE_OUTPUTDIR)/native$(EXEC): $(NATIVE_OBJFILES)
	$(NATIVE_CC) $^ $(NATIVE_CFLAGS) $(NATIVE_LDFLAGS) -o $@

$(NATIVE_OUTPUTDIR)/%.o: %.c
	$(NATIVE_CC) $< $(NATIVE_CFLAGS) -o $@ -c


# Firmware compiler
SDCC_CC        = sdcc
SDCC_CFLAGS    = -I. -MMD --model-large
SDCC_LDFLAGS   = --xram-loc 0xFB00 --xram-size 640
SDCC_OUTPUTDIR = output

SDCC_RELFILES := $(addprefix $(SDCC_OUTPUTDIR)/, $(notdir $(SRCFILES:.c=.rel)))
SDCC_DFILES   := $(addprefix $(SDCC_OUTPUTDIR)/, $(notdir $(SRCFILES:.c=.d)))

firmware: $(SDCC_OUTPUTDIR) $(SDCC_OUTPUTDIR)/firmware.bin

$(SDCC_OUTPUTDIR):
	mkdir $(SDCC_OUTPUTDIR)

$(SDCC_OUTPUTDIR)/firmware.hex: $(SDCC_RELFILES)
	$(SDCC_CC) $^ $(SDCC_CFLAGS) $(SDCC_LDFLAGS) -o $@

$(SDCC_OUTPUTDIR)/firmware.bin: $(SDCC_OUTPUTDIR)/firmware.hex
	makebin $(SDCC_OUTPUTDIR)/firmware.hex $(SDCC_OUTPUTDIR)/firmware.bin

$(SDCC_OUTPUTDIR)/%.rel: %.c
	$(SDCC_CC) -o $@ -c $(SDCC_CFLAGS) $<


all: native firmware

program: $(SDCC_OUTPUTDIR)/firmware.bin
	$(PROGRAMMER) "$(CURDIR)/$(SDCC_OUTPUTDIR)/firmware.bin"

clean:
	$(RMDIR) $(NATIVE_OUTPUTDIR)
	$(RMDIR) $(SDCC_OUTPUTDIR)

# Include dependency target files
-include $(NATIVE_DFILES)
-include $(SDCC_DFILES)