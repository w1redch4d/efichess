## References 

[UEFI 2.6](https://uefi.org/sites/default/files/resources/UEFI%20Spec%202_6.pdf)

## Building

### Pre-requisits
Cmake, llvm-toolchain, edk2-ovmf, qemu
[Get OVMF.fd](https://github.com/tianocore/tianocore.github.io/wiki/How-to-build-OVMF)

### Commands

blindly follow these, and dig down the rabbit hole using google to know what these commands does

```
mkdir -p build/esp/EFI/BOOT
cd build
cmake ..
cp BOOTx64.EFI ./esp/EFI/BOOT
cp /path/to/OVMF.fd .
qemu-system-x86_64 -drive if=pflash,format=raw,file=OVMF.fd -M accel=kvm:tcg -net none -serial stdio -drive format=raw,file=fat:rw:esp
```