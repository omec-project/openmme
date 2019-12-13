/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#include "modifyBearerRequestMsg.h"
#include "../ieClasses/manual/gtpV2Ie.h"
#include "../ieClasses/gtpV2IeFactory.h"
#include "../ieClasses/meiIe.h"
#include "../ieClasses/uliIe.h"
#include "../ieClasses/servingNetworkIe.h"
#include "../ieClasses/ratTypeIe.h"
#include "../ieClasses/indicationIe.h"
#include "../ieClasses/fTeidIe.h"
#include "../ieClasses/ambrIe.h"
#include "../ieClasses/delayValueIe.h"
#include "../ieClasses/bearerContextIe.h"
#include "../ieClasses/bearerContextsToBeModifiedInModifyBearerRequest.h"
#include "../ieClasses/bearerContextIe.h"
#include "../ieClasses/bearerContextsToBeRemovedInModifyBearerRequest.h"
#include "../ieClasses/recoveryIe.h"
#include "../ieClasses/ueTimeZoneIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/fqCsidIe.h"
#include "../ieClasses/uciIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/portNumberIe.h"
#include "../ieClasses/localDistinguishedNameIe.h"
#include "../ieClasses/localDistinguishedNameIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/portNumberIe.h"
#include "../ieClasses/ipAddressIe.h"
#include "../ieClasses/cnOperatorSelectionEntityIe.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/mmeS4SgsnsOverloadControlInformationInModifyBearerRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/sgwsOverloadControlInformationInModifyBearerRequest.h"
#include "../ieClasses/overloadControlInformationIe.h"
#include "../ieClasses/epdgsOverloadControlInformationInModifyBearerRequest.h"
#include "../ieClasses/servingPlmnRateControlIe.h"
#include "../ieClasses/counterIe.h"
#include "../ieClasses/imsiIe.h"
#include "../ieClasses/uliIe.h"
#include "../ieClasses/twanIdentifierIe.h"
#include "../ieClasses/twanIdentifierTimestampIe.h"
#include "../ieClasses/secondaryRatUsageDataReportIe.h"

ModifyBearerRequestMsg::ModifyBearerRequestMsg()
{
    msgType = ModifyBearerRequestMsgType;

}

ModifyBearerRequestMsg::~ModifyBearerRequestMsg()
{

}

