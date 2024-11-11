#pragma once
#include <proto/device_path.h>
#include "efi_types.h"

typedef struct EFI_SYSTEM_TABLE EFI_SYS_TABLE;
#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

/* Raises a task’s priority level and returns its previous level. */
typedef EFI_TPL (EFIAPI *EFI_RAISE_TPL)(EFI_TPL NewTpl);

/* Restores a task’s priority level to its previous value. */
typedef void (EFIAPI *EFI_RESTORE_TPL)(EFI_TPL OldTpl);

/* Allocates memory pages from the system */
typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_PAGES) (
    EFI_ALLOCATE_TYPE Type,
    EFI_MEMORY_TYPE MemoryType,
    UINTN Pages,
    EFI_PHYSICAL_ADDRESS *Memory
);

/* Frees memory pages */
typedef EFI_STATUS (EFIAPI *EFI_FREE_PAGES) (
    EFI_PHYSICAL_ADDRESS Memory,
    UINTN Pages
);


/* Returns the current memory map. */
typedef EFI_STATUS (EFIAPI *EFI_GET_MEMORY_MAP) (
    UINTN *MemoryMapSize,
    EFI_MEMORY_DESCRIPTOR *MemoryMap,
    UINTN *MapKey,
    UINTN *DescriptorSize,
    UINT32 *DescriptorVersion
);

/* allocates pool memory */
typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_POOL) (
    EFI_MEMORY_TYPE PoolType,
    UINTN Size,
    void **Buffer
);

/* returns pool memory to the system */
typedef EFI_STATUS (EFIAPI *EFI_FREE_POOL) (
    void *Buffer
);

/* creates an event */
typedef EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT) (
    UINT32 Type,
    EFI_TPL NotifyTpl,
    EFI_EVENT_NOTIFY NotifyFunction,
    void *NotifyContext,
    EFI_EVENT *Event
);

/* closes an event */
typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT) (
    EFI_EVENT Event
);

/* signals an event */
typedef
EFI_STATUS
(EFIAPI *EFI_SIGNAL_EVENT) (
    EFI_EVENT Event
);

/* stops execution until event is signaled */
typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
 UINTN NumberOfEvents,
 EFI_EVENT *Event,
 UINTN *Index
);

/* check wheter an event is in the signaled state */
typedef
EFI_STATUS
(EFIAPI *EFI_CHECK_EVENT) (
    EFI_EVENT Event
);

/* Sets the type of timer and the trigger time for a timer event */
typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER) (
    EFI_EVENT Event,
    EFI_TIMER_DELAY Type,
    UINT64 TriggerTime
);

/* Installs a protocol interface on a device handle. If the handle does not exist,
     it is created and added to the list of handles in the system.  */
typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
    EFI_HANDLE *Handle,
    EFI_GUID *Protocol,
    EFI_INTERFACE_TYPE InterfaceType,
    void *Interface
);

/* Removes a protocol interface from a device handle.  */
typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
    EFI_HANDLE Handle,
    EFI_GUID *Protocol,
    void *Interface
);

/* Reinstalls a protocol interface on a device handle. */
typedef
EFI_STATUS
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
    EFI_HANDLE Handle,
    EFI_GUID *Protocol,
    void *OldInterface,
    void *NewInterface
);

/* Creates an event that is to be signaled whenever an interface is installed for a specified protocol. */
typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
    EFI_GUID *Protocol,
    EFI_EVENT Event,
    void **Registration
);

/* Returns an array of handles that support a specified protocol. */
typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE) (
    EFI_LOCATE_SEARCH_TYPE SearchType,
    EFI_GUID *Protocol,
    void *SearchKey,
    UINTN *BufferSize,
    EFI_HANDLE *Buffer
);

/* Queries a handle to determine if it supports a specified protocol. 
WARNING : The HandleProtocol() function is still available for use by old EFI applications and drivers.
However, all new applications and drivers should use
EFI_BOOT_SERVICES.OpenProtocol() in place of HandleProtocol()*/

typedef
EFI_STATUS
(EFIAPI *EFI_HANDLE_PROTOCOL) (
 EFI_HANDLE Handle,
 EFI_GUID *Protocol,
 void **Interface
);

/* Locates the handle to a device on the device path that supports the specified protocol */
typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_DEVICE_PATH) (
    EFI_GUID *Protocol,
    EFI_DEVICE_PATH_PROTOCOL **DevicePath,
    EFI_HANDLE *Device
);

/* Adds, updates, or removes a configuration table entry from the EFI System Table. */
typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (
    EFI_GUID *Guid,
    void *Table
);

