# Functions for converting between raw binary and RTD2662 OSD Variable Length Code (VLC)
# NOTE: Here MSN and LSN mean Most Significant Nibble and Least Significant Nibble respectivly

from bitstring import BitStream

test_data = [ # "@" Symbol 12x16
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00100000,
    0b00000010,
    0b00011100,
    0b01100000,
    0b00000101,
    0b01001010,
    0b00100000,
    0b00000101,
    0b01010010,
    0b11100000,
    0b00000100,
    0b01010010,
    0b11100000,
    0b00000001,
    0b00100000,
    0b00000000,
    0b00000000,
    0b00000000,
]

# RTD2660 Datasheet, Page 387
# Note that the codes are bit-reversed (See Note 2)
vlc_dict = {
    0:  "0b0",
    1:  "0b001",

    2:  "0b0101",
    3:  "0b1101",

    4:  "0b0011",
    5:  "0b01011",


    6:  "0b11011",
    7:  "0b00111",

    8:  "0b010111",
    9:  "0b110111",

    10: "0b001111",
    11: "0b101111",


    12: "0b0011111",
    13: "0b1011111",

    14: "0b0111111",
    15: "0b01111111",
}

# TODO: Research bugs with VLC Code - 15: "0b11111110"
def encode_vlc(data):
    """Convert binary data into VLC"""
    # Break bytes into nibbles (!!! Most Significant First !!!)
    data_nib = []
    for data_byte in data:
        data_nib.append((data_byte >> 4) & 0xF) # MSN
        data_nib.append(data_byte & 0xF)        # LSN

    # Count the number of occurrences of each 4-bit value
    data_freq = []
    for i in range(16):
        data_freq.append((i, data_nib.count(i)))
    # Sort array, Most Frequent First
    data_freq = sorted(data_freq, key=lambda x:-x[1])
    data_freq = [ i[0] for i in data_freq ] # Remove frequency
    # Pack two nibbles into byte
    data_codes = [ (data_freq[i*2] << 4 | data_freq[i*2+1]) for i in range(8)]

    # Assign a code to each number based on frequency (Shorter codes to most common nibbles)
    data_vlc = [0] * 16
    for i in range(16):
        data_vlc[data_freq[i]] = vlc_dict[i]
    # Create a bitstream, which we fill with vlc codes
    data_bitstr = BitStream()
    for nibble in data_nib:
        data_bitstr.prepend(data_vlc[nibble])
    data_bitstr.prepend("0b11111111") # Put an end of data code
    if (len(data_bitstr) % 8):
        data_bitstr.prepend(8 - (len(data_bitstr) % 8)) # Pad to whole byte
    data_out = [ i.uint for i in data_bitstr.cut(8) ] # Convert to 8 bit int array
    data_out.reverse()

    return data_codes, data_out

# TODO: Finish decode_vlc
def decode_vlc(nib_vlc, data):
    data.reverse()
    data_bitstr = BitStream()


#print(encode_vlc(test_data))