bool ModifyBearerRequestMsg::encodeModifyBearerRequestMsg(MsgBuffer &buffer,
                        ModifyBearerRequestMsgData
							const &data)
{
    bool rc = false;
    GtpV2IeHeader header;
    Uint16 startIndex = 0;
    Uint16 endIndex = 0;
    Uint16 length = 0;

    if (data.meIdentityIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = MeiIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        MeiIe mei=
        dynamic_cast<
        MeiIe&>(GtpV2IeFactory::getInstance().getIeObject(MeiIeType));
        rc = mei.encodeMeiIe(buffer, data.meIdentity);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: meIdentity\n");
            return false;
        }
    }

    if (data.userLocationInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UliIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        rc = uli.encodeUliIe(buffer, data.userLocationInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: userLocationInformation\n");
            return false;
        }
    }

    if (data.servingNetworkIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ServingNetworkIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ServingNetworkIe servingNetwork=
        dynamic_cast<
        ServingNetworkIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingNetworkIeType));
        rc = servingNetwork.encodeServingNetworkIe(buffer, data.servingNetwork);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: servingNetwork\n");
            return false;
        }
    }

    if (data.ratTypeIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = RatTypeIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        RatTypeIe ratType=
        dynamic_cast<
        RatTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(RatTypeIeType));
        rc = ratType.encodeRatTypeIe(buffer, data.ratType);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: ratType\n");
            return false;
        }
    }

    if (data.indicationFlagsIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IndicationIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IndicationIe indication=
        dynamic_cast<
        IndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(IndicationIeType));
        rc = indication.encodeIndicationIe(buffer, data.indicationFlags);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: indicationFlags\n");
            return false;
        }
    }

    if (data.senderFTeidForControlPlaneIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FTeidIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        rc = fTeid.encodeFTeidIe(buffer, data.senderFTeidForControlPlane);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: senderFTeidForControlPlane\n");
            return false;
        }
    }

    if (data.aggregateMaximumBitRateIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = AmbrIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        AmbrIe ambr=
        dynamic_cast<
        AmbrIe&>(GtpV2IeFactory::getInstance().getIeObject(AmbrIeType));
        rc = ambr.encodeAmbrIe(buffer, data.aggregateMaximumBitRate);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: aggregateMaximumBitRate\n");
            return false;
        }
    }

    if (data.delayDownlinkPacketNotificationRequestIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = DelayValueIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        DelayValueIe delayValue=
        dynamic_cast<
        DelayValueIe&>(GtpV2IeFactory::getInstance().getIeObject(DelayValueIeType));
        rc = delayValue.encodeDelayValueIe(buffer, data.delayDownlinkPacketNotificationRequest);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: delayDownlinkPacketNotificationRequest\n");
            return false;
        }
    }

        // First validate if the applicatoin provided more than the expected cardinality
    if (data.bearerContextsToBeModifiedCount > 11)
    {
        errorStream.add((char *)"Number of entries of bearerContextsToBeModified exceeded\n");
        errorStream.add((char *)"Expected count: 11 Received count: ");
        errorStream.add((char *)"data.bearerContextsToBeModifiedCount");
        errorStream.endOfLine();
        return false;
    }
    for (Uint8 i = 0; i < data.bearerContextsToBeModifiedCount; i++)
    {
        // Encode the Ie Header
        header.ieType = BearerContextIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        BearerContextIe bearerContext=
        dynamic_cast<
        BearerContextIe&>(GtpV2IeFactory::getInstance().
        getIeObject(BearerContextIeType));
        BearerContextsToBeModifiedInModifyBearerRequest groupedIeInstance = dynamic_cast<BearerContextsToBeModifiedInModifyBearerRequest&>(bearerContext.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeBearerContextsToBeModifiedInModifyBearerRequest(buffer, data.bearerContextsToBeModified[i]);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;

        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);
    }

    if (!(rc))
    { 
        errorStream.add((char *)"Failed to encode IE: bearerContextsToBeModified\n");
        return false;
    }

        // First validate if the applicatoin provided more than the expected cardinality
    if (data.bearerContextsToBeRemovedCount > 11)
    {
        errorStream.add((char *)"Number of entries of bearerContextsToBeRemoved exceeded\n");
        errorStream.add((char *)"Expected count: 11 Received count: ");
        errorStream.add((char *)"data.bearerContextsToBeRemovedCount");
        errorStream.endOfLine();
        return false;
    }
    for (Uint8 i = 0; i < data.bearerContextsToBeRemovedCount; i++)
    {
        // Encode the Ie Header
        header.ieType = BearerContextIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        BearerContextIe bearerContext=
        dynamic_cast<
        BearerContextIe&>(GtpV2IeFactory::getInstance().
        getIeObject(BearerContextIeType));
        BearerContextsToBeRemovedInModifyBearerRequest groupedIeInstance = dynamic_cast<BearerContextsToBeRemovedInModifyBearerRequest&>(bearerContext.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeBearerContextsToBeRemovedInModifyBearerRequest(buffer, data.bearerContextsToBeRemoved[i]);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;

        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);
    }

    if (!(rc))
    { 
        errorStream.add((char *)"Failed to encode IE: bearerContextsToBeRemoved\n");
        return false;
    }

    if (data.recoveryIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = RecoveryIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        RecoveryIe recovery=
        dynamic_cast<
        RecoveryIe&>(GtpV2IeFactory::getInstance().getIeObject(RecoveryIeType));
        rc = recovery.encodeRecoveryIe(buffer, data.recovery);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: recovery\n");
            return false;
        }
    }

    if (data.ueTimeZoneIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UeTimeZoneIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UeTimeZoneIe ueTimeZone=
        dynamic_cast<
        UeTimeZoneIe&>(GtpV2IeFactory::getInstance().getIeObject(UeTimeZoneIeType));
        rc = ueTimeZone.encodeUeTimeZoneIe(buffer, data.ueTimeZone);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: ueTimeZone\n");
            return false;
        }
    }

    if (data.mmeFqCsidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FqCsidIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        rc = fqCsid.encodeFqCsidIe(buffer, data.mmeFqCsid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: mmeFqCsid\n");
            return false;
        }
    }

    if (data.sgwFqCsidIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = FqCsidIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        rc = fqCsid.encodeFqCsidIe(buffer, data.sgwFqCsid);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: sgwFqCsid\n");
            return false;
        }
    }

    if (data.userCsgInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UciIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UciIe uci=
        dynamic_cast<
        UciIe&>(GtpV2IeFactory::getInstance().getIeObject(UciIeType));
        rc = uci.encodeUciIe(buffer, data.userCsgInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: userCsgInformation\n");
            return false;
        }
    }

    if (data.ueLocalIpAddressIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IpAddressIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        rc = ipAddress.encodeIpAddressIe(buffer, data.ueLocalIpAddress);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: ueLocalIpAddress\n");
            return false;
        }
    }

    if (data.ueUdpPortIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PortNumberIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        rc = portNumber.encodePortNumberIe(buffer, data.ueUdpPort);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: ueUdpPort\n");
            return false;
        }
    }

    if (data.mmeS4SgsnLdnIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = LocalDistinguishedNameIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        rc = localDistinguishedName.encodeLocalDistinguishedNameIe(buffer, data.mmeS4SgsnLdn);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: mmeS4SgsnLdn\n");
            return false;
        }
    }

    if (data.sgwLdnIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = LocalDistinguishedNameIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        rc = localDistinguishedName.encodeLocalDistinguishedNameIe(buffer, data.sgwLdn);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: sgwLdn\n");
            return false;
        }
    }

    if (data.hNbLocalIpAddressIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IpAddressIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        rc = ipAddress.encodeIpAddressIe(buffer, data.hNbLocalIpAddress);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: hNbLocalIpAddress\n");
            return false;
        }
    }

    if (data.hNbUdpPortIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = PortNumberIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        rc = portNumber.encodePortNumberIe(buffer, data.hNbUdpPort);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: hNbUdpPort\n");
            return false;
        }
    }

    if (data.mmeS4SgsnIdentifierIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = IpAddressIeType;
        header.instance = 2;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        rc = ipAddress.encodeIpAddressIe(buffer, data.mmeS4SgsnIdentifier);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: mmeS4SgsnIdentifier\n");
            return false;
        }
    }

    if (data.cnOperatorSelectionEntityIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = CnOperatorSelectionEntityIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        CnOperatorSelectionEntityIe cnOperatorSelectionEntity=
        dynamic_cast<
        CnOperatorSelectionEntityIe&>(GtpV2IeFactory::getInstance().getIeObject(CnOperatorSelectionEntityIeType));
        rc = cnOperatorSelectionEntity.encodeCnOperatorSelectionEntityIe(buffer, data.cnOperatorSelectionEntity);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: cnOperatorSelectionEntity\n");
            return false;
        }
    }

    if (data.mmeS4SgsnsOverloadControlInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = OverloadControlInformationIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
        MmeS4SgsnsOverloadControlInformationInModifyBearerRequest groupedIeInstance =
        dynamic_cast<
         MmeS4SgsnsOverloadControlInformationInModifyBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        rc = groupedIeInstance.encodeMmeS4SgsnsOverloadControlInformationInModifyBearerRequest(buffer, data.mmeS4SgsnsOverloadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: mmeS4SgsnsOverloadControlInformation\n");
            return false;
        }
    }

    if (data.sgwsOverloadControlInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = OverloadControlInformationIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
        SgwsOverloadControlInformationInModifyBearerRequest groupedIeInstance =
        dynamic_cast<
         SgwsOverloadControlInformationInModifyBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        rc = groupedIeInstance.encodeSgwsOverloadControlInformationInModifyBearerRequest(buffer, data.sgwsOverloadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: sgwsOverloadControlInformation\n");
            return false;
        }
    }

    if (data.epdgsOverloadControlInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = OverloadControlInformationIeType;
        header.instance = 2;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
        EpdgsOverloadControlInformationInModifyBearerRequest groupedIeInstance =
        dynamic_cast<
         EpdgsOverloadControlInformationInModifyBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 2));
        rc = groupedIeInstance.encodeEpdgsOverloadControlInformationInModifyBearerRequest(buffer, data.epdgsOverloadControlInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: epdgsOverloadControlInformation\n");
            return false;
        }
    }

    if (data.servingPlmnRateControlIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ServingPlmnRateControlIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ServingPlmnRateControlIe servingPlmnRateControl=
        dynamic_cast<
        ServingPlmnRateControlIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingPlmnRateControlIeType));
        rc = servingPlmnRateControl.encodeServingPlmnRateControlIe(buffer, data.servingPlmnRateControl);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: servingPlmnRateControl\n");
            return false;
        }
    }

    if (data.moExceptionDataCounterIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = CounterIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        CounterIe counter=
        dynamic_cast<
        CounterIe&>(GtpV2IeFactory::getInstance().getIeObject(CounterIeType));
        rc = counter.encodeCounterIe(buffer, data.moExceptionDataCounter);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: moExceptionDataCounter\n");
            return false;
        }
    }

    if (data.imsiIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = ImsiIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        ImsiIe imsi=
        dynamic_cast<
        ImsiIe&>(GtpV2IeFactory::getInstance().getIeObject(ImsiIeType));
        rc = imsi.encodeImsiIe(buffer, data.imsi);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: imsi\n");
            return false;
        }
    }

    if (data.userLocationInformationForSgwIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = UliIeType;
        header.instance = 1;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        rc = uli.encodeUliIe(buffer, data.userLocationInformationForSgw);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: userLocationInformationForSgw\n");
            return false;
        }
    }

    if (data.wlanLocationInformationIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = TwanIdentifierIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        TwanIdentifierIe twanIdentifier=
        dynamic_cast<
        TwanIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierIeType));
        rc = twanIdentifier.encodeTwanIdentifierIe(buffer, data.wlanLocationInformation);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: wlanLocationInformation\n");
            return false;
        }
    }

    if (data.wlanLocationTimestampIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = TwanIdentifierTimestampIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        TwanIdentifierTimestampIe twanIdentifierTimestamp=
        dynamic_cast<
        TwanIdentifierTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierTimestampIeType));
        rc = twanIdentifierTimestamp.encodeTwanIdentifierTimestampIe(buffer, data.wlanLocationTimestamp);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: wlanLocationTimestamp\n");
            return false;
        }
    }

    if (data.secondaryRatUsageDataReportIePresent)
    {
            
        // Encode the Ie Header
        header.ieType = SecondaryRatUsageDataReportIeType;
        header.instance = 0;
        header.length = 0; // We will encode the IE first and then update the length
        GtpV2Ie::encodeGtpV2IeHeader(buffer, header);
        startIndex = buffer.getCurrentIndex(); 
        SecondaryRatUsageDataReportIe secondaryRatUsageDataReport=
        dynamic_cast<
        SecondaryRatUsageDataReportIe&>(GtpV2IeFactory::getInstance().getIeObject(SecondaryRatUsageDataReportIeType));
        rc = secondaryRatUsageDataReport.encodeSecondaryRatUsageDataReportIe(buffer, data.secondaryRatUsageDataReport);
        endIndex = buffer.getCurrentIndex();
        length = endIndex - startIndex;
    
        // encode the length value now
        buffer.goToIndex(startIndex - 3);
        buffer.writeUint16(length, false);
        buffer.goToIndex(endIndex);

        if (!(rc))
        { 
            errorStream.add((char *)"Failed to encode IE: secondaryRatUsageDataReport\n");
            return false;
        }
    }
    return rc;

}

