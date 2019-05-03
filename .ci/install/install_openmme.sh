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

export INSTALL_CI_PATH=$1

cd "$(dirname "${BASH_SOURCE[0]}")"
# shellcheck disable=SC1091
source "${INSTALL_CI_PATH}"/openmme/.ci/install/install_openmme_config.sh
# shellcheck disable=SC1091
source "${INSTALL_CI_PATH}"/openmme/.ci/common/utils.sh


check_process()
{
    # Kill any running process
    # shellcheck disable=SC2009
    ps -e | grep -P "(mme|s11|s1ap|s6a)-app" | grep -v grep || echo "no running process found"

    if pgrep -f [m]me-app; then pkill -f [m]me-app; fi
    sleep 1
    if pgrep -f [s]1ap-app; then pkill -f [s]1ap-app; fi
    sleep 1
    if pgrep -f [s]11-app; then pkill -f [s]11-app; fi
    sleep 1
    if pgrep -f [s]6a-app; then pkill -f [s]6a-app; fi

    # shellcheck disable=SC2009
    ps -e | grep -P "(mme|s11|s1ap|s6a)-app" | grep -v grep && exit 1 || echo "no running process found"
}


# Main

# Clean log dir or create it, if needed
log_step "Clean log directory ${LOG_DIR} ..."
clean_all_logs "${LOG_DIR}"

log_step "Check/kill processes, if any ..."
check_process


log_step "Copy config files ..."
cp -f "${INSTALL_CI_PATH}"/openmme/.ci/config/mme.json    "${INSTALL_CI_PATH}"/openmme/src/mme-app/conf/mme.json
cp -f "${INSTALL_CI_PATH}"/openmme/.ci/config/s1ap.json   "${INSTALL_CI_PATH}"/openmme/src/s1ap/conf/s1ap.json
cp -f "${INSTALL_CI_PATH}"/openmme/.ci/config/s11.json    "${INSTALL_CI_PATH}"/openmme/src/s11/conf/s11.json
cp -f "${INSTALL_CI_PATH}"/openmme/.ci/config/s6a.json    "${INSTALL_CI_PATH}"/openmme/src/s6a/conf/s6a.json
cp -f "${INSTALL_CI_PATH}"/openmme/.ci/config/s6a_fd.conf "${INSTALL_CI_PATH}"/openmme/src/s6a/conf/s6a_fd.conf

log_step "Make openmme ..."
cd "${INSTALL_CI_PATH}"/openmme
make clean && make 1>"${MME_MAKE_STDOUT_LOG}" 2>"${MME_MAKE_STDERR_LOG}"

log_step "Install openmme ..."
make install 1>"${MME_INSTALL_STDOUT_LOG}" 2>"${MME_INSTALL_STDERR_LOG}"

log_step "Make Certificates ..."
cd "${INSTALL_CI_PATH}"/openmme/target/conf && ./make_certs.sh mme localdomain
