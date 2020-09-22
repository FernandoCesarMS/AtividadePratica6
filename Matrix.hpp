#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

template <class TValor> class Matrix;

using namespace std;

template <class TValor>
class Matrix {
    
    private:
        TValor **m; // m é um array 2D a ser implementado como um pointer de pointers
        int nRows;  // numero de linhas
        int nCols;  //  numero de colunas 
        
    public:
        //Construtores 
        //matriz vazia
        
        Matrix()
        {
            m = NULL;
            nRows = 0;
            nCols = 0;
        };
        //matriz com valores = 0
        
        Matrix(int rows, int cols)
        {
            nRows = rows;
            nCols = cols;
            m = new TValor *[nRows];
            for (int i = 0; i < nRows; i++)
            {
                m[i] = new TValor[nCols];
                for (int j = 0; j < nCols; j++)
                {
                    m[i][j] = NULL;
                }
            }
        };
        //matriz com valores = parametro
        
        Matrix(int rows, int cols, const TValor& valor)
        {
            nRows = rows;
            nCols = cols;
            m = new TValor *[nRows];
            for (int i = 0; i < nRows; i++)
            {
                m[i] = new TValor[nCols];
                for (int j = 0; j < nCols; j++)
                {
                    m[i][j] = valor;
                }
            }
        };
        //construtor de copia
        
        Matrix(const Matrix<TValor> &that)
        {
            this->nRows = that.nRows;
            this->nCols = that.nCols;
            m = new TValor *[nRows];
            for (int i = 0; i < nRows; i++)
            {
                m[i] = new TValor[nCols];
                for (int j = 0; j < nCols; j++)
                {
                    this->m[i][j] = that.m[i][j];
                }
            }
        };
        // Destrutor
        
        ~Matrix()
        {
            for (int i; i < nRows; i++)
            {
                delete[] m[nCols];
                delete[] m;
            }
        };

        //manipuladores de matrix

        // obtem o numero de linhas
        
        int getRows() const
        {
            return nRows;
        };

        // obtem o numero de colunas
        
        int getCols() const
        {
            return nCols;
        };
        
        // obtem um elemento específico na posição (row,col). Obs: deve checar consistencia
        
        TValor get(int row, int col) const
        {
            if (row <= (this->nRows - 1) && col <= (this->nCols - 1))
            {
                return this->m[row][col];
            }
            else
            {
                cout << "Não foi encontrado esse elemento!" << endl;
                return NULL;
            }
        };

        // imprime o conteudo da matriz
        
