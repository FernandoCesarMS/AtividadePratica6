#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "MatrixAntiga.hpp"

// construtor default - cria uma matriz vazia com nRows = nCols = 0
Matrix::Matrix()
{
    m = NULL;
    nRows = 0;
    nCols = 0;
}

// construtor parametrico 1 - cria uma matriz com nRows  = rows, nCols = cols e
// com todos os elementos iguais a 0.0 (double)
Matrix::Matrix(int rows, int cols, const double &value)
{
    nRows = rows;
    nCols = cols;
    m = new double *[nRows];
    for (int i = 0; i < nRows; i++)
    {
        m[i] = new double[nCols];
        for (int j = 0; j < nCols; j++)
        {
            m[i][j] = 0.0;
        }
    }
}

// construtor parametrico 2 - cria uma matriz com os dados fornecidos pelo arquivo texto myFile.
Matrix::Matrix(ifstream &myFile)
{
    vector<string> texto;
    for (int i = 0; !myFile.fail(); i++)
    { // Guardando as informações do arquivo num vector de string
        string str;
        getline(myFile, str);
        texto.push_back(str);
    }
    this->nRows = texto.size() - 1;
    m = new double *[this->nRows];
    for (int i = 0; i < texto.size() - 1; i++)
    {
        vector<double> matriz;
        for (int j = 0; j < texto[i].size(); j++)
        { // transformando os caracteres em int
            int num;
            if (((int)texto[i][j] >= 48) && ((int)texto[i][j] <= 57))
            {
                num = texto[i][j] - '0';
                matriz.push_back(num);
            }
        }
        m[i] = new double[matriz.size()];
        for (int j = 0; j < matriz.size(); j++)
        { // atribuindo os numeros a matrix
            this->m[i][j] = matriz[j];
        }
        this->nCols = matriz.size();
    }
    myFile.close();
}

// construtor de copia
Matrix::Matrix(const Matrix &that)
{
    this->nRows = that.nRows;
    this->nCols = that.nCols;
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            this->m[i][j] = that.m[i][j];
        }
    }
}

// destrutor
Matrix::~Matrix()
{
    for (int i; i < nRows; i++)
    {
        delete[] m[nCols];
        delete[] m;
    }
}
// obtem o numero de linhas
int Matrix::getRows() const
{
    return nRows;
}
// obtem o numero de colunas
int Matrix::getCols() const
{
    return nCols;
}

// obtem um elemento específico na posição (row,col). Obs: deve checar consistencia
double Matrix::get(int row, int col) const
{
    if (row <= (this->nRows - 1) && col <= (this->nCols - 1))
    {
        return this->m[row][col];
    }
    else
    {
        cout << "Não foi encontrado esse elemento!" << endl;
        return 0.0;
    }
}

// imprime o conteudo da matriz
void Matrix::print() const
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// faz com que a matriz torne-se uma matriz identidade
void Matrix::unit()
{
    if (nCols == nRows)
    {

        for (int i = 0; i < nRows; i++)
        {

            for (int j = 0; j < nCols; j++)
            {

                if (j == i)
                {
                    m[i][j] = 1.0;
                }
                else
                {

                    m[i][j] = 0.0;
                }
            }
        }
    }
    else
    {
        std::cout << "Essa matriz nao pode ser transformada em identidade";
    }
}

// faz com que a matriz torne-se uma matriz nula
void Matrix::zeros()
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            m[i][j] = 0.0;
        }
    }
}

// faz com que a matriz torne-se uma matriz cujos elementos sao iguais a 1
void Matrix::ones()
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            m[i][j] = 1.0;
        }
    }
}

//---------------------------------------------------------
//metodos de sobrecarga de operadores

Matrix Matrix::operator()(const Matrix &that)
{
    Matrix x;
    cout << "oi";
    return x;
}
//verifica igualdade entre as matrizes
bool Matrix::operator==(const Matrix &that) const
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
bool Matrix::operator!=(const Matrix &that) const
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
Matrix Matrix::operator+(const Matrix &that)
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
            std::cout << "Matrixes incompativeis para essa operacao";
        }
    }
    else
    {
        std::cout << "Matrixes incompativeis para essa operacao";
    }
};

