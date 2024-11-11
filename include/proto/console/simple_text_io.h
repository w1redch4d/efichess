#pragma once
#include <efi_types.h>

//*******************************************************
//INPUT GUID
//*******************************************************
#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
{0x387477c1,0x69c7,0x11d2,\
{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

// Define EFI_INPUT_KEY structure
typedef struct {
  UINT16 ScanCode;       // Scan code for the key (specific to the keyboard layout or device)
  CHAR16 UnicodeChar;    // Unicode character representation of the key pressed
} EFI_INPUT_KEY;

// Define EFI_SIMPLE_TEXT_INPUT_PROTOCOL structure
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
  EFI_STATUS (EFIAPI *Reset) (
    struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
    BOOLEAN ExtendedVerification
  );
  
  EFI_STATUS (EFIAPI *ReadKeyStroke) (
    struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
    EFI_INPUT_KEY *Key
  );

  EFI_EVENT WaitForKey;  // Event that the system will wait for a keypress
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

//*******************************************************
//OUTPUT GUID
//*******************************************************

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
 {0x387477c2,0x69c7,0x11d2,\
  {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

// Define SIMPLE_TEXT_OUTPUT_MODE struct
typedef struct {
  INT32                              MaxMode;
  INT32                              Mode;
  INT32                              Attribute;
  INT32                              CursorColumn;
  INT32                              CursorRow;
  BOOLEAN                            CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

// Define the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL struct
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
  EFI_STATUS (EFIAPI *Reset) (
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    BOOLEAN ExtendedVerification
  );
  EFI_STATUS (EFIAPI *OutputString) (
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    CHAR16 *String
  );
  EFI_STATUS (EFIAPI *TestString) (
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    CHAR16 *String
  );
  EFI_STATUS (EFIAPI *QueryMode) (
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    UINTN ModeNumber,
    UINTN *Columns,
    UINTN *Rows
  );
  EFI_STATUS (EFIAPI *SetMode) (
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    UINTN ModeNumber
  );
  EFI_STATUS (EFIAPI *SetAttribute) (
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    UINTN Attribute
  );
  EFI_STATUS (EFIAPI *ClearScreen) (
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
  );
  EFI_STATUS (EFIAPI *SetCursorPosition) (
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    UINTN Column,
    UINTN Row
  );
  EFI_STATUS (EFIAPI *EnableCursor) (
    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    BOOLEAN Visible
  );
  SIMPLE_TEXT_OUTPUT_MODE *Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;


