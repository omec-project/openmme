#
# Copyright 2019-present Open Networking Foundation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
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
