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
#include "colorconverter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_tw_pallete_cellClicked(int row, int column);

    void on_lineEdit_editingFinished();

    void setVar();
    void setMessage();

    void on_pb_ColMod1_clicked();
    void on_pb_ColMod2_clicked();
    void on_pb_ColMod3_clicked();


    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);


private:
    Ui::MainWindow *ui;
    ColorModel colMod;
    QImage* img;
    QPoint center;
    QPixmap circle;
    ColorConverter* converter;
    QVector<ColorModel> pb_colors;
    void paintEvent(QPaintEvent*);
    void initilalizePalette();
    void initializePanel();
    void initializeActions();
    void initializeVars();
    void updatePanel();
    void changePanelParams(QString CM, int max1, int max2, int max3, int val1, int val2, int val3 );

};
#endif // MAINWINDOW_H
