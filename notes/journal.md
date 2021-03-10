# Journal

Notes on things, problems, and found solutions for record.

## Creating CDs

Relates to the playwav2-cd sample.

Based on the following [guide](http://ps2.x-pec.com/bootable_ps2_disc.html), learnt how to convert a given elf file and files into a bootable CD.
Originally, the incentive was due to not being able to get files loaded from a networked host (host:) on PCSX2, until discovering shortly afterwards that PCSX2 does support it.

## Vector Command-Line

Found how to install and run the Sony-issued VCL; The tool is downloaded from the [ps2linux](https://ps2linux.no-ip.info/playstation2-linux.com) archives and installed through the `Dockerfile` and invokable through the `vcl` command.
Installation required installing the 32-bit version of libstdc++5.

## Building gsKit with file-loading libraries

When trying out the \'alpha\' example from gsKit, I wasn't able to get the lirary to implement the image-loading routines (namely `gskit_texture_tiff()`).
Turns out, after installing gsKit through ps2dev, I needed to compile and install the ps2sdk-ports (including zlib, libpng, libtiff, and libjpeg).
Once compiled, I recompile gsKit using the libraries.
