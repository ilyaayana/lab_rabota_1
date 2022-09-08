#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hue = 1,val = 100;

    colMod = HSV;

    img = new QImage(150,150,QImage::Format_ARGB32);
    circle = QPixmap("C:\\Personal\\example\\lol.png");
    circle = circle.scaled(100,100,Qt::IgnoreAspectRatio);
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
    else if(colMod == RGB)
        red = value;
    update();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
   if(colMod == HSV)
        saturation = value;
   else if(colMod == RGB)
        green = value;
    update();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    if(colMod == HSV)
        val = value;
    else if(colMod == RGB)
        blue = value;
    update();
}

void MainWindow::paintEvent(QPaintEvent *){
    if(colMod == RGB)
        RGBtoHSV();
    QPalette pal = ui->label_4->palette();
    pal.setColor(QPalette::Window, QColor::fromHsv(hue-1,saturation*255/100,val*255/100));
    ui->label_4->setPalette(pal);
    img->fill(Qt::black);
    QPainter p;
    p.begin(img);
    p.setOpacity(val/100);
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
     QColor tmp = QColor::fromHsv(hue,saturation*255/100.0,val*255/100.0);
     red = tmp.red();
     green = tmp.green();
     blue = tmp.blue();
}

void MainWindow::RGBtoHSV(){
    QColor tmp(red,green,blue);
    hue = tmp.hsvHue();
    saturation = tmp.hsvSaturation()*100.0/255;
    val = tmp.value()*100.0/255;
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
        ui->label->setText("H");
        ui->label_3->setText("S");
        ui->label_2->setText("V");
        ui->horizontalSlider->setMaximum(360);
        ui->horizontalSlider_2->setValue(saturation);
        ui->horizontalSlider_3->setValue(val);
        ui->horizontalSlider_2->setMaximum(100);
        ui->horizontalSlider_3->setMaximum(100);
        ui->horizontalSlider->setValue(hue);
        break;
    case XYZ:
        break;
    default:
        break;
}
}
