export PATH=$PATH:/usr/local/i386elfgcc/bin

mkdir Binaries

nasm "boot/boot.asm" -f bin -o "Binaries/boot.bin"
nasm "boot/entry.asm" -f elf -o "Binaries/kernel_entry.o"
i386-elf-gcc -ffreestanding -m32 -g -c "mandelbrot.c" -o "Binaries/kernel.o"
nasm "boot/zero.asm" -f bin -o "Binaries/zeroes.bin"

i386-elf-ld -o "Binaries/full_kernel.bin" -Ttext 0x1000 "Binaries/kernel_entry.o" "Binaries/kernel.o" --oformat binary

cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/zeroes.bin"  > "Binaries/OS.bin"

qemu-system-i386 "Binaries/OS.bin"