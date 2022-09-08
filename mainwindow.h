#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QImage>
#include <QLabel>


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
    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_tw_pallete_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    ColorModel colMod;
    QImage* img;
    QLabel* im;
    int hue,saturation;
    double val;
    QRect rect;
    QPoint center;
    double red,green,blue;

    void paintEvent(QPaintEvent*);
    void initilalizePalette();
    void initializePanel();
    void recalcPosition();
    void HSVtoRGB();
    void RGBtoHSV();
    void updatePanel();
};
#endif // MAINWINDOW_H
