#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QImage>
#include <QLabel>
#include <QtMath>
#include <QPainter>
#include <QDebug>
#include <QSet>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum ColorModel{
    RGB,
    HSV,
    XYZ,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_tw_pallete_cellClicked(int row, int column);

    void on_lineEdit_editingFinished();

    void on_pb_ColMod1_clicked();

    void on_pb_ColMod2_clicked();

    void on_pb_ColMod3_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    ColorModel colMod;
    QImage* img;
    int hsv[3];
    int rgb[3];
    int xyz[3];
    QPoint center;
    QPixmap circle;

    void paintEvent(QPaintEvent*);
    void initilalizePalette();
    void initializePanel();
    void HSVtoRGB();
    void RGBtoHSV();
    void RGBtoXYZ();
    void XYZtoRGB();
    void updatePanel();
    void changePanelParams(QString CM, int max1, int max2, int max3, int val1, int val2, int val3 );
    double F1(double x);
    double F2(double x);

};
#endif // MAINWINDOW_H
