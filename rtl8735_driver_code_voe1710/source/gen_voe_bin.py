import os
import sys
import posixpath
import struct
import datetime



voe_iram_file   = "output/voeiram.bin"		# itcm file
voe_dram_file   = "output/voedram.bin"		# dtcm file
voe_ddr_file    = "output/voe_ddr.bin"		# ddr file
voe_ddr2_file    = "output/voe_ddr2.bin"	# ddr 2-stage file
sensor_ddr_file = "output/sensor_ddr.bin"	# sensor ddr file

sensor_file     = "output/sensor.bin"		# sensor out bin file
voe_file        = "output/voe.bin"			# voe out bin file
version_file    = "version"					# sensor out bin file

version_padding =b'\0\0\0\0'

def getSize(fileobject):
    fileobject.seek(0,2) # move the cursor to the end of the file
    size = fileobject.tell()
    return size

####################
### Start gen. binary
####################

####################
### GET Build code date
####################

date = datetime.datetime.now()

####################
### Get VOE version
####################

with open(version_file, "rb") as f:
	version_data = f.read(20)
	version_data += version_padding


####################
### Gen. sensor.bin header
####################

with open(sensor_ddr_file, "rb") as f:
	sensor_data = f.read()
	sensor_sz = getSize(f)
	
print ('SENSOR ddr size = ', sensor_sz, hex(sensor_sz))
	
with open(sensor_file, "wb") as f:
	f.seek(0, 0)
	f.write(struct.pack('H', date.year))	# 2B length	year
	f.write(struct.pack('B', date.month))	# 1B length	month
	f.write(struct.pack('B', date.day))		# 1B length	day
	f.write(version_data)					# 24B length write itcm size
	f.write(struct.pack('I', sensor_sz))	# 4B length write dtcm size
	f.write(sensor_data)	
	f.close()	

####################
### Gen. voe.bin header
####################
	
with open(voe_iram_file, "rb") as f:
	iram_data = f.read()
	iram_sz = getSize(f)
	iram_alig = ((((int(iram_sz) + 0x1f)) >> 0x5) << 0x5) - iram_sz
print ('VOE iram size = ', iram_sz, hex(iram_sz), iram_alig)

with open(voe_dram_file, "rb") as f:
	dram_data = f.read()
	dram_sz = getSize(f)
	dram_alig = ((((int(dram_sz) + 0x1f)) >> 0x5) << 0x5) - dram_sz
	
print ('VOE dram size = ', dram_sz, hex(dram_sz), dram_alig)

with open(voe_ddr_file, "rb") as f:
	ddr_data = f.read()
	ddr_sz = getSize(f)
	ddr_alig = ((((int(ddr_sz) + 0x1f)) >> 0x5) << 0x5) - ddr_sz
	
print ('VOE ddr  size = ', ddr_sz, hex(ddr_sz),ddr_alig)
	
with open(voe_ddr2_file, "rb") as f:
	ddr2_data = f.read()
	ddr2_sz = getSize(f)
	ddr2_alig = ((((int(ddr2_sz) + 0x1f)) >> 0x5) << 0x5) - ddr2_sz
	
print ('VOE ddr2 size = ', ddr2_sz, hex(ddr2_sz),ddr2_alig)


with open(voe_file, "wb") as f:
	f.seek(0, 0)
	f.write(struct.pack('H', date.year))	# 2B length	year
	f.write(struct.pack('B', date.month))	# 1B length	month
	f.write(struct.pack('B', date.day))		# 1B length	day
	f.write(version_data)					# 24B length write itcm size

	f.write(struct.pack('I', iram_sz))		# 4B length write itcm size
	f.write(struct.pack('I', dram_sz))		# 4B length write dtcm size
	f.write(struct.pack('I', ddr_sz))		# 4B length write ddr size
	f.write(struct.pack('I', ddr2_sz))		# 4B length write ddr2 size
	for i in range(0,20):					# 20B reserved
		f.write(b'\0')
	f.write(iram_data)
	for i in range(0,iram_alig):			# alignment
		f.write(b'\0')
	
	f.write(dram_data)
	for i in range(0,dram_alig):			# alignment
		f.write(b'\0')

	f.write(ddr_data)
	for i in range(0,ddr_alig):				# alignment
		f.write(b'\0')
	f.write(ddr2_data)
	f.close()
	
cmd = "rm -rf "+voe_ddr_file+";"
cmd += "rm -rf "+voe_iram_file+";"
cmd += "rm -rf "+voe_dram_file+";"
#print(cmd)
os.system(cmd)
	