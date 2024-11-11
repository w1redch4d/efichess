#include <efi.h>

#include <stdbool.h>

/* I'm too lazy to type this out five times */
#define ERR(x) if(EFI_ERROR((x))) return (x)

EFI_STATUS EfiMain(EFI_HANDLE handle __attribute__((unused)), EFI_SYSTEM_TABLE *st) {
	EFI_STATUS status;
	EFI_INPUT_KEY key;

	/* reset the watchdog timer */
	status = st->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	ERR(status);

	/* clear the screen */
	status = st->ConOut->ClearScreen(st->ConOut);
	ERR(status);

	/* print 'Hello World' */
	status = st->ConOut->OutputString(st->ConOut, L"Hello World");
	ERR(status);

	/* flush console input buffer */
	status = st->ConIn->Reset(st->ConIn, false);
	ERR(status);

	/* poll for a keystroke */
	while((status = st->ConIn->ReadKeyStroke(st->ConIn, &key)) == EFI_NOT_READY);
	ERR(status);

	return EFI_SUCCESS;
}