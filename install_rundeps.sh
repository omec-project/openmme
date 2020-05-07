#!/bin/bash
#
# Copyright 2019-present Open Networking Foundation
#
# SPDX-License-Identifier: Apache-2.0
#

SUDO=''
[[ $EUID -ne 0 ]] && SUDO=sudo

install_run_pkg_deps() {
	$SUDO apt-get update && $SUDO apt-get install -y \
		openssl \
		libidn11 \
		libgnutls30 \
		netbase \
		libsctp1
}

install_run_utils() {
        $SUDO apt-get update && $SUDO apt-get install -y \
                jq \
                dnsutils \
		iproute2 \
		iputils-ping \
		tcpdump
}

cleanup_image() {
	$SUDO rm -rf /var/lib/apt/lists/*
}

install_run_deps() {
        install_run_pkg_deps
}

(return 2>/dev/null) && echo "Sourced" && return

set -o errexit
set -o pipefail
set -o nounset

install_run_deps
echo "Dependency install completed"
