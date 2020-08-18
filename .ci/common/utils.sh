#!/bin/bash

#  Copyright 2019-present Open Networking Foundation
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#  http:# www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

set -o nounset
set -o errexit

clean_all_logs()
{
    # Clean all logs
    local LOG_DIR=$1

    if [ ! -d "${LOG_DIR}" ]; then mkdir -p "${LOG_DIR}"; fi
    rm -fr "${LOG_DIR:?}"/*
}


log_step()
{
    local ARG=$1
    local LENGTH=${#ARG}
    printf "\n%s\n" "${ARG}"
    # shellcheck disable=SC2046
    printf "%.s-" $(seq 1 "${LENGTH}")
    printf "\n"
}
