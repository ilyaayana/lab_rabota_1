#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtMath>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hue = 1,val = 100;

    colMod = HSV;

    img = new QImage(150,150,QImage::Format_ARGB32);
    center = QPoint(73,73);

    initializePanel();
    initilalizePalette();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initilalizePalette(){
    for(int i = 0; i < ui->tw_pallete->rowCount(); i++){
        for(int j = 0; j < ui->tw_pallete->columnCount(); j++){
            QTableWidgetItem *tmp = new QTableWidgetItem();
            tmp->setBackground(QColor::fromHsv(24*j,255,255-51*(i+1)));
            ui->tw_pallete->setItem(i,j,tmp);
        }
    }
}

void MainWindow::initializePanel(){
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)),ui->horizontalSlider,SLOT(setValue(int)) );
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->spinBox_3,SLOT(setValue(int)) );
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)),ui->horizontalSlider_2,SLOT(setValue(int)) );
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),ui->spinBox_2,SLOT(setValue(int)) );
    connect(ui->spinBox, SIGNAL(valueChanged(int)),ui->horizontalSlider_3,SLOT(setValue(int)) );
    connect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),ui->spinBox,SLOT(setValue(int)) );
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if(colMod == HSV)
        hue = value;
    else if(colMod = RGB)
        red = value;
    update();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
   if(colMod == HSV)
        saturation = value;
    update();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    if(colMod == HSV)
        val = value;
    update();
}

void MainWindow::paintEvent(QPaintEvent *){
    QPalette pal = ui->label_4->palette();
    pal.setColor(QPalette::Window, QColor::fromHsv(hue-1,saturation*255/100,val*255/100));
    ui->label_4->setPalette(pal);
    img->fill(Qt::black);
    QPixmap circle("C:\\Personal\\example\\lol.png");
    circle = circle.scaled(100,100,Qt::IgnoreAspectRatio);
    QPainter p;
    p.begin(img);
    p.setOpacity(val/100);
    qDebug() << p.opacity() << Qt::endl;
    p.drawPixmap(0,0,150,150,circle);
    p.drawEllipse(center.x()+65*saturation/100*qCos(hue*3.14/180),center.y()-65*saturation/100*qSin(hue*3.14/180),10,10);
    p.end();
    ui->label_5->setPixmap(QPixmap::fromImage(*img));

}

void MainWindow::on_pushButton_clicked()
{
    colMod = RGB;
    HSVtoRGB();
    updatePanel();
}
void MainWindow::HSVtoRGB(){
      double C = val/100 * saturation/100;
      double X = C*(1-abs(fmod((hue/60), 2) -1));
      double m = val/100-C;
          if(hue <60){
              red= C;
              green = X;
              blue = 0;
          }
          else if(hue < 120){
              red= X;
              green = C;
              blue = 0;
          }
          else if(hue < 180){
              red= 0;
              green = C;
              blue = X;
          }
          else if(hue < 240){
              red= 0;
              green = X;
              blue = C;
          }
          else if(hue < 300){
              red= X;
              green = 0;
              blue = C;
          }
          else if(hue < 360){
              red= C;
              green = 0;
              blue = X;
          }
      red = (red+m)*255;
      green = (green+m)*255;
      blue = (blue+m)*255;
}

void MainWindow::RGBtoHSV(){
    double R = red/255, G = green/255, B = blue/255;
    char Cmax,Cmin;
    if(R > G && R >B ){
       Cmax = 'R';
       Cmin = G<B? 'G' : 'B';
    }
    else if(G > R && G >B ){
        Cmax = 'G';
        Cmin = B<R? 'B' : 'R';
     }
    else{
           Cmax = 'B';
           Cmin = R<G? 'R' : 'G';
        }
    if(Cmax == 'R' && )
}

void MainWindow::on_pushButton_3_clicked()
{
    colMod = HSV;
    RGBtoHSV();
    updatePanel();
}

void MainWindow::on_tw_pallete_cellClicked(int row, int column)
{
    hue = 24*column;
    saturation = 100;
    val = 100 - 20*row;
    updatePanel();
}

void MainWindow::updatePanel(){
    switch(colMod){
    case RGB:
        ui->label->setText("R");
        ui->label_3->setText("G");
        ui->label_2->setText("B");
        ui->horizontalSlider->setMaximum(255);
        ui->horizontalSlider_2->setMaximum(255);
        ui->horizontalSlider_3->setMaximum(255);
        ui->horizontalSlider->setValue(red);
        ui->horizontalSlider_2->setValue(green);
        ui->horizontalSlider_3->setValue(blue);
        break;
    case HSV:
        ui->label->setText("R");
        ui->label_3->setText("G");
        ui->label_2->setText("B");
        ui->horizontalSlider->setMaximum(255);
        ui->horizontalSlider_2->setMaximum(255);
        ui->horizontalSlider_3->setMaximum(255);
        ui->horizontalSlider->setValue(hue);
        ui->horizontalSlider_2->setValue(saturation);
        ui->horizontalSlider_3->setValue(val);
        break;
    case XYZ:
        break;
    default:
        break;
}
}
