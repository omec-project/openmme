/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "S1AP-IEs"
 * 	found in "./asn1c/S1AP-IEs.asn"
 * 	`asn1c -fcompound-names -fno-include-deps -gen-PER -findirect-choice -pdu=S1AP-PDU`
 */

#ifndef	_ProSeDirectDiscovery_H_
#define	_ProSeDirectDiscovery_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ProSeDirectDiscovery {
	ProSeDirectDiscovery_authorized	= 0,
	ProSeDirectDiscovery_not_authorized	= 1
	/*
	 * Enumeration is extensible
	 */
} e_ProSeDirectDiscovery;

/* ProSeDirectDiscovery */
typedef long	 ProSeDirectDiscovery_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_ProSeDirectDiscovery_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_ProSeDirectDiscovery;
extern const asn_INTEGER_specifics_t asn_SPC_ProSeDirectDiscovery_specs_1;
asn_struct_free_f ProSeDirectDiscovery_free;
asn_struct_print_f ProSeDirectDiscovery_print;
asn_constr_check_f ProSeDirectDiscovery_constraint;
ber_type_decoder_f ProSeDirectDiscovery_decode_ber;
der_type_encoder_f ProSeDirectDiscovery_encode_der;
xer_type_decoder_f ProSeDirectDiscovery_decode_xer;
xer_type_encoder_f ProSeDirectDiscovery_encode_xer;
oer_type_decoder_f ProSeDirectDiscovery_decode_oer;
oer_type_encoder_f ProSeDirectDiscovery_encode_oer;
per_type_decoder_f ProSeDirectDiscovery_decode_uper;
per_type_encoder_f ProSeDirectDiscovery_encode_uper;
per_type_decoder_f ProSeDirectDiscovery_decode_aper;
per_type_encoder_f ProSeDirectDiscovery_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _ProSeDirectDiscovery_H_ */
#include <asn_internal.h>
