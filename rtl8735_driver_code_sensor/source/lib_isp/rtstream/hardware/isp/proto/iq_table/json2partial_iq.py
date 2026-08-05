import json
import sys
from pathlib import Path
import google.protobuf.json_format as json_format
from isp_iq_table_pb2 import *
from unpack_iq_with_tag_offset import prettyjson

in_path = Path(sys.argv[1])
if not in_path.exists():
    print(in_path, "not exists!")
    sys.exit(1)

iq = isp_iq_table_t()
print("Parsing", in_path)
with open(in_path, 'r') as json_f:
    json_format.Parse(json_f.read(), iq)
pb = iq.SerializeToString()

with open(str(in_path.parent/in_path.stem)+".bin", 'wb') as out_f:
    out_f.write(pb)

print("Done!")