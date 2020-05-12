# 
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
# 

import json, sys, os
from os.path import join
import utils

with open('dataModels/stateMachineAppModel.json') as jsonFile:
    stateMachineAppModelJSON = json.load(jsonFile)
with open('dataModels/ctxtManagerAppModel.json') as jsonFile:
    contextMgrAppModelJSON = json.load(jsonFile)

def processTemplate(templateIp):
    from template import Template
    
    utils.outputFileName = ''
    if utils.outputFileKeyword != '':
        utils.outputFileName = utils.getFileName(templateIp[utils.outputFileKeyword])    
    if utils.outputFile != '':
        utils.outputFileName = utils.outputFileName + utils.outputFile
    
    utils.outputFileName = utils.outputFileName + utils.outputFileExt

    tt = Template({'EVAL_PYTHON':1, 'AUTO_RESET':1})
    op = tt.process(utils.ttFileName, {'TemplateInputVar' : templateIp})
    utils.WriteFile(utils.outputDir, utils.outputFileName, op, utils.mode)

def getTemplateIn(appModelItems, depth):
    depthChanged = False

    if (depth == 0):
        print(appModelItems)
        processTemplate(appModelItems)
        return
    
    if depthChanged == False:
        depth = depth - 1
        depthChanged = True
        
    for item in appModelItems:
        getTemplateIn(item, depth)
      
def genCppCode(genModel, appModelJSON):
    for item in genModel:
        keyWord = item["appModelKeyword"]
        depth = item["appModelValueDepth"]
        utils.ttFileName = item["templateFile"]
        utils.outputDir = item["outputPath"]
        utils.outputFile = item["outputFile"]
        utils.outputFileKeyword = item["outputFileKey"]
        utils.outputFileExt = item["outputFileExt"]
        utils.mode = item["mode"]
        
        if not os.path.exists(utils.outputDir):
            os.makedirs(utils.outputDir)
        
        appModelItems = utils.get_key_values(appModelJSON, keyWord) 
        getTemplateIn(appModelItems, depth)
            
with open('dataModels/generationItem.json') as JSONFile:
    GenItemJSON = json.load(JSONFile)
    if 'Model1' in GenItemJSON:
        genCppCode(GenItemJSON['Model1'], stateMachineAppModelJSON)
    if "Model2" in GenItemJSON:
        genCppCode(GenItemJSON['Model2'], contextMgrAppModelJSON)
    
