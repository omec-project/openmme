#
# Copyright 2019-present Open Networking Foundation
# Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
# Copyright (c) 2017 Intel Corporation
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

PROJECT_NAME		 := openmme
VERSION                  ?= $(shell cat ./VERSION)

TOPTARGETS 		 := all clean install
SUBDIRS 		 := src/common src/s6a src/s1ap src/s11 src/mme-app/
#$(wildcard src/mme-app/.)

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

## Docker related
DOCKER_REGISTRY          ?=
DOCKER_REPOSITORY        ?=
DOCKER_BUILD_ARGS        ?=
DOCKER_TAG               ?= ${VERSION}
DOCKER_IMAGENAME         := ${DOCKER_REGISTRY}${DOCKER_REPOSITORY}${PROJECT_NAME}:${DOCKER_TAG}

## Docker labels. Only set ref and commit date if committed
DOCKER_LABEL_VCS_URL     ?= $(shell git remote get-url $(shell git remote))
DOCKER_LABEL_VCS_REF     ?= $(shell git diff-index --quiet HEAD -- && git rev-parse HEAD || echo "unknown")
DOCKER_LABEL_COMMIT_DATE ?= $(shell git diff-index --quiet HEAD -- && git show -s --format=%cd --date=iso-strict HEAD || echo "unknown" )
DOCKER_LABEL_BUILD_DATE  ?= $(shell date -u "+%Y-%m-%dT%H:%M:%SZ")

# https://docs.docker.com/engine/reference/commandline/build/#specifying-target-build-stage---target
docker-build:
	docker build $(DOCKER_BUILD_ARGS) \
		-t ${DOCKER_IMAGENAME} \
		--build-arg org_label_schema_version="${VERSION}" \
		--build-arg org_label_schema_vcs_url="${DOCKER_LABEL_VCS_URL}" \
		--build-arg org_label_schema_vcs_ref="${DOCKER_LABEL_VCS_REF}" \
		--build-arg org_label_schema_build_date="${DOCKER_LABEL_BUILD_DATE}" \
		--build-arg org_opencord_vcs_commit_date="${DOCKER_LABEL_COMMIT_DATE}" \
		.

docker-push:
	docker push ${DOCKER_IMAGENAME}

.PHONY: $(TOPTARGETS) $(SUBDIRS) docker-build docker-push
