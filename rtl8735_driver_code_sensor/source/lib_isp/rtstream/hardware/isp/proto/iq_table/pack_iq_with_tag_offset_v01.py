#!/usr/bin/env python3

import os
import collections
import struct
import google.protobuf.json_format as json_format
from isp_iq_table_pb2 import *


class IqGroup(object):
    def __init__(self, name, day_id, night_id):
        self.name = name
        self.day_id = day_id
        self.night_id = night_id


class IqBinary(object):
    def __init__(self, json):
        iq = isp_iq_table_t()
        with open(json, 'r') as json_f:
            json_format.Parse(json_f.read(), iq)
        self.pb = iq.SerializeToString()


def print_help():
    print('Usage: {} packed_iq.bin iq0_day.json iq0_night.json ...'
          .format(os.sys.argv[0]))
    exit()


if len(os.sys.argv) < 4 or len(os.sys.argv) % 2 != 0:
    print_help()

pack_file = os.sys.argv[1]
json_files = os.sys.argv[2:]

pb_index = -1
pb_index_dict = {}
iq_groups = []
iq_binaries = []
for i in range(0, len(json_files), 2):
    for dn_json in json_files[i:i + 2]:
        if dn_json not in pb_index_dict:
            pb_index += 1
            pb_index_dict[dn_json] = pb_index
            iq_binaries.append(IqBinary(dn_json))
    iq_groups.append(IqGroup('IQ{}'.format(i // 2),
                             pb_index_dict[json_files[i]],
                             pb_index_dict[json_files[i + 1]]))

group_num = len(iq_groups)
binary_num = len(iq_binaries)
header_fmt = '<IIQBBB13s'
group_fmt = '<32sBB14s'
binary_fmt = '<II8s'
off = (struct.calcsize(header_fmt) + group_num * struct.calcsize(group_fmt) +
       binary_num * struct.calcsize(binary_fmt))

iq_b_total = off
for iq_b in iq_binaries:
    iq_b_total += len(iq_b.pb)
print(hex(iq_b_total))
header = struct.pack(header_fmt, 0x504B4951, 1, 0,
                     group_num, 0, binary_num, b'\0')
group = b''
for iq_g in iq_groups:
    group += struct.pack(group_fmt, bytes(iq_g.name, 'utf-8'),
                         iq_g.day_id, iq_g.night_id, b'\0')
binary = b''
for iq_b in iq_binaries:
    binary += struct.pack(binary_fmt, off, len(iq_b.pb), b'\0')
    print(off)
    off += len(iq_b.pb)

with open(pack_file, 'wb') as bin_f:
    bin_f.write((iq_b_total).to_bytes(4, byteorder="little", signed=False))
    bin_f.write(header + group + binary)
    for iq_b in iq_binaries:
        bin_f.write(iq_b.pb)
print('Generated {} from {}'.format(pack_file, json_files))

with open(pack_file+".tmp.bin", 'wb') as bin_f:
    bin_f.write(iq_binaries[0].pb)
