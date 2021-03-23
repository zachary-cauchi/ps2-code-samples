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

## Tried to rewrite the vu1 sample with gsKit, failing badly

Tried to rewrite the vu1 sample using gsKit instead of the ps2sdk draw library. Reason was to have the readied image-loading routines.
Instead, will try to reverse-engineer the image-loading routine using the ps2sdk and ported libraries.

## Getting fonts working.

Managed to get a sample demo working taken from the ps2sdk repo, using the bios built-in font `KROM`. Currently, only managed to get ascii encoding working and using only FontX, with FontStudio being disabled. Next step would be to find a way of using custom fonts, either in FontX or FontStudio format.

## Got multi-path rendering working

After a lot of troubleshooting and strange bugs, I finally managed to merge the vu1 and graph samples together into one, rendering multiple coloured rectangles atop an array of cubes with the rectangles acting as UI elements. The next step from here will be to convert the sample to C++ and following quickly after with controller input.
