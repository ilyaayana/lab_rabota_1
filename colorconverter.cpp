#include "colorconverter.h"

ColorConverter::ColorConverter()
{
    colMod = HSV;
}

void ColorConverter::setColMode(ColorModel colorMod){
    colMod = colorMod;
}
ColorModel ColorConverter::getColMode(){
    return colMod;
}

void ColorConverter::updateColors(int val1, int val2, int val3, int val4, ColorModel clMode){
    switch(colMod){
        case RGB:
        rgb[0] = val1;
        rgb[1] = val2;
        rgb[2] = val3;
        RGBtoHSV();
        RGBtoXYZ();
        break;
    case HSV:
        hsv[0] = val1;
        hsv[1] = val2;
        hsv[2] = val3;
        HSVtoRGB();
        RGBtoXYZ();
        break;
    case XYZ:
        xyz[0] = val1;
        xyz[1] = val2;
        xyz[2] = val3;
        XYZtoRGB();
        RGBtoHSV();
    case HSL:
        //HStoHSV();
        break;
    }
}
QVector<int> ColorConverter::getColors(ColorModel clMode){
    QVector<int> colors(4);
    switch(clMode){
    case HSV:
        colors[0] = hsv[0];
        colors[1] = hsv[1];
        colors[2] = hsv[2];
        break;
    case RGB:
        colors[0] = rgb[0];
        colors[1] = rgb[1];
        colors[2] = rgb[2];
        break;
    case XYZ:
        colors[0] = xyz[0];
        colors[1] = xyz[1];
        colors[2] = xyz[2];
        break;
 }
    return colors;
}

void ColorConverter::RGBtoXYZ(){
    double Rn = F1(rgb[0]/255.0)*100;
    double Gn = F1(rgb[1]/255.0)*100;
    double Bn = F1(rgb[2]/255.0)*100;
    xyz[0] = 0.412453*Rn+0.357580*Gn+0.180423*Bn;
    xyz[1] = 0.212671*Rn+0.715160*Gn+0.072169*Bn;
    xyz[2] = 0.019334*Rn+0.119193*Gn+0.950227*Bn;
}

double ColorConverter::F1(double x){
    if(x>0.04045)
        return pow((x+0.055)/1.055,2.4);
    return x/12.92;
}

void ColorConverter::XYZtoRGB(){
    double x = xyz[0]/100.0, y = xyz[1]/100.0, z = xyz[2]/100.0;
    double Rn = 3.2406 * x - 1.5372* y - 0.4986*z;
    double Gn = -0.9689 * x + 1.8758* y + 0.0415*z;
    double Bn = 0.0557 * x - 0.2040* y + 1.0570*z;
    rgb[0] = F2(Rn)*255;
    rgb[1] = F2(Gn) * 255;
    rgb[2] = F2(Bn)*255;
}
double ColorConverter::F2(double x)
{
    if(x>=0.0031308)
        return 1.055*pow(x,1/2.4)-0.055;
    return 12.92*x;
}
void ColorConverter::HSVtoRGB()
{
     QColor::fromHsv(hsv[0],hsv[1]*255/100.0,hsv[2]*255/100.0).getRgb(&rgb[0],&rgb[1],&rgb[2]);
}

void ColorConverter::RGBtoHSV()
{
    QColor tmp(rgb[0],rgb[1],rgb[2]);
    hsv[0] = tmp.hsvHue();
    hsv[1] = tmp.hsvSaturation()*100.0/255;
    hsv[2] = tmp.value()*100.0/255;
}
void ColorConverter::XYZtoLAB(){
    double Xw = 95.047, Yw = 100, Zw = 108.883;
    double L = 116*F3(xyz[1]/Yw)-16;
    double a = 500*F3(xyz[0]/Xw)-F3(xyz[1]/Yw);
    double b = 200*F3(xyz[1]/Yw)-F3(xyz[2]/Zw);
}
double ColorConverter::F3(double x){
    if(x>=0.008856)
        return pow(x,1.0/3);
    return 7.787*x+16.0/116;
}
void ColorConverter::LABtoXYZ(){
    double L,a,b;
    double Xw = 95.047, Yw = 100, Zw = 108.883;
    xyz[1] = F4((L+16)/116)+Xw;
    xyz[0] = F4(a/500+(L+16)/116)*Yw;
    xyz[2] = F4((L+16)/116-b/200)*Zw;
}
double ColorConverter::F4(double x){
    if(pow(x,3) >=0.008856)
        return pow(x,3);
    return (x-16.0/116)/7.787;
}
void ColorConverter::HSVtoHSL(){
    double Sv = hsv[1]/100.0, v =hsv[2]/100.0;
    int Hl = hsv[0];
    double L = v*(1-Sv/2);
    double Sl;
    if(L == 0 || L ==1)
        Sl = 0;
    else
        Sl = (v-L)/(L<1-L ? L: 1-L);
}
void ColorConverter::HSLtoHSV(){
    //hsv[0] = HSL;
}
