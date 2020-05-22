class Matrix {
	int rowCount; // amount of rows in the matrix
	int colCount; // amount of columns in the matrix
	double** data; // two dimensional array which holds the data of the matrix
public:
	Matrix(int row, int column) {
		this->rowCount = row; // equalize rows
		this->colCount = column; // equalize columns
		this->data = new double* [rowCount]; // create rows of the matrix
		for (int i = 0; i < rowCount; i++) {
			this->data[i] = new double[colCount]; // create columns of the matrix
		}
	}
	void setData(int rowNum, int colNum, double data) {
		this->data[rowNum][colNum] = data; // sets the data to the element at the given row and column
	}
	double getData(int rowNum, int colNum) {
		return this->data[rowNum][colNum]; // gets the data from the element for the rowNum and colNum
	}
	void multiply(Matrix* first, Matrix* second) {
		// this function multiplies matrix first with the second and the result is set to this matrix
		double z = 0.0; // holds the total value of an element
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {
				for (int k = 0; k < first->getColCount(); k++) {
					this->data[i][j] += first->getData(i, k) * second->getData(k, j); // matrix multiplication
				}
			}
		}
	}
	void add(Matrix* second) {
		// this function adds the second matrix to this matrix
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {
				this->data[i][j] += second->getData(i, j);
			}
		}
	}
	int getRowCount() {
		return this->rowCount; // returns row count
	}
	int getColCount() {
		return this->colCount; // returns column count
	}
};