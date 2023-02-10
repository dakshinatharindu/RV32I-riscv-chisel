verilator -Wall --cc ../verilog/Core.v --exe Core.cpp &>-
make -C obj_dir -f VCore.mk &>-
obj_dir/VCore