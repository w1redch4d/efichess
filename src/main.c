#include <efi.h>
#include <stdbool.h>
#include "include/chess.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
/* I'm too lazy to type this out five times */
#define ERR(x) if(EFI_ERROR((x))) return (x)

INT32 uwustrncmp( CHAR16 * s1, CHAR16 * s2, INTN n )
{
    while ( n && *s1 && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
        --n;
    }
    if ( n == 0 )
    {
        return 0;
    }
    else
    {
        return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
    }
}


EFI_STATUS EfiMain(EFI_HANDLE handle __attribute__((unused)), EFI_SYSTEM_TABLE *st) {
	EFI_STATUS status;
	EFI_INPUT_KEY key;
	UINTN HandleCount = 0;
    EFI_HANDLE *HandleBuffer = NULL;
    UINTN HandleIndex = 0;

	

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
	
	INTN depth = 3;
    INTN side = WHITE;
	CHAR16 user_move[6];

	printboard(st);

	while(1) {

		if(!get_input_string(st, user_move, 6))continue;
		
		if(uwustrncmp(user_move, u"\r\n", 2) == 0) continue;

        INTN user_src, user_dst;

        for(INTN sq = 0; sq < 128; sq++)
        {
            if(!(sq & 0x88))
            {
                if(!uwustrncmp(user_move, notation[sq], 2))
                    user_src = sq;

                if(!uwustrncmp(user_move + 2, notation[sq], 2))
                    user_dst = sq;
            }
        }
        
        // make user move
        board[user_dst] = board[user_src];
        board[user_src] = 0;

        // if pawn promotion
        if(((board[user_dst] == 9) && (user_dst >= 0 && user_dst <= 7)) ||
           ((board[user_dst] == 18) && (user_dst >= 112 && user_dst <= 119)))
            board[user_dst] |= 7;
		
		printboard(st);

		side = 24 - side;   // change side
              
        INTN score = SearchPosition(side, depth, -10000, 10000);

        // make AI move
        board[best_dst] = board[best_src];
        board[best_src] = 0;

        // if pawn promotion
        if(((board[best_dst] == 9) && (best_dst >= 0 && best_dst <= 7)) ||
           ((board[best_dst] == 18) && (best_dst >= 112 && best_dst <= 119)))
            board[best_dst] |= 7;

        side = 24 - side;    // change side

        printboard(st);

		uwuprintf(st, u"\r\nscore: '%d'\r\n", score);

        // Checkmate detection
        if(score == 10000 || score == -10000) {
			uwuprintf(st, u"Checkmate!\r\n"); break;
		}

        uwuprintf(st, u"best move: '%s'\r\n", notation[best_dst]);

	}
	

	// uwuprintf(st, u"%s", get_input_string(st, 256));
	/* flush console input buffer */
	status = st->ConIn->Reset(st->ConIn, false);
	ERR(status);

	/* poll for a keystroke */
	while ((status = st->ConIn->ReadKeyStroke(st->ConIn, &key)) != NULL && (uintptr_t)status == EFI_NOT_READY);
	ERR(status);

	return EFI_SUCCESS;
}