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

# Import common variables.
cd "$(dirname "${BASH_SOURCE[0]}")" || exit
source "${INSTALL_CI_PATH}"/openmme/.ci/install/install_config.sh

export LOG_DIR=${BASE_LOG_DIR}


# Log file names.

export MME_MAKE_STDOUT_LOG="${LOG_DIR}/cicd_openmme${ACTION_MAKE}${STDOUT_EXT}"
export MME_MAKE_STDERR_LOG="${LOG_DIR}/cicd_openmme${ACTION_MAKE}${STDERR_EXT}"

export MME_INSTALL_STDOUT_LOG="${LOG_DIR}/cicd_openmme${ACTION_INST}${STDOUT_EXT}"
export MME_INSTALL_STDERR_LOG="${LOG_DIR}/cicd_openmme${ACTION_INST}${STDERR_EXT}"
