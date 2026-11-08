#pragma once
#include <vector>
#include <type_traits>
#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <chrono>


class RandomGen{
    private:
        uint32_t state;
    public:
        RandomGen(uint32_t seed){
            if(seed == 0){
                seed  = 1;
            }
            state = seed;
        }
       RandomGen() : RandomGen(static_cast<uint32_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count())) {}
        uint32_t gen(){
            state ^= state << 13;
            state ^= state >> 17;
            state ^= state << 5;

            return state;
        }


        template <typename T>
        T uniform(T low,T high){
            T r = gen()/ 4294967296.0;
            T range = high - low;

            return low + range*r;
        }

        int uniformi(int low ,int high){
            uint32_t count = high-low+1;
            return low + gen() % count;
        }
      
};

template <typename T>
class Matrix{

    //restricts the matrix type to be that of numbers
    static_assert(std::is_arithmetic_v<T>,"Matrix Type Must Be A Number");
    private:
        //stores rows columns and the vector containing the actual data
        int rows_;
        int columns_;
        std::vector<T> data;
        

    public:


        //constructor intitalizes the matrix
        Matrix(int row,int column){
            rows_ = row;
            columns_ = column;
            data.resize(rows_*columns_);
        }

        //getter for the number of columns
        int columns() const{
            return columns_;
        }

        //getter for the number of rows
        int rows() const{
            return rows_;
        }



        //getter for the element at the ith row and jth column
        T get(int row,int column) const{


            //places a bounds on the row and column so that they are within the shape of the matrix
            if(column >= columns_ || row >= rows_|| row < 0 || column < 0){
                throw std::out_of_range("Matrix index out of range");
            }

            //returns the element in the ith row and jth column
            return data[row*columns_ + column];
        }


        //setter for the element but follows the same logic as getter
        void set(int row,int column,T data_){
            if(column >= columns_ || row >= rows_|| row < 0 || column < 0){
                throw std::out_of_range("Matrix index out of range");
            }
            data[row*columns_ + column] = data_;//sets the value of data
        }


    
        struct Size
        {
            int rows;
            int columns;
            bool operator==(const Size& other) const {return rows == other.rows && columns == other.columns;}
            bool operator!=(const Size& other) const {return !(*this == other);}

            
        };
        

        Size size() const{
            return {rows_,columns_};      
        }
        T& operator()(int row,int column){
            if(column >= columns_ || row >= rows_|| row < 0 || column < 0){
                throw std::out_of_range("Matrix index out of range");
            }
            return data[row * columns_ + column];
        }

        T operator()(int row,int column) const{
            return get(row,column);
        }
        

        
        Matrix operator+(const Matrix& other) const{
            if (this->size() != other.size()){
                throw std::invalid_argument("Both Matricies Must Be Of The Same Size!!!");
            }

            Size sizes = other.size();

            int row = sizes.rows;
            int column = sizes.columns;
            Matrix m(row,column);
            for(int i = 0 ; i  < row;i ++){
                for (int j = 0; j < column;j++){
                    m(i,j) = (*this)(i,j) + other(i,j);
                }
            }

            return m;
        }

         Matrix operator-(const Matrix& other) const{
            if (this->size() != other.size()){
                throw std::invalid_argument("Both Matricies Must Be Of The Same Size!!!");
            }

            Size sizes = other.size();

            int row = sizes.rows;
            int column = sizes.columns;
            Matrix m(row,column);
            for(int i = 0 ; i  < row;i ++){
                for (int j = 0; j < column;j++){
                    m(i,j) = (*this)(i,j) - other(i,j);
                }
            }

            return m;
        }


        Matrix operator*(T scalar) const{
            Size s = this->size();

            int row = s.rows;
            int column = s.columns;


            Matrix m(row,column);

            for(int i =0;i < row;i++){
                for(int j =0; j < column;j++){
                    m(i,j) = (*this)(i,j) * scalar;
                }
            }

            return m;
        }

        Matrix Transpose() const{
            Size s = this->size();

            int row = s.rows;
            int column = s.columns;

            Matrix m(column,row);

            for(int i = 0; i < row;i++){
                for(int j = 0; j < column;j++){
                    m(j,i) = (*this)(i,j);
                }
            }
            return m;
        }

        void randomize(RandomGen& rgen,T low,T high){
            for (int i = 0; i < rows_;i++){
                for(int j =0;j < columns_;j++){
                    (*this)(i,j) = rgen.uniform(low,high);
                }
            }
        }

        Matrix operator*(const Matrix& other) const{
            if(other.rows() != this->columns()){
                throw std::invalid_argument("Matrix sizes don't fit for multiplication");
            }

            
            Matrix m(other.rows(),this->columns;)
        }

};


template <typename T>
void print_m(const Matrix<T>& m){
    int rows = m.rows();
    int columns = m.columns();


    for(int i = 0;i < rows;i++){
        std::cout << "|\t" ;
        for(int j=0; j < columns;j++){
            std::cout << m(i,j) << "\t";
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "(" << rows << " x " << columns << ")" << std::endl;
}


