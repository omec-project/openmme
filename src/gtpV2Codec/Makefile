# Copyright (c) 2019, Infosys Ltd.
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




include ../../Makefile.common

gtpV2CodecOBJDIR := $(OBJDIR)/gtpV2Codec

gtpV2CodecLIB := $(LIBDIR)/libgtpV2Codec.so

gtpV2CodecOBJS := $(addprefix $(gtpV2CodecOBJDIR)/, \
	ieClasses/imsiIe.o \
	ieClasses/gtpV2IeFactory.o \
	ieClasses/dataTypeCodecUtils.o \
	ieClasses/manual/gtpV2Ie.o \
	ieClasses/causeIe.o \
	ieClasses/msisdnIe.o \
	ieClasses/meiIe.o \
	ieClasses/uliIe.o \
	ieClasses/servingNetworkIe.o \
	ieClasses/ratTypeIe.o \
	ieClasses/indicationIe.o \
	ieClasses/fTeidIe.o \
	ieClasses/apnIe.o \
	ieClasses/selectionModeIe.o \
	ieClasses/pdnTypeIe.o \
	ieClasses/paaIe.o \
	ieClasses/apnRestrictionIe.o \
	ieClasses/ambrMmbrIe.o \
	ieClasses/ambrIe.o \
	ieClasses/ebiIe.o \
	ieClasses/pcoIe.o \
	ieClasses/traceInformationIe.o \
	ieClasses/recoveryIe.o \
	ieClasses/ueTimeZoneIe.o \
	ieClasses/uciIe.o \
	ieClasses/chargingCharacteristicsIe.o \
	ieClasses/localDistinguishedNameIe.o \
	ieClasses/signallingPriorityIndicationIe.o \
	ieClasses/additionalProtocolConfigurationOptionsIe.o \
	ieClasses/fqCsidIe.o \
	ieClasses/bearerTftIe.o \
	ieClasses/bearerQosIe.o \
	ieClasses/changeReportingActionIe.o \
	ieClasses/csgInformationReportingActionIe.o \
	ieClasses/fqdnIe.o \
	ieClasses/epcTimerIe.o \
	ieClasses/chargingIdIe.o \
	ieClasses/bearerFlagsIe.o \
	ieClasses/ipAddressIe.o \
	ieClasses/delayValueIe.o \
	ieClasses/portNumberIe.o \
	ieClasses/cnOperatorSelectionEntityIe.o \
	ieClasses/servingPlmnRateControlIe.o \
	ieClasses/counterIe.o \
	ieClasses/twanIdentifierIe.o \
	ieClasses/twanIdentifierTimestampIe.o \
	ieClasses/secondaryRatUsageDataReportIe.o \
	ieClasses/ranNasCauseIe.o \
	ieClasses/epcoIe.o \
	ieClasses/maximumPacketLossRateIe.o \
	ieClasses/fContainerIe.o \
	ieClasses/nodeIdentifierIe.o \
	ieClasses/upFunctionSelectionIndicationFlagsIe.o \
	ieClasses/henbInformationReportingIe.o \
	ieClasses/ip4cpIe.o \
	ieClasses/presenceReportingAreaActionIe.o \
	ieClasses/nodeTypeIe.o \
	ieClasses/ptiIe.o \
	ieClasses/twmiIe.o \
	ieClasses/millisecondTimeStampIe.o \
	ieClasses/integerNumberIe.o \
	ieClasses/mappedUeUsageTypeIe.o \
	ieClasses/uliTimestampIe.o \
	ieClasses/metricIe.o \
	ieClasses/remoteUserIdIe.o \
	ieClasses/remoteUeIpInformationIe.o \
	ieClasses/sequenceNumberIe.o \
	ieClasses/apnAndRelativeCapacityIe.o \
	ieClasses/arpIe.o \
	ieClasses/throttlingIe.o \
	ieClasses/pagingAndServiceInformationIe.o \
	msgClasses/createSessionRequestMsg.o \
	msgClasses/gtpV2MsgFactory.o \
	gtpV2Stack.o \
	msgClasses/manual/gtpV2Message.o \
	msgClasses/createSessionResponseMsg.o \
	msgClasses/modifyBearerRequestMsg.o \
	msgClasses/modifyBearerResponseMsg.o \
	msgClasses/deleteSessionRequestMsg.o \
	msgClasses/deleteSessionResponseMsg.o \
	msgClasses/releaseAccessBearersRequestMsg.o \
	msgClasses/releaseAccessBearersResponseMsg.o \
	msgClasses/createBearerRequestMsg.o \
	msgClasses/createBearerResponseMsg.o \
	msgClasses/deleteBearerRequestMsg.o \
	msgClasses/deleteBearerResponseMsg.o \
	msgClasses/downlinkDataNotificationMsg.o \
	msgClasses/downlinkDataNotificationAcknowledgeMsg.o \
	msgClasses/downlinkDataNotificationFailureIndicationMsg.o \
	ieClasses/bearerContextsToBeModifiedInModifyBearerRequest.o \
	ieClasses/bearerContextIe.o \
	ieClasses/manual/gtpV2GroupedIe.o \
	ieClasses/bearerContextsToBeRemovedInModifyBearerRequest.o \
	ieClasses/bearerContextsMarkedForRemovalInModifyBearerResponse.o \
	ieClasses/bearerContextsModifiedInModifyBearerResponse.o \
	ieClasses/bearerContextsToBeCreatedInCreateSessionRequest.o \
	ieClasses/bearerContextsToBeRemovedInCreateSessionRequest.o \
	ieClasses/bearerContextsCreatedInCreateSessionResponse.o \
	ieClasses/bearerContextsMarkedForRemovalInCreateSessionResponse.o \
	ieClasses/sgwsOverloadControlInformationInCreateSessionRequest.o \
	ieClasses/overloadControlInformationIe.o \
	ieClasses/twanEpdgsOverloadControlInformationInCreateSessionRequest.o \
	ieClasses/mmeS4SgsnsOverloadControlInformationInCreateSessionRequest.o \
	ieClasses/remoteUeContextConnectedInCreateSessionRequest.o \
	ieClasses/remoteUeContextIe.o \
	ieClasses/pgwsOverloadControlInformationInCreateSessionResponse.o \
	ieClasses/sgwsOverloadControlInformationInCreateSessionResponse.o \
	ieClasses/pgwsNodeLevelLoadControlInformationInCreateSessionResponse.o \
	ieClasses/loadControlInformationIe.o \
	ieClasses/pgwsApnLevelLoadControlInformationInCreateSessionResponse.o \
	ieClasses/sgwsNodeLevelLoadControlInformationInCreateSessionResponse.o \
	ieClasses/mmeS4SgsnsOverloadControlInformationInModifyBearerRequest.o \
	ieClasses/sgwsOverloadControlInformationInModifyBearerRequest.o \
	ieClasses/epdgsOverloadControlInformationInModifyBearerRequest.o \
	ieClasses/sgwsOverloadControlInformationInModifyBearerResponse.o \
	ieClasses/pgwsOverloadControlInformationInModifyBearerResponse.o \
	ieClasses/sgwsNodeLevelLoadControlInformationInModifyBearerResponse.o \
	ieClasses/pgwsApnLevelLoadControlInformationInModifyBearerResponse.o \
	ieClasses/pgwsNodeLevelLoadControlInformationInModifyBearerResponse.o \
	ieClasses/mmeS4SgsnsOverloadControlInformationInDeleteSessionRequest.o \
	ieClasses/sgwsOverloadControlInformationInDeleteSessionRequest.o \
	ieClasses/twanEpdgsOverloadControlInformationInDeleteSessionRequest.o \
	ieClasses/sgwsOverloadControlInformationInDeleteSessionResponse.o \
	ieClasses/pgwsOverloadControlInformationInDeleteSessionResponse.o \
	ieClasses/pgwsNodeLevelLoadControlInformationInDeleteSessionResponse.o \
	ieClasses/pgwsApnLevelLoadControlInformationInDeleteSessionResponse.o \
	ieClasses/sgwsNodeLevelLoadControlInformationInDeleteSessionResponse.o \
	ieClasses/sgwsOverloadControlInformationInReleaseAccessBearersResponse.o \
	ieClasses/sgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse.o \
	ieClasses/bearerContextsInCreateBearerRequest.o \
	ieClasses/pgwsNodeLevelLoadControlInformationInCreateBearerRequest.o \
	ieClasses/pgwsApnLevelLoadControlInformationInCreateBearerRequest.o \
	ieClasses/sgwsNodeLevelLoadControlInformationInCreateBearerRequest.o \
	ieClasses/pgwsOverloadControlInformationInCreateBearerRequest.o \
	ieClasses/sgwsOverloadControlInformationInCreateBearerRequest.o \
	ieClasses/bearerContextsInCreateBearerResponse.o \
	ieClasses/mmeS4SgsnsOverloadControlInformationInCreateBearerResponse.o \
	ieClasses/sgwsOverloadControlInformationInCreateBearerResponse.o \
	ieClasses/twanEpdgsOverloadControlInformationInCreateBearerResponse.o \
	ieClasses/failedBearerContextsInDeleteBearerRequest.o \
	ieClasses/pgwsNodeLevelLoadControlInformationInDeleteBearerRequest.o \
	ieClasses/pgwsApnLevelLoadControlInformationInDeleteBearerRequest.o \
	ieClasses/sgwsNodeLevelLoadControlInformationInDeleteBearerRequest.o \
	ieClasses/pgwsOverloadControlInformationInDeleteBearerRequest.o \
	ieClasses/sgwsOverloadControlInformationInDeleteBearerRequest.o \
	ieClasses/bearerContextsInDeleteBearerResponse.o \
	ieClasses/mmeS4SgsnsOverloadControlInformationInDeleteBearerResponse.o \
	ieClasses/sgwsOverloadControlInformationInDeleteBearerResponse.o \
	ieClasses/twanEpdgsOverloadControlInformationInDeleteBearerResponse.o \
	ieClasses/sgwsNodeLevelLoadControlInformationInDownlinkDataNotification.o \
	ieClasses/sgwsOverloadControlInformationInDownlinkDataNotification.o \
	ieClasses/manual/dataTypeCodecUtils_manual.o \
	gtpV2StackWrappers.o )
all :  $(gtpV2CodecLIB)

.PHONY : all

$(gtpV2CodecLIB) : $(gtpV2CodecOBJS)
	mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) -shared -o $(gtpV2CodecLIB) $(gtpV2CodecOBJS)

$(gtpV2CodecOBJS) : $(OBJDIR)/gtpV2Codec/%.o : %.cpp
	echo "$@ from $< "
	mkdir -p $(gtpV2CodecOBJDIR)/ieClasses/manual
	mkdir -p $(gtpV2CodecOBJDIR)/msgClasses/manual
	$(CC) $(CFLAGS) $(INC_DIRS) -fPIC -c $< -o $@

install:
	mkdir -p $(TOPDIR)/target/lib
	cp -rf  $(gtpV2CodecLIB) $(TOPDIR)/target/lib

clean :
	rm -rf $(gtpV2CodecLIB)
	rm -rf $(gtpV2CodecOBJDIR)

.PHONY : clean