//soma
Matrix Matrix::operator+=(const Matrix &that)
{
    if (this->nRows == that.nRows)
    {
        if (this->nCols == that.nCols)
        {
            for (int i = 0; i < this->nRows; i++)
            {
                for (int j = 0; j < this->nCols; j++)
                {
                    this->m[i][j] + that.m[i][j];
                }
            }
            return *this;
        }
        else
        {
            std::cout << "Matrixes incompativeis para essa operacao";
        }
    }
    else
    {
        std::cout << "Matrixes incompativeis para essa operacao";
    }
};

//subtrai
Matrix Matrix::operator-(const Matrix &that)
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
            std::cout << "Matrixes incompativeis para essa operacao";
        }
    }
    else
    {
        std::cout << "Matrixes incompativeis para essa operacao";
    }
};

//subtrai
Matrix Matrix::operator-=(const Matrix &that)
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
            std::cout << "Matrixes incompativeis para essa operacao";
        }
    }
    else
    {
        std::cout << "Matrixes incompativeis para essa operacao";
    }
};

//multiplicação por C
Matrix Matrix::operator*(int C)
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

//multiplicação por C
Matrix Matrix::operator*=(int C)
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
Matrix Matrix::operator*(const Matrix &that)
{
    Matrix retorno;
    retorno.nCols = this->nRows;
    retorno.nRows = that.nCols;
    retorno.m = new double *[this->nRows];
    if (this->nCols == that.nRows)
        for (int i = 0; i < this->nRows; i++)
        {
            retorno.m[i] = new double[that.nCols];
            for (int j = 0; j < that.nCols; j++)
            {
                double pos = 0;
                for (int k = 0; k < this->nCols; k++)
                    pos += this->m[i][k] * that.m[k][j];
                retorno.m[i][j] = pos;
            }
        }
    return retorno;
};

//multiplicação por matrix
Matrix Matrix::operator*=(const Matrix &that)
{
    int x = this->getCols();
    Matrix Aux(this->getRows(), this->getCols());
    this->nCols = that.getCols();
    Aux.m = new double *[this->nRows];
    if (x == that.getRows())
        for (int i = 0; i < this->nRows; i++)
        {
            Aux.m[i] = new double[this->nCols];
            for (int j = 0; j < this->nCols; j++)
            {
                double pos = 0;
                for (int k = 0; k < x; k++)
                    pos += this->m[i][k] * that.m[k][j];
                Aux.m[i][j] = pos;
                pos = 0;
            }
        }
    for (int i = 0; i < this->nRows; i++)
    {
        for (int j = 0; j < this->nCols; j++)
        {
            this->m[i][j] = Aux.m[i][j];
        }
    }
    return Aux;
};

//transposta
Matrix &Matrix::operator~()
{

    int auxRows = nCols;
    int auxCols = nRows;
    Matrix aux(auxRows, auxCols);
    aux.m = new double *[auxRows];
    for (int i = 0; i < auxRows; i++)
    {
        aux.m[i] = new double[auxCols];
        for (int j = 0; j < auxCols; j++)
        {
            aux.m[i][j] = m[j][i];
        }
    }
    return aux;
};

ostream &operator<<(ostream &op, const Matrix &matriz)
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
istream &operator>>(istream &op, Matrix &matriz)
{
    cout << endl
         << "Insira o numero de linhas: ";
    op >> matriz.nRows;
    cout << endl
         << "Insira o numero de colunas: ";
    op >> matriz.nCols;
    matriz.m = new double *[matriz.nRows];
    for (int i = 0; i < matriz.nRows; i++)
    {
        matriz.m[i] = new double[matriz.nCols];
        for (int j = 0; j < matriz.nCols; j++)
        {
            op >> matriz.m[i][j];
        }
    }
    return op;
}