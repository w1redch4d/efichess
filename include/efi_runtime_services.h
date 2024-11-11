#pragma once
#include <efi_types.h>


#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION

//*******************************************************
//EFI_TIME
//*******************************************************
// This represents the current time information
typedef struct {
    UINT16 Year; // 1900 – 9999
    UINT8 Month; // 1 – 12
    UINT8 Day; // 1 – 31
    UINT8 Hour; // 0 – 23
    UINT8 Minute; // 0 – 59
    UINT8 Second; // 0 – 59
    UINT8 Pad1;
    UINT32 Nanosecond; // 0 – 999,999,999
    INT16 TimeZone; // -1440 to 1440 or 2047
    UINT8 Daylight;
    UINT8 Pad2;
} EFI_TIME;

//*******************************************************
// EFI_TIME_CAPABILITIES
//*******************************************************
// This provides the capabilities of the
// real time clock device as exposed through the EFI interfaces.
typedef struct {
    UINT32 Resolution;
    UINT32 Accuracy;
    BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;

//*******************************************************
// EFI_RESET_TYPE
//*******************************************************
typedef enum {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

//*******************************************************
// EFI_CAPSULE_HEADER
//*******************************************************
typedef struct {
    EFI_GUID CapsuleGuid;
    UINT32 HeaderSize;
    UINT32 Flags;
    UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

/* Returns the current time and date, and the time-keeping
    capabilities of the platform. */
typedef
EFI_STATUS
(EFIAPI *EFI_GET_TIME) (
    EFI_TIME *Time,
    EFI_TIME_CAPABILITIES *Capabilities
);

/* Sets the current local time and date information. */
typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIME) (
    EFI_TIME *Time
);

/* Returns the current wakeup alarm clock setting. */
typedef
EFI_STATUS
(EFIAPI *EFI_GET_WAKEUP_TIME) (
    BOOLEAN* Enabled,
    BOOLEAN* Pending,
    EFI_TIME* Time
);

/* Sets the system wakeup alarm clock time */
typedef
EFI_STATUS
(EFIAPI *EFI_SET_WAKEUP_TIME) (
    BOOLEAN Enable,
    EFI_TIME *Time
);

typedef EFI_STATUS (EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP)(
    size_t MemoryMapSize,
    size_t DescriptorSize,
    UINT32 DescriptorVersion,
    EFI_MEMORY_DESCRIPTOR* VirtualMap
);

typedef EFI_STATUS (EFIAPI *EFI_CONVERT_POINTER)(
    size_t DebugDisposition,
    void** Addr
);

typedef EFI_STATUS (EFIAPI *EFI_GET_VARIABLE)(
    CHAR16* VarName,
    EFI_GUID* VendorGuid,
    UINT32* Attributes,
    size_t* DataSize,
    void* Data
);

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_VARIABLE_NAME)(
    size_t* VarNameSize,
    CHAR16* VarName,
    EFI_GUID* VendorGuid
);

typedef EFI_STATUS (EFIAPI *EFI_SET_VARIABLE)(
    CHAR16* VarName,
    EFI_GUID* VendorGuid,
    UINT32 Attributes,
    size_t DataSize,
    const void* Data
);

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT)(
    UINT32* HighCount
);

typedef EFI_STATUS (EFIAPI *EFI_RESET_SYSTEM)(
    EFI_RESET_TYPE ResetType,
    EFI_STATUS ResetStatus,
    size_t DataSize,
    void* ResetData
);

typedef EFI_STATUS (EFIAPI *EFI_UPDATE_CAPSULE)(
    EFI_CAPSULE_HEADER** CapsuleHeaderArray,
    size_t CapsuleCount,
    EFI_PHYSICAL_ADDRESS ScatterGatherList
);

typedef EFI_STATUS (EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES)(
    EFI_CAPSULE_HEADER** CapsuleHeaderArray,
    size_t CapsuleCount,
    UINT64* MaxCapsuleSize,
    EFI_RESET_TYPE* ResetType
);

typedef EFI_STATUS (EFIAPI *EFI_QUERY_VARIABLE_INFO)(
    UINT32 Attributes,
    UINT64* MaxVarStorageSize,
    UINT64* RemainingVarStorageSize,
    UINT64* MaxVarSize
);

typedef struct {
    EFI_TABLE_HEADER Hdr;
    //
    // Time Services
    //
    EFI_GET_TIME GetTime;
    EFI_SET_TIME SetTime;
    EFI_GET_WAKEUP_TIME GetWakeupTime;
    EFI_SET_WAKEUP_TIME SetWakeupTime;
    //
    // Virtual Memory Services
    //
    EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
    EFI_CONVERT_POINTER ConvertPointer;
    //
    // Variable Services
    //
    EFI_GET_VARIABLE GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
    EFI_SET_VARIABLE SetVariable;
    //
    // Miscellaneous Services
    //
    EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM ResetSystem;
    //
    // UEFI 2.0 Capsule Services
    //
    EFI_UPDATE_CAPSULE UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;
    //
    // Miscellaneous UEFI 2.0 Service
    //
    EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
} EFI_RUNTIME_SERVICES;