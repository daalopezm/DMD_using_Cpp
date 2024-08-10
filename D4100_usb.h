#ifndef D4100_USB_H
#define D4100_USB_H
#include "RegisterDefines.h"
#ifdef __cplusplus
extern "C" {
#endif

// Define fixed-width integer types manually
typedef unsigned char uint8_t;
typedef short int int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

// Define UCHAR as uint8_t for compatibility
typedef uint8_t UCHAR;

// Function prototypes

// int program_FPGA(UCHAR* write_buffer, int32_t write_size, int16_t DeviceNumber)
__declspec(dllimport) int program_FPGA(UCHAR* write_buffer, int32_t write_size, int16_t DeviceNumber);

// int16_t GetNumDev(void)
__declspec(dllimport) int16_t GetNumDev(void);

// int GetDescriptor(int32_t* descriptor, int16_t DeviceNum)
__declspec(dllimport) int GetDescriptor(int32_t* descriptor, int16_t DeviceNum);

// uint32_t GetDriverRev(int16_t DeviceNumber)
__declspec(dllimport) uint32_t GetDriverRev(int16_t DeviceNumber);

// uint32_t GetFirmwareRev(int16_t DeviceNumber)
__declspec(dllimport) uint32_t GetFirmwareRev(int16_t DeviceNumber);

// int16_t GetUsbSpeed(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetUsbSpeed(int16_t DeviceNumber);

// uint32_t GetDLLRev(void)
__declspec(dllimport) uint32_t GetDLLRev(void);

// uint32_t GetFPGARev(int16_t DeviceNumber)
__declspec(dllimport) uint32_t GetFPGARev(int16_t DeviceNumber);

// int16_t GetDDCVERSION(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetDDCVERSION(int16_t DeviceNumber);

// int16_t GetDMDTYPE(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetDMDTYPE(int16_t DeviceNumber);

// int16_t LoadControl(int16_t DeviceNumber)
__declspec(dllimport) int16_t LoadControl(int16_t DeviceNumber);

// int LoadData(UCHAR* RowData, uint32_t length, int16_t DMDType, int16_t DeviceNumber)
__declspec(dllimport) int LoadData(UCHAR* RowData, uint32_t length, int16_t DMDType, int16_t DeviceNumber);

// int16_t ClearFifos(int16_t DeviceNumber)
__declspec(dllimport) int16_t ClearFifos(int16_t DeviceNumber);

// int16_t SetBlkMd(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetBlkMd(int16_t value, int16_t DeviceNumber);

// int16_t GetBlkMd(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetBlkMd(int16_t DeviceNumber);

// int16_t SetBlkAd(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetBlkAd(int16_t value, int16_t DeviceNumber);

// int16_t GetBlkAd(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetBlkAd(int16_t DeviceNumber);

// int16_t SetRST2BLKZ(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetRST2BLKZ(int16_t value, int16_t DeviceNumber);

// int16_t GetRST2BLKZ(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetRST2BLKZ(int16_t DeviceNumber);

// int16_t SetRowMd(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetRowMd(int16_t value, int16_t DeviceNumber);

// int16_t GetRowMd(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetRowMd(int16_t DeviceNumber);

// int16_t SetRowAddr(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetRowAddr(int16_t value, int16_t DeviceNumber);

// int16_t GetRowAddr(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetRowAddr(int16_t DeviceNumber);

// int16_t SetCOMPDATA(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetCOMPDATA(int16_t value, int16_t DeviceNumber);

// int16_t GetCOMPDATA(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetCOMPDATA(int16_t DeviceNumber);

// int16_t SetNSFLIP(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetNSFLIP(int16_t value, int16_t DeviceNumber);

// int16_t GetNSFLIP(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetNSFLIP(int16_t DeviceNumber);

// int16_t SetWDT(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetWDT(int16_t value, int16_t DeviceNumber);

// int16_t GetWDT(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetWDT(int16_t DeviceNumber);

// int16_t SetPWRFLOAT(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetPWRFLOAT(int16_t value, int16_t DeviceNumber);

// int16_t GetPWRFLOAT(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetPWRFLOAT(int16_t DeviceNumber);

// int16_t SetEXTRESETENBL(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetEXTRESETENBL(int16_t value, int16_t DeviceNumber);

// int16_t GetEXTRESETENBL(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetEXTRESETENBL(int16_t DeviceNumber);

// int16_t SetGPIO(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetGPIO(int16_t value, int16_t DeviceNumber);

// int16_t GetGPIO(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetGPIO(int16_t DeviceNumber);

// int16_t GetRESETCOMPLETE(int32_t waittime, int16_t DeviceNumber)
__declspec(dllimport) int16_t GetRESETCOMPLETE(int32_t waittime, int16_t DeviceNumber);

// int16_t SetGPIORESETCOMPLETE(int16_t DeviceNumber)
__declspec(dllimport) int16_t SetGPIORESETCOMPLETE(int16_t DeviceNumber);

// int16_t GetSWOverrideEnable(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetSWOverrideEnable(int16_t DeviceNumber);

// int16_t SetSWOverrideEnable(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetSWOverrideEnable(int16_t value, int16_t DeviceNumber);

// int16_t GetSWOverrideValue(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetSWOverrideValue(int16_t DeviceNumber);

// int16_t SetSWOverrideValue(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetSWOverrideValue(int16_t value, int16_t DeviceNumber);

// int16_t GetTPGEnable(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetTPGEnable(int16_t DeviceNumber);

// int16_t SetTPGEnable(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetTPGEnable(int16_t value, int16_t DeviceNumber);

// int16_t GetPatternForce(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetPatternForce(int16_t DeviceNumber);

// int16_t SetPatternForce(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetPatternForce(int16_t value, int16_t DeviceNumber);

// int16_t GetPatternSelect(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetPatternSelect(int16_t DeviceNumber);

// int16_t SetPatternSelect(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetPatternSelect(int16_t value, int16_t DeviceNumber);

// int16_t GetLoad4(int16_t DeviceNumber)
__declspec(dllimport) int16_t GetLoad4(int16_t DeviceNumber);

// int16_t SetLoad4(int16_t value, int16_t DeviceNumber)
__declspec(dllimport) int16_t SetLoad4(int16_t value, int16_t DeviceNumber);

#ifdef __cplusplus
}
#endif

#endif // D4100_USB_H
