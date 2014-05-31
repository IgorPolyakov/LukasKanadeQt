#ifndef LK_VEC2F_H
#define LK_VEC2F_H

#include <src/lk_vec2i.h>

//! @class lk_vec2f - Класс двуемрного вектора чисел с плавающей запятой

/*! Класс содержит набор инструметнов для работы с двумерными векторами чисел с плавающей запятой */

class lk_vec2f
{
public:
    //! Конструктор по умолчанию
    lk_vec2f();
    //! Конструктор по двум числам
    lk_vec2f(float nx, float ny);
    //! Значения вектора
//    float data[2];
    float x,y;
    //! Оператор сложения векторов
    lk_vec2f operator + (const lk_vec2f & op) const;
    //! Оператор вычитания векторов
    lk_vec2f operator - (const lk_vec2f & op) const;
    //! Оператор поэлементного произведения векторов
    lk_vec2f operator * (const lk_vec2f & op) const;
    //! Оператор умножения вектора на число
    lk_vec2f operator * (const float & op) const;
    //! Оператор деления вектора на число
    lk_vec2f operator / (const float & op) const;
    //! Функция округления вектора до ближайшего целого
    lk_vec2i round () const;
    //! Получение значений вектора
    float & operator []( int n);
    void add (float ax, float ay);
};

#endif // LK_VEC2F_H
