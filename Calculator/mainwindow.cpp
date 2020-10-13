#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
double firstOp;
bool typing = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui -> pushButton_0, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_1, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_2, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_3, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_4, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_5, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_6, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_7, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_8, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_9, SIGNAL( released() ), this, SLOT( digit_pressed() ) );
    connect( ui -> pushButton_PlusMinus, SIGNAL( released() ), this, SLOT( unary_operation_pressed() ) );
    connect( ui -> pushButton_Percent, SIGNAL( released() ), this, SLOT( unary_operation_pressed() ) );
    connect( ui -> pushButton_Add, SIGNAL( released() ), this, SLOT( binary_operation_pressed() ) );
    connect( ui -> pushButton_Multiply, SIGNAL( released() ), this, SLOT( binary_operation_pressed() ) );
    connect( ui -> pushButton_Divide, SIGNAL( released() ), this, SLOT( binary_operation_pressed() ) );
    connect( ui -> pushButton_MInus, SIGNAL( released() ), this, SLOT( binary_operation_pressed() ) );
    connect( ui -> pushButton_Sin, SIGNAL( released() ), this, SLOT( unary_operation_pressed() ) );
    connect( ui -> pushButton_Cos, SIGNAL( released() ), this, SLOT( unary_operation_pressed() ) );
    connect( ui -> pushButton_Power, SIGNAL( released() ), this, SLOT( binary_operation_pressed() ) );

    ui -> pushButton_Add -> setCheckable( true );
    ui -> pushButton_MInus -> setCheckable( true );
    ui -> pushButton_Multiply -> setCheckable( true );
    ui -> pushButton_Divide -> setCheckable( true );
    ui -> pushButton_Power -> setCheckable( true );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow:: digit_pressed()
{
    QPushButton* button = ( QPushButton* ) sender();
    double labelNumber;
    QString newLabel;
    if( ( ui -> pushButton_Add -> isChecked() ||  ui -> pushButton_MInus -> isChecked() ||  ui -> pushButton_Multiply -> isChecked() ||  ui -> pushButton_Divide -> isChecked() || ui -> pushButton_Power -> isChecked() ) && !typing ){
        labelNumber = button -> text().toDouble();
        typing = true;
        newLabel = QString::number( labelNumber, 'g', 15 );
    }
    else{
        if( ui -> label -> text().contains( "." ) && button -> text() == "0" ){
            newLabel = ui -> label -> text() + button -> text();
        }
        else{
            labelNumber = ( ui -> label -> text() + button -> text() ).toDouble();
            newLabel = QString::number( labelNumber, 'g' , 15 );
        }
    }
    ui->label->setText( newLabel );
}

void MainWindow::on_pushButton_decimal_released()
{
    ui->label->setText( ui->label->text() + "." );
}

void MainWindow:: unary_operation_pressed()
{
    QPushButton* button = ( QPushButton* ) sender();
    double labelNumber;
    QString newLabel;
    if( button -> text() == "+/-" ){
        labelNumber = ui -> label -> text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number( labelNumber, 'g', 15 );
        ui -> label -> setText( newLabel );
    }
    else if( button -> text() == "%" ){
        labelNumber = ui -> label -> text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number( labelNumber, 'g', 15 );
        ui -> label -> setText( newLabel );
    }
    else if( button -> text() == "sin" ){
        labelNumber = ui -> label -> text().toDouble();
        labelNumber = qSin( qRadiansToDegrees( labelNumber ) );
        newLabel = QString::number( labelNumber, 'g', 15 );
        ui -> label -> setText( newLabel );
    }
    else if( button -> text() == "cos" ){
        labelNumber = ui -> label -> text().toDouble();
        labelNumber = qCos( qRadiansToDegrees( labelNumber ) );
        newLabel = QString::number( labelNumber, 'g', 15 );
        ui -> label -> setText( newLabel );
    }

}

void MainWindow::on_pushButton_Clear_released()
{
    ui -> pushButton_Add -> setChecked(false);
    ui -> pushButton_MInus -> setChecked(false);
    ui -> pushButton_Multiply -> setChecked(false);
    ui -> pushButton_Divide -> setChecked(false);

    typing = false;
    ui -> label -> setText("0");
}

void MainWindow::on_pushButton_Equals_released()
{
    double labelNumber, secondOp;
    QString newLabel;
    secondOp = ui -> label -> text().toDouble();

    if( ui -> pushButton_Add -> isChecked() ){
        labelNumber = firstOp + secondOp;
        newLabel = QString :: number( labelNumber, 'g', 15 );
        ui -> label -> setText( newLabel );
        ui -> pushButton_Add -> setChecked(false);
    }
    else if( ui -> pushButton_MInus -> isChecked() ){
        labelNumber = firstOp - secondOp;
        newLabel = QString :: number( labelNumber, 'g', 15 );
        ui -> label -> setText( newLabel );
        ui -> pushButton_MInus -> setChecked(false);
    }
    else if( ui -> pushButton_Multiply -> isChecked() ){
        labelNumber = firstOp * secondOp;
        newLabel = QString :: number( labelNumber, 'g', 15 );
        ui -> label -> setText( newLabel );
        ui -> pushButton_Multiply -> setChecked(false);
    }
    else if( ui -> pushButton_Divide -> isChecked() ){
        labelNumber = firstOp / secondOp;
        newLabel = QString :: number( labelNumber, 'g', 15 );
        ui -> label -> setText( newLabel );
        ui -> pushButton_Divide -> setChecked(false);
    }
    else if( ui -> pushButton_Power -> isChecked() ){
        labelNumber = qPow( firstOp, secondOp );
        newLabel = QString :: number( labelNumber, 'g', 15 );
        ui -> label -> setText( newLabel );
        ui -> pushButton_Power -> setChecked(false);
    }
    typing = false;
}

void MainWindow ::binary_operation_pressed()
{
    QPushButton* button = ( QPushButton* ) sender();
    firstOp = ui -> label -> text().toDouble();
    button -> setChecked( true );
}
