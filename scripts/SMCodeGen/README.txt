Requirements:
1.Python3.6.
2.Install the template-toolkit package.
	a. pip install Template-Toolkit-Python or 
	b. git clone https://github.com/lmr/Template-Toolkit-Python, and set the path of the package in the codeGen.py script [as argument in sys.path.append]

Inputs:
	3 Json files:
		generateItem.json - Defines path of templates, the class type to be generated(State/actionHandler/Enum), output directory to be produced.
		stateMachineAppModel.json - Defines procedures, states for each procedure, event for each state, actions to be taken under each event and nextstate of the procedure.
		ctxtManagerAppModel.json - Defines the data to be stored in various contexts maintained by the MME.
		
		Existing actionHandler.h and attachActionHandlers.cpp,detachActionHandlers.cpp,s1ReleaseActionHandlers.cpp files from <top-dir>/include/mme-app/actionHandlers and <top-dir>/src/mme-app/actionHandlers respectively.
		Place it in output directories as the output produced should be merged with existing file properly. 

Output:
	1.	mme states .cpp and header files. Copy to <top-dir>/src/mme-app/mme-states and <top-dir>/include/mme-app/mme-states
	2.	stateFactory.h and stateFactory.cpp Copy to <top-dir>/src/mme-app/mme-states and <top-dir>/include/mme-app/mme-states
	3.	actionHandlers
			actionHandler.h and actionHandler source files per procedure (eg: attachActionHandlers.cpp, detachActionHandlers.cpp )
			actionHandler.h should be placed in <top-dir>/include/mme-app/actionHandlers
			attachActionHandler.cpp should placed in <top-dir>/src/mme-app/actionHandlers
	4.	enums used by the MME state machine - <top-dir>/include/stateMachineFwk

Execution:
-Run the below command:
	python3 codeGen.py


