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

ARG org_label_schema_version=unknown
ARG org_label_schema_vcs_url=unknown
ARG org_label_schema_vcs_ref=unknown
ARG org_label_schema_build_date=unknown
ARG org_opencord_vcs_commit_date=unknown

LABEL org.label-schema.schema-version=1.0 \
      org.label-schema.name=openmme \
      org.label-schema.version=$org_label_schema_version \
      org.label-schema.vcs-url=$org_label_schema_vcs_url \
      org.label-schema.vcs-ref=$org_label_schema_vcs_ref \
      org.label-schema.build-date=$org_label_schema_build_date \
      org.opencord.vcs-commit-date=$org_opencord_vcs_commit_date
