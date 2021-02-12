package app;

import java.io.*;
import java.util.*;

public class Lab7 {

	static double[][] getMainMatrix(int size, Scanner inputFile) throws Exception {
		double[][] mainMatrix = new double[size][size];
		
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				mainMatrix[i][j] = inputFile.nextDouble();
			}
		}
		return mainMatrix;
	}

	public static void getMatrixWithoutRowAndCol(double[][] matrix, int size, int row, int col, double[][] newMatrix) {
		int offsetRow = 0;
		int offsetCol = 0;
		for (int i = 0; i < size - 1; i++) {

			if (i == row) {
				offsetRow = 1;
			}

			offsetCol = 0;
			for (int j = 0; j < size - 1; j++) {

				if (j == col) {
					offsetCol = 1;
				}

				newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
			}
		}
	}

	public static double matrixDet(double[][] matrix, int size) {
		double det = 0;
		int degree = 1; // (-1)^(1+j)

		if (size == 1) {
			return matrix[0][0];
		} else if (size == 2) {
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		} else {
			double[][] newMatrix = new double[size - 1][size - 1];
			for (int i = 0; i < size - 1; i++) {
				newMatrix[i] = new double[size - 1];
			}

			for (int j = 0; j < size; j++) {
				getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

				det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));

				degree = -degree;
			}

			for (int i = 0; i < size - 1; i++) {
				newMatrix[i] = null;
			}
			newMatrix = null;
		}

		return det;
	}
	
	 public static double[][] getInverseMatrix(double[][] matrix) {
	        double temp;
	        int size = matrix.length;
	        double[][] identityMatrix = new double[size][size];
	        double[][] inversedMatrix = new double[size][size];

	        for (int i = 0; i < size; i++)
	            for (int j = 0; j < size; j++) {
	                inversedMatrix[i][j] = matrix[i][j];
	            }

	        for (int i = 0; i < size; i++)
	            for (int j = 0; j < size; j++) {
	                identityMatrix[i][j] = 0;

	                if (i == j)
	                    identityMatrix[i][j] = 1;
	            }

	        for (int k = 0; k < size; k++) {
	          if(inversedMatrix[k][k]==0)
	            {
	            	int mainRow=k+1;
	            	for(int p=k+1;p<size;p++) {
	            		if(Math.abs(inversedMatrix[p][k])> Math.abs(inversedMatrix[mainRow][k])) {
	            			mainRow=p;
	            		}
	            		if (Math.abs(inversedMatrix[mainRow][k]) == 0) {
	            			continue;
	            		}
	            	}
	            		for(int j=0;j<size;j++) {
	            			double change1=inversedMatrix[k][j];
	            			inversedMatrix[k][j]=inversedMatrix[mainRow][j];
	            			inversedMatrix[mainRow][j]=change1;
	            			
	            			double change2=identityMatrix[k][j];
	            			identityMatrix[k][j]=identityMatrix[mainRow][j];
	            			identityMatrix[mainRow][j]=change2;
	            		}
	            }
	          temp = inversedMatrix[k][k];
	          
	            for (int j = 0; j < size; j++) {
	                inversedMatrix[k][j] /= temp; 
	                identityMatrix[k][j] /= temp;
	            }

	            for (int i = k + 1; i < size; i++) 
	            {
	                temp = inversedMatrix[i][k];

	                for (int j = 0; j < size; j++) {
	                    inversedMatrix[i][j] -= inversedMatrix[k][j] * temp;
	                    identityMatrix[i][j] -= identityMatrix[k][j] * temp;
	                }
	            }
	        }
	
	        for (int k = size - 1; k > 0; k--) {
	            for (int i = k - 1; i >= 0; i--) {
	                temp = inversedMatrix[i][k];

	                for (int j = 0; j < size; j++) {
	                    inversedMatrix[i][j] -= inversedMatrix[k][j] * temp;
	                    identityMatrix[i][j] -= identityMatrix[k][j] * temp;
	                }
	            }
	        }

	        for (int i = 0; i < size; i++)
	            for (int j = 0; j < size; j++)
	                inversedMatrix[i][j] = identityMatrix[i][j];

	        return inversedMatrix;
	    }
	 
	 public static void printMatrix(double[][] matrix) {
		 for (int i = 0; i < matrix.length; i++) {
				for (int j = 0; j < matrix.length; j++) {
					if (j == matrix.length - 1)
						System.out.println(matrix[i][j]);
					else
						System.out.print(matrix[i][j]+"  ");
				}
			}
	 }

	public static void main(String[] args) throws Exception {
		Scanner inputFile;
		try {
			inputFile = new Scanner(new FileReader("E:\\eclipse\\JAVAworkspace\\Lab.7\\src\\input.txt"));
		} catch (java.io.FileNotFoundException e) {
			System.out.println("Error: File not found");
			return;
		}
		int n;
		double[][] mainMatrix;
		double[][] inverstedMatrix;
		try {
			n = inputFile.nextInt();
			mainMatrix = getMainMatrix(n, inputFile);
		} catch (java.util.InputMismatchException e) {
			System.out.println("Error: Invalid argument(s)");
			inputFile.close();
			return;
		} catch (java.util.NoSuchElementException e) {
			System.out.println("Error: Not enough arguments");
			inputFile.close();
			return;
		}
		if (inputFile.hasNext()) {
			System.out.println("Error: Too many arguments");
			inputFile.close();
			return;
		}
		printMatrix(mainMatrix);
		if(matrixDet(mainMatrix,n)!=0) {
		inverstedMatrix=getInverseMatrix(mainMatrix);
		printMatrix(inverstedMatrix);
		}
		else System.out.println("Matrix can not be inversed");
		inputFile.close();
	}
}