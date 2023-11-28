#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "meal.h"
#include "user.h"
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    Meal meal;
    User user;


    QStandardItemModel* model = new QStandardItemModel();

signals:
    void calorieChanged();


private slots:
    void updateUI();

};
#endif // WIDGET_H
