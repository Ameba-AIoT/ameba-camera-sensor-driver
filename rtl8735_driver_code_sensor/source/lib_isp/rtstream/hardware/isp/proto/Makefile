
PBS = isp_algo_param.pb isp_iq_table.pb isp_statis.pb
IQ_TABLE_JSONS := $(sort $(wildcard iq_table/default/*.json))
PROTOC = ./protoc.exe
# Linear Mode
IQ_TABLE_GP1 := iq_table/default/iq_ameba_iq0.json iq_table/default/iq_ameba_iq1.json iq_table/default/iq_ameba_iq_other_0.json
# HDR Mode
IQ_TABLE_GP2 := iq_table/default/iq_ameba_iq2.json iq_table/default/iq_ameba_iq3.json iq_table/default/iq_ameba_iq_other_1.json
#4 table
# Linear Mode
IQ_TABLE_GP1_woOther := iq_table/default/iq_ameba_iq0.json iq_table/default/iq_ameba_iq1.json
# HDR Mode
IQ_TABLE_GP2_woOther := iq_table/default/iq_ameba_iq2.json iq_table/default/iq_ameba_iq3.json


all: $(PBS) iq.bin

%.pb:%.proto
	$(PROTOC) -o$@ $<
	python3 ./nanopb/generator/nanopb_generator.py $@

iq_ext.bin:$(IQ_TABLE_GP1) $(IQ_TABLE_GP2)
	$(PROTOC) --python_out=./iq_table isp_iq_table.proto
	python3 iq_table/pack_iq_with_tag_offset.py $@ $^

iq.bin:$(IQ_TABLE_GP1_woOther) $(IQ_TABLE_GP2_woOther)
	$(PROTOC) --python_out=./iq_table isp_iq_table.proto
	python3 iq_table/pack_iq_with_tag_offset_wo_other.py $@ $^

iq_linear.bin:$(IQ_TABLE_GP1_woOther) 
	$(PROTOC) --python_out=./iq_table isp_iq_table.proto
	python3 iq_table/pack_iq_with_tag_offset_wo_other.py $@ $^



clean:
	-rm ./iq_table/isp_iq_table_pb2.py
	-rm -rf ./iq_table/__pycache__
	-rm *.pb.c *.pb.h *.pb
	-rm *.bin
	-rm -fr .libs/
