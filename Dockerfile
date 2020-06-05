#
# Copyright 2019-present Open Networking Foundation
#
# SPDX-License-Identifier: Apache-2.0
#

ARG BASE_OS=ubuntu:16.04

FROM $BASE_OS AS builder
WORKDIR /openmme
COPY install_builddeps.sh .
RUN ./install_builddeps.sh

COPY . ./
RUN make && make install

FROM $BASE_OS AS runtime
COPY install_rundeps.sh .
RUN bash -c "source ./install_rundeps.sh && install_run_deps && install_run_utils && cleanup_image"
COPY --from=builder /usr/local/lib /usr/local/lib

WORKDIR /openmme/target
COPY --from=builder /openmme/target .
