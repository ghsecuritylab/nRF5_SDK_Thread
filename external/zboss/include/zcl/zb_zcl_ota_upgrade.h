/* ZBOSS Zigbee 3.0
 *
 * Copyright (c) 2012-2018 DSR Corporation, Denver CO, USA.
 * http://www.dsr-zboss.com
 * http://www.dsr-corporation.com
 * All rights reserved.
 *
 *
 * Use in source and binary forms, redistribution in binary form only, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 2. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 3. This software, with or without modification, must only be used with a Nordic
 *    Semiconductor ASA integrated circuit.
 *
 * 4. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
PURPOSE: OTA Upgrade cluster defintions
*/

#if ! defined ZB_ZCL_OTA_UPGRADE_H
#define ZB_ZCL_OTA_UPGRADE_H

#ifndef ZB_WINDOWS
#include "zcl/zb_zcl_common.h"
#include "zcl/zb_zcl_commands.h"
#else
#pragma pack(1)
#endif

#if defined ZB_ZCL_SUPPORT_CLUSTER_OTA_UPGRADE || defined DOXYGEN

/** @cond DOXYGEN_ZCL_SECTION */

/** @addtogroup ZB_ZCL_OTA_UPGRADE
 *  @{
 *    @details
 *    All commands in the cluster have only request form, and carry no payload.
 */

/** @brief Hook on Write attribute
 * send Check-in if change Check-in interval & Check-in remain time > new check-in interval */
/* zb_void_t zb_zcl_ota_upgrade_write_attr_hook(zb_uint8_t endpoint, zb_uint16_t attr_id, zb_uint8_t *new_value); */

/*! @name OTA File Header format
    Structures for representation OTA File Header
    @{
*/

