# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.158.0/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version: debian-10, debian-9, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends gcc make patch git wget nano libjpeg-dev libpng-dev libtiff5-dev libsdl2-image-dev texinfo build-essential gettext bison flex cmake libgmp-dev libmpfr-dev libmpc-dev

ENV PS2DEV=/usr/local/ps2dev
ENV PS2SDK=$PS2DEV/ps2sdk
ENV GSKIT=$PS2DEV/gsKit
ENV PATH=$PATH:$PS2DEV/bin:$PS2DEV/ee/bin:$PS2DEV/iop/bin:$PS2DEV/dvp/bin:$PS2SDK/bin

RUN rm -rf $PS2DEV
RUN git clone https://github.com/ps2dev/ps2dev
RUN ps2dev/build-all.sh
