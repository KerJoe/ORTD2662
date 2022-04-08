# Native compiler
NATIVE_CC = gcc
NATIVE_CFLAGS =
NATIVE_LDFLAGS =
NATIVE_OUTPUTDIR = output_native
# Firmware compiler
SDCC_CC = sdcc
SDCC_CFLAGS =
SDCC_LDFLAGS =
SDCC_OUTPUTDIR = output


# File that has the main() function
MAINFILE = core/main.c


# Add all subdirectories 1 level deep into make search path
VPATH += $(wildcard ./*/)
# Compile all .c files in directories
SRCFILES := $(wildcard */*.c)
# folderA/file1.c -> file1.d
DFILES   := $(notdir $(SRCFILES:.c=.d))
# folderA/file1.c -> file1.o
OBJFILES := $(notdir $(SRCFILES:.c=.o))


native: $(NATIVE_OUTPUTDIR) $(NATIVE_OUTPUTDIR)/native

$(NATIVE_OUTPUTDIR):
	mkdir $(NATIVE_OUTPUTDIR)

$(NATIVE_OUTPUTDIR)/native: $(addprefix $(NATIVE_OUTPUTDIR)/, $(OBJFILES))
	$(NATIVE_CC) $(NATIVE_CFLAGS) $(NATIVE_LDFLAGS) -o $@ $^

$(NATIVE_OUTPUTDIR)/%.o: %.c
	$(NATIVE_CC) $(NATIVE_CFLAGS) -MMD -o $@ -c $<


clean:
	rm -r $(NATIVE_OUTPUTDIR)