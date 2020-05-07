/*
 * gtpV2GrpIeDataTypes.h 
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef GTPV2GRPIEDATATYPES_H_
#define GTPV2GRPIEDATATYPES_H_

#include "../../gtpV2Codec/ieClasses/gtpV2IeDataTypes.h"


typedef struct
{
  bool tftIePresent;
  bool s1UEnodebFTeidIePresent;
  bool s4USgsnFTeidIePresent;
  bool s5S8USgwFTeidIePresent;
  bool s5S8UPgwFTeidIePresent;
  bool s12RncFTeidIePresent;
  bool s2bUEpdgFTeidIePresent;
  bool s2aUTwanFTeidIePresent;
  bool s11UMmeFTeidIePresent;

  EbiIeData epsBearerId;
  BearerTftIeData tft;
  FTeidIeData s1UEnodebFTeid;
  FTeidIeData s4USgsnFTeid;
  FTeidIeData s5S8USgwFTeid;
  FTeidIeData s5S8UPgwFTeid;
  FTeidIeData s12RncFTeid;
  FTeidIeData s2bUEpdgFTeid;
  FTeidIeData s2aUTwanFTeid;
  FTeidIeData s11UMmeFTeid;
  BearerQosIeData bearerLevelQos;
}BearerContextsToBeCreatedInCreateSessionRequestData;

typedef struct
{
  bool s4USgsnFTeidIePresent;

  EbiIeData epsBearerId;
  FTeidIeData s4USgsnFTeid;
}BearerContextsToBeRemovedInCreateSessionRequestData;

typedef struct
{
  bool tftIePresent;
  bool s1USgwFTeidIePresent;
  bool s4USgwFTeidIePresent;
  bool s5S8UPgwFTeidIePresent;
  bool s12SgwFTeidIePresent;
  bool s2bUPgwFTeidIePresent;
  bool s2aUPgwFTeidIePresent;
  bool bearerLevelQosIePresent;
  bool chargingIdIePresent;
  bool bearerFlagsIePresent;
  bool s11USgwFTeidIePresent;

  EbiIeData epsBearerId;
  CauseIeData cause;
  BearerTftIeData tft;
  FTeidIeData s1USgwFTeid;
  FTeidIeData s4USgwFTeid;
  FTeidIeData s5S8UPgwFTeid;
  FTeidIeData s12SgwFTeid;
  FTeidIeData s2bUPgwFTeid;
  FTeidIeData s2aUPgwFTeid;
  FTeidIeData s11USgwFTeid;
  BearerQosIeData bearerLevelQos;
  ChargingIdIeData chargingId;
  BearerFlagsIeData bearerFlags;
  
  }BearerContextsCreatedInCreateSessionResponseData;

typedef struct
{

  EbiIeData epsBearerId;
  CauseIeData cause;
}BearerContextsMarkedForRemovalInCreateSessionResponseData;

typedef struct
{
  bool s1EnodebFTeidIePresent;
  bool s58USgwFTeidIePresent;
  bool s12RncFTeidIePresent;
  bool s4USgsnFTeidIePresent;
  bool s11UMmeFTeidIePresent;

  EbiIeData epsBearerId;
  FTeidIeData s1EnodebFTeid;
  FTeidIeData s58USgwFTeid;
  FTeidIeData s12RncFTeid;
  FTeidIeData s4USgsnFTeid;
  FTeidIeData s11UMmeFTeid;
}BearerContextsToBeModifiedInModifyBearerRequestData;

typedef struct
{

  EbiIeData epsBearerId;
}BearerContextsToBeRemovedInModifyBearerRequestData;

typedef struct
{
  bool s1USgwFTeidIePresent;
  bool s12SgwFTeidIePresent;
  bool s4USgwFTeidIePresent;
  bool chargingIdIePresent;
  bool bearerFlagsIePresent;
  bool s11USgwFTeidIePresent;

  EbiIeData epsBearerId;
  CauseIeData cause;
  FTeidIeData s1USgwFTeid;
  FTeidIeData s12SgwFTeid;
  FTeidIeData s4USgwFTeid;
  ChargingIdIeData chargingId;
  BearerFlagsIeData bearerFlags;
  FTeidIeData s11USgwFTeid;
}BearerContextsModifiedInModifyBearerResponseData;

typedef struct
{

  EbiIeData epsBearerId;
  CauseIeData cause;
}BearerContextsMarkedForRemovalInModifyBearerResponseData;

typedef struct
{
  EbiIeData epsBearerId;
  CauseIeData cause;
}BearerContextsInDeleteSessionRequestData;

typedef struct
{
  RemoteUserIdIeData remoteUserId;
  RemoteUeIpInformationIeData remoteUeIpInformation;
}RemoteUeContextConnectedInCreateSessionRequestData;


typedef struct
{
  bool listOfAccessPointNameIePresent;
  
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
  ApnIeData listOfAccessPointName;
}PgwsOverloadControlInformationInCreateSessionResponseData;

typedef struct
{
  bool listOfAccessPointNameIePresent;
  
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
  ApnIeData listOfAccessPointName;
}SgwsOverloadControlInformationInCreateSessionResponseData;

typedef struct
{
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
}MmeS4SgsnsOverloadControlInformationInCreateSessionRequestData;
typedef struct
{
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
}SgwsOverloadControlInformationInCreateSessionRequestData;

typedef struct
{
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
}TwanEpdgsOverloadControlInformationInCreateSessionRequestData;

typedef struct
{
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
}MmeS4SgsnsOverloadControlInformationInDeleteSessionRequestData;

typedef struct
{
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
}SgwsOverloadControlInformationInDeleteSessionRequestData;

typedef struct
{
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
}TwanEpdgsOverloadControlInformationInDeleteSessionRequestData;

typedef struct
{
  bool listOfAccessPointNameIePresent;
  
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
  ApnIeData listOfAccessPointName;
}SgwsOverloadControlInformationInDeleteSessionResponseData;

typedef struct
{
  bool listOfAccessPointNameIePresent;
  
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
  ApnIeData listOfAccessPointName;
}PgwsOverloadControlInformationInDeleteSessionResponseData;


typedef struct
{
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
}MmeS4SgsnsOverloadControlInformationInModifyBearerRequestData;

typedef struct
{
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
}SgwsOverloadControlInformationInModifyBearerRequestData;

typedef struct
{
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
}EpdgsOverloadControlInformationInModifyBearerRequestData;

typedef struct
{
  bool listOfAccessPointNameIePresent;
  
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
  ApnIeData listOfAccessPointName;
}SgwsOverloadControlInformationInModifyBearerResponseData;

typedef struct
{
  bool listOfAccessPointNameIePresent;
  
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
  ApnIeData listOfAccessPointName;
}PgwsOverloadControlInformationInModifyBearerResponseData;

typedef struct
{
  bool listOfAccessPointNameIePresent;
  
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
  ApnIeData listOfAccessPointName;
}SgwsOverloadControlInformationInReleaseAccessBearersResponseData;


typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
  
}PgwsNodeLevelLoadControlInformationInCreateSessionResponseData;

typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
}PgwsApnLevelLoadControlInformationInCreateSessionResponseData;
typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
}SgwsNodeLevelLoadControlInformationInCreateSessionResponseData;

typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
}PgwsNodeLevelLoadControlInformationInDeleteSessionResponseData;

typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
}PgwsApnLevelLoadControlInformationInDeleteSessionResponseData;

typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
}SgwsNodeLevelLoadControlInformationInDeleteSessionResponseData;

typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
}PgwsNodeLevelLoadControlInformationInModifyBearerResponseData;

typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
}PgwsApnLevelLoadControlInformationInModifyBearerResponseData;

typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
}SgwsNodeLevelLoadControlInformationInModifyBearerResponseData;

typedef struct
{
  SequenceNumberIeData loadControlSequenceNumber;
  MetricIeData loadMetric;
  ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
}SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponseData;




typedef struct
{
 bool epsBearerIdIePresent;
 bool tftIePresentIePresent;
 bool s1USgwFTeidIePresent;
 bool s58UPgwFTeidIePresent;
 bool s12SgwFTeidIePresent;
 bool s4USgwFTeidIePresent;
 bool s2bUPgwFTeidIePresent;
 bool s2aUPgwFTeidIePresent;
 bool bearerLevelQosIePresent;
 bool chargingIdIePresent;
 bool bearerFlagsIePresent;
 bool protocolConfigurationOptionsIePresent;
 bool extendedProtocolConfigurationOptionsIePresent;
 bool maximumPacketLossRateIePresent;
 
 EbiIeData epsBearerId;
 BearerTftIeData tft;
 FTeidIeData s1USgwFTeid;
 FTeidIeData s58UPgwFTeid;
 FTeidIeData s12SgwFTeid;
 FTeidIeData s4USgwFTeid;
 FTeidIeData s2bUPgwFTeid;
 FTeidIeData s2aUPgwFTeid;
 BearerQosIeData bearerLevelQos;
 ChargingIdIeData chargingId;
 BearerFlagsIeData bearerFlags;
 PcoIeData protocolConfigurationOptions;
 EpcoIeData extendedProtocolConfigurationOptions;
 MaximumPacketLossRateIeData maximumPacketLossRate;

 }BearerContextsInCreateBearerRequestData;
 
 
 typedef struct
{
	
	SequenceNumberIeData loadControlSequenceNumber;
	MetricIeData loadMetric;
	ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
		
}PgwsNodeLevelLoadControlInformationInCreateBearerRequestData;


 typedef struct
{

	SequenceNumberIeData loadControlSequenceNumber;
	MetricIeData loadMetric;
	ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
		
}PgwsApnLevelLoadControlInformationInCreateBearerRequestData;

 typedef struct
{

	SequenceNumberIeData loadControlSequenceNumber;
	MetricIeData loadMetric;
	ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;
		
}SgwsNodeLevelLoadControlInformationInCreateBearerRequestData;


typedef struct
{

	bool listofAccessPointNameIePresent;
	
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
	ApnIeData listOfAccessPointName;
	
}PgwsOverloadControlInformationInCreateBearerRequestData;

typedef struct
{
	bool listofAccessPointNameIePresent;
	
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
	ApnIeData listOfAccessPointName;
	
}SgwsOverloadControlInformationInCreateBearerRequestData;

typedef struct
{
	bool epsBearerIdIePresent;
	bool causeIePresent;
	bool s1USgwFTeidIePresent;
	bool s1UEnodebFTeidIePresent;
	bool s58USgwFTeidIePresent;
	bool s58UPgwFTeidIePresent;
	bool s12RncFTeidIePresent;
	bool s12SgwFTeidIePresent;
	bool s4USgsnFTeidIePresent;
	bool s4USgwFTeidIePresent;
	bool s2bUEpdgFTeidIePresent;
	bool s2bUPgwFTeidIePresent;
	bool s2aUTwanFTeidIePresent;
	bool s2aUPgwFTeidIePresent;
	bool protocolConfigurationOptionsIePresent;
	bool ranNasCauseIePresent;
	bool extendedProtocolConfigurationOptionsIePresent;
	
	EbiIeData epsBearerId;
	CauseIeData cause;
	FTeidIeData s1UEnodebFTeid;
	FTeidIeData s1USgwFTeid;
	FTeidIeData s58USgwFTeid;
	FTeidIeData s58UPgwFTeid;
	FTeidIeData s12RncFTeid;
	FTeidIeData s12SgwFTeid;
	FTeidIeData s4USgsnFTeid;
	FTeidIeData s4USgwFTeid;
	FTeidIeData s2bUEpdgFTeid;
	FTeidIeData s2bUPgwFTeid;
	FTeidIeData s2aUTwanFTeid;
	FTeidIeData s2aUPgwFTeid;
	PcoIeData protocolConfigurationOptions;
	RanNasCauseIeData ranNasCause;
	EpcoIeData extendedProtocolConfigurationOptions;
		
}BearerContextsInCreateBearerResponseData;


typedef struct
{
		
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
		
}MmeS4SgsnsOverloadControlInformationInCreateBearerResponseData;

typedef struct
{
		
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
		
}SgwsOverloadControlInformationInCreateBearerResponseData;

typedef struct
{
		
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
		
}TwanEpdgsOverloadControlInformationInCreateBearerResponseData;


 
typedef struct
{ 
	bool epsBearerIdIePresent;
	bool causeIePresent;
	
	EbiIeData epsBearerId;
	CauseIeData cause;
		
}FailedBearerContextsInDeleteBearerRequestData;  

 

typedef struct
{ 
	bool listOfApnAndRelativeCapacityIePresent;

	SequenceNumberIeData loadControlSequenceNumber;
	MetricIeData loadMetric;
	ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;

}PgwsNodeLevelLoadControlInformationInDeleteBearerRequestData;

typedef struct
{ 
	bool listOfApnAndRelativeCapacityIePresent;

	SequenceNumberIeData loadControlSequenceNumber;
	MetricIeData loadMetric;
	ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;

}SgwsNodeLevelLoadControlInformationInDeleteBearerRequestData;


typedef struct
{ 
	bool listOfApnAndRelativeCapacityIePresent;

	
	SequenceNumberIeData loadControlSequenceNumber;
	MetricIeData loadMetric;
	ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;

}PgwsApnLevelLoadControlInformationInDeleteBearerRequestData;


typedef struct
{ 
	bool listOfApnAndRelativeCapacityIePresent;
	
	SequenceNumberIeData loadControlSequenceNumber;
	MetricIeData loadMetric;
	ApnAndRelativeCapacityIeData listOfApnAndRelativeCapacity;

}SgwsApnLevelLoadControlInformationInDeleteBearerRequestData;


typedef struct
{ 

	bool listOfAccessPointNameIePresent;
	
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
	ApnIeData listOfAccessPointName;

}PgwsOverloadControlInformationInDeleteBearerRequestData;


typedef struct
{ 

	bool listOfAccessPointNameIePresent;
	
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
	ApnIeData listOfAccessPointName;

}SgwsOverloadControlInformationInDeleteBearerRequestData;


typedef struct
{ 
	bool epsBearerIdIePresent;
	bool causeIePresent;
	bool protocolConfigurationOptionsIePresent;
	bool ranNasCauseIePresent;
	bool extendedProtocolConfigurationOptionsIePresent;
	
	EbiIeData epsBearerId;
	CauseIeData cause;
	PcoIeData protocolConfigurationOptions;
	RanNasCauseIeData ranNasCause;
	EpcoIeData extendedProtocolConfigurationOptions;
}BearerContextsInDeleteBearerResponseData;


typedef struct
{ 
		
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
	
}MmeS4SgsnsOverloadControlInformationInDeleteBearerResponseData;

typedef struct
{ 

		
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
	
}SgwsOverloadControlInformationInDeleteBearerResponseData;

typedef struct
{ 
		
	SequenceNumberIeData overloadControlSequenceNumber;
	MetricIeData overloadReductionMetric;
	EpcTimerIeData periodOfValidity;
	
}TwanEpdgsOverloadControlInformationInDeleteBearerResponseData;



typedef struct
{ 
	SequenceNumberIeData loadControlSequenceNumber;
    MetricIeData loadMetric;
		
}SgwsNodeLevelLoadControlInformationInDownlinkDataNotificationData;  


typedef struct
{
    
  SequenceNumberIeData overloadControlSequenceNumber;
  MetricIeData overloadReductionMetric;
  EpcTimerIeData periodOfValidity;
  
}SgwsOverloadControlInformationInDownlinkDataNotificationData;


static const Uint8 BearerContextIeType = 93;
static const Uint8 RemoteUeContextIeType = 191;
static const Uint8 OverloadControlInformationIeType = 180;
static const Uint8 LoadControlInformationIeType = 181;


#endif
