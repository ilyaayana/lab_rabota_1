#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hsv[0] = 1,hsv[2] = 100;

    colMod = HSV;

    img = new QImage(150,150,QImage::Format_ARGB32);
    circle = QPixmap(":/ColorCircle.png");
    center = QPoint(73,73);

    initializePanel();
    initilalizePalette();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete img;
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

void MainWindow::paintEvent(QPaintEvent *){
    if(colMod == RGB)
        RGBtoHSV();
    QPalette pal = ui->label_4->palette();
    pal.setColor(QPalette::Window, QColor::fromHsv(hsv[0]-1,hsv[1]*255.0/100,hsv[2]*255.0/100));
    ui->label_4->setPalette(pal);
    img->fill(Qt::black);
    QPainter p;
    p.begin(img);
    p.setOpacity(hsv[2]/100.0);
    p.drawPixmap(0,0,150,150,circle);
    p.drawEllipse(center.x()+65*hsv[1]/100.0*qCos(hsv[0]*3.14/180),center.y()-65*hsv[1]/100.0*qSin(hsv[0]*3.14/180.0),10,10);
    p.end();
    ui->lb_colCircle->setPixmap(QPixmap::fromImage(*img));
}

void MainWindow::on_pb_ColMod1_clicked()
{
    colMod = RGB;
    HSVtoRGB();
    updatePanel();
}

void MainWindow::HSVtoRGB(){
     QColor::fromHsv(hsv[0],hsv[1]*255/100.0,hsv[2]*255/100.0).getRgb(&rgb[0],&rgb[1],&rgb[2]);
}

void MainWindow::RGBtoHSV(){
    QColor tmp(rgb[0],rgb[1],rgb[2]);
    hsv[0] = tmp.hsvHue();
    hsv[1] = tmp.hsvSaturation()*100.0/255;
    hsv[2] = tmp.value()*100.0/255;
}

void MainWindow::on_pb_ColMod3_clicked()
{
    colMod = HSV;
    RGBtoHSV();
    updatePanel();
}

void MainWindow::on_tw_pallete_cellClicked(int row, int column)
{
    hsv[0] = 24*column;
    hsv[1] = 100;
    hsv[2] = 100 - 20*row;
    if(colMod == RGB)
        HSVtoRGB();
    updatePanel();
}

void MainWindow::updatePanel(){
    switch(colMod){
    case RGB:
        changePanelParams("RGB",255,255,255,rgb[0],rgb[1],rgb[2]);
        break;
    case HSV:
        changePanelParams("HSV",360,100,100,hsv[0],hsv[1],hsv[2]);
        break;
    case XYZ:
        changePanelParams("XYZ",100,100,100,xyz[0],xyz[1],xyz[2]);
        break;
    default:
        break;
}
}

void MainWindow::on_lineEdit_editingFinished()
{
    QString html_code = ui->lineEdit->text();
    QStringRef r(&html_code,1,2);
    QStringRef g(&html_code,3,2);
    QStringRef b(&html_code,5,2);
    bool ok;
    rgb[0] = r.toUInt(&ok,16) ;
    rgb[1]  = g.toUInt(&ok,16);
    rgb[2] = b.toUInt(&ok,16);
    updatePanel();
}

void MainWindow::on_pb_ColMod2_clicked()
{
    if(colMod == HSV)
        HSVtoRGB();
    colMod = XYZ;
    double Rn = F(rgb[0]/255.0)*100;
    double Gn = F(rgb[1]/255.0)*100;
    double Bn = F(rgb[2]/255.0)*100;
    xyz[0] = 0.412453*Rn+0.357580*Gn+0.180423*Bn;
    xyz[1] = 0.212671*Rn+0.715160*Gn+0.072169*Bn;
    xyz[2] = 0.019334*Rn+0.119193*Gn+0.950227*Bn;
    updatePanel();
}

double MainWindow::F(double x){
    if(x>0.04045)
        return pow((x+0.055)/1.055,2.4);
    return x/12.92;
}

void MainWindow::changePanelParams(QString CM, int max1, int max2, int max3, int val1, int val2, int val3 ){
    ui->label->setText(QString(CM[0]));
    ui->label_3->setText(QString(CM[1]));
    ui->label_2->setText(QString(CM[2]));
    ui->horizontalSlider->setMaximum(max1);
    ui->horizontalSlider_2->setMaximum(max2);
    ui->horizontalSlider_3->setMaximum(max3);
    ui->horizontalSlider->setValue(val1);
    ui->horizontalSlider_2->setValue(val2);
    ui->horizontalSlider_3->setValue(val3);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    if(colMod == HSV)
        hsv[0] = position;
    else if(colMod == RGB)
        rgb[0] = position;
    update();
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    if(colMod == HSV)
         hsv[1] = position;
    else if(colMod == RGB)
         rgb[1] = position;
     update();
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    if(colMod == HSV)
        hsv[2] = position;
    else if(colMod == RGB)
        rgb[2] = position;
    update();
}
