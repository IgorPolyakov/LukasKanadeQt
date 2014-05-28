#ifndef LK_MAT22F_H
#define LK_MAT22F_H
#ifdef __MMX__
#include <mmintrin.h>
#endif
#ifdef __SSE3__
#include <pmmintrin>
#endif
#ifdef __SSSE3__
#include <tmmintrin.h>
#endif
#if defined (__SSE4_2__) || defined (__SSE4_1__)
#include <smmintrin>
#endif
#include <lk_vec2f.h>

//! @class lk_mat22f - Класс матриц 2х2 с плавающей запятой для проведения вычислений

/*! Класс содержит набор инструметнов для работы с матрицами размером 2х2, содержащими числа с плавающей запятой */

class lk_mat22f
{
private:
    //! Константа точности вычислений
    static float eps;
public:
    //! Конструктор по умолчанию
    lk_mat22f();
    //! Конструктор по четырем значениям
    lk_mat22f(float na11, float na12, float na21, float na22);
    //! Конструктов по вектор-столбцам
    lk_mat22f(lk_vec2f na1, lk_vec2f na2);
    //! Вектор-столбцы
    lk_vec2f a1,a2;
    //! Оператор поэлементного сложения матриц
    lk_mat22f operator + (const lk_mat22f & op) const;
    //! Оператор поэлементного вычитания матрицы
    lk_mat22f operator - (const lk_mat22f & op) const;
    //! Оператор матричного произведения
    lk_mat22f operator * (const lk_mat22f & op) const;
    //! Оператор умножения матрицы на константу
    lk_mat22f operator * (const float & op) const;
    //! Опретатор деления матрицы на константу
    lk_mat22f operator / (const float & op) const;
    //! Оператор умножения матрицы на вектор-столбец
    lk_vec2f operator * (const lk_vec2f & op) const;
    //! Оператор получения вектор-столбца матрицы
    lk_vec2f & operator []( int n);
    //! Функция вычисления определителя матрицы
    float det () const;
    //! Функция решения матричного уравнения методом Крамера
    lk_vec2f solve (lk_vec2f) const;
    void add (float a11, float a12, float a21, float a22);
};


#endif // LK_MAT22F_H
