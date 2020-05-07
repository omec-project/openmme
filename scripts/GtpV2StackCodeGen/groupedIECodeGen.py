# Copyright 2019-present Infosys Limited     
# SPDX-License-Identifier: Apache-2.0


import re
import os

from template import Template
from xlUtils import xlUtils,wb
templateData = {}
templateData['instList']=[]
grpIeDataTypeData={}
grpIeDataTypeData['grpList']=[]
grpIeDataTypeData['grpTypeList']=[]
class GenerateGrpIeClass():
    def __init__( self ):
        
        self.groupIEParser()
    
    def groupIEParser(self):
        
        
        sheet = wb['Grouped IE Modeling']
        state = ''
        
        data = {}
        grpIeData = {}
        currentGrpie = ''
        currentMsg = ''
        currentVar = ''
        currentInstance = ''
        currentInstanceValue = 0
        grpIeList = []
        ieDetailsList = []
        ieList = []
       
        for i in range(1,sheet.max_row+1):
            
            cell_value_B = xlUtils.getCellValue(sheet,i,'B')
            
            mGroupedIeDefStart = re.search('Grouped IE Definition Start:(\w+):(\d+):(\w+):(\w+):Instance\[(\d+)]',str(cell_value_B))
            mGroupedIeDefEnd = re.search('Grouped IE Definition End:(\w+):(\w+)',str(cell_value_B))
            
            if mGroupedIeDefStart:
                
                state = 'StartDetected'
                currentGrpie = mGroupedIeDefStart.group(1)
                currentMsg = mGroupedIeDefStart.group(4)
                currentVar = mGroupedIeDefStart.group(3)
                currentInstanceValue = mGroupedIeDefStart.group(5)
                currentInstance = currentVar + 'In' + currentMsg
                
                if currentGrpie not in grpIeList:
                     grpIeList.append(currentGrpie)
                     data['grpIeList'] = grpIeList
                data['grpIeDetails'] = {}
                data['grpIeDetails'][currentGrpie] = {}
                data['grpIeDetails'][currentGrpie]['ieTypeValue'] = mGroupedIeDefStart.group(2)
                data['grpIeDetails'][currentGrpie]['instList'] = []
                data['grpIeDetails'][currentGrpie]['instList'].append(currentInstance)
                data['grpIeDetails'][currentGrpie][currentInstance] = {}
                data['grpIeDetails'][currentGrpie][currentInstance]['instance'] = currentInstanceValue
                grpIeData = data['grpIeDetails'][currentGrpie][currentInstance]
                grpIeData['msgName'] = currentMsg
                
            elif mGroupedIeDefEnd:
                state = 'EndDetected'
                grpIeData = {} 
                ieList = []
                grpIeList=[]
                ieDetailsList = []
               
                GenerateGrpIeClass.generateGroupedIeClasses(data)
                GenerateGrpIeClass.prepareGrpIeMakeFile()
                
                
            elif state == 'StartDetected':
                state = 'IeListStart'
                
            elif state == 'IeListStart':
                
                if xlUtils.getCellValue(sheet,i,'D') != None:
                    ieData = {}
                    ieDescription = xlUtils.getCellValue(sheet,i,'D')
                    ieData['ieDescription'] = xlUtils.getCellValue(sheet,i,'D')
                    ieData['presence'] = xlUtils.getCellValue(sheet,i,'E')
                    ieData['grouped'] = xlUtils.getCellValue(sheet,i,'B')
                    ieData['cardinality'] = xlUtils.getCellValue(sheet,i,'C')
                    ieData['instance'] = xlUtils.getCellValue(sheet,i,'H') 
                    
                    if ieData['cardinality'] is None:
                        ieData['cardinality'] = 1 
                    ieTypeDescription = xlUtils.getCellValue(sheet,i,'G')
                    ieData['ieTypeDescription'] = ieTypeDescription
                    
                    ieVarName  = xlUtils.getVarNameFromString(ieDescription,0)
                    
                    ieTypeName  = xlUtils.getVarNameFromString(ieTypeDescription,1)
                    
                    if ieData['grouped'] == 'Yes':
                        ieData['ieGroupTypeName'] = ieVarName + 'In' + currentMsg
                        
                    ieData['ieVarName'] = ieVarName
                    ieData['ieTypeName'] = ieTypeName
                    
                    
                    ieList.append(ieVarName)
                    grpIeData['ieList'] = ieList
                    grpIeData['ieDetails'] = {}
                    grpIeData['ieDetails'][ieVarName] = ieData
                    ieDetailsList.append(grpIeData['ieDetails'])
                    grpIeData['ieDetails'] = ieDetailsList
                    
        
    def generateGroupedIeClasses(data):
        parsedData = data
        
        for grpIe in parsedData['grpIeList']:
            
            grpIeDetails = parsedData['grpIeDetails'][grpIe]
            
            GenerateGrpIeClass.generateGroupedIeClass(grpIeDetails,grpIe)
            GenerateGrpIeClass.generateGroupedIeDataType(grpIeDetails, grpIe)
    def generateGroupedIeClass(grpIeDetails,grpIe):
        
        templateData['fileName'] = grpIe[0].lower()+grpIe[1:] + 'Ie'
        templateData['className'] = grpIe + 'Ie'
        templateData['classNameUC'] = templateData['fileName'].upper()
        fileName=templateData['fileName']

        for inst in grpIeDetails['instList']:
            instanceInfo = {}
            instDetails  = grpIeDetails[inst]
            GenerateGrpIeClass.generateGroupedIeInstanceClass(instDetails, inst)
            
            instanceInfo['className'] = inst
            instanceInfo['fileName'] = inst[0].lower()+inst[1:]
            instanceInfo['msgType'] =  instDetails['msgName'] + 'MsgType'
            instanceInfo['instance'] = instDetails['instance']
            
            if instanceInfo not in templateData['instList']:
                templateData['instList'].append(instanceInfo)
            
        templateData[fileName]=[inst for inst in templateData['instList'] if grpIe in inst['className']]                
           
        outputDir = '../../src/gtpV2Codec/ieClasses'
        ttFileNameCpp = 'tts/grpietemplate.cpp.tt'
        ttFileNameH = 'tts/grpietemplate.h.tt'
        xlUtils.templateProcess(templateData,ttFileNameCpp,ttFileNameH,outputDir,outputDir)
        
        objectfile ='ieClasses/' + templateData['fileName'] + '.o'
        sourcefile = 'ieClasses/' + templateData['fileName'] + '.cpp'
        xlUtils.addToMakeSo('gtpV2Stack.so',objectfile,sourcefile)
    
    def generateGroupedIeDataType(grpIeDetails, grpIe):
        grpIeInfo={}
        
        grpIeInfo['iePresenceList']=[]
        grpIeTypeInfo={}
        grpIeTypeInfo['grpIeTypeName']=grpIe + 'IeType'
        grpIeTypeInfo['grpIeTypeValue']=grpIeDetails['ieTypeValue']
        if grpIeTypeInfo not in grpIeDataTypeData['grpTypeList']:
            grpIeDataTypeData['grpTypeList'].append(grpIeTypeInfo)
        
        for inst in grpIeDetails['instList']:
            
            instDetails  = grpIeDetails[inst]
            grpIeInfo={}
            grpIeInfo['iePresenceList']=[]
            grpIeInfo['grpIeName']= inst+'Data'
            grpIeInfo['ieList']=[]
            for ieDict in instDetails['ieDetails']:
                for ieDetails in ieDict:
                    if ieDict[ieDetails]['presence']!='M':
                        grpIeInfo['iePresenceList'].append(ieDict[ieDetails]['ieVarName']+'IePresent')
                    ieInfo={}
                    ieInfo['ieTypeName']=ieDict[ieDetails]['ieTypeName']+'IeData'
                    ieInfo['ieVarName']=ieDict[ieDetails]['ieVarName']
                    ieInfo['ieCardinality'] = ieDict[ieDetails]['cardinality']
                    ieInfo['grouped'] = ieDict[ieDetails]['grouped']
                    if ieInfo['grouped']=='Yes':
                        ieInfo['grpIeInstClassName'] =ieDict[ieDetails]['ieGroupTypeName'][0].upper()+ieDict[ieDetails]['ieGroupTypeName'][1:]
                       
                    grpIeInfo['ieList'].append(ieInfo)
        
        if grpIeInfo not in grpIeDataTypeData['grpList']:
            grpIeDataTypeData['grpList'].append(grpIeInfo)
        template = Template()
        ttFileNamefactoryH = 'tts/grpIeDataTypetemplate.h.tt'
        outputDir = '../../src/gtpV2Codec/ieClasses/'
        
        if not os.path.exists(outputDir):
            os.makedirs(outputDir)
        outputFileName = 'gtpV2GrpIeDataTypes.h'
        template.__init__({'OUTPUT' : outputFileName, 'OUTPUT_PATH' : outputDir})
        template.process(ttFileNamefactoryH, {'tempdata' : grpIeDataTypeData})
        
    def generateGroupedIeInstanceClass(instDetails, inst):
        templateInstData = {}
        ieTypeList = []
        ieTypeDetailsList = []
       
        ieInfoList =[]
       
        templateInstData['fileName'] = inst[0].lower()+inst[1:]
        
        templateInstData['msgClassName'] = inst
        templateInstData['classNameUC'] = templateInstData['fileName'].upper()
        templateInstData['msgType'] =  instDetails['msgName'] + 'MsgType'
        
        for ieEntry in instDetails['ieList']:
            
            ieInfo = {}
            ieTypeInfo = {}
            
            ies = instDetails['ieDetails']
            for x in ies:
                
                ie = x.get(ieEntry)
                
                if ie != None and ieEntry == ie.get('ieVarName'):
                    ieInfo['ieName'] =  ie['ieVarName']
                    ieInfo['ieVarName'] = ie['ieVarName']
                    ieInfo['ieType'] = ie['ieTypeName']
                    ieInfo['ieFileName'] = ie['ieTypeName'][0].lower()+ie['ieTypeName'][1:] + 'Ie'
                    ieInfo['ieLocalVar'] = ie['ieTypeName'][0].lower()+ie['ieTypeName'][1:]
                    ieInfo['iePresence'] = ie['presence']
                    ieInfo['ieCardinality'] = ie['cardinality']
                    ieInfo['instance'] = ie['instance']
                    ieInfo['grouped'] = ie['grouped']
                    if ieInfo['grouped']=='Yes':
                        ieInfo['grpIeInstClassName'] = ie['ieGroupTypeName'][0].upper()+ie['ieGroupTypeName'][1:]
                        ieInfo['grpIeInstFileName'] = ie['ieGroupTypeName']                   
                    ieType = ieInfo['ieType']
                    
                    ieTypeInfo['ieName'] =  ie['ieVarName']
                    ieTypeInfo['ieVarName'] = ie['ieVarName']
                    ieTypeInfo['ieType'] = ie['ieTypeName']
                    ieTypeInfo['ieFileName'] = ie['ieTypeName'][0].lower()+ie['ieTypeName'][1:] + 'Ie'
                    ieTypeInfo['ieLocalVar'] = ie['ieTypeName'][0].lower()+ie['ieTypeName'][1:]
                    ieTypeInfo['iePresence'] = ie['presence']
                    ieTypeInfo['ieCardinality'] = ie['cardinality']
                    ieTypeInfo['instance'] = ie['instance']
                    ieTypeInfo['grouped'] = ie['grouped']
                    if ieTypeInfo['grouped']=='Yes':
                        ieTypeInfo['grpIeInstClassName'] = ie['ieGroupTypeName'][0].upper()+ie['ieGroupTypeName'][1:]
                        ieTypeInfo['grpIeInstFileName'] = ie['ieGroupTypeName'].capitalize() 
                                       
                    if ieInfo['ieType'] not in ieTypeList:   
                        ieTypeList.append(ieInfo['ieType'])
                        templateInstData['ieTypeList'] = ieTypeList
                                        
                    if ieInfo not in ieInfoList:
                                              
                        ieInfoList.append(ieInfo)
                        templateInstData['ieList'] = ieInfoList
                    
                    templateInstData['ieTypeDetails'] = {}
                    templateInstData['ieTypeDetails'][ieType] = []
                    if ieTypeInfo not in templateInstData['ieTypeDetails'][ieType]:
                        templateInstData['ieTypeDetails'][ieType].append(ieTypeInfo)
                        ieTypeDetailsList.append(templateInstData['ieTypeDetails'])
                        templateInstData['ieTypeDetails'] = ieTypeDetailsList
      
        GenerateGrpIeClass.templateInstanceprocess(templateInstData)
        outputDirCpp = 'ieClasses/'
        objectfile = outputDirCpp +templateInstData['fileName'] + '.o'
        sourcefile = outputDirCpp + templateInstData['fileName'] + '.cpp'
        xlUtils.addToMakeSo('gtpV2Stack.so',objectfile,sourcefile)
        
    def templateInstanceprocess(templateInstData):
        
        ttFileNameInstCpp = 'tts/grpieinsttemplate.cpp.tt'
        outputDir = '../../src/gtpV2Codec/ieClasses'
        ttFileNameInstH = 'tts/grpieinsttemplate.h.tt'
        xlUtils.templateProcess(templateInstData,ttFileNameInstCpp,ttFileNameInstH,outputDir,outputDir)
            
    def prepareGrpIeMakeFile():
        outputDirCpp = 'ieClasses/manual/'
        xlUtils.addToMakeSo("gtpV2Stack.so", outputDirCpp+'gtpV2GroupedIe.o',outputDirCpp+'gtpV2GroupedIe.cpp')
                    
GenerateGrpIeClass()
