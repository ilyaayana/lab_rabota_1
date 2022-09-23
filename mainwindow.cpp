#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    converter = new ColorConverter();
    pb_colors.push_back(RGB);
    pb_colors.push_back(XYZ);
    pb_colors.push_back(HSV);

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
    connect(ui->spinBox_4, SIGNAL(valueChanged(int)),ui->horizontalSlider_4,SLOT(setValue(int)) );
    connect(ui->horizontalSlider_4,SIGNAL(valueChanged(int)),ui->spinBox_4,SLOT(setValue(int)) );
    ui->horizontalSlider_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->spinBox_4->setVisible(false);
}

void MainWindow::paintEvent(QPaintEvent *){
    QVector<int> colors = converter->getColors(HSV);
    QPalette pal = ui->label_4->palette();
    pal.setColor(QPalette::Window, QColor::fromHsv(colors[0]-1,colors[1]*255.0/100,colors[2]*255.0/100));
    ui->label_4->setPalette(pal);
    img->fill(Qt::black);
    QPainter p;
    p.begin(img);
    p.setOpacity(colors[2]/100.0);
    p.drawPixmap(0,0,150,150,circle);
    p.drawEllipse(center.x()+65*colors[1]/100.0*qCos(colors[0]*3.14/180),center.y()-65*colors[1]/100.0*qSin(colors[0]*3.14/180.0),10,10);
    p.end();
    ui->lb_colCircle->setPixmap(QPixmap::fromImage(*img));
}

void MainWindow::on_pb_ColMod1_clicked()
{
    converter->setColMode(pb_colors[0]);
    updatePanel();
}

void MainWindow::on_pb_ColMod2_clicked()
{
    converter->setColMode(pb_colors[1]);
    updatePanel();
}

void MainWindow::on_pb_ColMod3_clicked()
{
    converter->setColMode(pb_colors[2]);
    updatePanel();
}

void MainWindow::on_tw_pallete_cellClicked(int row, int column)
{
    converter->updateColors(24*column,100,100-20*row,0,HSV);
    updatePanel();
}

void MainWindow::updatePanel(){
    QVector<int> colors = converter->getColors(converter->getColMode());

    if(converter->getColMode()!= LAB){
        ui->horizontalSlider_2->setMinimum(0);
        ui->horizontalSlider_3->setMinimum(0);
        ui->spinBox_2->setMinimum(0);
        ui->spinBox->setMinimum(0);
    }
    if(converter->getColMode()!= CMYK){
        ui->horizontalSlider_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->spinBox_4->setVisible(false);
    }

    switch(converter->getColMode()){
    case RGB:
        changePanelParams("RGB",255,255,255,colors[0],colors[1],colors[2]);
        break;
    case HSV:
        changePanelParams("HSV",360,100,100,colors[0],colors[1],colors[2]);
        break;
    case XYZ:
        changePanelParams("XYZ",100,100,100,colors[0],colors[1],colors[2]);
        break;
    case LAB:
        ui->horizontalSlider_2->setMinimum(-128);
        ui->horizontalSlider_3->setMinimum(-128);
        ui->spinBox_2->setMinimum(-128);
        ui->spinBox->setMinimum(-128);
        changePanelParams("Lab",100,128,128,colors[0],colors[1],colors[2]);
        break;
    case CMYK:
        ui->horizontalSlider_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->spinBox_4->setVisible(true);
        ui->horizontalSlider_4->setValue(colors[3]);
        changePanelParams("CMY",100,100,100,colors[0],colors[1],colors[2]);
        break;
    case HSL:
        changePanelParams("HSL",360,100,100,colors[0],colors[1],colors[2]);
        break;
    default:
        break;
}
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

void MainWindow::on_lineEdit_editingFinished()
{
    QString html_code = ui->lineEdit->text();
    QStringRef r(&html_code,1,2);
    QStringRef g(&html_code,3,2);
    QStringRef b(&html_code,5,2);
    bool ok;
    converter->updateColors(r.toUInt(&ok,16),g.toUInt(&ok,16),b.toUInt(&ok,16),0,RGB);
    updatePanel();
}

void MainWindow::on_action2_triggered()
{
    pb_colors[0] = RGB;
    pb_colors[1] = CMYK;
    pb_colors[2] = HSL;
    ui->pb_ColMod1->setText("RGB");
    ui->pb_ColMod2->setText("CMYK");
    ui->pb_ColMod3->setText("HSL");
    converter->setColMode(pb_colors[0]);
    updatePanel();
}
void MainWindow::on_action3_triggered()
{
    pb_colors[0] = RGB;
    pb_colors[1] = XYZ;
    pb_colors[2] = LAB;
    ui->pb_ColMod1->setText("RGB");
    ui->pb_ColMod2->setText("XYZ");
    ui->pb_ColMod3->setText("LAB");
    converter->setColMode(pb_colors[0]);
    updatePanel();
}
void MainWindow::on_action4_triggered()
{
    pb_colors[0] = RGB;
    pb_colors[1] = HSV;
    pb_colors[2] = LAB;
    ui->pb_ColMod1->setText("RGB");
    ui->pb_ColMod2->setText("HSV");
    ui->pb_ColMod3->setText("LAB");
    converter->setColMode(pb_colors[0]);
    updatePanel();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    converter->updateColors(ui->horizontalSlider->value(),ui->horizontalSlider_2->value(),ui->horizontalSlider_3->value());
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    converter->updateColors(ui->horizontalSlider->value(),ui->horizontalSlider_2->value(),ui->horizontalSlider_3->value());
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    converter->updateColors(ui->horizontalSlider->value(),ui->horizontalSlider_2->value(),ui->horizontalSlider_3->value());
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    converter->updateColors(ui->horizontalSlider->value(),ui->horizontalSlider_2->value(),ui->horizontalSlider_3->value(),ui->horizontalSlider_4->value());
}

void MainWindow::on_action6_triggered()
{
    pb_colors[0] = CMYK;
    pb_colors[1] = RGB;
    pb_colors[2] = HSL;
    ui->pb_ColMod1->setText("CMYK");
    ui->pb_ColMod2->setText("RGB");
    ui->pb_ColMod3->setText("HSL");
    converter->setColMode(pb_colors[0]);
    updatePanel();
}
