#!/usr/bin/python

import os
import sys
import posixpath
import struct
import datetime


sensor_ddr_file = "sensor_ddr.bin"	# sensor ddr file
sensor_file     = "sensor.bin"		# sensor out bin file
version_file    = "../version"		# sensor out bin file

version_padding =b'\0\0\0\0'
#version_padding =bytes([0x00, 0x00, 0x00, 0x00])

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


	