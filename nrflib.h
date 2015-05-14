/**********************************************/
/* NRF24L01x functions header for nrf library */
/**********************************************/

#include "nrf24l01.h"

typedef enum
{
  DR1MBPS,
  DR2MBPS,
  DR250KBPS
} DataRate;

typedef enum
{
    POWER_ON,
    POWER_OFF
} PowerMode;

typedef enum
{
    PA18DBM = 0x00,
    PA12DBM = 0x01,
    PA6DBM  = 0x02,
    PA0DBM  = 0x03
} PACtrl;

typedef enum
{
    LNAGainOFF = 0x00,
    LNAGainON  = 0x01
} LNAGain;

typedef enum
{
    P0 = 0x00,
    P1,
    P2,
    P3,
    P4,
    P5
} DataPipe;

// Following timings values has a safety margin added
#define TIME_TX_PULSE	12		// Min TX pulse
#define TIME_TPD2STBY	4600	// Power down -> Standby
#define TIME_TSTBY2A	140		// Standby modes -> TX/RX mode
#define TIME_TPECE3CSN	5       // CE positive edge to CSN LOW

#define NRF_OK			0
#define NRF_ERROR		-1

int NRF_Init(void);

int NRF_FlushTX(char *);
int NRF_FlushRX(char *);
int NRF_ReuseTX_PL(char *);
int NRF_ReadRXPLWidth(int *, char *);

int NRF_ReadRegisterMB(char, char *, int, char *);
int NRF_ReadRegister(char, char *, char *);
int NRF_WriteRegisterMB(char, char *, int, char *);
int NRF_WriteRegister(char, char, char *);

int NRF_WriteTXPayload(char *, int, char *);
int NRF_WriteACKPayload(char *, DataPipe, int, char *);
int NRF_WriteTXPayloadNOACK(char *, int, char *);
int NRF_ReadRXPayload(char *, int, char *);

int NRF_GetStatus(char *);
int NRF_ClearRX_DR(char *);
int NRF_ClearTX_DS(char *);
int NRF_ClearMAX_RT(char *);
void NRF_DisplayStatus(char);

int NRF_SetModePRX(char *);
int NRF_SetModePTX(char *);
int NRF_SetPowerMode(PowerMode, char *);
int NRF_SetDataRate(DataRate, char *);
int NRF_SetRFChannel(int, char *);
int NRF_SetPAControl(PACtrl, char *);

int NRF_SetAutoRetransmitDelay(int, char *); // p33/78
int NRF_SetAutoRetransmitCount(int, char *);
int NRF_GetLostPacketsCount(int *, char *);
int NRF_GetLostRetriesCount(int *, char *);

int NRF_SetAddressWidth(int, char *);
int NRF_SetTxAddress(const char *, char *);
int NRF_SetRxAddress(DataPipe, const char *, char *);
int NRF_EnableDataPipe(DataPipe, char *);
int NRF_SetDataPipeLength(DataPipe, int, char *);

void NRF_StartRX(void);
void NRF_StopRX(void);
void NRF_TXPayload(void);


