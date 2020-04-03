# Copyright 2019-present Infosys Limited     
# SPDX-License-Identifier: Apache-2.0


import re
import os
from template import Template
from xlUtils import xlUtils,wb

ieFactoryData = {}
ieFactoryData['ieList'] = []

ieDataTypeData = {}
ieDataTypeData['ieTypeList'] = []
ieDataTypeData['ieList'] = []
class GenerateIeClass:
    
    def __init__( self ):
        
        self.ieParser()
    
    #Parse the data from excel sheet 'IE Modeling' 
    #and build to a dict 'iedata'
    def ieParser(self):
        
        sheet = wb['IE Modeling']
        state = ''
        
        encodeSeq = []
        byteLength = 0
        currentType = ''
        validation = ''
        count = ''
        decodeCondition = ''
        encodeCondition = ''
        typeVal = ''
        presence = ''
        bitLength = 0        
        varDetailList = []
        ieData = dict()         
        ieTypeList = []
        lengthStr = ''        
        varType = ''
        varName = ''
        mType=0
        varList=[]
        grpIeList = []
        
        for i in range(1,sheet.max_row+1):
            presence = ''
            bitLength = 0
            byteLength = 0
            cell_value_B = xlUtils.getCellValue(sheet,i,'B')
            cell_value_D = xlUtils.getCellValue(sheet,i,'D')
            cell_value_H = xlUtils.getCellValue(sheet,i,'H')
            
            # Search pattern for IE definition start,end 
            mGroupedIe = re.search('Grouped IE Definition:(\w+)',str(cell_value_B))
            mIeDefStart = re.search('IE Definition Start:(\w+)',str(cell_value_B))
            mIeDefEnd = re.search('IE Definition End:(\w+)' ,str(cell_value_B))
             
            if mGroupedIe:
                
                grpIeName = mGroupedIe.group(1)
                grpIeList.append(grpIeName)
                for grpie in grpIeList:
                    self.generateIeFactory(grpie)
                
            if mIeDefStart:
                currentType = mIeDefStart.group(1)
                state = 'StartDetected'
                ieTypeList.append(currentType)
                
            elif mIeDefEnd:
                
                state = 'EndDetected' 
                self.templateIes(ieData,currentType)
                self.generateIeFactory(currentType)
                self.generateIeDataType(currentType,typeVal,varList)
                self.prepareIeMakeFile()
                varList = []
                
            elif state == 'StartDetected':
                varDetailList = []
                encodeSeq = []
                
                colDValue = str(cell_value_D)
                mType = re.search('Type = (\d+)',colDValue)
                mSpare = re.search('Spare',colDValue)
                mInstance = re.search('Instance',str(cell_value_H))
                
                if mType:
                    typeVal = mType.group(1)
                    ieData['ieDetails'] = {}
                    ieData['ieDetails'][currentType] = {}
                    ieData['ieDetails'][currentType]['ieName'] = currentType
                    ieData['ieDetails'][currentType]['ieTypeVal'] = typeVal
                    
                if mSpare and mInstance:
                    state = 'TypeDefinitionStart'
                                    
            elif state == 'TypeDefinitionStart':
                
                (byteLength,lengthStr) = xlUtils.getByteLength(sheet,i)
                
                #for fields less than 1 bytelength
                if byteLength == 0:
                    
                   for j in map(chr, range( ord('D'), ord('L'))):
                       field = xlUtils.getCellValue(sheet,i,j)
                       fieldDetails=dict()
                       if field != None:
                           
                           bitLength = xlUtils.getBitLength(sheet,i,j) 
                           (varName,varType,encodeCondition,decodeCondition,validation,count) = xlUtils.extractField(field)
                           
                           if varType == '':
                               varType = 'Uint8'
                           if bitLength == 8:
                               byteLength = 1
                               bitLength = 0        
                           if varName != 'Spare':
                               fieldDetails['varName']=varName
                               fieldDetails['varType']=varType
                               fieldDetails['presence']=presence
                               varList.append(fieldDetails)
                              
                               ieData['varDetails'] = {}
                               ieData['varDetails'][varName] = {}
                               ieData['varDetails'][varName]['varType'] = varType
                               ieData['varDetails'][varName]['decodeCondition'] = decodeCondition
                               ieData['varDetails'][varName]['encodeCondition'] = encodeCondition
                               ieData['varDetails'][varName]['validation'] = validation
                               ieData['varDetails'][varName]['bitLength'] = bitLength
                               ieData['varDetails'][varName]['byteLength'] = byteLength
                               ieData['varDetails'][varName]['lengthStr'] = lengthStr
                               ieData['varDetails'][varName]['presence'] = presence
                               ieData['varDetails'][varName]['count'] = count
                               varDetailList.append(ieData['varDetails'])
                               ieData['varDetails'] = varDetailList
                               
                               encStrBit = 'encode:' + varName + ':' + str(bitLength) + ':Bits'
                               encodeSeq.append(encStrBit)
                               ieData['encodeSeq'] = encodeSeq
                               
                           else:
                               skipStrBit = 'skip:'+ str(bitLength) + ':Bits'
                               encodeSeq.append(skipStrBit)
                               ieData['encodeSeq'] = encodeSeq
                
                #for fields of length 1 byte
                else:
                                        
                    field = sheet.cell(row=i, column=4).value
                    (varName,varType,encodeCondition,decodeCondition,validation,count) = xlUtils.extractField(field)
                    fieldDetails=dict()
                    if varType == '':
                        varType = xlUtils.lengthToType(byteLength)
                
                    if varName != 'Spare':
                        fieldDetails['varName']=varName
                        fieldDetails['varType']=varType
                        if xlUtils.getCellValue(sheet,i,'B') == 'Yes':
                             presence = 'optional'
                        fieldDetails['presence']=presence
                        varList.append(fieldDetails)
                                              
                        ieData['varDetails'] = {}
                        ieData['varDetails'][varName] = {}
                        ieData['varDetails'][varName]['varType'] = varType
                        ieData['varDetails'][varName]['decodeCondition'] = decodeCondition
                        ieData['varDetails'][varName]['encodeCondition'] = encodeCondition
                        ieData['varDetails'][varName]['validation'] = validation
                        ieData['varDetails'][varName]['bitLength'] = bitLength
                        ieData['varDetails'][varName]['byteLength'] = byteLength
                        ieData['varDetails'][varName]['lengthStr'] = lengthStr
                        ieData['varDetails'][varName]['count'] = count
                                           
                        if xlUtils.getCellValue(sheet,i,'B') == 'Yes':
                             presence = 'optional' 
                             
                             ieData['varDetails'][varName]['presence'] = presence
                        varDetailList.append(ieData['varDetails'])
                        ieData['varDetails'] = varDetailList
                        
                        encstrbyte = 'encode:' + varName + ':' + str(byteLength) + ':Bytes'
                        encodeSeq.append(encstrbyte)
                        ieData['encodeSeq'] = encodeSeq
                    else:
                        skipstrbyte = 'skip:'+ str(byteLength) + ':Bytes'
                        encodeSeq.append(skipstrbyte)
                        ieData['encodeSeq'] = encodeSeq    
        return ieData    
    
    def templateIes(self,ieData,currentType):
        
        templateData = dict()  
        varDetailsList = []
        sequenceList = []
        varDetailsList = ieData['varDetails']
        templateData['className'] = ieData['ieDetails'][currentType]['ieName']+'Ie'
        templateData['fileName'] = templateData['className'][0].lower() + templateData['className'][1:] 
        templateData['classNameUC'] = templateData['className'].upper()
        templateData['ieTypeVal'] = ieData['ieDetails'][currentType]['ieTypeVal']
        
        #building the dictionary obtained to a dict 'templateData'
        #which is the input to template process 
        
        for en in ieData['encodeSeq']:   
            mEncode = re.search('encode:(\w+):',en)
            mSkip = re.search('skip:(\d+):(\w+)',en)
            item = dict()
            if mSkip:
                bitByte = mSkip.group(2)
                skipValue = mSkip.group(1)
                item['skipType'] = 'y'
                item['bitByte'] = bitByte
                item['skipValue'] = skipValue
            elif mEncode:
                varName = mEncode.group(1)
                for variableDetails in varDetailsList:
                    for key,value in variableDetails.items():
                        if key == varName:
                            item['fieldName'] = varName
                            if value['bitLength'] != 0:
                                item['bitField'] = 'y'
                                item['fieldSize'] = value['bitLength']
                                item['leafType'] = 'y'
                            else:
                                item['fieldSize'] = value['byteLength']
                            if value['decodeCondition'] != '':
                                item['decodeConditional'] = 'y'
                                item['decodeCondition'] = value['decodeCondition']
                            if value['encodeCondition'] != '':
                                item['encodeConditional'] = 'y'
                                item['encodeCondition'] = value['encodeCondition']
                            if value.get('presence') == 'optional':
                                item['presence'] = 'optional'
                            item['fieldType'] = value['varType']
                            mUint = re.search('^Uint(\d+)$',value['varType'])
                            if mUint or value['varType'] == 'bool':
                                item['leafType'] = 'y'                    
                            else:
                                if value['lengthStr'] == 'EOI' or value['lengthStr'] == '':
                                    item['length'] = 'lengthLeft'
                                else:
                                    item['length'] = value['lengthStr']
                            if value['validation'] != '':
                    
                                item['validationPresent'] = 'y'
                                item['validationRule'] = value['validation']
                            mArray = re.search('Array',value['varType'])
                            if mArray:
                                item['arrayType']='y'
                                if value['count'] =='':
                                    item['count']=0
                                else:
                                    item['count']=value['count']
                                
            if  item != {}:
                sequenceList.append(item)
                templateData['sequence'] = sequenceList
   
        outputDir = '../../src/gtpV2Codec/ieClasses'
        ttFileNameCpp = 'tts/ietemplate.cpp.tt'
        ttFileNameH = 'tts/ietemplate.h.tt'
        xlUtils.templateProcess(templateData,ttFileNameCpp,ttFileNameH,outputDir,outputDir)
        
        objectFile = 'ieClasses/' +templateData['fileName'] + '.o'
        sourceFile ='ieClasses/' + templateData['fileName'] + '.cpp'
        xlUtils.addToMakeSo('gtpV2Stack.so',objectFile,sourceFile)
       
    def ieFactoryTemplate(self,ieFactoryData):
        
        ieFactoryData['fileName']='gtpV2IeFactory'
        ttFileNameFactoryCpp = 'tts/iefactorytemplate.cpp.tt'
        outputDir = '../../src/gtpV2Codec/ieClasses'
        ttFileNamefactoryH = 'tts/iefactorytemplate.h.tt'
        xlUtils.templateProcess(ieFactoryData,ttFileNameFactoryCpp,ttFileNamefactoryH,outputDir,outputDir)
        
    def generateIeFactory(self,currentType):
        ieinfo = {}
        ieinfo['className'] = currentType + 'Ie'
        ieinfo['ieFileName'] = currentType[0].lower()+currentType[1:] + 'Ie'
        if ieinfo not in ieFactoryData['ieList']:
            ieFactoryData['ieList'].append(ieinfo)
        outputDir = 'ieClasses/'
        self.ieFactoryTemplate(ieFactoryData)
        xlUtils.addToMakeSo('gtpV2Stack.so',outputDir+'gtpV2IeFactory.o',outputDir+'gtpV2IeFactory.cpp')
        
    def generateIeDataType(self,currentType,typeVal,varList):
        ieinfo = {}
        ieTypeInfo={}    
        ieinfo['ieName'] = currentType + 'IeData'
        ieinfo['varList'] = varList
        ieTypeInfo['ieName']=currentType + 'IeType'
        ieTypeInfo['value']=typeVal
        if ieinfo not in ieDataTypeData['ieList']:
            ieDataTypeData['ieList'].append(ieinfo)
        if ieTypeInfo not in ieDataTypeData['ieTypeList']:
            ieDataTypeData['ieTypeList'].append(ieTypeInfo)
        #print(ieDataTypeData)
        template = Template()
        ttFileNamefactoryH = 'tts/ieDataTypetemplate.h.tt'
        outputDir = '../../src/gtpV2Codec/ieClasses'
        
        if not os.path.exists(outputDir):
            os.makedirs(outputDir)
        outputFileName = 'gtpV2IeDataTypes.h'
        template.__init__({'OUTPUT' : outputFileName, 'OUTPUT_PATH' : outputDir})
        template.process(ttFileNamefactoryH, {'tempdata' : ieDataTypeData})
        
    def prepareIeMakeFile(self):
        outputDir = 'ieClasses/'
        xlUtils.addToMakeSo('gtpV2Stack.so', outputDir+'dataTypeCodecUtils.o', outputDir+'dataTypeCodecUtils.cpp')
        xlUtils.addToMakeSo('gtpV2Stack.so', outputDir+'manual/gtpV2Ie.o', outputDir+'manual/gtpV2Ie.cpp')
        
GenerateIeClass()