        void print() const
        {
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    std::cout << m[i][j] << " ";
                }
                std::cout << "\n";
            }

            throw "Matriz não existe!";
        };

        // faz com que a matriz torne-se uma matriz nula
        
        void zeros()
        {
            for (int i = 0; i < nRows; i++)
            {
                for (int j = 0; j < nCols; j++)
                {
                    m[i][j] = m[i][j]-m[i][j];
                }
            }
        };

        //metodos de sobrecarga de operadores

        
        TValor& operator()(const int rows, const int cols) const 
        {
            if (rows <= this->getRows() && cols <= this->getCols())
            {
                return this->m[rows-1][cols-1];
            }
            return this->m[rows-1][cols-1];   
        };

        //verifica igualdade entre as matrizes
        
        bool operator==(const Matrix<TValor> &that) const
        {
            if (this->nRows == that.nRows)
            {
                if (this->nCols == that.nCols)
                {
                    for (int i = 0; i < this->nRows; i++)
                    {
                        for (int j = 0; j < this->nCols; j++)
                        {
                            if (this->m[i][j] != that.m[i][j])
                            {
                                return 0;
                            }
                        }
                    }
                    return 1;
                }
                return 0;
            }
            return 0;
        };

        //verifica desigualdade
        
        bool operator!=(const Matrix<TValor> &that) const
        {
            if (this->nRows == that.nRows)
            {
                if (this->nCols == that.nCols)
                {
                    for (int i = 0; i < this->nRows; i++)
                    {
                        for (int j = 0; j < this->nCols; j++)
                        {
                            if (this->m[i][j] != that.m[i][j])
                            {
                                return 1;
                            }
                        }
                    }
                    return 0;
                }
                return 1;
            }
            return 1;
        };

        //soma
        
        Matrix operator+(const Matrix<TValor> &that)
        {
            if (this->nRows == that.nRows)
            {
                if (this->nCols == that.nCols)
                {
                    for (int i = 0; i < this->nRows; i++)
                    {
                        for (int j = 0; j < this->nCols; j++)
                        {
                            this->m[i][j] = this->m[i][j] + that.m[i][j];
                        }
                    }
                    return *this;
                }
                else
                {
                    throw "Matriz Icompativel para essa operacao!";
                }
            }
            else
            {
                throw "Matriz Icompativel para essa operacao!";
            }
        };

        //subtrai
        
        Matrix operator-(const Matrix<TValor> &that)
        {
            if (this->nRows == that.nRows)
            {
                if (this->nCols == that.nCols)
                {
                    for (int i = 0; i < this->nRows; i++)
                    {
                        for (int j = 0; j < this->nCols; j++)
                        {
                            this->m[i][j] - that.m[i][j];
                        }
                    }
                    return *this;
                }
                else
                {
                    throw "Matriz Icompativel para essa operacao!";
                }
            }
            else
            {
                throw "Matriz Icompativel para essa operacao!";
            }
        };

        //multiplicação por C
        
        Matrix operator*(TValor C)
        {
            for (int i = 0; i < this->nRows; i++)
            {
                for (int j = 0; j < this->nCols; j++)
                {
                    this->m[i][j] * C;
                }
            }
            return *this;
        };

        //multiplicação por matrix
        
        Matrix operator*(const Matrix<TValor> &that)
        {
            Matrix retorno;
            retorno.nCols = this->nRows;
            retorno.nRows = that.nCols;
            retorno.m = new TValor *[this->nRows];
            TValor pos;
            if (this->nCols == that.nRows)
                for (int i = 0; i < this->nRows; i++)
                {
                    retorno.m[i] = new TValor[that.nCols];
                    for (int j = 0; j < that.nCols; j++)
                    {
                        pos = pos-pos;
                        for (int k = 0; k < this->nCols; k++)
                            pos += this->m[i][k] * that.m[k][j];
                        retorno.m[i][j] = pos;
                    }
                }
            return retorno;
        };

        //transposta
        
        Matrix& operator~()
        {

            int auxRows = nCols;
            int auxCols = nRows;
            Matrix aux(auxRows, auxCols);
            aux.m = new TValor *[auxRows];
            for (int i = 0; i < auxRows; i++)
            {
                aux.m[i] = new TValor[auxCols];
                for (int j = 0; j < auxCols; j++)
                {
                    aux.m[i][j] = m[j][i];
                }
            }
            return aux;
        };

        friend ostream &operator<<(ostream &op, const Matrix &matriz)
        {
            for (int i = 0; i < matriz.nRows; i++)
            {
                for (int j = 0; j < matriz.nCols; j++)
                {
                    op << matriz.m[i][j] << " ";
                }
                op << "\n";
            }
            return op;
        }

        friend istream &operator>>(istream &op, Matrix &matriz)
        {
            cout << endl
                << "Insira o numero de linhas: ";
            op >> matriz.nRows;
            cout << endl
                << "Insira o numero de colunas: ";
            op >> matriz.nCols;
            matriz.m = new TValor *[matriz.nRows];
            for (int i = 0; i < matriz.nRows; i++)
            {
                matriz.m[i] = new TValor[matriz.nCols];
                for (int j = 0; j < matriz.nCols; j++)
                {
                    op >> matriz.m[i][j];
                }
            }
            return op;
        }

};
#endif
