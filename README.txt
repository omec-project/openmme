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

    a. update the following configuration files:
        {install_path}/openmme/src/mme-app/conf/mme.json
        {install_path}/openmme/src/s1ap/conf/s1ap.json
        {install_path}/openmme/src/s11/conf/s11.json
        {install_path}/openmme/src/s6a/conf/*.json

       update the Diameter Configuration File:
        {install_path}/openmme/src/s6a/conf/s6a_fd.conf

        the following values shall be defined:
          Identity:
          - the diameter identity.
          - default value: mme.localdomain

          Realm:
          - the diameter realm (everything past the first period of Identity)
          - default value: localdomain

    b. build open mme components as follows:
        cd {install_path}/openmme
        make clean; make; make install

    c. generate certificates

       NOTE: The "Diameter Identity" is a fully qualified domain name that is
       used to access the the Diameter peer. The "Diameter Host" is
       everything up to the first period of the "Diameter Identity". The
       "Diameter Realm" is everything after the first period of the
       "Diameter Identity".

       Execute the following command, using the "Identity" configured in
       {install_path}/openmme/src/s6a/conf/s6a_fd.conf

          cd {install_path}/openmme/target/conf
          ./make_certs.sh <diameter_host> <diameter_realm>

        For Example: ./make_certs.sh mme localdomain

    d. cd {install_path}/openmme/target/

    e. start the mme modules
        ./run.sh


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

