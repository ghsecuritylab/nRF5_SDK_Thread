/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_NRF_802154_RSCH_CRIT_SECT_H
#define _MOCK_NRF_802154_RSCH_CRIT_SECT_H

#ifndef __STATIC_INLINE
#define __STATIC_INLINE
#else
#undef __STATIC_INLINE
#define __STATIC_INLINE
#endif
#define SUPPRESS_INLINE_IMPLEMENTATION

#include <nrf_802154_rsch_crit_sect.h>
#undef SUPPRESS_INLINE_IMPLEMENTATION
#undef __STATIC_INLINE
#define __STATIC_INLINE __STATIC_INLINE1

void mock_nrf_802154_rsch_crit_sect_Init(void);
void mock_nrf_802154_rsch_crit_sect_Destroy(void);
void mock_nrf_802154_rsch_crit_sect_Verify(void);




#define nrf_802154_rsch_crit_sect_init_Ignore() nrf_802154_rsch_crit_sect_init_CMockIgnore()
void nrf_802154_rsch_crit_sect_init_CMockIgnore(void);
#define nrf_802154_rsch_crit_sect_init_Expect() nrf_802154_rsch_crit_sect_init_CMockExpect(__LINE__)
void nrf_802154_rsch_crit_sect_init_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_nrf_802154_rsch_crit_sect_init_CALLBACK)(int cmock_num_calls);
void nrf_802154_rsch_crit_sect_init_StubWithCallback(CMOCK_nrf_802154_rsch_crit_sect_init_CALLBACK Callback);
#define nrf_802154_rsch_crit_sect_prio_request_Ignore() nrf_802154_rsch_crit_sect_prio_request_CMockIgnore()
void nrf_802154_rsch_crit_sect_prio_request_CMockIgnore(void);
#define nrf_802154_rsch_crit_sect_prio_request_Expect(prio) nrf_802154_rsch_crit_sect_prio_request_CMockExpect(__LINE__, prio)
void nrf_802154_rsch_crit_sect_prio_request_CMockExpect(UNITY_LINE_TYPE cmock_line, rsch_prio_t prio);
typedef void (* CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALLBACK)(rsch_prio_t prio, int cmock_num_calls);
void nrf_802154_rsch_crit_sect_prio_request_StubWithCallback(CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALLBACK Callback);
#define nrf_802154_rsch_crit_sect_prio_request_IgnoreArg_prio() nrf_802154_rsch_crit_sect_prio_request_CMockIgnoreArg_prio(__LINE__)
void nrf_802154_rsch_crit_sect_prio_request_CMockIgnoreArg_prio(UNITY_LINE_TYPE cmock_line);

#endif
