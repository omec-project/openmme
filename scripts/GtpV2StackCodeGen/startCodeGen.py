
# Copyright 2019-present Infosys Limited     
# SPDX-License-Identifier: Apache-2.0   

from iECodeGen import GenerateIeClass
from datatypeCodeGen import GenerateDataTypeClass
from xlUtils import xlUtils
from msgCodeGen import GenerateMsgClass
from groupedIECodeGen import GenerateGrpIeClass

GenerateIeClass()
GenerateDataTypeClass()
GenerateMsgClass()
GenerateGrpIeClass()

xlUtils.generateMakeFile()
