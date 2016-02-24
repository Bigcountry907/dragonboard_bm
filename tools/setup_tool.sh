#!/bin/sh

a64_fname=gcc-linaro-5.2-2015.11-1-x86_64_aarch64-elf

url="http://releases.linaro.org/components/toolchain/binaries/latest-5.2/aarch64-elf/"

echo "Running: wget $url/${a64_fname}.tar.xz"
wget "$url/${a64_fname}.tar.xz"

tar xpvf "${a64_fname}.tar.xz"

ln -sf $a64_fname latest_aarch64

