#ifndef COLORCONVERTER_H
#define COLORCONVERTER_H
#include <QtMath>
#include <QPainter>
#include <QMainWindow>
#include <QDebug>
#include <QVector>
#include <QtMath>

enum ColorModel{
    None,
    RGB,
    HSV,
    XYZ,
    LAB,
    HSL,
    CMYK
};

class ColorConverter:public QMainWindow
{
    Q_OBJECT

public:
    ColorConverter();
    void setColMode(ColorModel colorMod);
    ColorModel getColMode();
    void updateColors(int val1, int val2, int val3, int val4 = 0, ColorModel clMode = None);
    QVector<int> getColors(ColorModel clMode);
signals:
    void XYZ_outOfBounds();

private:
    ColorModel colMod;
    int hsv[3];
    int rgb[3];
    int xyz[3];
    void sincColors(ColorModel mode);
    void HSVtoRGB();
    void RGBtoHSV();
    void RGBtoXYZ();
    QVector<int> RGBtoCMYK();
    void CMYKtoRGB(int,int,int,int);
    void XYZtoRGB();
    QVector<int> XYZtoLAB();
    void LABtoXYZ(double,double,double);
    QVector<int> HSVtoHSL();
    void HSLtoHSV(double,double,double);
    double F1(double x);
    double F2(double x);
    double F3(double x);
    double F4(double x);
};

#endif // COLORCONVERTER_H
