mkdir build  
cd build  
cmake .. -DPICO_BOARD=pico_w  
make -j4  

cyw43_hang.uf2 hangs. It has 2 interrupts added and then cyw43_arch_init is called
cyw43_no_hang.uf2 does not hang. It has only the 2 interrupts and cyw43_arch_init is not called