bool ModifyBearerRequestMsg::decodeModifyBearerRequestMsg(MsgBuffer &buffer,
 ModifyBearerRequestMsgData 
 &data, Uint16 length)
{

    bool rc = false;
    GtpV2IeHeader ieHeader;
  
    set<Uint16> mandatoryIeLocalList = mandatoryIeSet;
    while (buffer.lengthLeft() > IE_HEADER_SIZE)
    {
        GtpV2Ie::decodeGtpV2IeHeader(buffer, ieHeader);
        if (ieHeader.length > buffer.lengthLeft())
        {
            // We do not have enough bytes left in the message for this IE
            errorStream.add((char *)"IE Length exceeds beyond message boundary\n");
            errorStream.add((char *)"  Offending IE Type: ");
            errorStream.add(ieHeader.ieType);
            errorStream.add((char *)"\n  Ie Length in Header: ");
            errorStream.add(ieHeader.length);
            errorStream.add((char *)"\n  Bytes left in message: ");
            errorStream.add(buffer.lengthLeft());
            errorStream.endOfLine();
            return false;
        }

        switch (ieHeader.ieType){
     
            case MeiIeType:
            {
                MeiIe ieObject =
                dynamic_cast<
                MeiIe&>(GtpV2IeFactory::getInstance().getIeObject(MeiIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeMeiIe(buffer, data.meIdentity, ieHeader.length);

                    data.meIdentityIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: meIdentity\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case UliIeType:
            {
                UliIe ieObject =
                dynamic_cast<
                UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeUliIe(buffer, data.userLocationInformation, ieHeader.length);

                    data.userLocationInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: userLocationInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeUliIe(buffer, data.userLocationInformationForSgw, ieHeader.length);

                    data.userLocationInformationForSgwIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: userLocationInformationForSgw\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case ServingNetworkIeType:
            {
                ServingNetworkIe ieObject =
                dynamic_cast<
                ServingNetworkIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingNetworkIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeServingNetworkIe(buffer, data.servingNetwork, ieHeader.length);

                    data.servingNetworkIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: servingNetwork\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case RatTypeIeType:
            {
                RatTypeIe ieObject =
                dynamic_cast<
                RatTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(RatTypeIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeRatTypeIe(buffer, data.ratType, ieHeader.length);

                    data.ratTypeIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: ratType\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case IndicationIeType:
            {
                IndicationIe ieObject =
                dynamic_cast<
                IndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(IndicationIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeIndicationIe(buffer, data.indicationFlags, ieHeader.length);

                    data.indicationFlagsIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: indicationFlags\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case FTeidIeType:
            {
                FTeidIe ieObject =
                dynamic_cast<
                FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeFTeidIe(buffer, data.senderFTeidForControlPlane, ieHeader.length);

                    data.senderFTeidForControlPlaneIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: senderFTeidForControlPlane\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case AmbrIeType:
            {
                AmbrIe ieObject =
                dynamic_cast<
                AmbrIe&>(GtpV2IeFactory::getInstance().getIeObject(AmbrIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeAmbrIe(buffer, data.aggregateMaximumBitRate, ieHeader.length);

                    data.aggregateMaximumBitRateIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: aggregateMaximumBitRate\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case DelayValueIeType:
            {
                DelayValueIe ieObject =
                dynamic_cast<
                DelayValueIe&>(GtpV2IeFactory::getInstance().getIeObject(DelayValueIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeDelayValueIe(buffer, data.delayDownlinkPacketNotificationRequest, ieHeader.length);

                    data.delayDownlinkPacketNotificationRequestIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: delayDownlinkPacketNotificationRequest\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case BearerContextIeType:
            {
                BearerContextIe ieObject =
                dynamic_cast<
                BearerContextIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerContextIeType));

                if(ieHeader.instance == 0)
                {
					// First check if we have enough space left to decode and store this instance
                    if (data.bearerContextsToBeModifiedCount == 11)
                    {
                        errorStream.add((char *)"More than 11 instances of bearerContextsToBeModified received\n");
                        return false;
                    }
                    BearerContextsToBeModifiedInModifyBearerRequest groupedIeInstance =
                    dynamic_cast<
                    BearerContextsToBeModifiedInModifyBearerRequest&>(ieObject.getGroupedIe(msgType, 0));
                    rc = groupedIeInstance.decodeBearerContextsToBeModifiedInModifyBearerRequest(buffer,
                    data.bearerContextsToBeModified[data.bearerContextsToBeModifiedCount], ieHeader.length);
                    data.bearerContextsToBeModifiedCount++; // TODO Count validation

                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: bearerContextsToBeModified\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					// First check if we have enough space left to decode and store this instance
                    if (data.bearerContextsToBeRemovedCount == 11)
                    {
                        errorStream.add((char *)"More than 11 instances of bearerContextsToBeRemoved received\n");
                        return false;
                    }
                    BearerContextsToBeRemovedInModifyBearerRequest groupedIeInstance =
                    dynamic_cast<
                    BearerContextsToBeRemovedInModifyBearerRequest&>(ieObject.getGroupedIe(msgType, 1));
                    rc = groupedIeInstance.decodeBearerContextsToBeRemovedInModifyBearerRequest(buffer,
                    data.bearerContextsToBeRemoved[data.bearerContextsToBeRemovedCount], ieHeader.length);
                    data.bearerContextsToBeRemovedCount++; // TODO Count validation

                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: bearerContextsToBeRemoved\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case RecoveryIeType:
            {
                RecoveryIe ieObject =
                dynamic_cast<
                RecoveryIe&>(GtpV2IeFactory::getInstance().getIeObject(RecoveryIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeRecoveryIe(buffer, data.recovery, ieHeader.length);

                    data.recoveryIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: recovery\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case UeTimeZoneIeType:
            {
                UeTimeZoneIe ieObject =
                dynamic_cast<
                UeTimeZoneIe&>(GtpV2IeFactory::getInstance().getIeObject(UeTimeZoneIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeUeTimeZoneIe(buffer, data.ueTimeZone, ieHeader.length);

                    data.ueTimeZoneIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: ueTimeZone\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case FqCsidIeType:
            {
                FqCsidIe ieObject =
                dynamic_cast<
                FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeFqCsidIe(buffer, data.mmeFqCsid, ieHeader.length);

                    data.mmeFqCsidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: mmeFqCsid\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeFqCsidIe(buffer, data.sgwFqCsid, ieHeader.length);

                    data.sgwFqCsidIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: sgwFqCsid\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case UciIeType:
            {
                UciIe ieObject =
                dynamic_cast<
                UciIe&>(GtpV2IeFactory::getInstance().getIeObject(UciIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeUciIe(buffer, data.userCsgInformation, ieHeader.length);

                    data.userCsgInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: userCsgInformation\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case IpAddressIeType:
            {
                IpAddressIe ieObject =
                dynamic_cast<
                IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));

                if(ieHeader.instance == 1)
                {
					rc = ieObject.decodeIpAddressIe(buffer, data.ueLocalIpAddress, ieHeader.length);

                    data.ueLocalIpAddressIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: ueLocalIpAddress\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeIpAddressIe(buffer, data.hNbLocalIpAddress, ieHeader.length);

                    data.hNbLocalIpAddressIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: hNbLocalIpAddress\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					rc = ieObject.decodeIpAddressIe(buffer, data.mmeS4SgsnIdentifier, ieHeader.length);

                    data.mmeS4SgsnIdentifierIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: mmeS4SgsnIdentifier\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case PortNumberIeType:
            {
                PortNumberIe ieObject =
                dynamic_cast<
                PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));

                if(ieHeader.instance == 1)
                {
					rc = ieObject.decodePortNumberIe(buffer, data.ueUdpPort, ieHeader.length);

                    data.ueUdpPortIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: ueUdpPort\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 0)
                {
					rc = ieObject.decodePortNumberIe(buffer, data.hNbUdpPort, ieHeader.length);

                    data.hNbUdpPortIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: hNbUdpPort\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case LocalDistinguishedNameIeType:
            {
                LocalDistinguishedNameIe ieObject =
                dynamic_cast<
                LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeLocalDistinguishedNameIe(buffer, data.mmeS4SgsnLdn, ieHeader.length);

                    data.mmeS4SgsnLdnIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: mmeS4SgsnLdn\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeLocalDistinguishedNameIe(buffer, data.sgwLdn, ieHeader.length);

                    data.sgwLdnIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: sgwLdn\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case CnOperatorSelectionEntityIeType:
            {
                CnOperatorSelectionEntityIe ieObject =
                dynamic_cast<
                CnOperatorSelectionEntityIe&>(GtpV2IeFactory::getInstance().getIeObject(CnOperatorSelectionEntityIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeCnOperatorSelectionEntityIe(buffer, data.cnOperatorSelectionEntity, ieHeader.length);

                    data.cnOperatorSelectionEntityIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: cnOperatorSelectionEntity\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case OverloadControlInformationIeType:
            {
                OverloadControlInformationIe ieObject =
                dynamic_cast<
                OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));

                if(ieHeader.instance == 0)
                {
					MmeS4SgsnsOverloadControlInformationInModifyBearerRequest groupedIeInstance =
					dynamic_cast<
					MmeS4SgsnsOverloadControlInformationInModifyBearerRequest&>(ieObject.getGroupedIe(msgType, 0));
					rc = groupedIeInstance.decodeMmeS4SgsnsOverloadControlInformationInModifyBearerRequest(buffer, data.mmeS4SgsnsOverloadControlInformation, ieHeader.length);

                    data.mmeS4SgsnsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: mmeS4SgsnsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 1)
                {
					SgwsOverloadControlInformationInModifyBearerRequest groupedIeInstance =
					dynamic_cast<
					SgwsOverloadControlInformationInModifyBearerRequest&>(ieObject.getGroupedIe(msgType, 1));
					rc = groupedIeInstance.decodeSgwsOverloadControlInformationInModifyBearerRequest(buffer, data.sgwsOverloadControlInformation, ieHeader.length);

                    data.sgwsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: sgwsOverloadControlInformation\n");
                        return false;
                    }
                }
                else if(ieHeader.instance == 2)
                {
					EpdgsOverloadControlInformationInModifyBearerRequest groupedIeInstance =
					dynamic_cast<
					EpdgsOverloadControlInformationInModifyBearerRequest&>(ieObject.getGroupedIe(msgType, 2));
					rc = groupedIeInstance.decodeEpdgsOverloadControlInformationInModifyBearerRequest(buffer, data.epdgsOverloadControlInformation, ieHeader.length);

                    data.epdgsOverloadControlInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: epdgsOverloadControlInformation\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case ServingPlmnRateControlIeType:
            {
                ServingPlmnRateControlIe ieObject =
                dynamic_cast<
                ServingPlmnRateControlIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingPlmnRateControlIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeServingPlmnRateControlIe(buffer, data.servingPlmnRateControl, ieHeader.length);

                    data.servingPlmnRateControlIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: servingPlmnRateControl\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case CounterIeType:
            {
                CounterIe ieObject =
                dynamic_cast<
                CounterIe&>(GtpV2IeFactory::getInstance().getIeObject(CounterIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeCounterIe(buffer, data.moExceptionDataCounter, ieHeader.length);

                    data.moExceptionDataCounterIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: moExceptionDataCounter\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case ImsiIeType:
            {
                ImsiIe ieObject =
                dynamic_cast<
                ImsiIe&>(GtpV2IeFactory::getInstance().getIeObject(ImsiIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeImsiIe(buffer, data.imsi, ieHeader.length);

                    data.imsiIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: imsi\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case TwanIdentifierIeType:
            {
                TwanIdentifierIe ieObject =
                dynamic_cast<
                TwanIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeTwanIdentifierIe(buffer, data.wlanLocationInformation, ieHeader.length);

                    data.wlanLocationInformationIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: wlanLocationInformation\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case TwanIdentifierTimestampIeType:
            {
                TwanIdentifierTimestampIe ieObject =
                dynamic_cast<
                TwanIdentifierTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierTimestampIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeTwanIdentifierTimestampIe(buffer, data.wlanLocationTimestamp, ieHeader.length);

                    data.wlanLocationTimestampIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: wlanLocationTimestamp\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }
     
            case SecondaryRatUsageDataReportIeType:
            {
                SecondaryRatUsageDataReportIe ieObject =
                dynamic_cast<
                SecondaryRatUsageDataReportIe&>(GtpV2IeFactory::getInstance().getIeObject(SecondaryRatUsageDataReportIeType));

                if(ieHeader.instance == 0)
                {
					rc = ieObject.decodeSecondaryRatUsageDataReportIe(buffer, data.secondaryRatUsageDataReport, ieHeader.length);

                    data.secondaryRatUsageDataReportIePresent = true;
                    if (!(rc))
                    {
                        errorStream.add((char *)"Failed to decode IE: secondaryRatUsageDataReport\n");
                        return false;
                    }
                }

                else
                {
                    // Unknown IE instance print error
                    errorStream.add((char *)"Unknown IE Type: ");
                    errorStream.add(ieHeader.ieType);
                    errorStream.endOfLine();
                    buffer.skipBytes(ieHeader.length);
                }
                break;
            }

            default:
            {
                // Unknown IE print error
                errorStream.add((char *)"Unknown IE Type: ");
                errorStream.add(ieHeader.ieType);
                errorStream.endOfLine();
                buffer.skipBytes(ieHeader.length);
            }
        }
    }
    return rc; // TODO validations
}

void ModifyBearerRequestMsg::
displayModifyBearerRequestMsgData_v(ModifyBearerRequestMsgData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ModifyBearerRequestMsg:");
    stream.endOfLine();
    stream.incrIndent();
        
    
    if (data.meIdentityIePresent)
    {


        stream.add((char *)"IE - meIdentity:");
        stream.endOfLine();
        MeiIe mei=
        dynamic_cast<
        MeiIe&>(GtpV2IeFactory::getInstance().getIeObject(MeiIeType));
        mei.displayMeiIe_v(data.meIdentity, stream);

    }
    if (data.userLocationInformationIePresent)
    {


        stream.add((char *)"IE - userLocationInformation:");
        stream.endOfLine();
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        uli.displayUliIe_v(data.userLocationInformation, stream);

    }
    if (data.servingNetworkIePresent)
    {


        stream.add((char *)"IE - servingNetwork:");
        stream.endOfLine();
        ServingNetworkIe servingNetwork=
        dynamic_cast<
        ServingNetworkIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingNetworkIeType));
        servingNetwork.displayServingNetworkIe_v(data.servingNetwork, stream);

    }
    if (data.ratTypeIePresent)
    {


        stream.add((char *)"IE - ratType:");
        stream.endOfLine();
        RatTypeIe ratType=
        dynamic_cast<
        RatTypeIe&>(GtpV2IeFactory::getInstance().getIeObject(RatTypeIeType));
        ratType.displayRatTypeIe_v(data.ratType, stream);

    }
    if (data.indicationFlagsIePresent)
    {


        stream.add((char *)"IE - indicationFlags:");
        stream.endOfLine();
        IndicationIe indication=
        dynamic_cast<
        IndicationIe&>(GtpV2IeFactory::getInstance().getIeObject(IndicationIeType));
        indication.displayIndicationIe_v(data.indicationFlags, stream);

    }
    if (data.senderFTeidForControlPlaneIePresent)
    {


        stream.add((char *)"IE - senderFTeidForControlPlane:");
        stream.endOfLine();
        FTeidIe fTeid=
        dynamic_cast<
        FTeidIe&>(GtpV2IeFactory::getInstance().getIeObject(FTeidIeType));
        fTeid.displayFTeidIe_v(data.senderFTeidForControlPlane, stream);

    }
    if (data.aggregateMaximumBitRateIePresent)
    {


        stream.add((char *)"IE - aggregateMaximumBitRate:");
        stream.endOfLine();
        AmbrIe ambr=
        dynamic_cast<
        AmbrIe&>(GtpV2IeFactory::getInstance().getIeObject(AmbrIeType));
        ambr.displayAmbrIe_v(data.aggregateMaximumBitRate, stream);

    }
    if (data.delayDownlinkPacketNotificationRequestIePresent)
    {


        stream.add((char *)"IE - delayDownlinkPacketNotificationRequest:");
        stream.endOfLine();
        DelayValueIe delayValue=
        dynamic_cast<
        DelayValueIe&>(GtpV2IeFactory::getInstance().getIeObject(DelayValueIeType));
        delayValue.displayDelayValueIe_v(data.delayDownlinkPacketNotificationRequest, stream);

    }

    Uint8 displayCount;
    
    displayCount = data.bearerContextsToBeModifiedCount;
    if (displayCount > 11)
    {
        stream.add((char *)"Invalid data more than 11 instances");
        stream.endOfLine();
        stream.add((char *)"Displaying only 11");
        stream.endOfLine();
        displayCount = 11;
    }
    for (Uint8 i = 0; i < displayCount; i++)
    {
        stream.add((char *)"IE -  bearerContextsToBeModified:");
        stream.endOfLine();
        BearerContextIe bearerContext=
        dynamic_cast<
        BearerContextIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerContextIeType));
                BearerContextsToBeModifiedInModifyBearerRequest groupedIeInstance =
        dynamic_cast<
        BearerContextsToBeModifiedInModifyBearerRequest&>(bearerContext.getGroupedIe(msgType, 0));
        groupedIeInstance.displayBearerContextsToBeModifiedInModifyBearerRequestData_v(data.bearerContextsToBeModified[i], stream);
    }

    

    
    displayCount = data.bearerContextsToBeRemovedCount;
    if (displayCount > 11)
    {
        stream.add((char *)"Invalid data more than 11 instances");
        stream.endOfLine();
        stream.add((char *)"Displaying only 11");
        stream.endOfLine();
        displayCount = 11;
    }
    for (Uint8 i = 0; i < displayCount; i++)
    {
        stream.add((char *)"IE -  bearerContextsToBeRemoved:");
        stream.endOfLine();
        BearerContextIe bearerContext=
        dynamic_cast<
        BearerContextIe&>(GtpV2IeFactory::getInstance().getIeObject(BearerContextIeType));
                BearerContextsToBeRemovedInModifyBearerRequest groupedIeInstance =
        dynamic_cast<
        BearerContextsToBeRemovedInModifyBearerRequest&>(bearerContext.getGroupedIe(msgType, 1));
        groupedIeInstance.displayBearerContextsToBeRemovedInModifyBearerRequestData_v(data.bearerContextsToBeRemoved[i], stream);
    }

    

    
    if (data.recoveryIePresent)
    {


        stream.add((char *)"IE - recovery:");
        stream.endOfLine();
        RecoveryIe recovery=
        dynamic_cast<
        RecoveryIe&>(GtpV2IeFactory::getInstance().getIeObject(RecoveryIeType));
        recovery.displayRecoveryIe_v(data.recovery, stream);

    }
    if (data.ueTimeZoneIePresent)
    {


        stream.add((char *)"IE - ueTimeZone:");
        stream.endOfLine();
        UeTimeZoneIe ueTimeZone=
        dynamic_cast<
        UeTimeZoneIe&>(GtpV2IeFactory::getInstance().getIeObject(UeTimeZoneIeType));
        ueTimeZone.displayUeTimeZoneIe_v(data.ueTimeZone, stream);

    }
    if (data.mmeFqCsidIePresent)
    {


        stream.add((char *)"IE - mmeFqCsid:");
        stream.endOfLine();
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        fqCsid.displayFqCsidIe_v(data.mmeFqCsid, stream);

    }
    if (data.sgwFqCsidIePresent)
    {


        stream.add((char *)"IE - sgwFqCsid:");
        stream.endOfLine();
        FqCsidIe fqCsid=
        dynamic_cast<
        FqCsidIe&>(GtpV2IeFactory::getInstance().getIeObject(FqCsidIeType));
        fqCsid.displayFqCsidIe_v(data.sgwFqCsid, stream);

    }
    if (data.userCsgInformationIePresent)
    {


        stream.add((char *)"IE - userCsgInformation:");
        stream.endOfLine();
        UciIe uci=
        dynamic_cast<
        UciIe&>(GtpV2IeFactory::getInstance().getIeObject(UciIeType));
        uci.displayUciIe_v(data.userCsgInformation, stream);

    }
    if (data.ueLocalIpAddressIePresent)
    {


        stream.add((char *)"IE - ueLocalIpAddress:");
        stream.endOfLine();
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        ipAddress.displayIpAddressIe_v(data.ueLocalIpAddress, stream);

    }
    if (data.ueUdpPortIePresent)
    {


        stream.add((char *)"IE - ueUdpPort:");
        stream.endOfLine();
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        portNumber.displayPortNumberIe_v(data.ueUdpPort, stream);

    }
    if (data.mmeS4SgsnLdnIePresent)
    {


        stream.add((char *)"IE - mmeS4SgsnLdn:");
        stream.endOfLine();
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        localDistinguishedName.displayLocalDistinguishedNameIe_v(data.mmeS4SgsnLdn, stream);

    }
    if (data.sgwLdnIePresent)
    {


        stream.add((char *)"IE - sgwLdn:");
        stream.endOfLine();
        LocalDistinguishedNameIe localDistinguishedName=
        dynamic_cast<
        LocalDistinguishedNameIe&>(GtpV2IeFactory::getInstance().getIeObject(LocalDistinguishedNameIeType));
        localDistinguishedName.displayLocalDistinguishedNameIe_v(data.sgwLdn, stream);

    }
    if (data.hNbLocalIpAddressIePresent)
    {


        stream.add((char *)"IE - hNbLocalIpAddress:");
        stream.endOfLine();
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        ipAddress.displayIpAddressIe_v(data.hNbLocalIpAddress, stream);

    }
    if (data.hNbUdpPortIePresent)
    {


        stream.add((char *)"IE - hNbUdpPort:");
        stream.endOfLine();
        PortNumberIe portNumber=
        dynamic_cast<
        PortNumberIe&>(GtpV2IeFactory::getInstance().getIeObject(PortNumberIeType));
        portNumber.displayPortNumberIe_v(data.hNbUdpPort, stream);

    }
    if (data.mmeS4SgsnIdentifierIePresent)
    {


        stream.add((char *)"IE - mmeS4SgsnIdentifier:");
        stream.endOfLine();
        IpAddressIe ipAddress=
        dynamic_cast<
        IpAddressIe&>(GtpV2IeFactory::getInstance().getIeObject(IpAddressIeType));
        ipAddress.displayIpAddressIe_v(data.mmeS4SgsnIdentifier, stream);

    }
    if (data.cnOperatorSelectionEntityIePresent)
    {


        stream.add((char *)"IE - cnOperatorSelectionEntity:");
        stream.endOfLine();
        CnOperatorSelectionEntityIe cnOperatorSelectionEntity=
        dynamic_cast<
        CnOperatorSelectionEntityIe&>(GtpV2IeFactory::getInstance().getIeObject(CnOperatorSelectionEntityIeType));
        cnOperatorSelectionEntity.displayCnOperatorSelectionEntityIe_v(data.cnOperatorSelectionEntity, stream);

    }
    if (data.mmeS4SgsnsOverloadControlInformationIePresent)
    {


        stream.add((char *)"IE - mmeS4SgsnsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            MmeS4SgsnsOverloadControlInformationInModifyBearerRequest groupedIeInstance =
        dynamic_cast<
        MmeS4SgsnsOverloadControlInformationInModifyBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 0));
        groupedIeInstance.displayMmeS4SgsnsOverloadControlInformationInModifyBearerRequestData_v(data.mmeS4SgsnsOverloadControlInformation, stream);

    }
    if (data.sgwsOverloadControlInformationIePresent)
    {


        stream.add((char *)"IE - sgwsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            SgwsOverloadControlInformationInModifyBearerRequest groupedIeInstance =
        dynamic_cast<
        SgwsOverloadControlInformationInModifyBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 1));
        groupedIeInstance.displaySgwsOverloadControlInformationInModifyBearerRequestData_v(data.sgwsOverloadControlInformation, stream);

    }
    if (data.epdgsOverloadControlInformationIePresent)
    {


        stream.add((char *)"IE - epdgsOverloadControlInformation:");
        stream.endOfLine();
        OverloadControlInformationIe overloadControlInformation=
        dynamic_cast<
        OverloadControlInformationIe&>(GtpV2IeFactory::getInstance().getIeObject(OverloadControlInformationIeType));
            EpdgsOverloadControlInformationInModifyBearerRequest groupedIeInstance =
        dynamic_cast<
        EpdgsOverloadControlInformationInModifyBearerRequest&>(overloadControlInformation.getGroupedIe(msgType, 2));
        groupedIeInstance.displayEpdgsOverloadControlInformationInModifyBearerRequestData_v(data.epdgsOverloadControlInformation, stream);

    }
    if (data.servingPlmnRateControlIePresent)
    {


        stream.add((char *)"IE - servingPlmnRateControl:");
        stream.endOfLine();
        ServingPlmnRateControlIe servingPlmnRateControl=
        dynamic_cast<
        ServingPlmnRateControlIe&>(GtpV2IeFactory::getInstance().getIeObject(ServingPlmnRateControlIeType));
        servingPlmnRateControl.displayServingPlmnRateControlIe_v(data.servingPlmnRateControl, stream);

    }
    if (data.moExceptionDataCounterIePresent)
    {


        stream.add((char *)"IE - moExceptionDataCounter:");
        stream.endOfLine();
        CounterIe counter=
        dynamic_cast<
        CounterIe&>(GtpV2IeFactory::getInstance().getIeObject(CounterIeType));
        counter.displayCounterIe_v(data.moExceptionDataCounter, stream);

    }
    if (data.imsiIePresent)
    {


        stream.add((char *)"IE - imsi:");
        stream.endOfLine();
        ImsiIe imsi=
        dynamic_cast<
        ImsiIe&>(GtpV2IeFactory::getInstance().getIeObject(ImsiIeType));
        imsi.displayImsiIe_v(data.imsi, stream);

    }
    if (data.userLocationInformationForSgwIePresent)
    {


        stream.add((char *)"IE - userLocationInformationForSgw:");
        stream.endOfLine();
        UliIe uli=
        dynamic_cast<
        UliIe&>(GtpV2IeFactory::getInstance().getIeObject(UliIeType));
        uli.displayUliIe_v(data.userLocationInformationForSgw, stream);

    }
    if (data.wlanLocationInformationIePresent)
    {


        stream.add((char *)"IE - wlanLocationInformation:");
        stream.endOfLine();
        TwanIdentifierIe twanIdentifier=
        dynamic_cast<
        TwanIdentifierIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierIeType));
        twanIdentifier.displayTwanIdentifierIe_v(data.wlanLocationInformation, stream);

    }
    if (data.wlanLocationTimestampIePresent)
    {


        stream.add((char *)"IE - wlanLocationTimestamp:");
        stream.endOfLine();
        TwanIdentifierTimestampIe twanIdentifierTimestamp=
        dynamic_cast<
        TwanIdentifierTimestampIe&>(GtpV2IeFactory::getInstance().getIeObject(TwanIdentifierTimestampIeType));
        twanIdentifierTimestamp.displayTwanIdentifierTimestampIe_v(data.wlanLocationTimestamp, stream);

    }
    if (data.secondaryRatUsageDataReportIePresent)
    {


        stream.add((char *)"IE - secondaryRatUsageDataReport:");
        stream.endOfLine();
        SecondaryRatUsageDataReportIe secondaryRatUsageDataReport=
        dynamic_cast<
        SecondaryRatUsageDataReportIe&>(GtpV2IeFactory::getInstance().getIeObject(SecondaryRatUsageDataReportIeType));
        secondaryRatUsageDataReport.displaySecondaryRatUsageDataReportIe_v(data.secondaryRatUsageDataReport, stream);

    }

    stream.decrIndent();
    stream.decrIndent();
}


