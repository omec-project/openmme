#
# Copyright 2019-present Open Networking Foundation
# Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
# Copyright (c) 2017 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0
#

VERSION                  ?= $(shell cat ./VERSION)

TOPTARGETS 		 := all clean install
SUBDIRS 		 := src/common src/cmn src/stateMachineFwk src/s1ap/contextManager src/gtpV2Codec src/s6a src/s1ap src/s11 src/mme-app/
#$(wildcard src/mme-app/.)

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

## Docker related
DOCKER_REGISTRY          ?=
DOCKER_REPOSITORY        ?=
DOCKER_BUILD_ARGS        ?=
DOCKER_TAG               ?= ${VERSION}
DOCKER_TARGET            := openmme
DOCKER_IMAGENAME         := ${DOCKER_REGISTRY}${DOCKER_REPOSITORY}${DOCKER_TARGET}:${DOCKER_TAG}

## Docker labels. Only set ref and commit date if committed
DOCKER_LABEL_VCS_URL     ?= $(shell git remote get-url $(shell git remote))
DOCKER_LABEL_VCS_REF     ?= $(shell git diff-index --quiet HEAD -- && git rev-parse HEAD || echo "unknown")
DOCKER_LABEL_COMMIT_DATE ?= $(shell git diff-index --quiet HEAD -- && git show -s --format=%cd --date=iso-strict HEAD || echo "unknown" )
DOCKER_LABEL_BUILD_DATE  ?= $(shell date -u "+%Y-%m-%dT%H:%M:%SZ")

# https://docs.docker.com/engine/reference/commandline/build/#specifying-target-build-stage---target
docker-build:
	docker build $(DOCKER_BUILD_ARGS) \
		-t ${DOCKER_IMAGENAME} \
		--label "org.label-schema.schema-version=1.0" \
		--label "org.label-schema.name=${DOCKER_TARGET}" \
		--label "org.label-schema.version=${VERSION}" \
		--label "org.label-schema.vcs-url=${DOCKER_LABEL_VCS_URL}" \
		--label "org.label-schema.vcs-ref=${DOCKER_LABEL_VCS_REF}" \
		--label "org.label-schema.build-date=${DOCKER_LABEL_BUILD_DATE}" \
		--label "org.opencord.vcs-commit-date=${DOCKER_LABEL_COMMIT_DATE}" \
		.

docker-push:
	docker push ${DOCKER_IMAGENAME}

.PHONY: $(TOPTARGETS) $(SUBDIRS) docker-build docker-push