/*! @brief Structure representsation of OTA File Header,
 * see OTA spec 6.3.2 */
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_file_header_s
{
  zb_uint32_t file_id;            /**< OTA upgrade file identifier*/
  zb_uint16_t header_version;     /**< OTA Header version */
  zb_uint16_t header_length;      /**< OTA Header length */
  zb_uint16_t fc;                 /**< OTA Header Field control */
  zb_uint16_t manufacturer_code;  /**< Manufacturer code */
  zb_uint16_t image_type;         /**< Image type */
  zb_uint32_t file_version;       /**< File version */
  zb_uint16_t stack_version;      /**< Zigbee Stack version */
  zb_char_t header_string[32];    /**< OTA Header string */
  zb_uint32_t total_image_size;   /**< Total Image size (including header) */

  // Optional parameters
#if 0
  zb_uint8_t credential_version;  /**< Security credential version - optional */
  zb_ieee_addr_t dst_addr;        /**< Upgrade file destination - optional */
  zb_uint16_t min_hw_version;     /**< Minimum hardware version - optional */
  zb_uint16_t max_hw_version;     /**< Maximum hardware version - optional */
#endif

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_file_header_t;


/**
   Optional parts of the OTA file header (commented out in the standard ZCL header)
 */
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_file_header_optional_s
{
  zb_uint8_t credential_version;  /**< Security credential version - optional */
//  zb_ieee_addr_t dst_addr;        /**< Upgrade file destination - optional. Do
//  not uses for bosch - exclude for now*/
  zb_uint16_t min_hw_version;     /**< Minimum hardware version - optional */
  zb_uint16_t max_hw_version;     /**< Maximum hardware version - optional */
} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_file_header_optional_t;

/** @cond internals_doc */
#define ZB_ZCL_OTA_UPGRADE_FILE_HEADER_FULL_SIZE        \
    (sizeof(zb_zcl_ota_upgrade_file_header_t) + 2*sizeof(zb_uint16_t)+sizeof(zb_ieee_addr_t))
/*! @}
 *  @endcond */ /* internals_doc */

/** @brief Default OTA Upgrade File Identifier, see spec 6.3.2.1 */
#define ZB_ZCL_OTA_UPGRADE_FILE_HEADER_FILE_ID          0x0BEEF11E

/** @brief Default OTA Upgrade File Version, see spec 6.3.2.2 */
#define ZB_ZCL_OTA_UPGRADE_FILE_HEADER_FILE_VERSION     0x0100

/*! @brief OTA File header - fc fields structure
    @see OTA spec, OTA Upgrade Cluster 6.3.2.4
*/
enum zb_zcl_ota_upgrade_file_header_fc_e
{
  /*! @brief Security Credential Version Present */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_FC_CREDENTIAL_VER      = 1 << 0,
  /*! @brief Device Specific File */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_FC_DEVICE_SPECIFIC     = 1 << 1,
  /*! @brief Hardware Versions Present */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_FC_HW_VER              = 1 << 2,
};

/** @brief Special Manufacturer Code, see spec 6.3.2.5 */
#define ZB_ZCL_OTA_UPGRADE_FILE_HEADER_MANUFACTURE_CODE_WILD_CARD   0xffff

/*! @brief OTA File header - Image Type Values
    @see OTA spec, OTA Upgrade Cluster 6.3.2.6
*/
enum zb_zcl_ota_upgrade_file_header_image_type_e
{
  /*! @brief Manufacturer Specific - maximum value */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_IMAGE_MANUF_SPEC_MAX   = 0xffbf,
  /*! @brief Security credential */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_IMAGE_SECURITY_CRED    = 0xffc0,
  /*! @brief Configuration */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_IMAGE_CONFIG           = 0xffc1,
  /*! @brief Log */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_IMAGE_LOG              = 0xffc2,
  /*! @brief Wild card value */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_IMAGE_WILD_CARD        = 0xffff,
};

/** @brief OTA Upgrade File Version, App release, see spec 6.3.2.7 */
#define ZB_ZCL_OTA_UPGRADE_FILE_GET_APP_RELEASE(ver)  (((ver) >>24) & 0xff)

/** @brief OTA Upgrade File Version, App build, see spec 6.3.2.7 */
#define ZB_ZCL_OTA_UPGRADE_FILE_GET_APP_BUILD(ver)  (((ver) >>16) & 0xff)

/** @brief OTA Upgrade File Version, Stack release, see spec 6.3.2.7 */
#define ZB_ZCL_OTA_UPGRADE_FILE_GET_STACK_RELEASE(ver)  (((ver) >>8) & 0xff)

/** @brief OTA Upgrade File Version, Stack build, see spec 6.3.2.7 */
#define ZB_ZCL_OTA_UPGRADE_FILE_GET_STACK_BUILD(ver)  ((ver) & 0xff)

/** @brief OTA Upgrade File Version, make file verston, see spec 6.3.2.7 */
#define ZB_ZCL_OTA_UPGRADE_FILE_MAKE_VERSION(app_rel, app_build, stack_rel, stack_build)  \
  ((app_rel) << 24 | (app_build) << 16 | (stack_rel) << 8 | (stack_build))


/* TODO: This comparing scheme forbids some upgrade cases:
   - downgrade Stack Build (Stack Major)
   - upgrade/downgrade Stack Release (Stack Minor) when other fields are the same
   - upgrade/downgrade Stack Build/Stack Release when Application Build and Application release are
   the same

   OTA Upgrade Spec (6.3.2.7 File Version) has dome recommendations about versioning (at least to
   divide version to 4 parts - Stack Build, Stack Release, Application Build and Application
   Release), but does not specify comparing method. Looks like we do not have any limitations and
   may upgrade/downgrade any f/w, so it is better to simplify this comparing to:
     ver1 != ver2
   Only one possible limitation now is NVRAM, but if dataset ids are not overlapped, it is also ok.
 */
/** @brief Compare version with stack ver is any */
/* VP: allow OTA server downgrade client's firmware. */
#define ZB_ZCL_OTA_UPGRADE_VERSION_CMP_WITHOUT_STACK(ver1, ver2)            \
    ( ((ver1) & 0xffff0000) != ((ver2) & 0xffff0000) )

/** @brief Compare version with stack release are equal */
#define ZB_ZCL_OTA_UPGRADE_VERSION_CMP_WITH_STACK_RELEASE_EQUAL(ver1, ver2) \
    ( ( ((ver1) & 0x0000ff00) == ((ver2) & 0x0000ff00) )  &&                \
      ZB_ZCL_OTA_UPGRADE_VERSION_CMP_WITHOUT_STACK((ver1), (ver2)) )

/** @brief Compare version with stack release are equal and stack build no less */
#define ZB_ZCL_OTA_UPGRADE_VERSION_CMP_WITH_STACK(ver1, ver2)               \
    ( ( ((ver1) & 0x000000ff) >= ((ver2) & 0x000000ff) )  &&                \
    ZB_ZCL_OTA_UPGRADE_VERSION_CMP_WITH_STACK_RELEASE_EQUAL((ver1), (ver2)) )


/*! @brief OTA File header - Zigbee Stack version
    @see OTA spec, OTA Upgrade Cluster 6.3.2.8
*/
enum zb_zcl_ota_upgrade_file_header_stack_version_e
{
  /*! @brief Zigbee 2006 */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_STACK_2006 = 0x0000,
  /*! @brief Zigbee 2007 */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_STACK_2007 = 0x0001,
  /*! @brief Zigbee Pro */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_STACK_PRO  = 0x0002,
  /*! @brief Zigbee IP */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_STACK_IP   = 0x0003,
};

/*! @brief OTA File header - Security Credential Version
    @see OTA spec, OTA Upgrade Cluster 6.3.2.11
*/
enum zb_zcl_ota_upgrade_file_header_security_version_e
{
  /*! @brief SE 1.0 */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_SECURITY_VER_SE1_0 = 0x00,
  /*! @brief SE 1.1 */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_SECURITY_VER_SE1_1 = 0x01,
  /*! @brief SE 2.0 */
  ZB_ZCL_OTA_UPGRADE_FILE_HEADER_SECURITY_VER_SE2_0 = 0x02,
};

/** @brief OTA Upgrade HW Version Get Version, see spec 6.3.2.13 */
#define ZB_ZCL_OTA_UPGRADE_FILE_GET_HW_VERSION(ver)  (((ver) >>8) & 0xff)

/** @brief OTA Upgrade HW Version Get Revision, see spec 6.3.2.13 */
#define ZB_ZCL_OTA_UPGRADE_FILE_GET_HW_REVISION(ver)  ((ver) & 0xff)

/** @brief OTA Upgrade Make HW Version, see spec 6.3.2.13 */
#define ZB_ZCL_OTA_UPGRADE_FILE_MAKE_HW_VERSION(ver, rev)  \
  ((ver) << 8 | (rev))

/** @brief Default value of OTA Upgrade HW Version */
#define ZB_ZCL_OTA_UPGRADE_FILE_HW_VERSION_DEF_VALUE    0xffff
/** @brief Default value of OTA Upgrade destanation address */
#define ZB_ZCL_OTA_UPGRADE_FILE_DEST_ADDRESS_DEF_VALUE  { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }

/*! @}
*/

/*! @name OTA File Sub-elementformat
    Structures for representation OTA File Sub-element
    @{
*/

/*! @brief Structure representsation of OTA File Sub-element,
 * see OTA spec 6.3.3 */
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_sub_element_s
{
  zb_uint16_t tag_id;     /** Tag ID*/
  zb_uint32_t length;     /** length */
  zb_uint8_t value[1];    /** data variable, length - see 'length' field */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_sub_element_t;


/*! @brief OTA File header - Tag Identifiers
    @see OTA spec, OTA Upgrade Cluster 6.3.4
*/
enum zb_zcl_ota_upgrade_sub_element_tags_e
{
  /*! @brief  */
  ZB_ZCL_OTA_UPGRADE_FILE_TAG_UPGRADE_IMAGE   = 0x0000,
  /*! @brief ECDSA Signature */
  ZB_ZCL_OTA_UPGRADE_FILE_TAG_ECDSA           = 0x0001,
  /*! @brief ECDSA Signature Certificate */
  ZB_ZCL_OTA_UPGRADE_FILE_TAG_ECDSA_CERT      = 0x0002,
  /*! @brief Manufacturer Specific Use - minimum */
  ZB_ZCL_OTA_UPGRADE_FILE_TAG_MANUF_MIN       = 0xf000,
  /*! @brief Manufacturer Specific Use - maximum */
  ZB_ZCL_OTA_UPGRADE_FILE_TAG_MANUF_MAX       = 0xffff,
};

/*! @brief Structure representsation of OTA ECDSA Signature,
 * see OTA spec 6.3.5 */
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_ecdsa_s
{
  zb_uint16_t tag_id;       /** Tag ID*/
  zb_uint32_t length;       /** length */
  zb_ieee_addr_t address;   /** address */
  zb_uint8_t value[42];     /** data variable */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_ecdsa_t;

/** @brief Special Manufacturer Code, see spec 6.3.5 */
#define ZB_ZCL_OTA_UPGRADE_ECDSA_TAG_ID   0x0001

/** @brief Special Manufacturer Code, see spec 6.3.5 */
#define ZB_ZCL_OTA_UPGRADE_ECDSA_LENGTH   0x00000032


/*! @brief Structure representsation of OTA ECDSA Signature,
 * see OTA spec 6.3.6 */
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_ecdsa_signing_s
{
  zb_uint16_t tag_id;         /** Tag ID*/
  zb_uint32_t length;         /** length */
  zb_uint8_t certificate[48]; /** data variable, length - see 'length' field */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_ecdsa_signing_t;

/** @brief Special Manufacturer Code, see spec 6.3.6 */
#define ZB_ZCL_OTA_UPGRADE_ECDSA_SIGNING_TAG_ID   0x0002

/** @brief Special Manufacturer Code, see spec 6.3.6 */
#define ZB_ZCL_OTA_UPGRADE_ECDSA_SIGNING_LENGTH   0x00000030


/*! @brief Structure representsation of OTA ECDSA Certificate,
 * see OTA spec 6.3.7 */
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_ecdsa_certificate_s
{
  zb_uint16_t tag_id;   /** Tag ID*/
  zb_uint32_t length;   /** length */
  zb_uint8_t hash[16];  /** hash */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_ecdsa_ertificate_t;

/** @brief Special Manufacturer Code, see spec 6.3.7 */
#define ZB_ZCL_OTA_UPGRADE_ECDSA_CERTIFICATE_TAG_ID   0x0003

/** @brief Special Manufacturer Code, see spec 6.3.7 */
#define ZB_ZCL_OTA_UPGRADE_ECDSA_CERTIFICATE_LENGTH   0x00000010


/*! @}
*/

/* Cluster ZB_ZCL_CLUSTER_ID_OTA_UPGRADE */

/*! @name OTA Upgrade cluster attributes
    @{
*/

/*! @brief Maximum size data for Query Image Block Request */
#define ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_BLOCK_DATA_SIZE_MAX   64

/*! @brief Callback function for send next data portion
 *
 */
typedef zb_uint8_t* (*zb_zcl_ota_upgrade_next_data_ind_t)(zb_uint8_t index, zb_uint32_t offset, zb_uint8_t size);

#if defined ZB_HA_ENABLE_OTA_UPGRADE_SERVER || defined DOXYGEN

/** @brief Initialize OTA Upgrade cluster - server part
 * For server clear custom data and registry next data indication
 *
 * @param endpoint - destination endpoint
 * @param next_data_ind_cb - callback to be called on received image block
 * For client initiate search Upgrade server */
zb_void_t zb_zcl_ota_upgrade_init_server(zb_uint8_t endpoint, zb_zcl_ota_upgrade_next_data_ind_t next_data_ind_cb);

/*! @brief Structure representsation of Data for insert OTA file to upgrade mechanizm */
typedef struct zb_zcl_ota_upgrade_server_insert_file_s
{
  zb_uint8_t endpoint;    /**< Endpoint */
  zb_uint8_t index;       /**< Index of table, index must be less value is set when create attibute */
  zb_uint8_t *ota_file;   /**< OTA file, place in memory, see OTA spec 6.3.2
                                note: OTA file must saved in memory until call zb_zcl_ota_upgrade_remove_file*/
  zb_uint32_t upgrade_time; /**< Upgrade time for this OTA file */

} zb_zcl_ota_upgrade_server_insert_file_t;

/*! @brief Insert upgrade OTA file into Server upgrade table
 *
 * @param param - buffer with @ref zb_zcl_ota_upgrade_server_insert_file_s structure
 *
 * note: OTA file must saved in memory until call zb_zcl_ota_upgrade_remove_file
*/
zb_ret_t zb_zcl_ota_upgrade_insert_file(zb_uint8_t param);

#define ZB_ZCL_OTA_UPGRADE_INSERT_FILE(buf, ep, i, file, upgrade_tm)    \
{                                                                       \
  zb_zcl_ota_upgrade_server_insert_file_t *file_data =                  \
    ZB_GET_BUF_PARAM(buf, zb_zcl_ota_upgrade_server_insert_file_t);     \
  file_data->endpoint = (ep);                                           \
  file_data->index = (i);                                               \
  file_data->ota_file = (file);                                         \
  file_data->upgrade_time = (upgrade_tm);                               \
  zb_ret_t zb_err_code = zb_zcl_ota_upgrade_insert_file(ZB_REF_FROM_BUF(buf)); \
  ZB_ASSERT(zb_err_code == RET_OK);                                          \
}

/*! @brief Structure representsation of Data for insert OTA file to upgrade mechanizm */
typedef struct zb_zcl_ota_upgrade_server_remove_file_s
{
  zb_uint8_t endpoint;    /**< Endpoint */
  zb_uint8_t index;       /**< Index of table, index must be less value is set when create attibute */

} zb_zcl_ota_upgrade_server_remove_file_t;

/*! @brief Remove upgrade file from Server upgrade table
 *
 * @param param - buffer with @ref zb_zcl_ota_upgrade_server_remove_file_s structure
 *
 * note: after coll this command OTA file may be remove from memory
*/
zb_ret_t zb_zcl_ota_upgrade_remove_file(zb_uint8_t param);

#define ZB_ZCL_OTA_UPGRADE_REMOVE_FILE(buf, ep, i)                  \
{                                                                   \
  zb_zcl_ota_upgrade_server_remove_file_t *file_data =              \
    ZB_GET_BUF_PARAM(buf, zb_zcl_ota_upgrade_server_remove_file_t); \
  file_data->endpoint = (ep);                                       \
  file_data->index = (i);                                           \
  zb_ret_t zb_err_code = zb_zcl_ota_upgrade_remove_file(ZB_REF_FROM_BUF(buf)); \
  ZB_ASSERT(zb_err_code == RET_OK);                                      \
}

/*! @brief Structure representsation of OTA file on server side */
typedef struct zb_zcl_ota_upgrade_data_s
{
  zb_zcl_ota_upgrade_file_header_t *file_header;
  zb_uint32_t upgrade_time;

} zb_zcl_ota_upgrade_data_t;

/*! @brief Structure representsation of server side variables */
typedef struct zb_zcl_ota_upgrade_server_variable_s
{
  zb_uint8_t *query_jitter;      /**< QueryJitter */
  //zb_uint8_t data_size;         /**< DataSize */
  //zb_uint8_t *ota_image_data;   /**< OTAImageData */
  zb_uint32_t *current_time;     /**< CurrentTime */
  //zb_uint32_t upgrade_time;     /**< UpgradeTime */

  // custom data
  zb_uint8_t table_length;                  /**< Length of server table with upgrade image data */
  zb_zcl_ota_upgrade_data_t *table;         /**< Server table with upgrade image data */

} zb_zcl_ota_upgrade_server_variable_t;

/*! @brief Default value for DataSize, OTA spec  */
#define ZB_ZCL_OTA_UPGRADE_DATA_SIZE_DEF_VALUE          0xff

/*! @brief Minimum value for QueryJitter, OTA spec  */
#define ZB_ZCL_OTA_UPGRADE_QUERY_JITTER_MIN_VALUE       0x01
/*! @brief Maximum value for QueryJitter, OTA spec  */
#define ZB_ZCL_OTA_UPGRADE_QUERY_JITTER_MAX_VALUE       0x64
/*! @brief Default value for QueryJitter, OTA spec  */
#define ZB_ZCL_OTA_UPGRADE_QUERY_JITTER_DEF_VALUE       0x32

/*! @brief Default value for currentTime, OTA spec  */
#define ZB_ZCL_OTA_UPGRADE_CURRENT_TIME_DEF_VALUE       0xffffffff

/*! @brief Default value for UpgradeTime, OTA spec  */
#define ZB_ZCL_OTA_UPGRADE_UPGRADE_TIME_DEF_VALUE       0xffffffff

typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_srv_query_img_param_s
{
  zb_zcl_addr_t *zcl_addr;
  zb_uint16_t    image_type;
  zb_uint32_t    version;
  zb_uint8_t    *table_idx;
}
  ZB_PACKED_STRUCT zb_zcl_ota_upgrade_srv_query_img_param_t;

typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_srv_upgrade_end_param_s
{
  zb_zcl_addr_t *zcl_addr;
  zb_uint16_t    image_type;
  zb_uint32_t    version;
}
  ZB_PACKED_STRUCT zb_zcl_ota_upgrade_srv_upgrade_end_param_t;

#endif /* defined ZB_HA_ENABLE_OTA_UPGRADE_SERVER || defined DOXYGEN */

#if defined ZB_HA_ENABLE_OTA_UPGRADE_CLIENT || defined DOXYGEN

/** @brief Initialize OTA Upgrade cluster - client part
 * For server clear custom data
 * For client initiate search Upgrade server
 @param param - empty buffer
*/
zb_void_t zb_zcl_ota_upgrade_init_client(zb_uint8_t param);

/** @brief Stop process OTA Upgrade / OTA query new images
 * Client stop shedule OTA command & clear OTA status*/
zb_void_t zb_zcl_ota_upgrade_stop_client(void);

/*! @brief Resume process OTA Upgrade if it was previously suspended by the application
 *
 *  @param param - buffer to be resumed
 *  @param upgrade_status - application upgrade status @see zb_zcl_ota_upgrade_status_e
 */
zb_void_t zb_zcl_ota_upgrade_resume_client(zb_uint8_t param, zb_uint8_t upgrade_status);

/*! @brief Set Freqency request server about new upgrade file (minutes)
 * @param endpoint - endpoint of the OTA cluster
 * @param interval - new interval value (in minutes)
 */
zb_void_t zb_zcl_ota_upgrade_set_query_interval(zb_uint8_t endpoint, zb_uint16_t interval);

/*! @brief Clear attribute after upgrade
 *
 * @param endpoint - endpoint
 *
 * note: after coll this command OTA file may be remove from memory
*/
zb_void_t zb_zcl_ota_upgrade_file_upgraded(zb_uint8_t endpoint);

/*! @brief Structure representsation of client side variables */
typedef struct zb_zcl_ota_upgrade_client_variable_s
{
  // custom data
  zb_uint32_t download_file_size;
  zb_uint16_t timer_query;
  zb_uint16_t timer_counter;
  zb_uint16_t hw_version;
  zb_uint8_t max_data_size;
  zb_uint8_t img_block_req_sent;
  zb_uint8_t pending_img_block_resp;
} zb_zcl_ota_upgrade_client_variable_t;

#endif /* defined ZB_HA_ENABLE_OTA_UPGRADE_CLIENT || defined DOXYGEN */

/*! @brief OTA Upgrade cluster attribute identifiers
    @see OTA spec, OTA Upgrade Cluster 6.7,
*/
enum zb_zcl_ota_upgrade_attr_e
{
  /** @brief UpgradeServerID attribute, OTA spec 6.7.1 */
  ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ID                     = 0x0000,
  /** @brief FileOffset attribute, OTA spec 6.7.2 */
  ZB_ZCL_ATTR_OTA_UPGRADE_FILE_OFFSET_ID                = 0x0001,
  /** @brief CurrentFileVersion attribute, OTA spec 6.7.3 */
  ZB_ZCL_ATTR_OTA_UPGRADE_FILE_VERSION_ID               = 0x0002,
  /** @brief CurrentZigbeeStackVersion attribute, OTA spec 6.7.4 */
  ZB_ZCL_ATTR_OTA_UPGRADE_STACK_VERSION_ID              = 0x0003,
  /** @brief DownloadedFileVersion attribute, OTA spec 6.7.5 */
  ZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_FILE_VERSION_ID    = 0x0004,
  /** @brief DownloadedZigbeeStackVersion attribute, OTA spec 6.7.6 */
  ZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_STACK_VERSION_ID   = 0x0005,
  /** @brief ImageUpgradeStatus attribute, OTA spec 6.7.7 */
  ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STATUS_ID               = 0x0006,
  /** @brief Manufacturer ID attribute, OTA spec 6.7.8 */
  ZB_ZCL_ATTR_OTA_UPGRADE_MANUFACTURE_ID                = 0x0007,
  /** @brief Image Type ID attribute, OTA spec 6.7.9 */
  ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_TYPE_ID                 = 0x0008,
  /** @brief MinimumBlockReque attribute, OTA spec 6.7.10 */
  ZB_ZCL_ATTR_OTA_UPGRADE_MIN_BLOCK_REQUE_ID            = 0x0009,
  /** @brief Image Stamp attribute, OTA spec 6.7.11 */
  ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STAMP_ID                = 0x000a,
  /** This attribute indicates what behavior the client device supports for activating
   *  a fully downloaded but not installed upgrade image. */
  ZB_ZCL_ATTR_OTA_UPGRADE_UPGRADE_ACTIVATION_POLICY_ID  = 0x000b,
  /** This attribute indicates what behavior the client device supports for activating
   *  a fully downloaded image when the OTA server cannot be reached. */
  ZB_ZCL_ATTR_OTA_UPGRADE_UPGRADE_TIMEOUT_POLICY_ID     = 0x000c,


  /*! @brief OTA server endpoint custom attribute */
  ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ENDPOINT_ID            = 0xfff3,
  /*! @brief OTA server addr custom attribute */
  ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ADDR_ID                = 0xfff2,
  /*! @brief DownloadedFileSize custom attribute */
  ZB_ZCL_ATTR_OTA_UPGRADE_CLIENT_DATA_ID                = 0xfff1,
    /*! @brief Server variables- see OTA spec 6.8
   * and Custom data */
  ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_DATA_ID                = 0xfff0,
};

/*! @brief Default value for UpgradeServerID attribute, OTA spec 6.7.1 */
#define ZB_ZCL_OTA_UPGRADE_SERVER_DEF_VALUE           { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }
/*! @brief Default value for FileOffset attribute, OTA spec 6.7.2 */
#define ZB_ZCL_OTA_UPGRADE_FILE_OFFSET_DEF_VALUE                0xffffffff
/*! @brief Default value for CurrentFileVersion attribute, OTA spec 6.7.3 */
#define ZB_ZCL_OTA_UPGRADE_FILE_VERSION_DEF_VALUE               0xffffffff
/*! @brief Default value for CurrentZigbeeStackVersion attribute, OTA spec 6.7.4 */
#define ZB_ZCL_OTA_UPGRADE_STACK_VERSION_DEF_VALUE              0xffff
/*! @brief Default value for DownloadedFileVersion attribute, OTA spec 6.7.5 */
#define ZB_ZCL_OTA_UPGRADE_DOWNLOADED_FILE_VERSION_DEF_VALUE    0xffffffff
/*! @brief Default value for DownloadedZigbeeStackVersion attribute, OTA spec 6.7.6 */
#define ZB_ZCL_OTA_UPGRADE_DOWNLOADED_STACK_DEF_VALUE           0xffff
/*! @brief Default value for ImageUpgradeStatus attribute, OTA spec 6.7.7 */
#define ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_DEF_VALUE               0x00
/*! @brief Maximum value for MinimumBlockReque attribute, OTA spec 6.7.11 */
#define ZB_ZCL_OTA_UPGRADE_IMAGE_STAMP_MIN_VALUE                0x0256

/*! @brief OTA Image Upgrade Status Attribute Values
    @see OTA spec, OTA Upgrade Cluster 6.7.7
*/
enum zb_zcl_ota_upgrade_image_status_e
{
  /*! @brief Normal */
  ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_NORMAL            = 0x00,
  /*! @brief Download in progress */
  ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_DOWNLOADING       = 0x01,
  /*! @brief Download complete */
  ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_DOWNLOADED        = 0x02,
  /*! @brief Waiting to upgrade */
  ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_WAITING_UPGRADE   = 0x03,
  /*! @brief Count down */
  ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_COUNT_DOWN        = 0x04,
  /*! @brief Wait for more */
  ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_WAIT_FOR_MORE     = 0x05,
};

/*! @brief Default Freqency request server about new upgrade file (minutes) */
#define ZB_ZCL_OTA_UPGRADE_QUERY_TIMER_COUNT_DEF          (24*60)

/*! @brief Timer interval for Query timer  */
#define ZB_ZCL_OTA_UPGRADE_QUERY_TIMER_INTERVAL   \
    60l * ZB_TIME_ONE_SECOND

/*! @brief Maximum value of nextImageQuery interval   */
#define ZB_ZCL_OTA_UPGRADE_MAX_INTERVAL 60

/*! @brief Resend buffer delay */
#define ZB_ZCL_OTA_UPGRADE_RESEND_BUFFER_DELAY ZB_TIME_ONE_SECOND * 45

/*! @cond internals_doc
    @name OTA Upgrade cluster internals
    Internal structures for attribute representation in cluster definitions.
    @{
*/


#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ID,                    \
  ZB_ZCL_ATTR_TYPE_IEEE_ADDR,                           \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_FILE_OFFSET_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_FILE_OFFSET_ID,               \
  ZB_ZCL_ATTR_TYPE_U32,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_FILE_VERSION_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_FILE_VERSION_ID,              \
  ZB_ZCL_ATTR_TYPE_U32,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_STACK_VERSION_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_STACK_VERSION_ID,             \
  ZB_ZCL_ATTR_TYPE_U16,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_FILE_VERSION_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_FILE_VERSION_ID,   \
  ZB_ZCL_ATTR_TYPE_U32,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_STACK_VERSION_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_STACK_VERSION_ID,  \
  ZB_ZCL_ATTR_TYPE_U16,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STATUS_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STATUS_ID,              \
  ZB_ZCL_ATTR_TYPE_8BIT_ENUM,                           \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_MANUFACTURE_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_MANUFACTURE_ID,               \
  ZB_ZCL_ATTR_TYPE_U16,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_TYPE_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_TYPE_ID,                \
  ZB_ZCL_ATTR_TYPE_U16,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_MIN_BLOCK_REQUE_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_MIN_BLOCK_REQUE_ID,           \
  ZB_ZCL_ATTR_TYPE_U16,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STAMP_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STAMP_ID,               \
  ZB_ZCL_ATTR_TYPE_U32,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_CLIENT_DATA_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_CLIENT_DATA_ID,               \
  ZB_ZCL_ATTR_TYPE_NULL,                                \
  ZB_ZCL_ATTR_ACCESS_INTERNAL,                            \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ADDR_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ADDR_ID,               \
  ZB_ZCL_ATTR_TYPE_U16,                                 \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ENDPOINT_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ENDPOINT_ID,           \
  ZB_ZCL_ATTR_TYPE_U8,                                  \
  ZB_ZCL_ATTR_ACCESS_READ_ONLY,                         \
  (zb_voidp_t) data_ptr                                 \
}

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_DATA_ID(data_ptr) \
{                                                       \
  ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_DATA_ID,               \
  ZB_ZCL_ATTR_TYPE_NULL,                                \
  ZB_ZCL_ATTR_ACCESS_INTERNAL,                          \
  (zb_voidp_t) data_ptr                                 \
}

/*! @internal Number of attributes mandatory for reporting in OTA Upgrade cluster */
#define ZB_ZCL_OTA_UPGRADE_REPORT_ATTR_COUNT 0

/*! @}
  * @
    @endcond endcond */ /* OTA Upgrade cluster internals */

/** @brief Declare attribute list for OTA Upgrade cluster - client side
    @param attr_list - attribure list name
    @param upgrade_server - pointer to variable to store UpgradeServerID attribute
    @param file_offset - pointer to variable to store FileOffset attribute
    @param file_version - pointer to variable to store CurrentFileVersion attribute
    @param stack_version - pointer to variable to store CurrentZigbeeStackVersion attribute
    @param downloaded_file_ver - pointer to variable to store DownloadedFileVersion attribute
    @param downloaded_stack_ver - pointer to variable to store DownloadedZigbeeStackVersion attribute
    @param image_status - pointer to variable to store ImageUpgradeStatus attribute
    @param manufacturer - pointer to variable to store Manufacturer ID attribute
    @param image_type - pointer to variable to store Image Type ID attribute
    @param min_block_reque - pointer to variable to store MinimumBlockReque attribute
    @param image_stamp - pointer to variable to store Image Stamp attribute
    @param server_addr - server short address
    @param server_ep - server endpoint
    @param hardware_version - (const) hardware version
    @param max_data_size - (const) maximum data size Query Block Image commands
    @param query_timer - (const) query timer count
*/
#define ZB_ZCL_DECLARE_OTA_UPGRADE_ATTRIB_LIST(attr_list,                                           \
    upgrade_server, file_offset, file_version, stack_version, downloaded_file_ver,                  \
    downloaded_stack_ver, image_status, manufacturer, image_type, min_block_reque, image_stamp,     \
    server_addr, server_ep, hardware_version, max_data_size, query_timer)                           \
  zb_zcl_ota_upgrade_client_variable_t client_var_##attr_list =                                     \
  {0, query_timer, 1, hardware_version, max_data_size, 0, 0};                                       \
  ZB_ZCL_START_DECLARE_ATTRIB_LIST(attr_list)                                                       \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ID                  , (upgrade_server))       \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_FILE_OFFSET_ID             , (file_offset))          \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_FILE_VERSION_ID            , (file_version))         \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_STACK_VERSION_ID           , (stack_version))        \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_FILE_VERSION_ID , (downloaded_file_ver))  \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_STACK_VERSION_ID, (downloaded_stack_ver)) \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STATUS_ID            , (image_status))         \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_MANUFACTURE_ID             , (manufacturer))         \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_TYPE_ID              , (image_type))           \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_MIN_BLOCK_REQUE_ID         , (min_block_reque))      \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STAMP_ID             , (image_stamp))          \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ADDR_ID             , (server_addr))          \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ENDPOINT_ID         , (server_ep))            \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_CLIENT_DATA_ID,         &(client_var_##attr_list))   \
   ZB_ZCL_FINISH_DECLARE_ATTRIB_LIST

/** @brief Declare attribute list for OTA Upgrade cluster - server side
    @param attr_list - attribure list name
    @param query_jitter - (8bit) pointer to variable to store QueryJitter value
    @param current_time - (32bit) pointer to variable to store CurrentTime
    @param length - (const) length of server table with upgrade image data
*/
#define ZB_ZCL_DECLARE_OTA_UPGRADE_ATTRIB_LIST_SERVER(attr_list,                          \
    query_jitter, current_time, length)                                                   \
  zb_zcl_ota_upgrade_data_t table_##attr_list[length];                                    \
  zb_zcl_ota_upgrade_server_variable_t server_var_##attr_list =  {                        \
    query_jitter, /* 0, 0,*/ current_time, /*ZB_ZCL_OTA_UPGRADE_UPGRADE_TIME_DEF_VALUE,*/ \
    length, table_##attr_list };                                                          \
  ZB_ZCL_START_DECLARE_ATTRIB_LIST(attr_list)                                             \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_DATA_ID, &(server_var_##attr_list)) \
  ZB_ZCL_FINISH_DECLARE_ATTRIB_LIST

/*! @} */ /* OTA Upgrade cluster attributes */

/*! @name OTA Upgrade cluster commands
    @{
*/

/*! @brief OTA Upgrade cluster client to server command identifiers
    @see OTA spec, OTA Upgrade Cluster, 6.10.1
*/
enum zb_zcl_ota_upgrade_cmd_e
{
  ZB_ZCL_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_ID    = 0x01, /**< "Query Next Image Request" command */
  ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_ID         = 0x03, /**< "Image Block Request" command */
  ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_PAGE_ID          = 0x04, /**< "Image Page Request" command */
  ZB_ZCL_CMD_OTA_UPGRADE_UPGRADE_END_ID         = 0x06, /**< "Upgrade End Request" command */
  ZB_ZCL_CMD_OTA_UPGRADE_QUERY_SPECIFIC_FILE_ID = 0x08, /**< "Query Specific File Request" command */
};

/*! @brief OTA Upgrade cluster server to client command identifiers
    @see OTA spec, OTA Upgrade Cluster, 6.10.1
*/
enum zb_zcl_ota_upgrade_resp_cmd_e
{
  ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_NOTIFY_ID              = 0x00, /**< "Image Notify" command */
  ZB_ZCL_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_RESP_ID     = 0x02, /**< "Query Next Image Response" command */
  ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_RESP_ID          = 0x05, /**< "Image Block Response" command */
  ZB_ZCL_CMD_OTA_UPGRADE_UPGRADE_END_RESP_ID          = 0x07, /**< "Upgrade End Response" command */
  ZB_ZCL_CMD_OTA_UPGRADE_QUERY_SPECIFIC_FILE_RESP_ID  = 0x09, /**< "Query Specific File Response" command */
};

/** @cond internals_doc */
/* OTA Upgrade cluster commands list : only for information - do not modify */
#define ZB_ZCL_CLUSTER_ID_OTA_UPGRADE_SERVER_ROLE_GENERATED_CMD_LIST                           \
                                              ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_NOTIFY_ID,          \
                                              ZB_ZCL_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_RESP_ID, \
                                              ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_RESP_ID,      \
                                              ZB_ZCL_CMD_OTA_UPGRADE_UPGRADE_END_RESP_ID,      \
                                              ZB_ZCL_CMD_OTA_UPGRADE_QUERY_SPECIFIC_FILE_RESP_ID

#define ZB_ZCL_CLUSTER_ID_OTA_UPGRADE_CLIENT_ROLE_RECEIVED_CMD_LIST ZB_ZCL_CLUSTER_ID_OTA_UPGRADE_SERVER_ROLE_GENERATED_CMD_LIST

#define ZB_ZCL_CLUSTER_ID_OTA_UPGRADE_CLIENT_ROLE_GENERATED_CMD_LIST                           \
                                              ZB_ZCL_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_ID,      \
                                              ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_ID,           \
                                              ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_PAGE_ID,            \
                                              ZB_ZCL_CMD_OTA_UPGRADE_UPGRADE_END_ID,           \
                                              ZB_ZCL_CMD_OTA_UPGRADE_QUERY_SPECIFIC_FILE_ID

#define ZB_ZCL_CLUSTER_ID_OTA_UPGRADE_SERVER_ROLE_RECEIVED_CMD_LIST                            \
                                              ZB_ZCL_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_ID,      \
                                              ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_ID,           \
                                              ZB_ZCL_CMD_OTA_UPGRADE_UPGRADE_END_ID,           \
                                              ZB_ZCL_CMD_OTA_UPGRADE_QUERY_SPECIFIC_FILE_ID
/*! @}
 *  @endcond */ /* internals_doc */


/************************* Query Next Image Request **************************/

/*! @brief Structure representsation of Query Next Image Request command payload
  @see OTA spec, OTA Upgrade Cluster 6.10.4.1
*/typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_query_next_image_s
{
  zb_uint8_t fc;              /**< Field Control, see @ref zb_zcl_ota_upgrade_image_notify_payload_type_e */
  zb_uint16_t manufacturer;   /**< Manufacturer code */
  zb_uint16_t image_type;     /**< Image type */
  zb_uint32_t file_version;   /**< File version */
  zb_uint16_t hw_version;     /**< Hardware version */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_query_next_image_t;

/*! @brief OTA Image Upgrade Status Attribute Values
    @see OTA spec, OTA Upgrade Cluster 6.10.4.1.2
*/
enum zb_zcl_ota_upgrade_query_next_image_fc_e
{
  /*! @brief Hardware Version Present */
  ZB_ZCL_OTA_UPGRADE_QUERY_NEXT_IMAGE_HW_VERSION                = 1 << 0,
};

/*! @brief Send "Query Next Image Request" command, see OTA spec 6.10.4
    @param buffer to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param def_resp - enable/disable default response
    @param cb - callback
    @param fc - Field Control, see @ref zb_zcl_ota_upgrade_image_notify_payload_type_e
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
    @param hw_version - Hardware version
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_QUERY_NEXT_IMAGE_REQ(                       \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, def_resp, cb,         \
    fc, manufacturer, image_type, file_version, hw_version)                 \
{                                                                           \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET_REQ(buffer)                            \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_REQ_FRAME_CONTROL(ptr, (def_resp))     \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER_REQ(ptr, ZB_ZCL_GET_SEQ_NUM(),                \
      ZB_ZCL_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_ID);                          \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (fc));                                       \
  ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type));                        \
  ZB_ZCL_PACKET_PUT_DATA32_VAL(ptr, (file_version));                        \
  if( (fc) & ZB_ZCL_OTA_UPGRADE_QUERY_NEXT_IMAGE_HW_VERSION )               \
  {                                                                         \
    ZB_ZCL_PACKET_PUT_DATA16_VAL(ptr, (hw_version));                        \
  }                                                                         \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                                      \
  ZB_ZCL_SEND_COMMAND_SHORT(                                                \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,                     \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, cb);                                   \
}

/** @brief Macro for getting "Query Next Image Request" command, see OTA spec 6.10.4
  * @attention Assumes that ZCL header already cut.
  * @param data_ptr - pointer to a variable of type @ref
  * zb_zcl_ota_upgrade_query_next_image_s.
  * @param buffer containing the packet (by pointer).
  * @param status - variable to put parse status to (see @ref zb_zcl_parse_status_t).
  */
#define ZB_ZCL_OTA_UPGRADE_GET_QUERY_NEXT_IMAGE_REQ(data_ptr, buffer, status)     \
{                                                                                 \
  zb_zcl_ota_upgrade_query_next_image_t *src_ptr =                                \
       (zb_zcl_ota_upgrade_query_next_image_t*)ZB_BUF_BEGIN((buffer));            \
  if (ZB_BUF_LEN((buffer)) != sizeof(zb_zcl_ota_upgrade_query_next_image_t) -     \
      ( src_ptr->fc & ZB_ZCL_OTA_UPGRADE_QUERY_NEXT_IMAGE_HW_VERSION ) ? 0 : sizeof(zb_uint16_t) ) \
  {                                                                               \
   (status) = ZB_ZCL_PARSE_STATUS_FAILURE;                                        \
  }                                                                               \
  else                                                                            \
  {                                                                               \
    (status) = ZB_ZCL_PARSE_STATUS_SUCCESS;                                       \
    (data_ptr)->fc = src_ptr->fc;                                                 \
    ZB_HTOLE16(&((data_ptr)->manufacturer), &(src_ptr->manufacturer));            \
    ZB_HTOLE16(&((data_ptr)->image_type), &(src_ptr->image_type));                \
    ZB_HTOLE32(&((data_ptr)->file_version), &(src_ptr->file_version));            \
    if( src_ptr->fc & ZB_ZCL_OTA_UPGRADE_QUERY_NEXT_IMAGE_HW_VERSION )            \
    {                                                                             \
      ZB_HTOLE16(&((data_ptr)->hw_version), &(src_ptr->hw_version));              \
    }                                                                             \
  }                                                                               \
}

/************************* Image Block Request **************************/

/*! @brief Structure representsation of Image Block Request command payload
  @see OTA spec, OTA Upgrade Cluster 6.10.6.1
*/
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_image_block_s
{
  zb_uint8_t fc;              /**< Field Control, see @ref zb_zcl_ota_upgrade_image_block_fc_e */
  zb_uint16_t manufacturer;   /**< Manufacturer code */
  zb_uint16_t image_type;     /**< Image type */
  zb_uint32_t file_version;   /**< File version */
  zb_uint32_t file_offset;    /**< File offset */
  zb_uint8_t data_size_max;   /**< Maximum data size */

  zb_ieee_addr_t node_addr;   /**< Request node address*/
  zb_uint16_t block_delay;    /**< BlockRequestDelay */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_image_block_t;

/*! @brief OTA Image Upgrade Status Attribute Values
    @see OTA spec, OTA Upgrade Cluster 6.10.6.1.2
*/
enum zb_zcl_ota_upgrade_image_block_fc_e
{
  /*! @brief Request node’s IEEE address Present */
  ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_BLOCK_IEEE_PRESENT     = 1 << 0,
  /*! @brief BlockRequestDelay present */
  ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_BLOCK_DELAY_PRESENT    = 1 << 1,
};

/*! @brief Send "Image Block Request" command, see OTA spec 6.10.6
    @param buffer to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param def_resp - enable/disable default response
    @param cb - callback
    @param fc - Field Control, see @ref zb_zcl_ota_upgrade_image_block_fc_e
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
    @param file_offset - File offset
    @param data_size_max - Maximum data size
    @param node_addr - Request node address
    @param block_delay - BlockRequestDelay
    @param current_delay - Delay current send (millisec)
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_IMAGE_BLOCK_REQ(                            \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, def_resp, cb,         \
    fc, manufacturer, image_type, file_version, file_offset, data_size_max, \
    node_addr, block_delay, current_delay)                                  \
{                                                                           \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET_REQ(buffer)                            \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_REQ_FRAME_CONTROL(ptr, (def_resp))     \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER_REQ(ptr, ZB_ZCL_GET_SEQ_NUM(),                \
      ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_ID);                               \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (fc));                                       \
  ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type));                        \
  ZB_ZCL_PACKET_PUT_2DATA32_VAL(ptr, (file_version), (file_offset));                        \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (data_size_max));                            \
  if( (fc) & ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_BLOCK_IEEE_PRESENT)             \
  {                                                                         \
    ZB_ZCL_PACKET_PUT_DATA_IEEE(ptr, (node_addr));                          \
  }                                                                         \
  if( (fc) & ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_BLOCK_DELAY_PRESENT)            \
  {                                                                         \
    ZB_ZCL_PACKET_PUT_DATA16_VAL(ptr, (block_delay));                       \
  }                                                                         \
  ZB_ZCL_FINISH_PACKET_O((buffer), ptr)                                      \
  ZB_ZCL_SEND_COMMAND_SHORT_SCHEDULE(                                 \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,                     \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, cb,                                    \
      current_delay);                                                       \
}

/** @brief Macro for getting "Image Block Request" command, see OTA spec 6.10.6
  * @attention Assumes that ZCL header already cut.
  * @param data_ptr - pointer to a variable of type @ref
  * zb_zcl_ota_upgrade_image_block_s.
  * @param buffer containing the packet (by pointer).
  * @param status - variable to put parse status to (see @ref zb_zcl_parse_status_t).
  */
#define ZB_ZCL_OTA_UPGRADE_GET_IMAGE_BLOCK_REQ(data_ptr, buffer, status)  \
{                                                                         \
  zb_zcl_ota_upgrade_image_block_t *src_ptr =                             \
       (zb_zcl_ota_upgrade_image_block_t*)ZB_BUF_BEGIN((buffer));         \
                                                                          \
  if (ZB_BUF_LEN((buffer)) != sizeof(zb_zcl_ota_upgrade_image_block_t) -  \
      ( !(src_ptr->fc & ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_BLOCK_IEEE_PRESENT) ? sizeof(zb_ieee_addr_t) : 0) -    \
      ( !(src_ptr->fc & ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_BLOCK_DELAY_PRESENT) ? sizeof(zb_uint16_t) : 0) )      \
  {                                                                       \
   (status) = ZB_ZCL_PARSE_STATUS_FAILURE;                                \
  }                                                                       \
  else                                                                    \
  {                                                                       \
    (status) = ZB_ZCL_PARSE_STATUS_SUCCESS;                               \
    (data_ptr)->fc = src_ptr->fc;                                         \
    ZB_HTOLE16(&((data_ptr)->manufacturer), &(src_ptr->manufacturer));    \
    ZB_HTOLE16(&((data_ptr)->image_type), &(src_ptr->image_type));        \
    ZB_HTOLE32(&((data_ptr)->file_version), &(src_ptr->file_version));    \
    ZB_HTOLE32(&((data_ptr)->file_offset), &(src_ptr->file_offset));      \
    (data_ptr)->data_size_max = src_ptr->data_size_max;                   \
    if( src_ptr->fc & ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_BLOCK_IEEE_PRESENT)  \
    {                                                                     \
      ZB_IEEE_ADDR_COPY((data_ptr)->node_addr, (src_ptr)->node_addr);     \
    }                                                                     \
    if( src_ptr->fc & ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_BLOCK_DELAY_PRESENT) \
    {                                                                     \
      ZB_HTOLE16(&((data_ptr)->block_delay), &(src_ptr->block_delay));    \
    }                                                                     \
  }                                                                       \
}

/************************* Image Page Request **************************/

/*! @brief Structure representsation of Image Page Request command payload
  @see OTA spec, OTA Upgrade Cluster 6.10.7.1
*/
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_image_page_s
{
  zb_uint8_t fc;                /**< Field Control, see @ref zb_zcl_ota_upgrade_image_page_fc_e */
  zb_uint16_t manufacturer;     /**< Manufacturer code */
  zb_uint16_t image_type;       /**< Image type */
  zb_uint32_t file_version;     /**< File version */
  zb_uint32_t file_offset;      /**< File offset */
  zb_uint8_t data_size_max;     /**< Maximum data size */
  zb_uint16_t page_size;        /**< Page size */
  zb_uint16_t response_spacing; /**< Response Spacing */

  zb_ieee_addr_t node_addr;     /**< Request node address */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_image_page_t;

/*! @brief OTA Image Upgrade Status Attribute Values
    @see OTA spec, OTA Upgrade Cluster 6.10.7.1.2
*/
enum zb_zcl_ota_upgrade_image_page_fc_e
{
  /*! @brief Request node's IEEE address Present */
  ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_PAGE_IEEE_PRESENT     = 1 << 0,
};

/*! @brief Send "Image Page Request" command, see OTA spec 6.10.7
    @param buffer to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param def_resp - enable/disable default response
    @param cb - callback
    @param fc - Field Control, see @ref zb_zcl_ota_upgrade_image_page_fc_e
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
    @param file_offset - File offset
    @param data_size_max - Maximum data size
    @param page_size - Page size
    @param response_spacing - Response Spacing
    @param node_addr - Request node address
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_IMAGE_PAGE_REQ(                             \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, def_resp, cb,         \
    fc, manufacturer, image_type, file_version, file_offset, data_size_max, \
    page_size, response_spacing, node_addr)                                 \
{                                                                           \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET_REQ(buffer)                            \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_REQ_FRAME_CONTROL(ptr, (def_resp))     \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER_REQ(ptr, ZB_ZCL_GET_SEQ_NUM(),                \
      ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_PAGE_ID);                                \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (fc));                                       \
  ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type));                        \
  ZB_ZCL_PACKET_PUT_2DATA32_VAL(ptr, (file_version), (file_offset));                        \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (data_size_max));                            \
  ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (page_size), (response_spacing));                           \
  if( (fc) & ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_PAGE_IEEE_PRESENT)              \
  {                                                                         \
    ZB_ZCL_PACKET_PUT_DATA_IEEE(ptr, (node_addr));                          \
  }                                                                         \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                                      \
  ZB_ZCL_SEND_COMMAND_SHORT(                                                \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,                     \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, cb);                                   \
}

/** @brief Macro for getting "Image Page Request" command, see OTA spec 6.10.7
  * @attention Assumes that ZCL header already cut.
  * @param data_ptr - pointer to a variable of type @ref
  * zb_zcl_ota_upgrade_image_page_s.
  * @param buffer containing the packet (by pointer).
  * @param status - variable to put parse status to (see @ref zb_zcl_parse_status_t).
  */
#define ZB_ZCL_OTA_UPGRADE_GET_IMAGE_PAGE_REQ(data_ptr, buffer, status)   \
{                                                                         \
  zb_zcl_ota_upgrade_image_page_t *src_ptr =                              \
       (zb_zcl_ota_upgrade_image_page_t*)ZB_BUF_BEGIN((buffer));          \
                                                                          \
  if (ZB_BUF_LEN((buffer)) != sizeof(zb_zcl_ota_upgrade_image_page_t) -   \
      ((src_ptr->fc & ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_PAGE_IEEE_PRESENT) ? sizeof(zb_ieee_addr_t) : 0) )      \
  {                                                                       \
   (status) = ZB_ZCL_PARSE_STATUS_FAILURE;                                \
  }                                                                       \
  else                                                                    \
  {                                                                       \
    (status) = ZB_ZCL_PARSE_STATUS_SUCCESS;                               \
    (data_ptr)->fc = src_ptr->fc;                                         \
    ZB_HTOLE16(&((data_ptr)->manufacturer), &(src_ptr->manufacturer));    \
    ZB_HTOLE16(&((data_ptr)->image_type), &(src_ptr->image_type));        \
    ZB_HTOLE32(&((data_ptr)->file_version), &(src_ptr->file_version));    \
    ZB_HTOLE32(&((data_ptr)->file_offset), &(src_ptr->file_offset));      \
    (data_ptr)->data_size_max = src_ptr->data_size_max;                   \
    ZB_HTOLE16(&((data_ptr)->page_size), &(src_ptr->page_size));          \
    ZB_HTOLE16(&((data_ptr)->response_spacing), &(src_ptr->response_spacing));    \
    if( src_ptr->fc & ZB_ZCL_OTA_UPGRADE_QUERY_IMAGE_PAGE_IEEE_PRESENT)   \
    {                                                                     \
      ZB_IEEE_ADDR_COPY((data_ptr)->node_addr, (src_ptr)->node_addr);     \
    }                                                                     \
  }                                                                       \
}

/************************* Upgrade End Request **************************/

/*! @brief Structure representsation of Upgrade End Request command payload
  @see OTA spec, OTA Upgrade Cluster 6.10.9.1
*/typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_upgrade_end_s
{
  zb_uint8_t status;          /**< Status */
  zb_uint16_t manufacturer;   /**< Manufacturer code */
  zb_uint16_t image_type;     /**< Image type */
  zb_uint32_t file_version;   /**< File version */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_upgrade_end_t;

/*! @brief OTA Image Upgrade Status Attribute Values
    @see OTA spec, OTA Upgrade Cluster 6.10.9.1.2
*/
/*! @brief Send "Upgrade End Request" command, see OTA spec 6.10.9
    @param buffer to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param def_resp - enable/disable default response
    @param cb - callback
    @param status - Status, see @ref zb_zcl_status_e
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_UPGRADE_END_REQ(                            \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, def_resp, cb,         \
    status, manufacturer, image_type, file_version)                         \
{                                                                           \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET_REQ(buffer)                            \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_REQ_FRAME_CONTROL(ptr, (def_resp))     \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER_REQ(ptr, ZB_ZCL_GET_SEQ_NUM(),                \
      ZB_ZCL_CMD_OTA_UPGRADE_UPGRADE_END_ID);                               \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (status));                                   \
  ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type));                  \
  ZB_ZCL_PACKET_PUT_DATA32_VAL(ptr, (file_version));                        \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                                      \
  ZB_ZCL_SEND_COMMAND_SHORT(                                                \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,                     \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, cb);                                   \
}

/** @brief Macro for getting "Upgrade End Request" command, see OTA spec 6.10.9
  * @attention Assumes that ZCL header already cut.
  * @param data_ptr - pointer to a variable of type @ref
  * zb_zcl_ota_upgrade_upgrade_end_s.
  * @param buffer containing the packet (by pointer).
  * @param status_ - variable to put parse status to (see @ref zb_zcl_parse_status_t).
  */
#define ZB_ZCL_OTA_UPGRADE_GET_UPGRADE_END_REQ(data_ptr, buffer, status_) \
{                                                                         \
  zb_zcl_ota_upgrade_upgrade_end_t *src_ptr =                             \
       (zb_zcl_ota_upgrade_upgrade_end_t*)ZB_BUF_BEGIN((buffer));         \
                                                                          \
  if (ZB_BUF_LEN((buffer)) != sizeof(zb_zcl_ota_upgrade_upgrade_end_t) )  \
  {                                                                       \
   (status_) = ZB_ZCL_PARSE_STATUS_FAILURE;                               \
  }                                                                       \
  else                                                                    \
  {                                                                       \
    (status_) = ZB_ZCL_PARSE_STATUS_SUCCESS;                              \
    (data_ptr)->status = src_ptr->status;                                 \
    ZB_HTOLE16(&((data_ptr)->manufacturer), &(src_ptr->manufacturer));    \
    ZB_HTOLE16(&((data_ptr)->image_type), &(src_ptr->image_type));        \
    ZB_HTOLE32(&((data_ptr)->file_version), &(src_ptr->file_version));    \
  }                                                                       \
}

/************************* Query Specific File Request **************************/

/*! @brief Structure representsation of Query Specific File Request command payload
  @see OTA spec, OTA Upgrade Cluster 6.10.11.1
*/typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_query_specific_file_s
{
  zb_ieee_addr_t node_addr;     /**< Node address */
  zb_uint16_t manufacturer;     /**< Manufacturer code */
  zb_uint16_t image_type;       /**< Image type */
  zb_uint32_t file_version;     /**< File version */
  zb_uint16_t stack_version;    /**< Zigbee stack version */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_query_specific_file_t;

/*! @brief Send "Query Specific File Request" command, see OTA spec 6.10.11
    @param buffer to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param def_resp - enable/disable default response
    @param cb - callback
    @param node_addr - Node address
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
    @param stack_version - Zigbee stack version
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_QUERY_SPECIFIC_FILE_REQ(                    \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, def_resp, cb,         \
    node_addr, manufacturer, image_type, file_version, stack_version)       \
{                                                                           \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET_REQ(buffer)                            \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_REQ_FRAME_CONTROL(ptr, (def_resp))     \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER_REQ(ptr, ZB_ZCL_GET_SEQ_NUM(),                \
      ZB_ZCL_CMD_OTA_UPGRADE_QUERY_SPECIFIC_FILE_ID);                       \
  ZB_ZCL_PACKET_PUT_DATA_IEEE(ptr, (node_addr));                            \
  ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type));                        \
  ZB_ZCL_PACKET_PUT_DATA32_VAL(ptr, (file_version));                        \
  ZB_ZCL_PACKET_PUT_DATA16_VAL(ptr, (stack_version));                       \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                                      \
  ZB_ZCL_SEND_COMMAND_SHORT(                                                \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,                     \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, cb);                                   \
}

/** @brief Macro for getting "Query Specific File Request" command, see OTA spec 6.10.11
  * @attention Assumes that ZCL header already cut.
  * @param data_ptr - pointer to a variable of type @ref
  * zb_zcl_ota_upgrade_query_specific_file_s.
  * @param buffer containing the packet (by pointer).
  * @param status - variable to put parse status to (see @ref zb_zcl_parse_status_t).
  */
#define ZB_ZCL_OTA_UPGRADE_GET_QUERY_SPECIFIC_FILE_REQ(data_ptr, buffer, status)  \
{                                                                         \
  if (ZB_BUF_LEN((buffer)) != sizeof(zb_zcl_ota_upgrade_query_specific_file_t) )  \
  {                                                                       \
   (status) = ZB_ZCL_PARSE_STATUS_FAILURE;                                \
  }                                                                       \
  else                                                                    \
  {                                                                       \
    zb_zcl_ota_upgrade_query_specific_file_t *src_ptr =                   \
       (zb_zcl_ota_upgrade_query_specific_file_t*)ZB_BUF_BEGIN((buffer)); \
    (status) = ZB_ZCL_PARSE_STATUS_SUCCESS;                               \
    ZB_IEEE_ADDR_COPY((data_ptr)->node_addr, (src_ptr)->node_addr);       \
    ZB_HTOLE16(&((data_ptr)->manufacturer), &(src_ptr->manufacturer));    \
    ZB_HTOLE16(&((data_ptr)->image_type), &(src_ptr->image_type));        \
    ZB_HTOLE32(&((data_ptr)->file_version), &(src_ptr->file_version));    \
    ZB_HTOLE16(&((data_ptr)->stack_version), &(src_ptr->stack_version));  \
  }                                                                       \
}

/******************************* Image Notify ******************************/

/*! @brief Structure representsation of Image Notify response command payload
    @see OTA spec, OTA Upgrade Cluster 6.10.3.1
*/
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_image_notify_s
{
  zb_uint8_t payload_type;  /** Payload type, see @ref zb_zcl_ota_upgrade_image_notify_payload_type_e */
  zb_uint8_t query_jitter;  /** Query jitter */
  zb_uint16_t manufacturer; /** Manufacturer code */
  zb_uint16_t image_type;   /** Image type */
  zb_uint32_t file_version; /** File version */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_image_notify_t;

/*! @brief OTA Image Upgrade Status Attribute Values
    @see OTA spec, OTA Upgrade Cluster 6.10.3.2
*/
enum zb_zcl_ota_upgrade_image_notify_payload_type_e
{
  /*! @brief Query jitter */
  ZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_JITTER                = 0x00,
  /*! @brief Query jitter and manufacturer code */
  ZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_JITTER_CODE           = 0x01,
  /*! @brief Query jitter, manufacturer code, and image type */
  ZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_JITTER_CODE_IMAGE     = 0x02,
  /*! @brief Query jitter, manufacturer code, image type, and new file version */
  ZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_JITTER_CODE_IMAGE_VER = 0x03,
};

/*! @brief Send Image Notify command, see OTA spec 6.10.3
    @param buffer - to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param def_resp - enable/disable default response
    @param cb - callback for getting command send status
    @param payload_type - Payload type
    @param query_jitter - Query jitter
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_IMAGE_NOTIFY_REQ(                           \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, def_resp, cb,         \
    payload_type, query_jitter, manufacturer, image_type, file_version)     \
{                                                                           \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET(buffer);                            \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_REQ_FRAME_CONTROL_A(                \
    ptr, ZB_ZCL_FRAME_DIRECTION_TO_CLI,                                 \
    ZB_ZCL_NOT_MANUFACTURER_SPECIFIC, (def_resp));                      \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER(ptr, ZB_ZCL_GET_SEQ_NUM(),                \
                                  ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_NOTIFY_ID); \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (payload_type));                             \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (query_jitter));                             \
  ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type));     \
  ZB_ZCL_PACKET_PUT_DATA32_VAL(ptr, (file_version));                        \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                                       \
  ZB_ZCL_SEND_COMMAND_SHORT(                                                \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,                     \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, cb);                                   \
}


#define ZB_ZCL_OTA_UPGRADE_GET_IMAGE_NOTIFY_REQ(data_ptr, buffer, status) \
{                                                                         \
  if (ZB_BUF_LEN((buffer)) <= sizeof(zb_uint8_t))  \
  {                                                                       \
   (status) = ZB_ZCL_PARSE_STATUS_FAILURE;                                \
  }                                                                       \
  else                                                                    \
  {                                                                       \
    zb_zcl_ota_upgrade_image_notify_t *src_ptr =                          \
         (zb_zcl_ota_upgrade_image_notify_t*)ZB_BUF_BEGIN((buffer));      \
    (status) = ZB_ZCL_PARSE_STATUS_SUCCESS;                               \
    (data_ptr)->payload_type = src_ptr->payload_type;                     \
    (data_ptr)->query_jitter = src_ptr->query_jitter;                     \
    switch ( src_ptr->payload_type )                                      \
    {                                                                     \
      case 0x03:                                                          \
        ZB_HTOLE32(&((data_ptr)->file_version), &(src_ptr->file_version));\
        /* FALLTHROUGH */                                                 \
      case 0x02:                                                          \
        ZB_HTOLE16(&((data_ptr)->image_type), &(src_ptr->image_type));    \
        /* FALLTHROUGH */                                                 \
      case 0x01:                                                          \
        ZB_HTOLE16(&((data_ptr)->manufacturer), &(src_ptr->manufacturer));\
        /* FALLTHROUGH */                                                 \
    default:                                                              \
        break;                                                            \
    }                                                                     \
  }                                                                       \
}




/******************************* Query Next Image Response  ******************************/

/*! @brief Structure representsation of Query Next Image Response command payload
  @see OTA spec, OTA Upgrade Cluster 6.10.5.1
*/typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_query_next_image_res_s
{
  zb_uint8_t status;        /** Status, see @ref zb_zcl_status_e */
  zb_uint16_t manufacturer; /** Manufacturer code */
  zb_uint16_t image_type;   /** Image type */
  zb_uint32_t file_version; /** File version */
  zb_uint32_t image_size;   /** Image size */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_query_next_image_res_t;


/*! @brief Send Query Next Image Response command, see OTA spec 6.10.5
    @param buffer - to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param seq - sequence
    @param status - Status, see @ref zb_zcl_status_e
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
    @param image_size - Image size
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_QUERY_NEXT_IMAGE_RES(               \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, seq,          \
    status, manufacturer, image_type, file_version, image_size)     \
{                                                                   \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET(buffer);                    \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_RES_FRAME_CONTROL(ptr);         \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER(ptr, seq,                         \
      ZB_ZCL_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_RESP_ID);             \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (status));                           \
  if( (status) == ZB_ZCL_STATUS_SUCCESS)                            \
  {                                                                 \
    ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type));   \
    ZB_ZCL_PACKET_PUT_2DATA32_VAL(ptr, (file_version), (image_size));              \
  }                                                                 \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                              \
  ZB_ZCL_SEND_COMMAND_SHORT(                                        \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,             \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, NULL);                         \
}

/** @brief Macro for getting Query Next Image Response command, see OTA spec 6.10.5
  * @attention Assumes that ZCL header already cut.
  * @param data_ptr - pointer to a variable of type @ref
  * zb_zcl_ota_upgrade_query_next_image_res_s.
  * @param buffer containing the packet (by pointer).
  * @param status_ - variable to put parse status to (see @ref zb_zcl_parse_status_t).
  */
#define ZB_ZCL_OTA_UPGRADE_GET_QUERY_NEXT_IMAGE_RES(data_ptr, buffer, status_)\
{                                                                             \
  zb_zcl_ota_upgrade_query_next_image_res_t *src_ptr =                        \
       (zb_zcl_ota_upgrade_query_next_image_res_t*)ZB_BUF_BEGIN((buffer));    \
                                                                              \
  if (ZB_BUF_LEN((buffer)) != ( (src_ptr->status)==ZB_ZCL_STATUS_SUCCESS ?    \
     sizeof(zb_zcl_ota_upgrade_query_next_image_res_t) : sizeof(zb_uint8_t))) \
  {                                                                           \
    (status_) = ZB_ZCL_PARSE_STATUS_FAILURE;                                  \
    TRACE_MSG(TRACE_ZLL1, "ERROR: buf_len %i", (FMT__H, ZB_BUF_LEN((buffer)))); \
  }                                                                           \
  else                                                                        \
  {                                                                           \
    (status_) = ZB_ZCL_PARSE_STATUS_SUCCESS;                                  \
    (data_ptr)->status = src_ptr->status;                                     \
    if( src_ptr->status == ZB_ZCL_STATUS_SUCCESS)                             \
    {                                                                         \
      ZB_HTOLE16(&((data_ptr)->manufacturer), &(src_ptr->manufacturer));      \
      ZB_HTOLE16(&((data_ptr)->image_type), &(src_ptr->image_type));          \
      ZB_HTOLE32(&((data_ptr)->file_version), &(src_ptr->file_version));      \
      ZB_HTOLE32(&((data_ptr)->image_size), &(src_ptr->image_size));          \
    }                                                                         \
  }                                                                           \
}

/******************************* Image Block Response ******************************/

/*! @brief Structure representsation of Image Block Response command payload
  @see OTA spec, OTA Upgrade Cluster 6.10.8.1
*/
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_image_block_res_s
{
  /** Status, see @ref zb_zcl_status_e */
  zb_uint8_t status;
  ZB_PACKED_PRE union
  {
    ZB_PACKED_PRE struct
    {
      zb_uint16_t manufacturer;     /**< Manufacturer code */
      zb_uint16_t image_type;       /**< Image type */
      zb_uint32_t file_version;     /**< File version */
      zb_uint32_t file_offset;      /**< File offset */
      zb_uint8_t data_size;         /**< Data size */
      zb_uint8_t *image_data;       /**< Image data */

    } ZB_PACKED_STRUCT success;     /**< Success response. */

    ZB_PACKED_PRE struct
    {
      zb_uint32_t current_time;     /**< Current time */
      zb_uint32_t request_time;     /**< Request time */
      zb_uint16_t delay;            /**< BlockRequestDelay */

    } ZB_PACKED_STRUCT wait_for_data;  /**< Wait for data  */

  } response;           /**< response data */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_image_block_res_t;

/*! @brief Send Image Block Response command - success status, see OTA spec 6.10.8
    @param buffer - to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param seq - sequence
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
    @param file_offset - File offset
    @param data_size - data size
    @param image_data - image data
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_IMAGE_BLOCK_SUCCESS_RES(            \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, seq,          \
    manufacturer, image_type, file_version, file_offset, data_size, image_data)     \
{                                                                   \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET(buffer);                    \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_RES_FRAME_CONTROL(ptr);         \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER(ptr, seq,                         \
      ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_RESP_ID);                  \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, ZB_ZCL_STATUS_SUCCESS);              \
  ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type)); \
  ZB_ZCL_PACKET_PUT_2DATA32_VAL(ptr, (file_version), (file_offset));                \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (data_size));                        \
  ZB_ASSERT(image_data != NULL);                                    \
  ZB_ZCL_PACKET_PUT_DATA_N(ptr, (image_data), (data_size));         \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                              \
  ZB_ZCL_SEND_COMMAND_SHORT(                                        \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,             \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, NULL);                         \
}

/*! @brief Send Image Block Response command - wait for data status, see OTA spec 6.10.8
    @param buffer - to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param seq - sequence
    @param current_time - Current time
    @param request_time - Request time
    @param delay - BlockRequestDelay
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_IMAGE_BLOCK_WAIT_FOR_DATA_RES(      \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, seq,          \
    current_time, request_time, delay)                              \
{                                                                   \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET(buffer);                    \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_RES_FRAME_CONTROL(ptr);         \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER(ptr, seq,                         \
      ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_RESP_ID);                  \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, ZB_ZCL_STATUS_WAIT_FOR_DATA);        \
  ZB_ZCL_PACKET_PUT_2DATA32_VAL(ptr, (current_time), (request_time));                \
  ZB_ZCL_PACKET_PUT_DATA16_VAL(ptr, (delay));                       \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                              \
  ZB_ZCL_SEND_COMMAND_SHORT(                                        \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,             \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, NULL);                         \
}

/*! @brief Send Image Block Response command - abort status, see OTA spec 6.10.8
    @param buffer - to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param seq - sequence
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_IMAGE_BLOCK_ABORT_RES(              \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, seq)          \
{                                                                   \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET(buffer);                    \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_RES_FRAME_CONTROL(ptr);         \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER(ptr, seq,                         \
      ZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_RESP_ID);                  \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, ZB_ZCL_STATUS_ABORT);                \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                              \
  ZB_ZCL_SEND_COMMAND_SHORT(                                        \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,             \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, NULL);                         \
}

/** @brief Macro for getting Image Block Response command, see OTA spec 6.10.8
  * @attention Assumes that ZCL header already cut.
  * @param data_ptr - pointer to a variable of type @ref
  * zb_zcl_ota_upgrade_image_block_res_s.
  * @param buffer containing the packet (by pointer).
  * @param status_ - variable to put parse status to (see @ref zb_zcl_parse_status_t).
  *
  * NOTE file data place`s in buffer, payload saves pointer to data only!
  */
#define ZB_ZCL_OTA_UPGRADE_GET_IMAGE_BLOCK_RES(data_ptr, buffer, status_)     \
{                                                                             \
  zb_zcl_ota_upgrade_image_block_res_t *src_ptr =                             \
       (zb_zcl_ota_upgrade_image_block_res_t*)ZB_BUF_BEGIN((buffer));         \
                                                                              \
  if (ZB_BUF_LEN((buffer)) != sizeof(zb_uint8_t) +                            \
      ((src_ptr->status)==ZB_ZCL_STATUS_SUCCESS ?                             \
          sizeof(src_ptr->response.success) - sizeof(zb_uint8_t*)+            \
                src_ptr->response.success.data_size : 0) +                    \
      ((src_ptr->status)==ZB_ZCL_STATUS_WAIT_FOR_DATA ?                       \
          sizeof(src_ptr->response.wait_for_data) : 0) )                      \
  {                                                                           \
    (status_) = ZB_ZCL_PARSE_STATUS_FAILURE;                                  \
  }                                                                           \
  else                                                                        \
  {                                                                           \
    (status_) = ZB_ZCL_PARSE_STATUS_SUCCESS;                                  \
    (data_ptr)->status = src_ptr->status;                                     \
    if( src_ptr->status == ZB_ZCL_STATUS_SUCCESS)                             \
    {                                                                         \
      ZB_HTOLE16(&((data_ptr)->response.success.manufacturer),                \
          &(src_ptr->response.success.manufacturer));                         \
      ZB_HTOLE16(&((data_ptr)->response.success.image_type),                  \
          &(src_ptr->response.success.image_type));                           \
      ZB_HTOLE32(&((data_ptr)->response.success.file_version),                \
          &(src_ptr->response.success.file_version));                         \
      ZB_HTOLE32(&((data_ptr)->response.success.file_offset),                 \
          &(src_ptr->response.success.file_offset));                          \
      (data_ptr)->response.success.data_size =                                \
          src_ptr->response.success.data_size;                                \
      /*ZB_MEMCPY((data_ptr)->response.success.image_data,  */                \
      /*    src_ptr->response.success.image_data,           */                \
      /*    src_ptr->response.success.data_size);           */                \
      (data_ptr)->response.success.image_data =                               \
          (zb_uint8_t*)(&(src_ptr->response.success.image_data));             \
    }                                                                         \
    if( src_ptr->status == ZB_ZCL_STATUS_WAIT_FOR_DATA)                       \
    {                                                                         \
      ZB_HTOLE32(&((data_ptr)->response.wait_for_data.current_time),          \
          &(src_ptr->response.wait_for_data.current_time));                   \
      ZB_HTOLE32(&((data_ptr)->response.wait_for_data.request_time),          \
          &(src_ptr->response.wait_for_data.request_time));                   \
      ZB_HTOLE16(&((data_ptr)->response.wait_for_data.delay),                 \
          &(src_ptr->response.wait_for_data.delay));                          \
    }                                                                         \
  }                                                                           \
}

/******************************* Upgrade End Response ******************************/

/*! @brief Structure representsation of Upgrade End  Response command payload
  @see OTA spec, OTA Upgrade Cluster 6.10.10.1
*/
typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_upgrade_end_res_s
{
  zb_uint16_t manufacturer;   /**< Manufacturer code */
  zb_uint16_t image_type;     /**< Image type */
  zb_uint32_t file_version;   /**< File version */
  zb_uint32_t current_time;   /**< Current time */
  zb_uint32_t upgrade_time;   /**< Upgrade time */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_upgrade_end_res_t;


/*! @brief Send Upgrade End  Response command, see OTA spec 6.10.10
    @param buffer - to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param seq - sequence
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
    @param current_time - Current time
    @param upgrade_time - Upgrade time
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_UPGRADE_END_RES(                    \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, seq,          \
    manufacturer, image_type, file_version, current_time, upgrade_time) \
{                                                                   \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET(buffer);                    \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_RES_FRAME_CONTROL(ptr);         \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER(ptr, seq,                         \
      ZB_ZCL_CMD_OTA_UPGRADE_UPGRADE_END_RESP_ID);                  \
  ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type));  \
  ZB_ZCL_PACKET_PUT_2DATA32_VAL(ptr, (file_version), (current_time));                \
  ZB_ZCL_PACKET_PUT_DATA32_VAL(ptr, (upgrade_time));                \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                              \
  ZB_ZCL_SEND_COMMAND_SHORT(                                        \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,             \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, NULL);                         \
}

/** @brief Macro for getting Upgrade End  Response command, see OTA spec 6.10.10
  * @attention Assumes that ZCL header already cut.
  * @param data_ptr - pointer to a variable of type @ref
  * zb_zcl_ota_upgrade_upgrade_end_res_s.
  * @param buffer containing the packet (by pointer).
  * @param status_ - variable to put parse status to (see @ref zb_zcl_parse_status_t).
  */
#define ZB_ZCL_OTA_UPGRADE_GET_UPGRADE_END_RES(data_ptr, buffer, status_)     \
{                                                                             \
  if (ZB_BUF_LEN((buffer)) != sizeof(zb_zcl_ota_upgrade_upgrade_end_res_t) )  \
  {                                                                           \
    (status_) = ZB_ZCL_PARSE_STATUS_FAILURE;                                  \
  }                                                                           \
  else                                                                        \
  {                                                                           \
    zb_zcl_ota_upgrade_upgrade_end_res_t *src_ptr =                           \
         (zb_zcl_ota_upgrade_upgrade_end_res_t*)ZB_BUF_BEGIN((buffer));       \
    (status_) = ZB_ZCL_PARSE_STATUS_SUCCESS;                                  \
    ZB_HTOLE16(&((data_ptr)->manufacturer), &(src_ptr->manufacturer));        \
    ZB_HTOLE16(&((data_ptr)->image_type), &(src_ptr->image_type));            \
    ZB_HTOLE32(&((data_ptr)->file_version), &(src_ptr->file_version));        \
    ZB_HTOLE32(&((data_ptr)->current_time), &(src_ptr->current_time));        \
    ZB_HTOLE32(&((data_ptr)->upgrade_time), &(src_ptr->upgrade_time));        \
  }                                                                           \
}

/******************************* Query Specific File Response ******************************/

/*! @brief Structure representsation of Query Specific File  Response command payload
  @see OTA spec, OTA Upgrade Cluster 6.10.12.1
*/typedef ZB_PACKED_PRE struct zb_zcl_ota_upgrade_query_specific_file_res_s
{
  zb_uint8_t status;        /** Status, see @ref zb_zcl_status_e */
  zb_uint16_t manufacturer; /** Manufacturer code */
  zb_uint16_t image_type;   /** Image type */
  zb_uint32_t file_version; /** File version */
  zb_uint32_t image_size;   /** Image size */

} ZB_PACKED_STRUCT zb_zcl_ota_upgrade_query_specific_file_res_t;


/*! @brief Send Query Specific File  Response command, see OTA spec 6.10.12
    @param buffer - to put packet to
    @param addr - address to send packet to
    @param dst_addr_mode - addressing mode
    @param dst_ep - destination endpoint
    @param ep - sending endpoint
    @param prfl_id - profile identifier
    @param seq - sequence
    @param status - Status, see @ref zb_zcl_status_e
    @param manufacturer - Manufacturer code
    @param image_type - Image type
    @param file_version - File version
    @param image_size - Image size
*/
#define ZB_ZCL_OTA_UPGRADE_SEND_QUERY_SPECIFIC_FILE_RES(            \
    buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id, seq,          \
    status, manufacturer, image_type, file_version, image_size)     \
{                                                                   \
  zb_uint8_t* ptr = ZB_ZCL_START_PACKET(buffer);                    \
  ZB_ZCL_CONSTRUCT_SPECIFIC_COMMAND_RES_FRAME_CONTROL(ptr);         \
  ZB_ZCL_CONSTRUCT_COMMAND_HEADER(ptr, seq,                         \
      ZB_ZCL_CMD_OTA_UPGRADE_QUERY_SPECIFIC_FILE_RESP_ID);          \
  ZB_ZCL_PACKET_PUT_DATA8(ptr, (status));                           \
  if( (status) == ZB_ZCL_STATUS_SUCCESS)                            \
  {                                                                 \
    ZB_ZCL_PACKET_PUT_2DATA16_VAL(ptr, (manufacturer), (image_type));   \
    ZB_ZCL_PACKET_PUT_2DATA32_VAL(ptr, (file_version), (image_size));              \
  }                                                                 \
  ZB_ZCL_FINISH_PACKET((buffer), ptr)                              \
  ZB_ZCL_SEND_COMMAND_SHORT(                                        \
      buffer, addr, dst_addr_mode, dst_ep, ep, prfl_id,             \
      ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, NULL);                         \
}

/** @brief Macro for getting Query Specific File  Response command, see OTA spec 6.10.12
  * @attention Assumes that ZCL header already cut.
  * @param data_ptr - pointer to a variable of type @ref
  * zb_zcl_ota_upgrade_query_specific_file_res_s.
  * @param buffer containing the packet (by pointer).
  * @param status_ - variable to put parse status to (see @ref zb_zcl_parse_status_t).
  */
#define ZB_ZCL_OTA_UPGRADE_GET_QUERY_SPECIFIC_FILE_RES(data_ptr, buffer, status_)   \
{                                                                                   \
  zb_zcl_ota_upgrade_query_specific_file_res_t *src_ptr =                           \
       (zb_zcl_ota_upgrade_query_specific_file_res_t*)ZB_BUF_BEGIN((buffer));       \
  if (ZB_BUF_LEN((buffer)) != ( (src_ptr->status)==ZB_ZCL_STATUS_SUCCESS ?          \
      sizeof(zb_zcl_ota_upgrade_query_specific_file_res_t) : sizeof(zb_uint8_t) ) ) \
  {                                                                                 \
    (status_) = ZB_ZCL_PARSE_STATUS_FAILURE;                                  \
  }                                                                           \
  else                                                                        \
  {                                                                           \
    (status_) = ZB_ZCL_PARSE_STATUS_SUCCESS;                                  \
    (data_ptr)->status = src_ptr->status;                                     \
    if( src_ptr->status == ZB_ZCL_STATUS_SUCCESS)                             \
    {                                                                         \
      ZB_HTOLE32(&((data_ptr)->manufacturer), &(src_ptr->manufacturer));      \
      ZB_HTOLE32(&((data_ptr)->image_type), &(src_ptr->image_type));          \
      ZB_HTOLE32(&((data_ptr)->file_version), &(src_ptr->file_version));      \
      ZB_HTOLE32(&((data_ptr)->image_size), &(src_ptr->image_size));          \
    }                                                                         \
  }                                                                           \
}

/*! @} */ /* OTA Upgrade cluster commands */



#if defined ZB_HA_ENABLE_OTA_UPGRADE_CLIENT || defined DOXYGEN

/** @brief Declare User Application about upgrade status
*/
typedef struct zb_zcl_ota_upgrade_value_param_s
{
  zb_uint8_t upgrade_status;          /**< Upgrade status, see @ref zb_zcl_ota_upgrade_status_e */
  union
  {
    struct zb_zcl_ota_upgrade_start_s
    {
      zb_uint16_t manufacturer;       /**< Manufacturer code */
      zb_uint16_t image_type;         /**< Image type */
      zb_uint32_t file_version;       /**< File version */
      zb_uint32_t file_length;        /**< File length */
    } start;                          /**< Parameters for start load upgrade file */
    struct zb_zcl_ota_upgrade_receive_s
    {
      zb_uint32_t file_offset;        /**< File offset */
      zb_uint8_t data_length;         /**< Data length */
      zb_uint8_t *block_data;         /**< Block data */
    } receive;                        /**< Parameters for receive part upgrade file */

  } upgrade;                          /**< Upgrade data */

} zb_zcl_ota_upgrade_value_param_t;

/** @brief Possible statuses of OTA upgrade
 */
enum zb_zcl_ota_upgrade_status_e
{
  ZB_ZCL_OTA_UPGRADE_STATUS_START,
  ZB_ZCL_OTA_UPGRADE_STATUS_APPLY,
  ZB_ZCL_OTA_UPGRADE_STATUS_RECEIVE,
  ZB_ZCL_OTA_UPGRADE_STATUS_FINISH,
  ZB_ZCL_OTA_UPGRADE_STATUS_ABORT,
  ZB_ZCL_OTA_UPGRADE_STATUS_CHECK,              // ask user app about received file
  ZB_ZCL_OTA_UPGRADE_STATUS_OK,                 // user app return value
  ZB_ZCL_OTA_UPGRADE_STATUS_ERROR,              // user app return value
  ZB_ZCL_OTA_UPGRADE_STATUS_REQUIRE_MORE_IMAGE, // user app return value
  ZB_ZCL_OTA_UPGRADE_STATUS_BUSY,               // user app return value.
                                                // Application is responsible for resuming OTA Upgrade process when it
                                                // return that error code to the OTA cluster */
};

/** @cond internals_doc */
#define ZB_ZCL_OTA_UPGRADE_START_USER_APP(buffer,                   \
  manufacturer_, image_type_, file_version_, file_length_, result)  \
{                                                                   \
  TRACE_MSG(TRACE_ZCL1, "ZB_ZCL_OTA_UPGRADE_START_USER_APP", (FMT__0)); \
  if (ZCL_CTX().device_cb)                                          \
  {                                                                 \
    zb_zcl_device_callback_param_t *user_app_data =                 \
        ZB_GET_BUF_PARAM(buffer, zb_zcl_device_callback_param_t);      \
    zb_zcl_ota_upgrade_value_param_t *value =                       \
        &(user_app_data->cb_param.ota_value_param);                 \
    value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_START;        \
    value->upgrade.start.manufacturer = (manufacturer_);            \
    value->upgrade.start.image_type  = (image_type_);               \
    value->upgrade.start.file_version = (file_version_);            \
    value->upgrade.start.file_length = (file_length_);              \
    user_app_data->device_cb_id = ZB_ZCL_OTA_UPGRADE_VALUE_CB_ID;   \
    user_app_data->endpoint = get_endpoint_by_cluster(ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE); \
    user_app_data->status = RET_OK;                                 \
    (ZCL_CTX().device_cb)(param);                                   \
    result = value->upgrade_status;                                 \
  }                                                                 \
}

// NOTE file data place`s in buffer, payload saves pointer to data only!
#define ZB_ZCL_OTA_UPGRADE_RECEIVE_USER_APP(buffer,                 \
                                            file_offset_, data_length_, block_data_, result) \
{                                                                   \
  TRACE_MSG(TRACE_ZCL1, "ZB_ZCL_OTA_UPGRADE_RECEIVE_USER_APP", (FMT__0)); \
  if (ZCL_CTX().device_cb)                                          \
  {                                                                 \
    zb_zcl_device_callback_param_t *user_app_data =                 \
      ZB_GET_BUF_PARAM(buffer, zb_zcl_device_callback_param_t);     \
    zb_zcl_ota_upgrade_value_param_t *value =                       \
        &(user_app_data->cb_param.ota_value_param);                 \
    value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_RECEIVE;      \
    value->upgrade.receive.file_offset = (file_offset_);            \
    value->upgrade.receive.data_length = (data_length_);            \
    value->upgrade.receive.block_data  = (block_data_);             \
    user_app_data->device_cb_id = ZB_ZCL_OTA_UPGRADE_VALUE_CB_ID;   \
    user_app_data->endpoint = get_endpoint_by_cluster(ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE); \
    user_app_data->status = RET_OK;                                 \
    (ZCL_CTX().device_cb)(param);                                   \
    result = value->upgrade_status;                                 \
  }                                                                 \
}

#define ZB_ZCL_OTA_UPGRADE_FINISH_USER_APP(buffer, result)          \
{                                                                   \
  zb_zcl_device_callback_param_t *user_app_data =                   \
      ZB_GET_BUF_PARAM(buffer, zb_zcl_device_callback_param_t);     \
  TRACE_MSG(TRACE_ZCL1, "ZB_ZCL_OTA_UPGRADE_FINISH_USER_APP", (FMT__0)); \
  result = ZB_ZCL_OTA_UPGRADE_STATUS_ERROR;                         \
  if (ZCL_CTX().device_cb)                                          \
  {                                                                 \
    zb_zcl_ota_upgrade_value_param_t *value =                       \
        &(user_app_data->cb_param.ota_value_param);                 \
    value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_FINISH;       \
    user_app_data->device_cb_id = ZB_ZCL_OTA_UPGRADE_VALUE_CB_ID;   \
    user_app_data->endpoint = get_endpoint_by_cluster(ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE); \
    user_app_data->status = RET_OK;                                 \
    (ZCL_CTX().device_cb)(param);                                   \
    if (user_app_data->status == RET_OK)                            \
    {                                                               \
      result = value->upgrade_status;                               \
    }                                                               \
  }else                                                             \
  {                                                                 \
    result = ZB_ZCL_OTA_UPGRADE_STATUS_OK;                          \
  }                                                                 \
}                                                                   \

#define ZB_ZCL_OTA_UPGRADE_APPLY_USER_APP(buffer, result)          \
{                                                                   \
  zb_zcl_device_callback_param_t *user_app_data =                   \
      ZB_GET_BUF_PARAM(buffer, zb_zcl_device_callback_param_t);     \
  TRACE_MSG(TRACE_ZCL1, "ZB_ZCL_OTA_UPGRADE_APPLY_USER_APP", (FMT__0)); \
  result = ZB_ZCL_OTA_UPGRADE_STATUS_ERROR;                         \
  if (ZCL_CTX().device_cb)                                          \
  {                                                                 \
    zb_zcl_ota_upgrade_value_param_t *value =                       \
        &(user_app_data->cb_param.ota_value_param);                 \
    value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_APPLY;       \
    user_app_data->device_cb_id = ZB_ZCL_OTA_UPGRADE_VALUE_CB_ID;   \
    user_app_data->endpoint = get_endpoint_by_cluster(ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE); \
    user_app_data->status = RET_OK;                                 \
    (ZCL_CTX().device_cb)(param);                                   \
    if (user_app_data->status == RET_OK)                            \
    {                                                               \
      result = value->upgrade_status;                               \
    }                                                               \
  }else                                                             \
  {                                                                 \
    result = ZB_ZCL_OTA_UPGRADE_STATUS_OK;                          \
  }                                                                 \
}                                                                   \

/* NK:WARNING: Implicit passing "param" to device_cb!
   TODO: Fix all cases! Use ZB_REF_FROM_BUF instead. */
#define ZB_ZCL_OTA_UPGRADE_ABORT_USER_APP(buffer)                   \
{                                                                   \
  TRACE_MSG(TRACE_ZCL1, "ZB_ZCL_OTA_UPGRADE_ABORT_USER_APP", (FMT__0)); \
  if (ZCL_CTX().device_cb)                                          \
  {                                                                 \
    zb_zcl_device_callback_param_t *user_app_data =                 \
        ZB_GET_BUF_PARAM(buffer, zb_zcl_device_callback_param_t);   \
    zb_zcl_ota_upgrade_value_param_t *value =                       \
        &(user_app_data->cb_param.ota_value_param);                 \
    value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_ABORT;        \
    user_app_data->device_cb_id = ZB_ZCL_OTA_UPGRADE_VALUE_CB_ID;   \
    user_app_data->endpoint = get_endpoint_by_cluster(ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE); \
    user_app_data->status = RET_OK;                                 \
    (ZCL_CTX().device_cb)(param);                                   \
  }                                                                 \
}

#define ZB_ZCL_OTA_UPGRADE_CHECK_USER_APP(buffer, result)           \
{                                                                   \
  zb_zcl_device_callback_param_t *user_app_data =                   \
      ZB_GET_BUF_PARAM(buffer, zb_zcl_device_callback_param_t);     \
  TRACE_MSG(TRACE_ZCL1, "ZB_ZCL_OTA_UPGRADE_CHECK_USER_APP", (FMT__0)); \
  result = ZB_ZCL_OTA_UPGRADE_STATUS_ERROR;                         \
  if (ZCL_CTX().device_cb)                                          \
  {                                                                 \
    zb_zcl_ota_upgrade_value_param_t *value =                       \
        &(user_app_data->cb_param.ota_value_param);                 \
    value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_CHECK;        \
    user_app_data->device_cb_id = ZB_ZCL_OTA_UPGRADE_VALUE_CB_ID;   \
    user_app_data->endpoint = get_endpoint_by_cluster(ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE); \
    user_app_data->status = RET_OK;                                 \
    (ZCL_CTX().device_cb)(param);                                   \
    if (user_app_data->status == RET_OK)                            \
    {                                                               \
      result = value->upgrade_status;                               \
    }                                                               \
  }else                                                             \
  {                                                                 \
    result = ZB_ZCL_OTA_UPGRADE_STATUS_OK;                          \
  }                                                                 \
}                                                                   \

zb_void_t zb_zcl_ota_upgrade_set_ota_status(zb_uint8_t endpoint, zb_uint8_t status);

zb_uint8_t zb_zcl_ota_upgrade_get_ota_status(zb_uint8_t endpoint);

zb_void_t zb_zcl_ota_upgrade_send_upgrade_end_req(zb_uint8_t param, zb_uint8_t status);

zb_void_t zb_zcl_ota_restart_after_rejoin(zb_uint8_t endpoint);

void zb_zcl_ota_set_file_size(zb_uint8_t endpoint, zb_uint32_t size);

zb_uint16_t zb_zcl_ota_upgrade_get16(zb_uint8_t endpoint, zb_uint16_t attr_id);

zb_uint32_t zb_zcl_ota_upgrade_get32(zb_uint8_t endpoint, zb_uint16_t attr_id);
/*! @}
 *  @endcond */ /* internals_doc */

/*! @brief Abort OTA Upgrade process
 *
 *  @param endpoint - endpoint for OTA Upgrade
 *  @param param - buffer to be aborted
 */
zb_void_t zcl_ota_abort(zb_uint8_t endpoint, zb_uint8_t param);

#endif /* defined ZB_HA_ENABLE_OTA_UPGRADE_CLIENT || defined DOXYGEN */

#if defined ZB_ENABLE_HA
zb_uint8_t zb_zcl_get_cmd_list_ota_upgrade(zb_bool_t is_client_generated, zb_uint8_t **cmd_list);
#endif /* defined ZB_ENABLE_HA */

#endif /* defined ZB_ZCL_SUPPORT_CLUSTER_OTA_UPGRADE || defined DOXYGEN */
/*! @} */ /* ZCL OTA Upgrade cluster definitions */

#ifdef ZB_HA_ENABLE_OTA_UPGRADE_CLIENT
#define ZCL_OTA_MAX_RESEND_RETRIES 3

typedef struct zb_zcl_ota_upgrade_cli_ctx_s
{
  zb_zcl_parsed_hdr_t cmd_info_2;
  zb_zcl_ota_upgrade_image_block_res_t payload_2;
  zb_uint_t resend_retries;
  zb_uint8_t ota_restart_after_rejoin;
} zb_zcl_ota_upgrade_cli_ctx_t;
#endif

/** @endcond */ /* DOXYGEN_ZCL_SECTION */

zb_void_t zb_zcl_ota_upgrade_init_srv(void);
zb_void_t zb_zcl_ota_upgrade_init_cli(void);
#define ZB_ZCL_CLUSTER_ID_OTA_UPGRADE_SERVER_ROLE_INIT zb_zcl_ota_upgrade_init_srv
#define ZB_ZCL_CLUSTER_ID_OTA_UPGRADE_CLIENT_ROLE_INIT zb_zcl_ota_upgrade_init_cli

#endif /* ! defined ZB_ZCL_OTA_UPGRADE_H */
