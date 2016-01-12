// Name: Tyler Gaunltett
// Date: 10/4/2015
// Course: COP 3502 Fall


#include <stdio.h>
#include <stdlib.h>


int** fillBoard(int moves, int slotsFilled);
void freeBoard(int **board, int moves);
void runPerms(int colorsPossible, int slotsFilled);
void recPerms(int perm[], int k, int n);
int permCheck(int array[]);
int basicCheck(int permutedArray[], int moveArray[], int slotsFilled, int* compareBlackPegs, int* compareWhitePegs);
int* blackPegsArray(int** board, int moves, int slotsFilled);
int* whitePegsArray(int** board, int moves, int slotsFilled);
int powerB(int base, int exp);
int** guessBoard(int moves, int slotsFilled);
int comparePegs(int solutionBlackPegs, int solutionWhitePegs, int clueBlackPegs, int clueWhitePegs);


int cases, slotsFilled, colorsPossible, moves;
int** board;
int** newGuessBoard;
int* blackPegs;
int* whitePegs;
int* compareBlackPegs;
int* compareWhitePegs;

int main(){

	
	scanf("%i", &cases);

	while (cases > 0){

		scanf("%i", &slotsFilled);

		scanf("%i", &colorsPossible);

		scanf("%i", &moves);

		// Takes in the board input.
		board = fillBoard(moves, slotsFilled);

		
		newGuessBoard = guessBoard(moves, slotsFilled);


		// Creates seperate black and white peg arrays.
		blackPegs = blackPegsArray(board, moves, slotsFilled);
		whitePegs = whitePegsArray(board, moves, slotsFilled);

		// Initialze two arrays to hold the generated
		// black and white pegs.
		compareBlackPegs = malloc(sizeof(int)*moves);
		compareWhitePegs = malloc(sizeof(int)*moves);

		// Initalizes the program.
		runPerms(colorsPossible, slotsFilled);

		freeBoard(board, moves);

		free(newGuessBoard, moves);

		free(blackPegs);

		free(whitePegs);

		cases--;

	}
	
	return 0;
}

// Fills a 2D array from standard input. Does not account for black and white pegs yet.
int** fillBoard(int moves, int slotsFilled){

	int** board = malloc(sizeof(int*)*moves);
	int i, j, k;


	for (i = 0; i < moves; i++){

		// Adds space for the black and white pegs.
		board[i] = malloc(sizeof(int)*(slotsFilled+2));
		
		// Scans two extra spots for the black and white pegs.
		for (j = 0; j < slotsFilled + 2; j++){

			// Puts the next value into k
			scanf("%i", &k);
			// Puts the value in k into the 2D board
			board[i][j] = k;
		}
		
		
	}

	return board;
}


int** guessBoard(int moves, int slotsFilled){

	int** guessBoard = malloc(sizeof(int*)*moves);
	int i, j, k;


	for (i = 0; i < moves; i++){

		// Adds space for the guesses.
		guessBoard[i] = malloc(sizeof(int)*(slotsFilled));

		for (j = 0; j < slotsFilled; j++){


			// Puts the values from board
			// into an array without black/white pegs.
			guessBoard[i][j] = board[i][j];

		}

	}

	return guessBoard;
}



// Stores white pegs in their own array.
int* blackPegsArray(int** board, int moves, int slotsFilled){

	int* blackPegs = malloc(sizeof(int*)*moves);

	int i;

	for (i = 0; i < moves; i++){

		blackPegs[i] = board[i][slotsFilled];

	}

	return blackPegs;
}


// Stores white pegs in their own array.
int* whitePegsArray(int** board, int moves, int slotsFilled){

	int* whitePegs = malloc(sizeof(int*)*moves);

	int i;

	for (i = 0; i < moves; i++){

		whitePegs[i] = board[i][(slotsFilled + 1)];

	}

	return whitePegs;

}

// Frees dynamically allocated standard input.
void freeBoard(int **board, int moves){
	
	int i;

	for (i = 0; i < moves; i++){
		free(board[i]);
	}
	free(board);
}


// Recursive function to generate all posisble
// color combos
void recPerms(int perm[], int k, int n) {
	
	// Base case.
	if (k == n) {
		permCheck(perm);
		
	}

	// Recursive call to print all permutations.
	else {

		int i;

		// Prints all possible numbers starting at n
		for (i = 0; i<n; i++) {
			perm[k] = i;
			recPerms(perm, k + 1, n);
		}
	}
}


void runPerms(int colorsPossible, int slotsFilled) {

	int permSize = powerB(colorsPossible, slotsFilled);

	int perm = malloc(sizeof(int)*permSize);

	recPerms(perm, 0, colorsPossible);

	printf("\n");
}


int permCheck(int array[]) {
	
	int i, j, k, matchCount = 0;

	for (i = 0; i < cases; i++){

		basicCheck(array, newGuessBoard[i], slotsFilled, &compareBlackPegs, &compareWhitePegs);

		k = comparePegs(&blackPegs[i], &whitePegs[i], &compareBlackPegs[i], &compareBlackPegs[i]);

		if (k == 1){
			
			matchCount++;

		}

	}
	
	return matchCount;
}


// Compares the guess to the permutation and counts
// number of black and white pegs awared.
int basicCheck(int permutedArray[], int moveArray[], int slotsFilled, int* compareBlackPegs, int* compareWhitePegs){

	int i, k, j, m, loopBreak;
	int *used = malloc(sizeof(int)*slotsFilled);

	// Counts the number of black pegs
	for (i = 0; i < slotsFilled; i++){

		if (permutedArray[i] == moveArray[i]){
			used[i] = 1;
			compareBlackPegs++;
			//printf("Black peg is %i at index: %i\n", compareBlackPeg, i);
		}

		else{
			used[i] = 0;
		}
	}
 

	i = 0;
	j = 0;

	// Counts the number of white pegs
	for (i = 0; i < slotsFilled; i++){

		j = 0;

		while (j < slotsFilled) {

			// Checks if array index is used already.
			if (!used[i]){

				// If indexes are equal, increment white pegs.
				if (permutedArray[i] == moveArray[j]) {

					// Checks if array index is used already.
					if (!used[i]){

						compareWhitePegs++;

						//printf("White peg is %i at used index: %i\n", compareWhitePeg, i);

						used[i] = 1;

						break;
					}

					else j++;

				}
				
				// If they are not equal, check next index.
				else
					j++;

			}

			// Infinite loop without increment. 
			else
				j++;

		}
	}

	return 0;
}


// Compares the actual pegs from the pegs generated by the possible solution.
// If they are equal, the solution is a possible answer.
int comparePegs(int solutionBlackPegs, int solutionWhitePegs, int clueBlackPegs, int clueWhitePegs){

	if ((solutionBlackPegs == clueBlackPegs) && (solutionWhitePegs == clueWhitePegs)){

		return 1;
	}

	return 0;
}


int powerB(int base, int exp) {

	// Everything raised to the 0 power is 1.
	if (exp == 0)
		return 1;

	// Anything raised to the 1st power is itself.
	else if (exp == 1)
		return base;

	// Utlize the even powered exponent and the rules of exponentiation.
	else if (exp % 2 == 0)
		return powerB(base*base, exp / 2);

	// If we can't, then just use our regular solution.
	else
		return base*powerB(base, exp - 1);
}