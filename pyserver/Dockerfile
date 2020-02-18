#
# Copyright 2020-present Open Networking Foundation
#
# SPDX-License-Identifier: Apache-2.0
#

FROM ubuntu:18.04

RUN apt update -y
RUN apt install python3 python3-dev python3-pip -y
RUN pip3 install flask
RUN pip3 install prometheus_client

WORKDIR /openmme
COPY ./monitor_client.py ./
COPY ./conf ./conf
