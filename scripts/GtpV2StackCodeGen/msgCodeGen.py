# Copyright 2019-present Infosys Limited     
# SPDX-License-Identifier: Apache-2.0


import re

import os
from template import Template


from xlUtils import xlUtils,wb
msgFactoryData = {}
msgFactoryData['msgList'] = []
msgDataTypeData = {}
msgDataTypeData['msgTypeList'] = []
msgDataTypeData['msgList'] = []
class GenerateMsgClass():
    def __init__( self ):
        self.msgParser()
    
    def msgParser(self):
        
        sheet = wb['Message Modeling']
        state = ''
        ieDetailList = []
        ieList = []
        
        currentMessage = ''
        msgValue = 0
        msgData = {}
        
        
        for i in range(1,sheet.max_row+1):
            
            cell_value_B = xlUtils.getCellValue(sheet,i,'B')
            
            mMsgDefinitionStart = re.search('Message Definition Start:(\w+):(\d+)',str(cell_value_B))
            mMsgDefinitionEnd = re.search('Message Definition End:(\w+)',str(cell_value_B))
            mResponseMsg = re.search('ResponseMessage',str(cell_value_B))
            mGrouped = re.search('Grouped',str(cell_value_B))
            
            
            if mMsgDefinitionStart:
                
                
                state = 'StartDetected'
                currentMessage = mMsgDefinitionStart.group(1)
                msgValue = mMsgDefinitionStart.group(2)
               
                
            if mMsgDefinitionEnd:
                
                ieList = []
                ieDetailList = []
                state = 'EndDetected'
                
                GenerateMsgClass.templateIes(msgData,currentMessage)
                GenerateMsgClass.generateMsgFactory(msgData,currentMessage)
                GenerateMsgClass.generateMsgDataType(msgData,currentMessage)
                GenerateMsgClass.prepareMsgMakeFile()
                
            elif state == 'StartDetected':
                
                msgData['msgDetails'] = {}
                msgData['msgDetails'][currentMessage] = {}
                msgData['msgDetails'][currentMessage]['msgValue'] = msgValue
                msgData['msgDetails'][currentMessage]['msgDataType'] = currentMessage + 'MsgData'
                msgData['msgDetails'][currentMessage]['msgCategory'] = "RequestMessage"
                if mResponseMsg:
                    
                    msgData['msgDetails'][currentMessage]['msgCategory'] = "ResponseMessage"
                elif mGrouped:
                    state = 'IeListStart'
                
                
                    
            elif state == 'IeListStart':
                
                if xlUtils.getCellValue(sheet,i,'D') != None:
                    
                    ieDescription  = xlUtils.getCellValue(sheet,i,'D')
                    presence = xlUtils.getCellValue(sheet,i,'E')
                    grouped = xlUtils.getCellValue(sheet,i,'B')
                    cardinality = xlUtils.getCellValue(sheet,i,'C')
                    instance = xlUtils.getCellValue(sheet,i,'H')
                    msgData['ieDetails'] = {}
                    msgData['ieDetails'][ieDescription] = {}
                    msgData['ieDetails'][ieDescription]['ieDescription'] = ieDescription
                    msgData['ieDetails'][ieDescription]['presence'] = presence
                    msgData['ieDetails'][ieDescription]['grouped'] = grouped
                    msgData['ieDetails'][ieDescription]['cardinality'] = cardinality
                    msgData['ieDetails'][ieDescription]['instance'] = instance
                    
                    if msgData['ieDetails'][ieDescription]['cardinality'] is None:
                        msgData['ieDetails'][ieDescription]['cardinality'] = 1
                    ieTypeDescription = xlUtils.getCellValue(sheet,i,'G')
                    msgData['ieDetails'][ieDescription]['ieTypeDescription'] = ieTypeDescription
                    
                    ieVarName = xlUtils.getVarNameFromString(ieDescription,0)
                    ieTypeName  = xlUtils.getVarNameFromString(ieTypeDescription,1)
                    ieVarName = ieVarName.replace('/','')
                    
                    msgData['ieDetails'][ieDescription]['ieGroupTypeName'] = ''
                    if msgData['ieDetails'][ieDescription]['grouped'] == 'Yes':
                        msgData['ieDetails'][ieDescription]['ieGroupTypeName'] = ieVarName + 'In' + currentMessage
                    msgData['ieDetails'][ieDescription]['ieVarName'] = ieVarName
                    msgData['ieDetails'][ieDescription]['ieTypeName'] = ieTypeName      
                               
                    if ieVarName!="privateExtension":
                        ieDetailList.append(msgData['ieDetails'])
                        
                        ieList.append(ieVarName)
                    msgData['ieList'] = ieList
                    msgData['ieDetails'] = ieDetailList
                      
        return msgData
    
    
    def templateIes(msgData,currentMessage):
        templateData = dict()
        ieListTemplate = []
        ieTypeTemplate = []
        ieTypeDetailList = []
        ieTypeList = []
        templateData['fileName'] = currentMessage[0].lower()+currentMessage[1:] + 'Msg'
        templateData['msgClassName'] = currentMessage[0].upper()+currentMessage[1:] + 'Msg'
        templateData['classNameUC'] = templateData['fileName'].upper()
        templateData['msgCategory'] = msgData['msgDetails'][currentMessage]['msgCategory']
        
        for ieDetail in msgData['ieDetails']:
            for key,value in ieDetail.items():
                for ie in msgData['ieList']:
                    ieInfo = {}
                    ieTypeInfo = {}
                    if value['ieVarName'] == ie:

                        ieInfo['ieName'] = value['ieVarName']
                        ieInfo['ieVarName'] = value['ieVarName']
                        ieInfo['ieType'] = value['ieTypeName']
                        ieInfo['ieFileName'] = value['ieTypeName'][0].lower()+value['ieTypeName'][1:] + 'Ie'
                        ieInfo['ieLocalVar'] = value['ieTypeName'][0].lower()+value['ieTypeName'][1:]
                        ieInfo['iePresence'] = value['presence']
                        ieInfo['ieCardinality'] = value['cardinality']
                        ieInfo['instance'] = value['instance']
                        ieInfo['grouped'] = value['grouped']
                        ieInfo['grpIeInstClassName'] = value['ieGroupTypeName']
                        if ieInfo['grouped']=='Yes':
                            ieInfo['grpIeInstClassName'] = value['ieGroupTypeName'][0].upper()+value['ieGroupTypeName'][1:]
                        ieInfo['grpIeInstFileName'] = value['ieGroupTypeName']
                        
                        ieType = ieInfo['ieType']
                        ieTypeInfo['ieName'] = value['ieVarName']
                        ieTypeInfo['ieVarName'] = value['ieVarName']
                        ieTypeInfo['ieType'] = value['ieTypeName']
                        ieTypeInfo['ieFileName'] = value['ieTypeName'][0].lower()+value['ieTypeName'][1:] + 'Ie'
                        ieTypeInfo['ieLocalVar'] = value['ieTypeName'].capitalize()
                        ieTypeInfo['iePresence'] = value['presence']
                        ieTypeInfo['ieCardinality'] = value['cardinality']
                        ieTypeInfo['instance'] = value['instance']
                        ieTypeInfo['grouped'] = value['grouped']
                        ieTypeInfo['grpIeInstClassName'] = value['ieGroupTypeName']
                        if ieTypeInfo['grouped']=='Yes':
                            ieTypeInfo['grpIeInstClassName'] = value['ieGroupTypeName'][0].upper()+value['ieGroupTypeName'][1:]
                        ieTypeInfo['grpIeInstFileName'] = value['ieGroupTypeName'].capitalize()
                        
                       
                        ieListTemplate.append(ieInfo)
                        templateData['ieList'] = ieListTemplate
                       
                        if ieInfo['ieType'] not in ieTypeList:   
                            ieTypeList.append(ieInfo['ieType'])
                            templateData['ieTypeList'] = ieTypeList
                            
                        ieTypeTemplate = []
                        ieTypeTemplate.append(ieTypeInfo)
                        templateData['ieTypeDetails'] = {}   
                        templateData['ieTypeDetails'][ieType] = ieTypeTemplate
                        
                        ieTypeDetailList.append(templateData['ieTypeDetails'])
                        templateData['ieTypeDetails'] = ieTypeDetailList
        
        outputDir = '../../src/gtpV2Codec/msgClasses'
        ttFileNameCpp = 'tts/msgtemplate.cpp.tt'
        ttFileNameH = 'tts/msgtemplate.h.tt'
        xlUtils.templateProcess(templateData,ttFileNameCpp,ttFileNameH,outputDir,outputDir)
        
        objectFile = 'msgClasses/' +templateData['fileName'] + '.o'
        sourceFile = 'msgClasses/' + templateData['fileName'] + '.cpp'
        xlUtils.addToMakeSo('gtpV2Stack.so',objectFile,sourceFile)
       
    def generateMsgFactory(msgData,currentMessage):
        msgInfo = {}
        
        msgInfo['className'] = currentMessage + 'Msg'
        msgInfo['msgFileName'] = currentMessage[0].lower()+currentMessage[1:] + 'Msg'
        msgInfo['dataMember'] = currentMessage[0].lower()+currentMessage[1:] + 'StackData'
        if msgInfo not in msgFactoryData['msgList']:
            msgFactoryData['msgList'].append(msgInfo)
        outputDirCpp = 'msgClasses/'
        GenerateMsgClass.msgfactoryStacktemplate(msgFactoryData)
        xlUtils.addToMakeSo('gtpV2Stack.so',outputDirCpp+'gtpV2MsgFactory.o',outputDirCpp+'gtpV2MsgFactory.cpp')
        xlUtils.addToMakeSo('gtpV2Stack.so','gtpV2Stack.o','gtpV2Stack.cpp')
        
    def msgfactoryStacktemplate(msgFactoryData):
 
        ttFileNamefactoryCpp = 'tts/msgfactorytemplate.cpp.tt'
        outputDir = '../../src/gtpV2Codec/msgClasses'   
        msgFactoryData['fileName'] = 'gtpV2MsgFactory'
        ttFileNamefactoryH = 'tts/msgfactorytemplate.h.tt'
        xlUtils.templateProcess(msgFactoryData,ttFileNamefactoryCpp,ttFileNamefactoryH,outputDir,outputDir)
        
        ttFileNameStackCpp = 'tts/stacktemplate.cpp.tt'
        outputDir = '../../src/gtpV2Codec/'
        msgFactoryData['fileName'] = 'gtpV2Stack' 
        ttFileNameStackH = 'tts/stacktemplate.h.tt'

        xlUtils.templateProcess(msgFactoryData,ttFileNameStackCpp,ttFileNameStackH,outputDir,outputDir)
        
        
      
    def prepareMsgMakeFile():
        outputDir = 'msgClasses/manual/'
        xlUtils.addToMakeSo('gtpV2Stack.so', outputDir+'gtpV2Message.o', outputDir+'gtpV2Message.cpp')
    def generateMsgDataType(msgData,currentMessage):
        msginfo = {}
        msgTypeInfo={}    
        msginfo['msgDataName'] = currentMessage + 'MsgData'
        msginfo['ieDetails']=[]
        msgTypeInfo['msgDataType']=currentMessage + 'MsgType'
        msgTypeInfo['msgValue']=msgData['msgDetails'][currentMessage]['msgValue']
        
        if  msgTypeInfo not in msgDataTypeData['msgTypeList']:
            msgDataTypeData['msgTypeList'].append(msgTypeInfo)
        
        for ieDetail in msgData['ieDetails']:
            for key,value in ieDetail.items():
                for ie in msgData['ieList']:
                    ieInfo = {}
                    
                    if value['ieVarName'] == ie:
                        ieInfo['ieName'] = value['ieVarName']
                        ieInfo['ieVarName'] = value['ieVarName']
                        ieInfo['ieType'] = value['ieTypeName']
                        ieInfo['iePresence'] = value['presence']
                        ieInfo['ieCardinality'] = value['cardinality']
                        ieInfo['grouped'] = value['grouped']
                        ieInfo['grpIeInstClassName'] = value['ieGroupTypeName']
                        if ieInfo['grouped']=='Yes':
                            ieInfo['grpIeInstClassName'] = value['ieGroupTypeName'][0].upper()+value['ieGroupTypeName'][1:]
                        ieInfo['grpIeInstFileName'] = value['ieGroupTypeName']
                        if ieInfo not in msginfo['ieDetails']:
                            msginfo['ieDetails'].append(ieInfo)
        if msginfo not in msgDataTypeData['msgList']:
            msgDataTypeData['msgList'].append(msginfo)
                        
        template = Template()
        ttFileNamefactoryH = 'tts/msgDataTypetemplate.h.tt'
        outputDir = '../../src/gtpV2Codec/msgClasses'
        
        if not os.path.exists(outputDir):
            os.makedirs(outputDir)
        outputFileName = 'gtpV2MsgDataTypes.h'
        template.__init__({'OUTPUT' : outputFileName, 'OUTPUT_PATH' : outputDir})
        template.process(ttFileNamefactoryH, {'tempdata' : msgDataTypeData})
    
        
GenerateMsgClass()