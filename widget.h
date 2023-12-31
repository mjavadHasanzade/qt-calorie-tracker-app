#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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
    User user;


    QStandardItemModel* model = new QStandardItemModel();

signals:
    void calorieChanged();


private slots:
    void updateTable();
    void updateLabelProgress();
    void deleteItem();

};
#endif // WIDGET_H
