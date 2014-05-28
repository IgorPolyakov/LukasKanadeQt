#ifndef LK_UTILS_H
#define LK_UTILS_H

#include <QtGui/QImage>
#include "lk_vec2f.h"
#include "lk_conv.h"

//! @namespace lk_utils - Набор функций для работы с изображением

/*! Удобные функции для работы с изображениями. Реализации могут быть заменены на более простые\эффективные в будущем */

namespace lk_utils
{
    static const float pi = 3.1415926535897932384626433832795028841f;
    //! Построение уменьшенного изображения по текущему
    QImage pyramide ( QImage src);
    //! Перевод цвета из HSV пространства в RGB
    QRgb hsv2rgb (QRgb color);
    //! Перевод цвета из RGB пространства в HSV
    QRgb rgb2hsv (QRgb color);
    QRgb hsv2rgb (float H, float S, float V);
    //! Вычисление угла вектора
    int vec2ang (lk_vec2f vect);
    float vec2angf (lk_vec2f vect);
    //! Вычисление амплитуды вектора
    int vec2amp (lk_vec2f vect);
    float vec2ampf (lk_vec2f vect);
    lk_conv gaussian_conv_kernel(int);
};

#endif // LK_UTILS_H
