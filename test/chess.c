#include <stdio.h>

const char* W_PIECES = "♔♕♖♗♘♙■";
const char* B_PIECES = "♚♛♜♝♞♟□";

/*
   navigation

    northwest    north   northeast
    noWe         nort         noEa
            +7    +8    +9
                \  |  /
    west    -1 <-  0 -> +1    east
                /  |  \
           -9    -8    -7
    soWe         sout         soEa
    southwest    south   southeast

*/


typedef unsigned long int board;

board createPositionMask(char position[2]){
    int fileIndex = (position[0] - 97);
    int rankIndex = position[1] - '0'; 
    int squareIndex = 8*rankIndex + fileIndex;
    board newPosition = 1 << squareIndex;
    return newPosition;
}

board createMoveMask(char from[2], char to[2]){
    board fromPositionMask = createPositionMask(from);
    board toPositionMask = createPositionMask(to);
    return fromPositionMask | toPositionMask;
}

board move(board *b, char from[2], char to[2]){
    board moveMask = createMoveMask(from, to);
    return *b ^ moveMask;
}

void printzeebits(board num){
    int i;
    for(i= (sizeof(unsigned long int)*8)-1;i>= 0; i--){
        char c = (num &(1LL<<i))? '1' : '0';
        putchar(c);
    }
    printf("\n");
}

void printboard(board *b){
    int i, j;
    int m = 0;
    char squares[64];
    for(i = (sizeof(unsigned long int)*8)-1;i>= 0; i--){
        m++;
        char c = (*b &(1LL<<i))? '1' : '.';
        squares[i] = c;
    }

    for(i = 63; i >= 0; i-=8){
        for(j = 7; j >= 0; j--){
            putchar(squares[i-j]);
            putchar(' ');
        }
        printf("\n");
    }
    printf("\n");
}

void initialize_pawns(board *b){
    int i;
    long int bit = 1;
    for(i = 0; i < 255;i+=8){
        *b |= (bit<<(i+1));
    }
}

void initialize_whitepawns(board *b){
    int i;
    long int bit = 1;
    for(i = 0; i < 255;i+=8){
        *b |= (bit<<(i+6));
    }
}

int main(){
    board black_pawns = 0;
    printf("Number = %lu\n",0x0101010101010101);
    board result = black_pawns | 0x0101010101010101;
    printboard(&result);
    printf("Number = %lu\n",0x00000000000000FF);
    result = black_pawns | 0x00000000000000FF;
    printboard(&result);
    printf("Number = %lu\n",0xFF00000000000000);
    result = black_pawns | 0xFF00000000000000;
    printboard(&result);
    printf("Number = %lu\n",0x8040201008040201);
    result = black_pawns | 0x8040201008040201;
    printboard(&result);
    printf("Number = %lu\n",0x55AA55AA55AA55AA);
    result = black_pawns | 0x55AA55AA55AA55AA;
    printboard(&result);
    int move = 27;
    board knightMoves = black_pawns | (0x1LL << move) 
        | (0x1LL << (move + 17))
        | (0x1LL << (move + 10))
        | (0x1LL << (move + 15))
        | (0x1LL << (move + 6))
        | (0x1LL << (move - 10))
        | (0x1LL << (move - 17))
        | (0x1LL << (move - 15))
        | (0x1LL << (move - 6));
    printf("Showing a Knight and the moves it can make: %lu\n", knightMoves);
    printboard(&knightMoves);

    board bishopMoves = black_pawns | (0x1LL << move) 
        | (0x1LL << (move + 9 + 9 + 9 + 9))
        | (0x1LL << (move + 9 + 9 + 9))
        | (0x1LL << (move + 9 + 9))
        | (0x1LL << (move + 9))
        | (0x1LL << (move + 7 + 7 + 7))
        | (0x1LL << (move + 7 + 7))
        | (0x1LL << (move + 7))
        | (0x1LL << (move - 9 ))
        | (0x1LL << (move - 9 - 9 ))
        | (0x1LL << (move - 9 - 9 - 9))
        | (0x1LL << (move - 7 ))
        | (0x1LL << (move - 7 - 7 ))
        | (0x1LL << (move - 7 - 7 - 7 ));
    printf("Showing a Bishop and the moves it can make: %lu\n", bishopMoves);
    printboard(&bishopMoves);


    printf("\n");
    board rookMoves = black_pawns | (0x1LL << move) 
        | (0x1LL << (move + 8))
        | (0x1LL << (move + 8 + 8))
        | (0x1LL << (move + 8 + 8 + 8))
        | (0x1LL << (move + 8 + 8 + 8 + 8))
        | (0x1LL << (move - 8))
        | (0x1LL << (move - 8 - 8))
        | (0x1LL << (move - 8 - 8 - 8))
        | (0x1LL << (move + 1))
        | (0x1LL << (move + 1 + 1))
        | (0x1LL << (move + 1 + 1 + 1))
        | (0x1LL << (move + 1 + 1 + 1 + 1))
        | (0x1LL << (move - 1))
        | (0x1LL << (move - 1 - 1))
        | (0x1LL << (move - 1 - 1 - 1));
    printf("Showing a Rook and the moves it can make: %lu\n", rookMoves);
    printboard(&rookMoves);

    board queenMoves = bishopMoves | rookMoves;
    printf("Showing a Queen and the moves it can make: %lu\n", queenMoves);
    printboard(&queenMoves);

    board kingMoves = black_pawns | (0x1LL << move)
        | (0x1LL << (move + 8))
        | (0x1LL << (move - 8))
        | (0x1LL << (move + 7))
        | (0x1LL << (move - 7))
        | (0x1LL << (move + 9))
        | (0x1LL << (move - 9))
        | (0x1LL << (move + 1))
        | (0x1LL << (move - 1));
    printf("Showing a King and the moves it can make: %lu\n", kingMoves);
    printboard(&kingMoves);
    return 0;
}

