#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Set column and row count
    model->setColumnCount(2);

    // Set headers for columns
    model->setHeaderData(0, Qt::Horizontal, "Meal Name");
    model->setHeaderData(1, Qt::Horizontal, "Meal Calorie");

    // Set the model for the table view
    ui->tableView->setModel(model);



    connect(ui->addMeal, &QPushButton::clicked,this,&Widget::updateUI);
    connect(this,&Widget::calorieChanged,this,[=](){
        if(user.getTotalCalories()>=user.dailyGoal()){

            ui->progressBar->setValue(100);

            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("You've the Daily Goal.");
            msgBox.exec();


        }
        ui->progressBar->setValue(static_cast<int>(user.getTotalCalories() / user.dailyGoal() * 100));
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateUI()
{
    int newRow = model->rowCount();
    qDebug()<<newRow;
    model->setItem(newRow, 0, new QStandardItem(ui->mealNameInput->text()));
    model->setItem(newRow, 1, new QStandardItem(QString::number(ui->mealCalorieSpin->value())));
    user.setTotalCalories(user.getTotalCalories()+ui->mealCalorieSpin->value());
    ui->totalCalorieLabel->setText(QString::number(user.getTotalCalories()));

    emit calorieChanged();
}

