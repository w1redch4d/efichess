#include <efi.h>

#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
/* I'm too lazy to type this out five times */
#define ERR(x) if(EFI_ERROR((x))) return (x)


EFI_STATUS EfiMain(EFI_HANDLE handle __attribute__((unused)), EFI_SYSTEM_TABLE *st) {
	EFI_STATUS status;
	EFI_INPUT_KEY key;
	UINTN HandleCount = 0;
    EFI_HANDLE *HandleBuffer = NULL;
    UINTN HandleIndex = 0;

	const CHAR16 english_chars[] = {
        u'A', u'B', u'C', u'D', u'E', u'F', u'G', u'H', u'I', u'J', u'K', u'L', u'M', u'N', u'O', u'P', u'Q', u'R', u'S', u'T', u'U', u'V', u'W', u'X', u'Y', u'Z'
	};

	/* reset the watchdog timer */
	status = st->BootServices->SetWatchdogTimer(0, 0x10000, 0, NULL);
	ERR(status);

	status = st->BootServices->LocateHandleBuffer(AllHandles, NULL, NULL, &HandleCount, &HandleBuffer);
	 if (!EFI_ERROR(status)) {
        for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) 
            status = st->BootServices->ConnectController(HandleBuffer[HandleIndex], NULL, NULL, true);

        st->BootServices->FreePool(HandleBuffer);
    }
	/* clear the screen */
	status = st->ConOut->ClearScreen(st->ConOut);
	ERR(status);

	uwuprintf(st, u"Number of enlish characters are: %d\r\n", ARRAY_SIZE(english_chars));
	for (UINTN i = 0; i < ARRAY_SIZE(english_chars); i++)
            uwuprintf(st, u"characters: %c\r\n", english_chars[i]);
	

	/* flush console input buffer */
	status = st->ConIn->Reset(st->ConIn, false);
	ERR(status);

	/* poll for a keystroke */
	while ((status = st->ConIn->ReadKeyStroke(st->ConIn, &key)) != NULL && (uintptr_t)status == EFI_NOT_READY);
	ERR(status);

	return EFI_SUCCESS;
}