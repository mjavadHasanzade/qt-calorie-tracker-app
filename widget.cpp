#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ================Setup Table=============================== //

    // Set column and row count
    model->setColumnCount(2);

    // Set headers for columns
    model->setHeaderData(0, Qt::Horizontal, "Meal Name");
    model->setHeaderData(1, Qt::Horizontal, "Meal Calorie");

    // Set the model for the table view
    ui->tableView->setModel(model);



    // ================Setup Input Dialog=============================== //

    bool ok;
    double dailyGoal = QInputDialog::getDouble(this, "Daily Goal", "Enter Your Daily Goal", 100, 0, 1000, 2, &ok);

    if (ok) {
        user.setDailyGoal(dailyGoal);
    } else {
        qDebug() << "User canceled or closed the input dialog.";
        user.setDailyGoal(100);
    }

    ui->dailyGoalLabel->setText(QString::number(user.dailyGoal()));



    connect(ui->addMeal, &QPushButton::clicked,this,&Widget::updateTable);
    connect(this,&Widget::calorieChanged,this,&Widget::updateLabelProgress);
    connect(ui->deleteMeal,&QPushButton::clicked,this,&Widget::deleteItem);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateTable()
{
    if(ui->mealNameInput->text().length()==0){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Name can't be Empty");
        msgBox.exec();
    }
    else if(ui->mealCalorieSpin->value()<=0){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Calorie can't be 0 or less");
        msgBox.exec();
    }
    else{

        int newRow = model->rowCount();
        model->setItem(newRow, 0, new QStandardItem(ui->mealNameInput->text()));
        model->setItem(newRow, 1, new QStandardItem(QString::number(ui->mealCalorieSpin->value())));
        user.setTotalCalories(user.getTotalCalories()+ui->mealCalorieSpin->value());

        emit calorieChanged();
    }
}

void Widget::updateLabelProgress()
{
    ui->totalCalorieLabel->setText(QString::number(user.getTotalCalories()));

    if(user.getTotalCalories()>=user.dailyGoal()){

        ui->progressBar->setValue(100);
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You've Reached the Daily Goal.");
        msgBox.exec();
    }

    ui->progressBar->setValue(static_cast<int>(user.getTotalCalories() / user.dailyGoal() * 100));
    ui->mealNameInput->setText("");
    ui->mealCalorieSpin->setValue(0);

}

void Widget::deleteItem()
{
    // Get the selected row(s)
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    // Check if exactly one row is selected
    if (selectedRows.size() == 1) {
        int row = selectedRows.at(0).row();
        QVariant rowCalorie=model->data(model->index(row, 1));

        model->removeRow(row);

        user.setTotalCalories(user.getTotalCalories() - rowCalorie.toDouble());
        emit calorieChanged();

    }else{
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Please Select one row.");
        msgBox.exec();
    }

}

