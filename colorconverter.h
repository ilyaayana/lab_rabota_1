#ifndef COLORCONVERTER_H
#define COLORCONVERTER_H
#include <QtMath>
#include <QPainter>
#include <QDebug>
#include <QVector>

enum ColorModel{
    None,
    RGB,
    HSV,
    XYZ,
    LAB,
    HSL,
    CMYK
};

class ColorConverter
{
public:
    ColorConverter();
    void setColMode(ColorModel colorMod);
    ColorModel getColMode();
    void updateColors(int val1, int val2, int val3, int val4 = 0, ColorModel clMode = None);
    QVector<int> getColors(ColorModel clMode);

private:
    ColorModel colMod;
    int hsv[3];
    int rgb[3];
    int xyz[3];

    void initilalizePalette();
    void initializePanel();
    void HSVtoRGB();
    void RGBtoHSV();
    void RGBtoXYZ();
    void XYZtoRGB();
    void XYZtoLAB();
    void LABtoXYZ();
    void HSVtoHSL();
    void HSLtoHSV();
    double F1(double x);
    double F2(double x);
    double F3(double x);
    double F4(double x);
};

#endif // COLORCONVERTER_H
