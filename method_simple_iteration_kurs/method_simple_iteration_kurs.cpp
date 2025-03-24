#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;

#define MAX_ITERATIONS 1000
#define EPSILON 1e-10
#define MATRIX_COLS 101
#define MATRIX_ROWS 101
#define VECTOR_SIZE 101

void print_matr(double** matr) {
	for (int i = 0; i < MATRIX_COLS; i++) {
		for (int j = 0; j < MATRIX_ROWS; j++)
		{
			cout<<matr[i][j]<<" ";
		}
		cout << endl;
	}

}

void print_vec(double* vec) {
	for (int i = 0; i < MATRIX_COLS; i++)
		cout << vec[i] << " ";
}

void init_matr(double** matr) {
	for (int i = 0; i < MATRIX_COLS; i++)
		matr[i] = new double [MATRIX_ROWS];
}

void readMatr(string path, double** matr) {
	ifstream file(path);
	if (!file.is_open())
		exit(EXIT_FAILURE);
	for (int i = 0; i < MATRIX_COLS; i++) {
		for (int j = 0; j < MATRIX_ROWS; j++)
		{
			file >> matr[i][j];
		}
	}

}

void readVec(string path, double* vec) {
	ifstream file(path);
	if (!file.is_open())
		exit(EXIT_FAILURE);
	for (int i = 0; i < MATRIX_ROWS; i++)
	{
		file >> vec[i];
	}

}

double norm(const double* x1, const double* x0) {
    double sum = 0.0;
    for (int i = 0; i < MATRIX_COLS; ++i) {
        double diff = x1[i] - x0[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}



int simple_system(double** matr, double* vec, double* result) {
    double* x0 = new double[MATRIX_ROWS];
    double* x1 = new double[MATRIX_ROWS];


   
        for (int j = 0; j < MATRIX_ROWS; j++)
        {
            x0[j] = 0;
            x1[j] = 0;
        }


    int iteration = 0;
    do{
        iteration++;

        if (iteration != 1) {
            for (int i = 0; i < MATRIX_ROWS; i++) {
                x0[i] = x1[i];
                x1[i] = 0;
            }
        }
       

        for (int i = 0; i < MATRIX_COLS; i++) {
            for (int j = 0; j < MATRIX_ROWS; j++)
            {
                if (i != j) x1[i] += -matr[i][j] * x0[j];
                else if (i == j) x1[i] += vec[i];
                
            }
            x1[i] /= matr[i][i];
        }
        
     
        
    } while (iteration < MAX_ITERATIONS && norm(x1, x0) > EPSILON);

    for (int i = 0; i < MATRIX_ROWS; i++)
    {
        result[i] = x1[i];
    }

    delete[] x0;
    delete[] x1;

    return iteration;
}

int main() {
    setlocale(LC_ALL, "rus");


    
	string matr_path = "D:\\The Science\\PGU\\abramov\\method_simple_iteration_kurs\\matrix.txt";
	string vec_path =  "D:\\The Science\\PGU\\abramov\\method_simple_iteration_kurs\\vector.txt";

	double** matr = new double*[MATRIX_COLS];
	double* vec = new double[MATRIX_COLS];
	double* result = new double[MATRIX_COLS];
    chrono::steady_clock::time_point startTime, endTime;

	init_matr(matr);

	readMatr(matr_path, matr);
	readVec(vec_path, vec);
    


    startTime = chrono::steady_clock::now();

    int iterCount = simple_system(matr, vec, result);

    endTime = chrono::steady_clock::now();
    auto time = chrono::duration_cast <chrono::microseconds>(endTime - startTime).count();
    cout << "Result after "<< iterCount << " iteration, with time "<< time <<" microseconds : " << endl;
    print_vec(result);

	for (int i = 0; i < MATRIX_COLS; ++i) {
		delete[] matr[i];
	}

	delete[] matr;
	//delete[] vec;
	delete[] result;

	return 0;
}