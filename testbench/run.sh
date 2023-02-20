rm -r obj_dir
verilator -Wall --trace --cc ../verilog/Processor.v --exe Processor.cpp &>-
make -C obj_dir -f VProcessor.mk &>-
obj_dir/VProcessor
gtkwave waveform.vcd