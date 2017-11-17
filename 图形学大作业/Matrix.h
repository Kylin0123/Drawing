#pragma once
#include <vector>
#include <iostream>
#include <exception>

template<typename T>
class Matrix
{
public:
	Matrix(T* data = nullptr, int M = 0, int N = 0)
	{
		this->data.resize(M);
		for (int i = 0; i < M; i++) {
			this->data[i].resize(N);
			for (int j = 0; j < N; j++) {
				this->data[i][j] = *(data + N * i + j);
			}
		}
	}
	Matrix(const std::vector<std::vector<T> >& data) :
		data(data)
	{
	}
	~Matrix()
	{
	}
	int getM() const {
		return data.size();
	}
	int getN() const {
		if (data.size() <= 0)
			throw std::exception("The vertical demension is below 1.");
		return data[0].size();
	}
	T get(int x, int y) const {
		if (x >= getM() || y >= getN())
			throw std::out_of_range::exception();
		return data[x][y];
	}
	friend std::ostream &operator<< (std::ostream &os, Matrix<T> &m) {
		int M = m.data.size();
		int N = m.data[0].size();
		os << std::endl << "[";
		for (int i = 0; i < M; i++) {
			if (i != 0)
				os << " ";
			for (int j = 0; j < N; j++) {
				if (i == M - 1 && j == N - 1)
					os << m.data[i][j];
				else
					os << m.data[i][j] << ",";
			}
			if (i == M - 1)
				os << "]" << std::endl;
			else
				os << std::endl;
		}
		return os;
	}
	friend Matrix operator*(Matrix m1, Matrix m2) {
		if (m1.getN() != m2.getM())
			throw std::exception("Dimensions not match!");

		int m = m1.getM();
		int n = m2.getN();

		std::vector<std::vector<T> >ret(m, std::vector<T>(n, 0));

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < m1.getN(); k++) {
					ret[i][j] += m1.data[i][k] * m2.data[k][j];
				}
			}
		}

		return Matrix(ret);
	}
	friend Matrix operator+(Matrix m1, Matrix m2) {
		if (m1.getM() != m2.getM() || m1.getN() != m2.getN())
			throw std::exception("Dimensions not match!");

		int m = m1.getM();
		int n = m1.getN();

		std::vector<std::vector<T> >ret(m, std::vector<T>(n, 0));

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				ret[i][j] = m1.data[i][j] + m2.data[i][j];

		return Matrix(ret);
	}
private:
	std::vector<std::vector<T> > data;
};

static Matrix<float> cast_to_float(Matrix<int> m) {

	int M = m.getM();
	int N = m.getN();
	
	std::vector<std::vector<float> >data(M, std::vector<float>(N, 0));
	
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			data[i][j] = m.get(i, j);
		}

	return Matrix<float>(data);
}