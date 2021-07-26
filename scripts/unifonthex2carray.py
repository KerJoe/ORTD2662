import os

ps = os.path.sep

fi = open(os.path.dirname(__file__)+ps+"unifont.hex", 'r')
fo = open(os.path.dirname(__file__)+ps+".."+ps+"osd"+ps+"1bit_font.c", 'w')

def hex2list(line):
    line_sep =  line.split(':') # Separate line into address and data strings
    address = int("0x"+line_sep[0], 16)
    data = []
    for i in range(0, len(line_sep[1]) - 1, 2):
        data.append(int("0x" + line_sep[1][i:i+2], 16))
    return { address:data } # Return a dictonary

char_dict = {}
for line in fi:
    char_dict.update(hex2list(line))

# Set Control characters to blank
char_dict[0x7f] = char_dict[0x20]
for i in range (0x00, 0x1f+1):
    char_dict[i] = char_dict[0x20]

fo.writelines(("#include <stdint.h>\n",
               "#include \"osd/1bit_font.h\"\n",
               "\n",
               "const uint8_t font_1bit[][16] =\n",
               "{\n"))
for i in range (0x00, 0x7f+1):
    fo.writelines("\t{\n")
    for row in char_dict[i]:
        row_comment = ""
        for k in range(7, 0-1, -1):
            if ((row >> k) & 1):
                row_comment += "# "
            else:
                row_comment += ". "
        fo.writelines("\t\t{0:#010b}, // {1}\n".format(row, row_comment))
    fo.writelines("\t},\n")

fo.writelines("};")