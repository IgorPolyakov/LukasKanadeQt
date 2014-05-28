#ifndef LK_CONV_H
#define LK_CONV_H

#include <QVector>
#include <QImage>

//! @class lk_conv - Класс для свертки картинки с помощью некоторого ядра

/*! Класс содержит набор инструметнов для создания и использования ядер свертки */

class lk_conv
{
private:
    //! Ядро свертки
    QVector < QVector <float> > kernel;
    //! Функция свертки по нормированному ядру
    QImage conv(
	    const QImage & src //!< Исходное изображение
	    ) const;
    //! Функция свертки по ядру с нулевой суммой
    QImage zeroconv(
	    const QImage & src //!< Исходное изображение
	    ) const;
    int
	    __width, //!< Ширина ядра
	    __height;//!< Высота ядра
public:
    //! Конструктор по умолчанию
    lk_conv ();
    //! Конструктор по размерам ядра
    lk_conv (
	    int w, //!< Ширина нового ядра
	    int h  //!< Высота нового ядра
	    );
    //! Оператор доступа к ячейкам ядра
    QVector <float> & operator [](
	    int i
	    );
    //! Оператор свертки по нормированному ядру
    QImage operator * (
	    const QImage & src //!< Исходное изображение
	    ) const;
    //! Оператор свертки по ядру с нулевой суммой
    QImage operator % (
	    const QImage & src //!< Исходное изображение
	    ) const;
    void mult(float);
    //! Функция нормализации ядра ( для ядер с ненулевой суммой)
    void normalize();
};

#endif // LK_CONV_H
