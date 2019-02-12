1. Introduction:

	OpenMME is a grounds up implementation of the Mobility Management Entity
EPC S1 front end to the Cell Tower (eNB). Its design is performance optimized for
high speed mobility events over the S1-MME interface, while maintaining state
coherent high transaction rate interactions over the S6a interface to the HSS
and the S11 interface to the Serving Gateway Control (SGWC).
The design allows maximum utilization of the transaction rate allowed by the
S1-MME Non-Access Stratum (NAS) messages over SCTP, S6a DIAMETER Attribute Value
Pairs (AVPs) over TCP and S11 GTPV2C messages over UDP protocols.

2. Build and Installation Procedure:

    a. Build open mme components as follows,
        cd {install_path}/openmme
        make clean;make

    b. update the following configuration files,
        src/mme-app/conf/mme.json
        src/s1ap/conf/s1ap.json
        src/s11/conf/s11.json
        src/s6a/conf/*.json

    c. update the certificates in src/s6a/conf/ with production one

    d. set LD_LIBRARY_PATH as follows before starting MME modules,
       (need to set on each terminal where modules started)

        export LD_LIBRARY_PATH={install_path}/openmme/src/common/

    e. start the mme modules in the following order,
        cd {install_path}/openmme/src/mme-app
        ./mme-app
        cd {install_path}/openmme/src/s1ap
        ./s1ap-app
        cd {install_path}/openmme/src/s11
        ./s11-app
        cd {install_path}/openmme/src/s6a
        ./s6a-app

3. Known Issues:
    a. O3 optimization flag is disabled in s6a module
	   Observed issues in attach procedure when -O3 optimization flag is enabled
	   in s6a module.
    b. APN value hardcoded in openMME
	   APN value sent in InitialContextSetupRequest message is hardcoded in the
	   following file,
	     FILE: src/s1ap/handlers/attach_icsreq.c
	     Function: icsreq_processing()
	     Code:
		  strncpy(apn_name, " apn", sizeof(" apn"));
		  strcat(apn_name, ".TestNetwork");
    c. Message Authentication Code (MAC) needs to be disabled at the RAN side to
       support number of devices >10 and S1-MME transaction rate >10

