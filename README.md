# OpenMME
## Table of Contents
[Introduction](#introduction)

[Builds and Installation Procedure](#build-and-installation-procedure)

[Update Config](#update-config)

[Known Issues](#known-issues)

[Config Parameters](#config-parameters)

## Introduction:
OpenMME is a grounds up implementation of the Mobility management Entity EPC S1 front end to the Cell Tower (eNB). Its design is performance optimized for high speed mobility events over the S1-MME interface, while maintaining state coherent high transaction rate interactions over the S6a interface to the HSS and the S11 interface to the Serving Gateway Control (SGWC). The design allows maximum utilization of the transaction rate allowed by the S1-MME Non-Access Stratum (NAS) messages over SCTP, S6a DIAMETER Attribute Value Pairs (AVPs) over TCP and S11 GTPV2C messages over UDP protocols.

## Build and Installation Procedure
### Update config 
Update following config files

    {install_path}/openmme/src/mme-app/conf/mme.json
    {install_path}/openmme/src/s1ap/conf/s1ap.json
    {install_path}/openmme/src/s11/conf/s11.json
    {install_path}/openmme/src/s6a/conf/*.json
    update the Diameter Configuration File:
        {install_path}/openmme/src/s6a/conf/s6a_fd.conf
       
- the following values shall be defined:
   - Identity:  
      - the diameter identity.
      - default value: mme.localdomain
   - Realm:
          - the diameter realm (everything past the first period of Identity)
          - default value: localdomain
          
  - Refer free diameter  [config link](http://www.freediameter.net/trac/wiki/Configuration) 

### Build open mme components as follows:
    cd {install_path}/openmme
    make clean; make; make install

### Generate certificates   
The "Diameter Identity" is a fully qualified domain name that is used to access the the Diameter peer. The "Diameter Host" is everything up to the first period of the "Diameter Identity". The  "Diameter Realm" is everything after the first period of the "Diameter Identity".

Execute the following command, using the "Identity" configured in        {install_path}/openmme/src/s6a/conf/s6a_fd.conf

    cd {install_path}/openmme/target/conf
    ./make_certs.sh <diameter_host> <diameter_realm>
    For Example: ./make_certs.sh mme localdomain

   ### Start MME modules
     cd {install_path}/openmme/target/
     ./run.sh

## Known Issues
- O3 optimization flag is disabled in s6a module Observed issues in attach procedure when -O3 optimization flag is enabled in s6a module.
- Message Authentication Code (MAC) needs to be disabled at the RAN side to support number of devices >10 and S1-MME transaction rate >10

## Appendix A.
Before starting openMME applications respective parameters should be  configured in the json files mentioned in section 2.b. For each of the application individual json file can be created, or a user can create a common json file for entire MME configuration(all interfaces), and copy contents of this file in all other jsons.
	OpenMME applications are designed modularly so that with extended IPC support user can have an individual application running on separate hosts/VMs, to help in this situation separate configuration files are created for each of the MME application(s1ap-app, s6a-app, s11-app, mme-app)

### Config Parameters
- Following is a description of each section under json file.
  - [U] - Reserved/Unused. Can be skipped in the json.
  - [M] - Mandatory parameter.

#### "mme" - Contains information relevant for mme-app & s1ap-app.
  Config Parameter Name | Reserved/Unused/Mandatory | Comments |
  ----------------------|---------------------------|----------|
  egtp_default_port     | Unused                    | Default S11 port for MME's S11 end |
  ip_addr               | Mandatory                 | MME's own ip address. Reserved for management. |
  s1ap_addr             | Unused | MME's s1ap interface IP address |
  egtp_addr             | Unused | MME's s11 interface IP address |
  sctp_port             | Unused | MME's sctp(s1ap) port number. |
  name                  | Unused | MME's name to use in s1 setup with eNB |
  egtp_default_hostname | Optional| | 
  MCC, MNC              | Mandatory | MCC, MNC for the MME|
  

#### "s1ap" -eNB information. Relevant for s1ap-app.
Config Parameter Name | Reserved/Unused/Mandatory | Comments |
----------------------|---------------------------|----------|
s1ap_local_addr | Mandatory | MME's s1ap interface source IP address |
sctp_port       | Mandatory | MME's s1ap interface source port |


#### "s11" - SGW information for s11 communication. Relevant for s11-app  
Config Parameter Name | Reserved/Unused/Mandatory | Comments |
----------------------|---------------------------|----------|
egtp_local_addr | Mandatory | MME's source s11 interface IP address. |
egtp_default_port | Mandatory | MME's source s11 interface port. |
sgw_addr | Mandatory | Destination SGW IP for s11 interface |
pgw_addr | Mandatory | PGW address. This field is not used as of now. Provision made in MME config for PGW information. |

#### "s6a" - HSS information for s6a communication. Relevant for s6a-app.
Config Parameter Name | Reserved/Unused/Mandatory | Comments |
----------------------|---------------------------|----------|
host_type | Mandatory | Two types are supported. "freediameter" - Communicate to HSS host over freediameter interface. "hss_perf" - Use local loopback HSS option. This is only for testing purpose. |
host_name | Mandatory | HSS destination host name. |
realm | Mandatory | Realm for HSS freediameter communication. |

