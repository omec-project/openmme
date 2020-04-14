# Copyright 2019-present Infosys Limited     
# SPDX-License-Identifier: Apache-2.0


import re
from template import Template
import os
from xlUtils import xlUtils,wb
dataTypeData={}
dataTypeData['arrayTypeList']=[]
dataTypeData['DataTypeListAuto']=[]
class GenerateDataTypeClass():
    def __init__( self ):
        self.templateDataTypes()  

        
    def templateDataTypes(self):
        typeDataTemplate = GenerateDataTypeClass.dataTypeParser()
        
        templateData = dict()
        sequenceList = []
        dataTypeListAuto = []
        arrayTypeInfoList = []
        dataTypeListManual = []
        templateData['className'] = 'DataTypeCodecUtils'
        templateData['fileName'] = templateData['className'][0].lower()+templateData['className'][1:]
        templateData['classNameUC'] = templateData['className'].upper()
        
        #building the dictionary obtained to a dict 'templateData'
        #which is the input to template process 
        for typeNames in typeDataTemplate['DataTypeList']:
            myData = {}
            sequenceList = []
            
            
            myData['typeName'] = typeNames
            for typeDetails in typeDataTemplate['typeDetails']:
                if typeNames in typeDetails:
                    myTypeData = typeDetails[typeNames]
                   
                    for varDetails in myTypeData['varDetails']:
                     
                        for key,value in varDetails.items():
                            for en in myTypeData['encodeSeq']:
                               
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
                                        if value['presence'] == 'optional':
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
                                        mArrayUint = re.search('^(\w+)Array(\d+)$',value['varType'])
                                        if mArrayUint :
                                
                                            item['arrayType'] = 'y'
                                            
                                            item['count'] =0
                                                
                                        if value['validation'] != '':
                    
                                            item['validationPresent'] = 'y'
                                            item['validationRule'] = value['validation']
                    
                                if item not in sequenceList and item!={}:
                                    sequenceList.append(item)
                                    
               
            
            for arrayLists in typeDataTemplate['ArrayTypeList']:
                arrayTypeInfo = {} 
                
                if typeNames in arrayLists:
                       
                    arrayType = arrayLists[typeNames]
                    arrayTypeInfo['typeName'] = arrayType['arrayTypeName']
                    arrayTypeInfo['subType'] = arrayType['arraySubType']
                    mArraySubType = re.search('^Uint\d+$',arrayTypeInfo['subType'])
                    if mArraySubType:
                        arrayTypeInfo['leafType'] = 'y'
                    
                    arrayTypeInfoList.append(arrayTypeInfo)
                        
            for dataCodecManual in typeDataTemplate['DataTypeCodecList']:
                if typeNames == dataCodecManual:
                    dataTypeListManual.append(myData)
                    
            
            
            if sequenceList != []:
                myData['sequence'] = sequenceList
                dataTypeListAuto.append(myData)
                
          
                   
        templateData['arrayTypeList'] = arrayTypeInfoList
        templateData['DataTypeListManual'] = dataTypeListManual
        templateData['DataTypeListAuto'] = dataTypeListAuto  
        
        GenerateDataTypeClass.generateDataType(templateData) 
        outputDir = '../../src/gtpV2Codec/ieClasses'  
        ttFileNameCpp = 'tts/datatypetemplate.cpp.tt'
        ttFileNameH = 'tts/datatypetemplate.h.tt'
        xlUtils.templateProcess(templateData,ttFileNameCpp,ttFileNameH,outputDir,outputDir)
       
    #Parse the data from excel sheet 'DataType Modeling' 
    #and build to a dict 'typeData'
    def dataTypeParser():
        
        sheet = wb['DataType Modeling']
        state = ''
        typeData = {}
        encodeSeq = []
        varDetailList = []
        dataTypeList = []
        dataTypeCodecList = []
        arrayTypeList = []
        typeDataList = []
        currentType = ''
        currentDataType = ''
        varType = ''
        decodeCondition = ''
        encodeCondition = ''
        validation = ''
        bitLength = 0
        byteLength = 0
        lengthStr = ''
        presence = ''
        dataType = {}
        
        for i in range(1,sheet.max_row+1):
            cell_value_B = xlUtils.getCellValue(sheet,i,'B')
            
            # Search pattern for data definition start,end 
            mDataDefineStartCodec = re.search('DataType Definition Start:(\w+):Codec\[Manual\]\s*$',str(cell_value_B))
            mArrayDefine = re.search('ArrayTypes Definition:([\w\d]*)Array(\d+)',str(cell_value_B))
            mDataDefineStart = re.search('DataType Definition Start:(\w+)',str(cell_value_B))
            mDataDefineEnd = re.search('DataType Definition End:(\w+)',str(cell_value_B))
            if mDataDefineStartCodec:
                currentType = mDataDefineStartCodec.group(1)
                currentDataType = currentType
                dataTypeCodecList.append(currentDataType)
                typeData['DataTypeCodecList'] = dataTypeCodecList
                dataTypeList.append(currentDataType)
                typeData['DataTypeList'] = dataTypeList
                continue
            
            if mArrayDefine:
                
                arraySubType = mArrayDefine.group(1)
                arrayCount = mArrayDefine.group(2)
                arrayTypeName = arraySubType + 'Array' + arrayCount
                typeData['ArrayTypeList'] = {}
                typeData['ArrayTypeList'][arrayTypeName] = {}
                typeData['ArrayTypeList'][arrayTypeName]['arrayTypeName'] = arrayTypeName
                typeData['ArrayTypeList'][arrayTypeName]['arraySubType'] = arraySubType
                typeData['ArrayTypeList'][arrayTypeName]['arrayCount'] = arrayCount
                arrayTypeList.append(typeData['ArrayTypeList'])
                typeData['ArrayTypeList'] = arrayTypeList
                dataTypeList.append(arrayTypeName)
                typeData['DataTypeList'] = dataTypeList
                continue
            
            if mDataDefineStart:
                currentType = mDataDefineStart.group(1)
                currentDataType = currentType
                
                state = 'StartDetected'
                dataTypeList.append(currentDataType)
                typeData['DataTypeList'] = dataTypeList
                typeData['typeDetails'] = {}
                typeData['typeDetails'][currentDataType] = {}
                dataType = typeData['typeDetails'][currentDataType]
                typeData['typeDetails'][currentDataType]['typeName'] = currentType
                typeDataList.append(typeData['typeDetails'])
                typeData['typeDetails'] = typeDataList
                
            elif mDataDefineEnd:
                state = 'EndDetected'
               
            elif state == 'StartDetected':
                encodeSeq = []
                varDetailList = []
                state = 'TypeDefinitionStart'
            elif state == 'TypeDefinitionStart':
                (byteLength,lengthStr) = xlUtils.getByteLength(sheet,i)
                
                #for fields less than 1 bytelength
                
                if byteLength == 0:
                   varList = []
                   
                   for j in map(chr, range( ord('D'), ord('L'))):
                       field = xlUtils.getCellValue(sheet,i,j)
                       bitLength = 0
                       byteLength = 0
                       if field != None:
                           
                           bitLength = xlUtils.getBitLength(sheet,i,j) 
                           (varName,varType,encodeCondition,decodeCondition,validation,count) = xlUtils.extractField(field)
                           
                           if varType == '':
                               varType = 'Uint8'
                           if bitLength == 8:
                               byteLength = 1
                               bitLength = 0        
                           if varName != 'Spare':
                               varList.append(varName)
                            
                               dataType['varDetails'] = {}
                               dataType['varDetails'][varName] = {}
                               dataType['varDetails'][varName]['varType'] = varType
                               dataType['varDetails'][varName]['decodeCondition'] = decodeCondition
                               dataType['varDetails'][varName]['encodeCondition'] = encodeCondition
                               dataType['varDetails'][varName]['validation'] = validation
                               dataType['varDetails'][varName]['bitLength'] = bitLength
                               dataType['varDetails'][varName]['byteLength'] = byteLength
                               dataType['varDetails'][varName]['lengthStr'] = lengthStr
                               dataType['varDetails'][varName]['presence'] = presence
                               
                               encStrBit = 'encode:' + varName + ':' + str(bitLength) + ':Bits'
                               encodeSeq.append(encStrBit)
                               dataType['encodeSeq'] = encodeSeq
                               varDetailList.append(dataType['varDetails'])
                               dataType['varDetails'] = varDetailList
                               
                               
                               
                               
                           else:
                               skipStrBit = 'skip:'+ str(bitLength) + ':Bits'
                               encodeSeq.append(skipStrBit)
                               dataType['encodeSeq'] = encodeSeq
                               
                #for fields of length 1 byte
                else:
                    varList = []
                    
                    field = sheet.cell(row=i, column=4).value
                    (varName,varType,encodeCondition,decodeCondition,validation,count) = xlUtils.extractField(field)
                    
                    if varType == '':
                        varType = xlUtils.lengthToType(byteLength)
                
                    if varName != 'Spare':
                        varList.append(varName)
                        
                        
                        dataType['varDetails'] = {}
                        dataType['varDetails'][varName] = {}
                        dataType['varDetails'][varName]['varType'] = varType
                        dataType['varDetails'][varName]['decodeCondition'] = decodeCondition
                        dataType['varDetails'][varName]['encodeCondition'] = encodeCondition
                        dataType['varDetails'][varName]['validation'] = validation
                        dataType['varDetails'][varName]['bitLength'] = bitLength
                        dataType['varDetails'][varName]['byteLength'] = byteLength
                        dataType['varDetails'][varName]['lengthStr'] = lengthStr
                        bitLength = 0
                        byteLength = 0
                        
                        if str(cell_value_B) == 'Yes':
                             presence = 'optional'  
                        dataType['varDetails'][varName]['presence'] = presence
                        varDetailList.append(dataType['varDetails'])
                        dataType['varDetails'] = varDetailList
                        
                        encStrByte = 'encode:' + varName + ':' + str(byteLength) + ':Bytes'
                        encodeSeq.append(encStrByte)
                        dataType['encodeSeq'] = encodeSeq
                        
                    else:
                        skipStrByte = 'skip:'+ str(byteLength) + ':Bytes'
                        encodeSeq.append(skipStrByte)
                        dataType['encodeSeq'] = encodeSeq
                        
        return typeData    
        
    def generateDataType(templateData):
        dataTypeInfo={}
        dataTypeData['arrayTypeList']=[]
        for dataType in templateData['arrayTypeList']:
            dataTypeInfo={}
            dataTypeInfo['typeName']=dataType['typeName']
            dataTypeInfo['subType']=dataType['subType']
            mtypeName = re.search('^(\w+)Array(\d+)$',dataTypeInfo['typeName'])
            if mtypeName:
                
                dataTypeInfo['arraySize']=mtypeName.group(2)
            dataTypeData['arrayTypeList'].append(dataTypeInfo)
        dataTypeData['DataTypeListAuto']=templateData['DataTypeListAuto']
        
        
        template = Template()
        ttFileNamefactoryH = 'tts/v2DataTypetemplate.h.tt'
        outputDir = '../../src/gtpV2Codec/ieClasses'
        
        if not os.path.exists(outputDir):
            os.makedirs(outputDir)
        outputFileName = 'gtpV2DataTypes.h'
        template.__init__({'OUTPUT' : outputFileName, 'OUTPUT_PATH' : outputDir})
        template.process(ttFileNamefactoryH, {'tempdata' : dataTypeData})
        
GenerateDataTypeClass()
