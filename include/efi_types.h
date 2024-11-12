#pragma once

#include <stdint.h>
#include <stddef.h> // size_t
#include <stdbool.h> // bool
/* typedefs */
typedef uint64_t UINT64;
typedef uint32_t UINT32;
typedef uint16_t CHAR16, UINT16;
typedef uint8_t UINT8;
typedef bool BOOLEAN;
typedef int32_t INT32;
typedef int16_t INT16;
typedef size_t UINTN;
typedef int INTN;

//*******************************************************
//EFI_HANDLE
//*******************************************************
typedef void *EFI_HANDLE;
typedef void *EFI_EVENT;
typedef void *EFI_STATUS;

/* macros */
#define EFI_SUCCESS 0u
#define EFI_ERROR_MASK ((uintptr_t)INTPTR_MAX + 1)
#define EFI_ERR(x) (EFI_ERROR_MASK | (x))
#define EFI_ERROR(x) (((intptr_t)(x)) < 0)
#define EFI_NOT_READY EFI_ERR(6)

//*******************************************************
// Event Types
//*******************************************************
// These types can be “ORed” together as needed – for example,
// EVT_TIMER might be “Ored” with EVT_NOTIFY_WAIT or 
// EVT_NOTIFY_SIGNAL.
#define EVT_TIMER 0x80000000
#define EVT_RUNTIME 0x40000000
#define EVT_NOTIFY_WAIT 0x00000100
#define EVT_NOTIFY_SIGNAL 0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES 0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202

//******************************************************
// UNICODE DRAWING CHARACTERS
//******************************************************

#define BOXDRAW_HORIZONTAL             0x2500
#define BOXDRAW_VERTICAL               0x2502
#define BOXDRAW_DOWN_RIGHT             0x250c
#define BOXDRAW_DOWN_LEFT              0x2510
#define BOXDRAW_UP_RIGHT               0x2514
#define BOXDRAW_UP_LEFT                0x2518
#define BOXDRAW_VERTICAL_RIGHT         0x251c
#define BOXDRAW_VERTICAL_LEFT          0x2524
#define BOXDRAW_DOWN_HORIZONTAL        0x252c
#define BOXDRAW_UP_HORIZONTAL          0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL    0x253c

#define BOXDRAW_DOUBLE_HORIZONTAL      0x2550
#define BOXDRAW_DOUBLE_VERTICAL        0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE      0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT      0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT      0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE       0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT       0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT       0x2557

#define BOXDRAW_UP_RIGHT_DOUBLE        0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT        0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT        0x255a
#define BOXDRAW_UP_LEFT_DOUBLE         0x255b
#define BOXDRAW_UP_DOUBLE_LEFT         0x255c
#define BOXDRAW_DOUBLE_UP_LEFT         0x255d

#define BOXDRAW_VERTICAL_RIGHT_DOUBLE  0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT  0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT  0x2560

#define BOXDRAW_VERTICAL_LEFT_DOUBLE   0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT   0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT   0x2563

#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE 0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL 0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL 0x2566

#define BOXDRAW_UP_HORIZONTAL_DOUBLE   0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL   0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL   0x2569

#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c

//******************************************************
// EFI Required Block Elements Code Chart
//******************************************************

#define BLOCKELEMENT_FULL_BLOCK        0x2588
#define BLOCKELEMENT_LIGHT_SHADE       0x2591

//******************************************************
// EFI Required Geometric Shapes Code Chart
//******************************************************

#define GEOMETRICSHAPE_UP_TRIANGLE     0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE  0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE   0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE   0x25c4

//******************************************************
// EFI Required Arrow shapes
//******************************************************

#define ARROW_UP                       0x2191
#define ARROW_DOWN                     0x2193

//*******************************************************
// Attributes
//*******************************************************
#define EFI_BLACK                              0x00
#define EFI_BLUE                               0x01
#define EFI_GREEN                              0x02
#define EFI_CYAN                               0x03
#define EFI_RED                                0x04
#define EFI_MAGENTA                            0x05
#define EFI_BROWN                              0x06
#define EFI_LIGHTGRAY                          0x07
#define EFI_BRIGHT                             0x08
#define EFI_DARKGRAY(EFI_BLACK)                0x08
#define EFI_LIGHTBLUE                          0x09
#define EFI_LIGHTGREEN                         0x0A
#define EFI_LIGHTCYAN                          0x0B
#define EFI_LIGHTRED                           0x0C
#define EFI_LIGHTMAGENTA                       0x0D
#define EFI_YELLOW                             0x0E
#define EFI_WHITE                              0x0F


