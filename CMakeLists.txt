cmake_minimum_required(VERSION 3.18)

project(uefi C)

# Define the source files
set(SRC tests/main.c)

# Include directories
include_directories(include efi)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_C_LINKER "/usr/bin/lld-link")
# Create the executable
add_executable(BOOTX64.EFI ${SRC})

# Set the necessary compilation and linking flags for the target
target_compile_options(BOOTX64.EFI PRIVATE
    -target x86_64-unknown-windows
    -ffreestanding
    -fno-stack-protector
    -fshort-wchar
    -mno-red-zone
    -mno-mmx
    -mno-sse
)

target_link_options(BOOTX64.EFI PRIVATE
    -target x86_64-unknown-windows
    -nostdlib
    -Wl,-entry:efi_main
    -Wl,-subsystem:efi_application
    -fuse-ld=lld
)
