#!/bin/bash
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

SUDO=''
[[ $EUID -ne 0 ]] && SUDO=sudo

install_build_pkg_deps() {
	$SUDO apt-get update && $SUDO apt-get install -y \
		git \
		build-essential \
		cmake \
		libuv-dev \
		libgcrypt-dev \
		libidn11-dev \
		bison \
		flex \
		libgnutls-dev \
		libsctp-dev \
		libssl-dev
}

install_freediameter() {
        $SUDO rm -rf /tmp/freediameter
	git clone -q https://github.com/omec-project/freediameter.git /tmp/freediameter
	pushd /tmp/freediameter
	mkdir -p build && cd build
	cmake -DDISABLE_SCTP:BOOL=ON .. && make -j && $SUDO make install
}

install_build_deps() {
	install_build_pkg_deps
	install_freediameter
}

(return 2>/dev/null) && echo "Sourced" && return

set -o errexit
set -o pipefail
set -o nounset

install_build_deps
echo "Dependency install completed"
