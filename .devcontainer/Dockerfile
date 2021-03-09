# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.158.0/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version: debian-10, debian-9, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends gcc make patch git wget nano libjpeg-dev libpng-dev libtiff5-dev libsdl2-image-dev texinfo build-essential gettext bison flex cmake libgmp-dev libmpfr-dev libmpc-dev

# Set initial variables.
ENV PS2DEV=/usr/local/ps2dev
ENV PS2SDK=$PS2DEV/ps2sdk
ENV GSKIT=$PS2DEV/gsKit
ENV PATH=$PATH:$PS2DEV/bin:$PS2DEV/ee/bin:$PS2DEV/iop/bin:$PS2DEV/dvp/bin:$PS2SDK/bin

# Clear out any residual resources that may conflict with the installation.
RUN rm -rf $PS2DEV
RUN rm -rf ps2dev

# Build ps2dev
RUN git clone https://github.com/ps2dev/ps2dev
RUN ps2dev/build-all.sh

# Prepare the ps2sdk ported libraries collection and compile some gskit dependencies.
RUN rm -rf $PS2DEV/ports && git clone https://github.com/ps2dev/ps2sdk-ports $PS2DEV/ports
ENV PORTS=$PS2DEV/ports
WORKDIR $PORTS
# Clone and build the libraries.
RUN make
RUN cd libjpeg && make
RUN cd libtiff && make
RUN rsync -a build/ .
RUN rm -rf build

# Clone the gsKit source code and recompile it with the new libraries (zlib, libpng, libjpeg, and libtiff).
WORKDIR $PS2DEV
ENV GSKITSRC=$PS2DEV/gsKitSrc
RUN rm -rf $GSKIT $GSKITSRC
RUN git clone https://github.com/ps2dev/gskit $GSKITSRC
RUN cd $GSKITSRC && ./setup.sh
RUN rsync -a $GSKITSRC/ $GSKIT
RUN rm -rf $GSKITSRC
ENV GSKITSRC=$GSKIT

# Clean up the ps2dev repo.
RUN rm -rf ps2dev

# Install Vector Command-Line (vcl) into the ps2sdk shared libraries directory.
WORKDIR $PS2DEV/share
ADD https://ps2linux.no-ip.info/playstation2-linux.com/download/vcl/vcl.1.4.beta7.x86.tar ./
RUN tar -xvf ./vcl.1.4.beta7.x86.tar
RUN mkdir vcl.1.4.beta7.x86/bin
RUN mv vcl.1.4.beta7.x86/vcl_14beta7_x86 vcl.1.4.beta7.x86/bin/vcl
RUN rm ./vcl.1.4.beta7.x86.tar

# Install 32-bit dependency of vcl.
RUN sudo dpkg --add-architecture i386
RUN sudo apt-get update
RUN sudo apt-get -y install libstdc++5:i386

# Add VCL to PATH.
ENV VCL_BIN=$PS2DEV/share/vcl.1.4.beta7.x86/bin
ENV PATH=$PATH:$VCL_BIN
