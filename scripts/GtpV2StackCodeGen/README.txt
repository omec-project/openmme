Requirements:
1.Python3.6.
2.Install the template-toolkit package.
	a. pip3 install Template-Toolkit-Python or 
	b. git clone https://github.com/lmr/Template-Toolkit-Python, and set the path of the package in the datatypeCodeGen.py,groupedIECodeGen.py,iECodeGen.py,msgCodeGen.py,xlUtils.py script [as argument in sys.path.append]

Inputs:
	1 Excel file with 4 spreadsheets:
		Message Modeling ,IE Modeling,Grouped IE Modeling and DataType Modeling: Defines the message structure,IEs,Grouped IEs and Datatype of IEs for the GTP classes to be generated . 
Output:
	1.	IE Classes .cpp and header files. 
	2.	Message Classes .cpp and header files.
	3.	gtpV2stack .cpp and header files
	4.	MakeFile


Remove all existing generated Files:
-Use below commands:
	rm ../../src/gtpV2Codec/ieClasses/*.cpp ../../src/gtpV2Codec/ieClasses/*.h;
	rm ../../src/gtpV2Codec/msgClasses/*.cpp ../../src/gtpV2Codec/msgClasses/*.h;
	rm ../../src/gtpV2Codec/Makefile;
Execution:
-Run the below command:
	python3 startCodeGen.py




