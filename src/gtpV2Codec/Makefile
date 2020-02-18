include ../../Makefile.common

gtpV2CodecOBJDIR := $(OBJDIR)/gtpV2Codec/

gtpV2CodecLIB := $(LIBDIR)/libgtpV2Codec.so

gtpV2CodecOBJS := $(addprefix $(gtpV2CodecOBJDIR), \
	ieClasses/imsiIe.o \
		ieClasses/gtpV2IeFactory.o \
		ieClasses/dataTypeCodecUtils.o \
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
		ieClasses/maximumPacketLossRateIe.o \
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
		msgClasses/createSessionResponseMsg.o \
		msgClasses/modifyBearerRequestMsg.o \
		msgClasses/modifyBearerResponseMsg.o \
		msgClasses/deleteSessionRequestMsg.o \
		msgClasses/deleteSessionResponseMsg.o \
		msgClasses/downlinkDataNotificationMsg.o \
		msgClasses/downlinkDataNotificationAcknowledgeMsg.o \
		msgClasses/downlinkDataNotificationFailureIndicationMsg.o \
		msgClasses/releaseAccessBearersRequestMsg.o \
		msgClasses/releaseAccessBearersResponseMsg.o \
		ieClasses/bearerContextsToBeModifiedInModifyBearerRequest.o \
		ieClasses/bearerContextIe.o \
		ieClasses/bearerContextsInCreateBearerRequest.o \
		ieClasses/bearerContextsInCreateBearerResponse.o \
		ieClasses/failedBearerContextsInDeleteBearerRequest.o \
		ieClasses/bearerContextsInDeleteBearerResponse.o \
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
		ieClasses/sgwsNodeLevelLoadControlInformationInDeleteBearerRequest.o \
		ieClasses/pgwsOverloadControlInformationInCreateBearerRequest.o \
		ieClasses/pgwsOverloadControlInformationInCreateSessionResponse.o \
		ieClasses/sgwsOverloadControlInformationInCreateSessionResponse.o \
		ieClasses/pgwsNodeLevelLoadControlInformationInCreateSessionResponse.o \
		ieClasses/loadControlInformationIe.o \
		ieClasses/pgwsNodeLevelLoadControlInformationInCreateBearerRequest.o \
		ieClasses/sgwsNodeLevelLoadControlInformationInCreateBearerRequest.o \
		ieClasses/pgwsApnLevelLoadControlInformationInCreateBearerRequest.o \
		ieClasses/mmeS4SgsnsOverloadControlInformationInCreateBearerResponse.o \
		ieClasses/sgwsOverloadControlInformationInCreateBearerResponse.o \
		ieClasses/sgwsNodeLevelLoadControlInformationInDownlinkDataNotification.o \
		ieClasses/sgwsOverloadControlInformationInDownlinkDataNotification.o \
		ieClasses/twanEpdgsOverloadControlInformationInCreateBearerResponse.o \
		ieClasses/pgwsNodeLevelLoadControlInformationInDeleteBearerRequest.o \
		ieClasses/pgwsApnLevelLoadControlInformationInDeleteBearerRequest.o \
		ieClasses/sgwsApnLevelLoadControlInformationInDeleteBearerRequest.o \
		ieClasses/pgwsOverloadControlInformationInDeleteBearerRequest.o \
		ieClasses/sgwsOverloadControlInformationInDeleteBearerRequest.o \
		ieClasses/mmeS4SgsnsOverloadControlInformationInDeleteBearerResponse.o \
		ieClasses/sgwsOverloadControlInformationInDeleteBearerResponse.o \
		ieClasses/twanEpdgsOverloadControlInformationInDeleteBearerResponse.o \
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
		ieClasses/sgwsOverloadControlInformationInCreateBearerRequest.o \
		ieClasses/manual/dataTypeCodecUtils_manual.o \
		ieClasses/manual/gtpV2GroupedIe.o \
		ieClasses/manual/gtpV2Ie.o \
		msgClasses/manual/gtpV2Message.o \
		gtpV2Stack.o \
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