typedef
EFI_STATUS
(EFIAPI *EFI_CALCULATE_CRC32) (
    void *Data,
    UINTN DataSize,
    UINT32 *Crc32
);

/* unloads an image */
typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_UNLOAD) (
    EFI_HANDLE ImageHandle
);

/* image entrypoint */
typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_ENTRY_POINT) (
    EFI_HANDLE ImageHandle,
    EFI_SYS_TABLE *SystemTable
);

/* Terminates a loaded EFI image and returns control to boot services */
typedef
EFI_STATUS
(EFIAPI *EFI_EXIT) (
    EFI_HANDLE ImageHandle,
    EFI_STATUS ExitStatus,
    UINTN ExitDataSize,
    CHAR16 *ExitData 
);

/* Queries a handle to determine if it supports a specified protocol.  */
typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL) (
    EFI_HANDLE Handle,
    EFI_GUID *Protocol,
    void **Interface,
    EFI_HANDLE AgentHandle,
    EFI_HANDLE ControllerHandle,
    UINT32 Attributes
);

/* etrieves the list of agents that currently have a protocol interface opened */
typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
    EFI_HANDLE Handle,
    EFI_GUID *Protocol,
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
    UINTN *EntryCount
);

/* Removes one or more protocol interfaces into the boot services environment */
typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    EFI_HANDLE Handle,
    ...
);

/* Closes a protocol on a handle that was opened */
typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_PROTOCOL) (
    EFI_HANDLE Handle,
    EFI_GUID *Protocol,
    EFI_HANDLE AgentHandle,
    EFI_HANDLE ControllerHandle
);

/* Connects one or more drivers to a controller. */
typedef
EFI_STATUS
(EFIAPI *EFI_CONNECT_CONTROLLER) (
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE *DriverImageHandle,
    EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath,
    BOOLEAN Recursive
);

/* Disconnects one or more drivers from a controller. */
typedef
EFI_STATUS
(EFIAPI *EFI_DISCONNECT_CONTROLLER) (
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE DriverImageHandle,
    EFI_HANDLE ChildHandle
);
/* Transfers control to a loaded image’s entry point. */
typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_START) (
    EFI_HANDLE ImageHandle,
    UINTN *ExitDataSize,
    CHAR16 **ExitData
);

/* Terminates all boot service */
typedef
EFI_STATUS
(EFIAPI *EFI_EXIT_BOOT_SERVICES) (
    EFI_HANDLE ImageHandle,
    UINTN MapKey
);

/* Returns a monotonically increasing count for the platform */
typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
    UINT64 *Count
);

/* Induces a fine-grained stall. */
typedef
EFI_STATUS
(EFIAPI *EFI_STALL) (
    UINTN Microseconds
);

/* Sets the system’s watchdog timer. */
typedef
EFI_STATUS
(EFIAPI *EFI_SET_WATCHDOG_TIMER) (
    UINTN Timeout,
    UINT64 WatchdogCode,
    UINTN DataSize,
    CHAR16 *WatchdogData
);

/* Retrieves the list of protocol interface GUIDs that are installed on a handle in a buffer allocated from
pool. */
typedef
EFI_STATUS
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
    EFI_HANDLE Handle,
    EFI_GUID ***ProtocolBuffer,
    UINTN *ProtocolBufferCount
);

/* Returns an array of handles that support the requested protocol in a buffer allocated from pool */
typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
    EFI_LOCATE_SEARCH_TYPE SearchType,
    EFI_GUID *Protocol,
    void *SearchKey,
    UINTN *NoHandles,
    EFI_HANDLE **Buffer
);

/* Returns the first protocol instance that matches the given protocol */
typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_PROTOCOL) (
    EFI_GUID *Protocol,
    void *Registration,
    void **Interface
);

/* copies the contents of one buffer to another buffer */
typedef
void
(EFIAPI *EFI_COPY_MEM) (
    void *Destination,
    void *Source,
    UINTN Length
);

/*  fills a buffer with a specified value. */
typedef
void
(EFIAPI *EFI_SET_MEM) (
    void *Buffer,
    UINTN Size,
    UINT8 Value
);

/* Creates an event in a group. */
typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT_EX) (
    UINT32 Type,
    EFI_TPL NotifyTpl,
    EFI_EVENT_NOTIFY NotifyFunction,
    const void *NotifyContext,
    const EFI_GUID *EventGroup,
    EFI_EVENT *Event
);

