ld EPS = 1e-9;

// Para sistemas de congruencia, reemplazar cada operacion por su respectivo mod y en vez de usar EPS hacer chequeo == 0
int gauss(vv<ld> A, vector<ld>& solution) {
	int nOfEquations = (int) SIZE(A), nOfVariables = (int) SIZE(A[0]) - 1; // Ya que la ultima columna es termino independiente
	vi pivotRowForVariable(nOfVariables, -1);
	int currentRow = 0;

	for (int col = 0; col < nOfVariables && currentRow < nOfEquations; col++) {
		int bestRow = currentRow;
		forsn(row, currentRow, nOfEquations) if (abs(A[row][col]) > abs(A[bestRow][col])) bestRow = row;
		if (abs(A[bestRow][col]) < EPS) continue; // La variable col-th es libre ya que fue eliminada de toda row >= currentRow
		swap(A[currentRow], A[bestRow]);
		pivotRowForVariable[col] = currentRow;		
		forn(row, nOfEquations) if (row != currentRow){ // Elimina la variable de todas las filas que no sean currentRow
			ld factor = A[row][col]/A[currentRow][col];
			forsn(j, col, nOfVariables+1) A[row][j] -= factor*A[currentRow][j];
		}
		currentRow++;
	}

	solution.assign(nOfVariables, 0);

	forn(var, nOfVariables) { // Reconstruir solucion, si la variable quedo libre le doy de valor 0 por default
		int row = pivotRowForVariable[var];
		if (row != -1) solution[var] = A[row][nOfVariables] / A[row][var]; // Ya que la ecuacion quedo: A[row][var]*x_var = A[row][nOfVariable]
	}

	forn(row, nOfEquations) { // Verificar si es incompatible
		ld leftValue = 0, rightValue = A[row][nOfVariables];
		forn(var, nOfVariables) leftValue += A[row][var] * solution[var];
		if (abs(leftValue - rightValue) > EPS) return 0; // No hay solucion
	}

	// Verificar si es indeterminado
	forn(var, nOfVariables) if (pivotRowForVariable[var] == -1) return 2; // Infinitas soluciones porque hay variable libre
	return 1; // Solucion unica
}