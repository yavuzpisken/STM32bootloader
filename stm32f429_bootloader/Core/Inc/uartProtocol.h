/*
 * uartProtocol.h
 *
 *  Created on: Apr 22, 2021
 *      Author: MrMaker
 */

#ifndef BOOTLOADER_UARTPROTOCOL_H_
#define BOOTLOADER_UARTPROTOCOL_H_
#include <stdint.h>

#define PROTOCOL_VERSION			0.1
#define BUILD_VERSION				0.1
#define BOOTLOADER_BAUD				115200
#define BOOTLOADER_SOP				0xBA
#define BOOTLOADER_HEARTBEAT_TO		2000

typedef enum UartReqPackKey_e {
    UartReqPack_Ack = 0,            // PC -> Ct, UartReqPackAck_t
    UartReqPack_Heartbeat,          // PC -> Ct, UartReqPackHeartbeat_t
    UartReqPack_Info,               // PC -> Ct, UartReqPackInfo_t
    UartReqPack_Debug,              // PC -> Ct, UartReqPackDebug_t
    UartReqPack_Bootloader,         // PC -> Ct, UartReqPackBootloader_t
    UartReqPack_Firmware,           // PC -> Ct, UartReqPackFirmware_t
    UartReqPack__Max_
} UartReqPackKey_t;

typedef enum UartResPackKey_e {
    UartResPack_Ack = 0,            // Ct -> PC, UartResPackAck_t
    UartResPack_Heartbeat,          // Ct -> PC, UartResPackHeartbeat_t
    UartResPack_Info,               // Ct -> PC, UartResPackInfo_t
    UartResPack_Debug,              // Ct -> PC, UartResPackDebug_t,
    UartResPack_Bootloader,         // Ct -> PC, UartResPackBootloader_t,
    UartResPack_Firmware,           // Ct -> PC, UartResPackFirmware_t
    UartResPack__Max_
} UartResPackKey_t;

typedef struct UartReqPackAck_s {
    uint8_t  sop;                   // ANT_UART_SOP
    uint8_t  key;                   // UartReqPack_Ack
    uint8_t  seq;                   // Incremental sequence number
    uint8_t  key_for_ack;           // One of UartResPackKey_t
    uint8_t  cka;                   // CRC field
    uint8_t  ckb;                   // CRC field
} UartReqPackAck_t;

typedef struct UartReqPackHeartbeat_s {
    uint8_t  sop;                   // ANT_UART_SOP
    uint8_t  key;                   // UartReqPack_Heartbeat
    uint8_t  seq;                   // Incremental sequence number
    uint32_t session_id;            // unique for each app start
    uint8_t  cka;                   // CRC field
    uint8_t  ckb;                   // CRC field
} UartReqPackHeartbeat_t;

typedef struct UartReqPackInfo_s {
    uint8_t  sop;                   // UART_SOP
    uint8_t  key;                   // UartReqPack_Info
    uint8_t  seq;                   // Incremental sequence number
    uint8_t  cka;                   // CRC field
    uint8_t  ckb;                   // CRC field
} UartReqPackInfo_t;

typedef struct UartReqPackDebug_s {
    uint8_t  sop;                   // ANT_UART_SOP
    uint8_t  key;                   // UartReqPack_Debug
    uint8_t  seq;                   // Incremental sequence number
    uint8_t  allowed_levels;        // alloved less than given here
    uint8_t  cka;                   // CRC field
    uint8_t  ckb;                   // CRC field
} UartReqPackDebug_t;

typedef struct UartReqPackBootloader_s {
    uint8_t  sop;                   // ANT_UART_SOP
    uint8_t  key;                   // UartReqPack_Bootloader
    uint8_t  seq;                   // Incremental sequence number
    uint32_t session_id;            // unique for each app start
    uint8_t  cka;                   // CRC field
    uint8_t  ckb;                   // CRC field
} UartReqPackBootloader_t;

typedef struct UartReqPackFirmware_s {
    uint8_t  sop;                   // ANT_UART_SOP
    uint8_t  key;                   // UartReqPack_Firmware
    uint8_t  seq;                   // Incremental sequence number
    uint16_t tot_pck;               // Total FW packet number
    uint16_t cur_pck;               // Current FW packet number
    uint8_t  data[ANT_FW_DATA_SIZE]; // FW Data
    uint8_t  cka;                   // CRC field
    uint8_t  ckb;                   // CRC field
} UartReqPackFirmware_t;

#endif /* BOOTLOADER_UARTPROTOCOL_H_ */
