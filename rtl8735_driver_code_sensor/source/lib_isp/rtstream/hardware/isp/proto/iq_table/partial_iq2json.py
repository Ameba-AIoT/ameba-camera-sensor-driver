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

with open(in_path, "rb") as f:
    buf = f.read()

iq = isp_iq_table_t()

iq.ParseFromString(buf)
data = json_format.MessageToJson(iq,
                                    including_default_value_fields=True,
                                    preserving_proto_field_name=True)
data = prettyjson(json.loads(data))
with open(str(in_path.parent/in_path.stem)+".json", 'w') as out_f:
    out_f.write(data)

print("Done!")