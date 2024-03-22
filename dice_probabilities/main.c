#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void *failMalloc(size_t nByte) {
	void *buffer = malloc(nByte);
	
	if (buffer == NULL) {
		fprintf(stderr, "failMalloc: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	return buffer;
}

static double computeProbability(size_t diceSum, size_t minDice, size_t maxDice, size_t nCombination) {
	size_t i;
	size_t j;
	size_t k;
	size_t nSuccessfulCombination;
	double probability;

	nSuccessfulCombination = 0;
	for (i = minDice; i <= maxDice; ++i) {
		for (j = minDice; j <= maxDice; ++j) {
			for (k = minDice; k <= maxDice; ++k) {
				if (i + j + k == diceSum) {
					++nSuccessfulCombination;
				}
			}
		}
	}

	probability = (double) nSuccessfulCombination / (double) nCombination;
	
	return probability;
}

static double **createProbabilityMatrix(size_t nDice, size_t *nRow, size_t nCol) {
	size_t MIN_DICE = 1;
	size_t MAX_DICE = 6;
	size_t MIN_SUM = nDice * MIN_DICE;
	size_t MAX_SUM = nDice * MAX_DICE;
	size_t N_SUM_COMBINATION = MAX_SUM - MIN_SUM + 1;
	size_t N_COMBINATION = (size_t) pow((double) MAX_DICE, (double) nDice);

	double **matrix;
	size_t i;

	*nRow = N_SUM_COMBINATION;

	matrix = failMalloc(N_SUM_COMBINATION * sizeof(double *));

	for (i = 0; i < N_SUM_COMBINATION; ++i) {
		matrix[i] = failMalloc(nCol * sizeof(double));
	}

	for (i = 0; i < N_SUM_COMBINATION; ++i) {
		matrix[i][0] = (double) (i + MIN_SUM);
		matrix[i][1] = computeProbability((size_t) matrix[i][0], MIN_DICE, MAX_DICE, N_COMBINATION);
	}

	return matrix;
}

static void printMatrix(double **matrix, size_t nRow, size_t nCol) {
	size_t i;
	size_t j;

	for (i = 0; i < nRow; ++i) {
		for (j = 0; j < nCol; ++j) {
			printf("%lf ", matrix[i][j]);
		}

		printf("\n");
	}
}

static void freeMatrix(double **matrix, size_t nRow) {
	size_t i;

	for (i = 0; i < nRow; ++i) {
		free(matrix[i]);
	}

	free(matrix);
}

int main(void) {
	size_t N_DICE = 3;
	size_t N_COL = 2;

	size_t nRow;
	double **probabilityMatrix;

	probabilityMatrix = createProbabilityMatrix(N_DICE, &nRow, N_COL);

	printMatrix(probabilityMatrix, nRow, N_COL);

	freeMatrix(probabilityMatrix, nRow);

	return 0;
}