#define EFI_BACKGROUND_BLACK                   0x00
#define EFI_BACKGROUND_BLUE                    0x10
#define EFI_BACKGROUND_GREEN                   0x20
#define EFI_BACKGROUND_CYAN                    0x30
#define EFI_BACKGROUND_RED                     0x40
#define EFI_BACKGROUND_MAGENTA                 0x50
#define EFI_BACKGROUND_BROWN                   0x60
#define EFI_BACKGROUND_LIGHTGRAY               0x70
//
// Macro to accept color values in their raw form to create
// a value that represents both a foreground and background
// color in a single byte.
// For Foreground, and EFI_\* value is valid from EFI_BLACK(0x00)
// to EFI_WHITE (0x0F).
// For Background, only EFI_BLACK, EFI_BLUE, EFI_GREEN,
// EFI_CYAN, EFI_RED, EFI_MAGENTA, EFI_BROWN, and EFI_LIGHTGRAY
// are acceptable.
//
// Do not use EFI_BACKGROUND_xxx values with this macro.
//#define EFI_TEXT_ATTR(Foreground,Background) \
((Foreground) | ((Background) << 4))

//*******************************************************
// This ABI is special for x86_64 (and possibly other architectures). Set the appropriate
// attribute per architecture, or allow the header to be used for types only with no function
// calls allowed.
//*******************************************************
#define EFIAPI __attribute__((ms_abi))

//*******************************************************
// Memory Attribute Definitions
//*******************************************************
// These types can be “ORed” together as needed.
#define EFI_MEMORY_UC 0x0000000000000001
#define EFI_MEMORY_WC 0x0000000000000002
#define EFI_MEMORY_WT 0x0000000000000004
#define EFI_MEMORY_WB 0x0000000000000008
#define EFI_MEMORY_UCE 0x0000000000000010
#define EFI_MEMORY_WP 0x0000000000001000
#define EFI_MEMORY_RP 0x0000000000002000
#define EFI_MEMORY_XP 0x0000000000004000
#define EFI_MEMORY_NV 0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_RO 0x0000000000020000
#define EFI_MEMORY_RUNTIME 0x8000000000000000

//*******************************************************
// EFI_TPL
//*******************************************************
typedef UINTN EFI_TPL;

//*******************************************************
//EFI_ALLOCATE_TYPE
//*******************************************************
// These types are discussed in the “Description” section below.
typedef enum {
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

//*******************************************************
//EFI_MEMORY_TYPE
//*******************************************************
// These type values are discussed in Table 26 and Table 27.
typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

//*******************************************************
//EFI_PHYSICAL_ADDRESS
//*******************************************************
typedef UINT64 EFI_PHYSICAL_ADDRESS;

//*******************************************************
//EFI_VIRTUAL_ADDRESS
//*******************************************************
typedef UINT64 EFI_VIRTUAL_ADDRESS;
//*******************************************************
// Memory Descriptor Version Number
//*******************************************************
#define EFI_MEMORY_DESCRIPTOR_VERSION 1

//*******************************************************
//EFI_MEMORY_DESCRIPTOR
//*******************************************************
typedef struct {
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

//*******************************************************
// EFI_EVENT_NOTIFY
//*******************************************************
typedef void (EFIAPI *EFI_EVENT_NOTIFY) (
    EFI_EVENT Event,
    void *Context
);

//*******************************************************
//EFI_TIMER_DELAY
//*******************************************************
typedef enum {
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} EFI_TIMER_DELAY;

//*******************************************************
// EFI_LOCATE_SEARCH_TYPE
//*******************************************************
typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

//*******************************************************
// Task Priority Levels
//*******************************************************
#define TPL_APPLICATION 4
#define TPL_CALLBACK 8
#define TPL_NOTIFY 16
#define TPL_HIGH_LEVEL 31

/* Data structure that precedes all of the standard EFI table types. */

typedef struct {
  UINT64      Signature;
  UINT32      Revision;
  UINT32      HeaderSize;
  UINT32      CRC32;
  UINT32      Reserved;
} EFI_TABLE_HEADER;

//*******************************************************
//EFI_GUID
//*******************************************************
typedef struct {
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
} EFI_GUID;
//*******************************************************
//EFI_INTERFACE_TYPE
//*******************************************************
typedef enum {
EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef struct {
    EFI_HANDLE AgentHandle;
    EFI_HANDLE ControllerHandle;
    UINT32 Attributes;
    UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

