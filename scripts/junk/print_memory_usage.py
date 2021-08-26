f = open("output/firmware.mem", 'r')
lines = f.readlines()

mems = {}

stack_start = int(lines[20][17:22], 16)
stack_size  = int(lines[20][44:lines[20].find(" byte")], 10)
# mems["Stack"] = [ stack_start, stack_size, 0 ]
mems["Internal RAM"] = [ 0, 256 - stack_size, 256 ]

# iram_start = int(lines[21][47:52], 16)
# iram_size  = int(lines[21][57:lines[21].find(" byte")], 10)
# mems["Internal RAM"] = [ iram_start, iram_size, 0 ]

xram_start = int(lines[27][20:27], 16)
xram_size  = int(lines[27][38:44], 10)
mems["External RAM"] = [ xram_start, xram_size, 640 ]

rom_start = int(lines[28][20:27], 16)
rom_size  = int(lines[28][38:44], 10)
mems["Flash"] = [ rom_start, rom_size, 65536 ]

print("Memory Usage")
print("------------")

for memstr in mems:
    mem = mems[memstr]
    if (mem[2] != 0):
        memperc = mem[1] / mem[2] * 100
    else:
        memperc = 0
    print((memstr+": ").ljust(15) + str(mem[1]).rjust(5) + " bytes " + "({:5.1f}% Full)".format(memperc))
