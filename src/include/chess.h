#pragma once
#include <efi.h>

#define BOARD_SIZE 128
#define SQUARES_PER_ROW 16
#define WHITE 8
#define BLACK 16

INTN board[BOARD_SIZE] = {  // 0x88 board + positional scores
    22, 20, 21, 23, 19, 21, 20, 22,    0,  0,  5,  5,  0,  0,  5,  0, 
    18, 18, 18, 18, 18, 18, 18, 18,    5,  5,  0,  0,  0,  0,  5,  5,
     0,  0,  0,  0,  0,  0,  0,  0,    5, 10, 15, 20, 20, 15, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0,    5, 10, 20, 30, 30, 20, 10,  5,    
     0,  0,  0,  0,  0,  0,  0,  0,    5, 10, 20, 30, 30, 20, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0,    5, 10, 15, 20, 20, 15, 10,  5,
     9,  9,  9,  9,  9,  9,  9,  9,    5,  5,  0,  0,  0,  0,  5,  5,
    14, 12, 13, 15, 11, 13, 12, 14,    0,  0,  5,  5,  0,  0,  5,  0
};


CHAR16 *notation[] = {  // Convert square ID to board notation
    u"a8", u"b8", u"c8", u"d8", u"e8", u"f8", u"g8", u"h8",     u"i8", u"j8", u"k8", u"l8", u"m8", u"n8", u"o8", u"p8",
    u"a7", u"b7", u"c7", u"d7", u"e7", u"f7", u"g7", u"h7",     u"i7", u"j7", u"k7", u"l7", u"m7", u"n7", u"o7", u"p7",
    u"a6", u"b6", u"c6", u"d6", u"e6", u"f6", u"g6", u"h6",     u"i6", u"j6", u"k6", u"l6", u"m6", u"n6", u"o6", u"p6",
    u"a5", u"b5", u"c5", u"d5", u"e5", u"f5", u"g5", u"h5",     u"i5", u"j5", u"k5", u"l5", u"m5", u"n5", u"o5", u"p5",
    u"a4", u"b4", u"c4", u"d4", u"e4", u"f4", u"g4", u"h4",     u"i4", u"j4", u"k4", u"l4", u"m4", u"n4", u"o4", u"p4",
    u"a3", u"b3", u"c3", u"d3", u"e3", u"f3", u"g3", u"h3",     u"i3", u"j3", u"k3", u"l3", u"m3", u"n3", u"o3", u"p3",
    u"a2", u"b2", u"c2", u"d2", u"e2", u"f2", u"g2", u"h2",     u"i2", u"j2", u"k2", u"l2", u"m2", u"n2", u"o2", u"p2",
    u"a1", u"b1", u"c1", u"d1", u"e1", u"f1", u"g1", u"h1",     u"i1", u"j1", u"k1", u"l1", u"m1", u"n1", u"o1", u"p1"
};


CHAR16 *pieces = u".-pknbrq-P-KNBRQ";

static INTN move_offsets[] = {
   15,  16,  17,   0,  -15, -16, -17,   0,   1,  16,  -1, -16,   0,
   1,  16,  -1, -16,  15, -15, 17, -17,   0,  14, -14,  18, -18,  31,
  -31,  33, -33,   0,   3,  -1,  12,  21,  16,   7,  12
};

INTN piece_weights[] = { 0, 0, -100, 0, -300, -350, -500, -900, 0, 100, 0, 0, 300, 350, 500, 900 };
INTN best_src, best_dst;  // to store the best move found in search

void printboard(EFI_SYSTEM_TABLE *st) {
    for(INTN sq = 0; sq < 128; sq++)
    {
        if(!(sq % 16)) uwuprintf(st, u" %d  ", 8 - (sq / 16));
        //printf(" %c", ((sq & 8) && (sq += 7)) ? '\n' : pieces[board[sq] & 15]);    // ASCII pieces
		if (sq & 8) {
			sq += 7;
			uwuprintf(st, u"\r\n");
		} else {
			// PrINTN the corresponding piece based on the current board state
			uwuprintf(st, u" %c", pieces[board[sq] & 15]);
		}   // unicode pieces
    }
    
    uwuprintf(st, u"\r\n     a b c d e f g h\r\nYour move: \r\n");
}

INTN SearchPosition(INTN side, INTN depth, INTN alpha, INTN beta)
{
    if(!depth)
    {
        // Evaluate position        
        INTN mat_score = 0, pos_score = 0, pce, eval = 0;
    
        for(INTN sq = 0; sq < 128; sq++)
        {
            if(!(sq & 0x88))
            {
                if((pce = board[sq]))
                {
                    mat_score += piece_weights[pce & 15]; // material score
                    (pce & 8) ? (pos_score += board[sq + 8]) : (pos_score -= board[sq + 8]); // positional score
                }
            }
        }
    
        eval = mat_score + pos_score;

        return (side == 8) ? eval : -eval;   // here returns current position's score
    }

    INTN old_alpha = alpha;
    INTN temp_src;
    INTN temp_dst;
    INTN score = -10000;

    // Generate moves
    INTN piece, type, directions, dst_square, captured_square, captured_piece, step_vector;
    
    for(INTN src_square = 0; src_square < 128; src_square++)
    {
        if(!(src_square & 0x88))
        {
            piece = board[src_square];
                                        
            if(piece & side)
            {
                type = piece & 7;
                directions = move_offsets[type + 30];
                
                while((step_vector = move_offsets[++directions]))
                {
                    dst_square = src_square;
                    
                    do
                    {
                        dst_square += step_vector;
                        captured_square = dst_square;
                        
                        if(dst_square & 0x88) break;
    
                        captured_piece = board[captured_square];                        
    
                        if(captured_piece & side) break;
                        if(type < 3 && !(step_vector & 7) != !captured_piece) break;
                        if((captured_piece & 7) == 3) return 10000;    // on king capture
                        
                        // make move
                        board[captured_square] = 0;
                        board[src_square] = 0;
                        board[dst_square] = piece;

                        // pawn promotion
                        if(type < 3)
                        {
                            if(dst_square + step_vector + 1 & 0x80)
                                board[dst_square]|=7;
                        }
                        
                        score = -SearchPosition(24 - side, depth - 1, -beta, -alpha);
                                              
                        // take back
                        board[dst_square] = 0;
                        board[src_square] = piece;
                        board[captured_square] = captured_piece;

                        //Needed to detect checkmate
                        best_src = src_square;
                        best_dst = dst_square;

                        // alpha-beta stuff
                        if(score > alpha)
                        {
                            if(score >= beta)
                                return beta;
                            
                            alpha = score;
        
                            temp_src = src_square;
                            temp_dst = dst_square;
                        }              
                        
                        captured_piece += type < 5;
                        
                        if(type < 3 & 6*side + (dst_square & 0x70) == 0x80)captured_piece--;  
                    }
    
                    while(!captured_piece);
                }
            }
        }
    }

    // store the best move
    if(alpha != old_alpha)
    {
        best_src = temp_src;
        best_dst = temp_dst;
    }

    return alpha;   // here returns the best score
}
