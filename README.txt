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
          
          Refer following link for further freediameter configuration help
          http://www.freediameter.net/trac/wiki/Configuration

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
    d. Multiple eNB support is added, but not tested beyond 2 eNB connections.

Appendix A.
-----------
	Before starting openMME applications respective parameters should be
configured in the json files mentioned in section 2.b. For each of the
application individual json file can be created, or a user can create a common
json file for entire MME configuration(all interfaces), and copy contents of
this file in all other jsons.
	OpenMME applications are designed modularly so that with extended IPC
support user can have an individual application running on separate hosts/VMs,
to help in this situation separate configuration files are created for each of
the MME application(s1ap-app, s6a-app, s11-app, mme-app)

	Following is a description of each section under json file.
	[U] - Reserved/Unused. Can be skipped in the json.
	[M] - Mandatory parameter.

	"mme" - Contains MME core information. Relevant for mme-app & s1ap-app.
		egtp_default_port[U] : Default S11 port for MME's s11 end.
		ip_addr[M] : MME's own ip address. Reserved for management.
		s1ap_addr[U] : MME's s1ap interface IP address
		egtp_addr[U] : MME's s11 interface IP address
		sctp_port[U] : MME's sctp(s1ap) port number.
		name[M] : MME's name to use in s1 setup with eNB
		egtp_default_hostname[O]:
		mcc[M], mnc[M] : MCC, MNC for the MME.

	"s1ap" -eNB information. Relevant for s1ap-app.
		s1ap_local_addr[M] : MME's s1ap interface source IP address.
		sctp_port[M] : MME's s1ap interface source port.

		Destination eNB information is only for testing purpose. eNB
		information is learned when eNB dynamically connects to MME.
		enb_addr[M] : Destination eNB IP for s1ap interface.
		enb_port[M] : Destination eNB port for s1ap interface.

	"s11" - SGW information for s11 communication. Relevant for s11-app.
		egtp_local_addr[M] : MME's source s11 interface IP address.
		egtp_default_port[M] : MME's source s11 interface port.
		sgw_addr[M] : Destination SGW IP for s11 interface
		pgw_addr[M] : PGW address. This field is not used as of now.
			Provision made in MME config for PGW information.

	"s6a" - HSS information for s6a communication. Relevant for s6a-app.
		host_type[M] : Two types are supported here as mentioned below:
			"freediameter" - Communicate to HSS host over
			freediameter interface
			"hss_perf" - Use local loopback HSS option. This is
			only for testing purpose.
		host_name[M] : HSS destination host name.
		realm[M] : Realm for HSS freediameter communication.