typedef struct {
    EFI_TABLE_HEADER     Hdr;

    //
    // Task Priority Services
    //
    EFI_RAISE_TPL        RaiseTPL;       // EFI 1.0+
    EFI_RESTORE_TPL      RestoreTPL;     // EFI 1.0+

    //
    // Memory Services
    //
    EFI_ALLOCATE_PAGES   AllocatePages;  // EFI 1.0+
    EFI_FREE_PAGES       FreePages;      // EFI 1.0+
    EFI_GET_MEMORY_MAP   GetMemoryMap;   // EFI 1.0+
    EFI_ALLOCATE_POOL    AllocatePool;   // EFI 1.0+
    EFI_FREE_POOL        FreePool;       // EFI 1.0+

    //
    // Event & Timer Services
    //
    EFI_CREATE_EVENT     CreateEvent;    // EFI 1.0+
    EFI_SET_TIMER        SetTimer;       // EFI 1.0+
    EFI_WAIT_FOR_EVENT   WaitForEvent;   // EFI 1.0+
    EFI_SIGNAL_EVENT     SignalEvent;    // EFI 1.0+
    EFI_CLOSE_EVENT      CloseEvent;     // EFI 1.0+
    EFI_CHECK_EVENT      CheckEvent;     // EFI 1.0+

    //
    // Protocol Handler Services
    //
    EFI_INSTALL_PROTOCOL_INTERFACE     InstallProtocolInterface;            // EFI 1.0+
    EFI_REINSTALL_PROTOCOL_INTERFACE   ReinstallProtocolInterface;          // EFI 1.0+
    EFI_UNINSTALL_PROTOCOL_INTERFACE   UninstallProtocolInterface;          // EFI 1.0+
    EFI_HANDLE_PROTOCOL                HandleProtocol;                      // EFI 1.0+
    void*   Reserved;    // EFI 1.0+
    EFI_REGISTER_PROTOCOL_NOTIFY       RegisterProtocolNotify;              // EFI  1.0+
    EFI_LOCATE_HANDLE                  LocateHandle;                        // EFI 1.0+
    EFI_LOCATE_DEVICE_PATH             LocateDevicePath;                    // EFI 1.0+
    EFI_INSTALL_CONFIGURATION_TABLE       InstallConfigurationTable;           // EFI 1.0+

    //
    // Image Services
    //
    EFI_IMAGE_UNLOAD               LoadImage;        // EFI 1.0+
    EFI_IMAGE_START                StartImage;       // EFI 1.0+
    EFI_EXIT                       Exit;             // EFI 1.0+
    EFI_IMAGE_UNLOAD               UnloadImage;      // EFI 1.0+
    EFI_EXIT_BOOT_SERVICES         ExitBootServices; // EFI 1.0+

    //
    // Miscellaneous Services
    //
    EFI_GET_NEXT_MONOTONIC_COUNT   GetNextMonotonicCount; // EFI 1.0+
    EFI_STALL                      Stall;                 // EFI 1.0+
    EFI_SET_WATCHDOG_TIMER         SetWatchdogTimer;      // EFI 1.0+

    //
    // DriverSupport Services
    //
    EFI_CONNECT_CONTROLLER         ConnectController;     // EFI 1.1
    EFI_DISCONNECT_CONTROLLER      DisconnectController;  // EFI 1.1+

    //
    // Open and Close Protocol Services
    //
    EFI_OPEN_PROTOCOL              OpenProtocol;           // EFI 1.1+
    EFI_CLOSE_PROTOCOL             CloseProtocol;          // EFI 1.1+
    EFI_OPEN_PROTOCOL_INFORMATION     OpenProtocolInformation;// EFI 1.1+

    //
    // Library Services
    //
    EFI_PROTOCOLS_PER_HANDLE       ProtocolsPerHandle;     // EFI 1.1+
    EFI_LOCATE_HANDLE_BUFFER       LocateHandleBuffer;     // EFI 1.1+
    EFI_LOCATE_PROTOCOL            LocateProtocol;         // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  InstallMultipleProtocolInterfaces;    // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;   // EFI 1.1+*

    //
    // 32-bit CRC Services
    //
    EFI_CALCULATE_CRC32    CalculateCrc32;     // EFI 1.1+

    //
    // Miscellaneous Services
    //
    EFI_COPY_MEM           CopyMem;        // EFI 1.1+
    EFI_SET_MEM            SetMem;         // EFI 1.1+
    EFI_CREATE_EVENT_EX    CreateEventEx;  // UEFI 2.0+
  } EFI_BOOT_SERVICES;
