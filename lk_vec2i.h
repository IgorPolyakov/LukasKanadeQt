#ifndef LK_VEC2I_H
#define LK_VEC2I_H

//! @class lk_vec2i - Класс целочисленных двумерных векторов

/*! Класс содержит набор инструметнов для работы с двумерными векторами целых чисел */

class lk_vec2i
{
public:
	//! Конструктор по умолчанию
	lk_vec2i();
	//! Конструктор по двум значениям
	lk_vec2i(int nx, int ny);
	//! Значения вектора
	int x,y;
	//! Оператор сложения векторов
	lk_vec2i operator + (const lk_vec2i & op) const;
	//! Оператор вычитания векторов
	lk_vec2i operator - (const lk_vec2i & op) const;
	//! Оператор поэлементного умножения векторов
	lk_vec2i operator * (const lk_vec2i & op) const;
	//! Оператор умножения вектора на число
	lk_vec2i operator * (const int & op) const;
	//! Оператор деления вектора на число
	lk_vec2i operator / (const int & op) const;
	//! Оператор получения значений элементов
	int & operator []( int n);
};

#endif // LK_VEC2I_H
