import os
import vlc_encode_decode

ps = os.path.sep

fi = open(os.path.dirname(__file__)+ps+"unifont.hex", 'r')
fo = open(os.path.dirname(__file__)+ps+".."+ps+"osd"+ps+"1bit_font_vlc.c", 'w')

def hex2list(line):
    line_sep =  line.rstrip().split(':') # Remove trailing characters then separate the line into address and data strings
    address = int(line_sep[0], 16)
    # Convert every pair of chars from hex, and store in array
    data = []
    for i in range(0, len(line_sep[1]), 2):
        data.append(int(line_sep[1][i:i+2], 16))
    return { address:data } # Return a dictonary

# Convert Unifont 8xN into RTD 12x18
def convertRTD(data_in):
    data_out = [0] * (12 * 18 // 8)
    for i in range(len(data_in) // 2):
        data_out[i*3+0] = (data_in[i*2+1] << 4) & 0xF0
        data_out[i*3+1] = (data_in[i*2+1] >> 4) & 0x0F
        data_out[i*3+2] = data_in[i*2] & 0xFF
    return data_out

# Fill dictionary with characters
char_dict = {}
for line in fi:
    char_dict.update(hex2list(line))


# Fill output array
char_arr = []
# Read dictionary excluding control characters (0-1F and 7F)
char_arr.extend([ char_dict[i] for i in range(0x20, 0x7F) ])
# TODO: Add pseudo-graphic characters


# Convert 8x16 to 12x18 with RTD byte order and output to 1 dimensional list
char_flat = []
for i in char_arr:
    char_flat.extend(convertRTD(i))

# Compress into VLC
code, arrdata = vlc_encode_decode.encode_vlc(char_flat)

fo.writelines(("#include <stdint.h>\n",
               "#include \"osd/1bit_font_vlc.h\"\n",
               "\n",
               "const uint8_t font_1bit_vlc[] =\n",
               "{\n"))
fo.writelines("\t// VLC Codes\n\t")
for i in code:
    fo.writelines("{0:#04x}, ".format(i))
fo.writelines("\n\t// Stream Length (MSB)\n\t")
fo.writelines("{1:#04x}, {0:#04x},".format(len(arrdata) & 0xFF, len(arrdata) >> 8))
fo.writelines("\n\t// VLC Data stream")
for i in range(len(arrdata)):
    if (not (i % 16)):
        fo.writelines("\n\t")
    fo.writelines("{0:#04x}, ".format(arrdata[i]))
fo.writelines("\n};")