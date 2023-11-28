#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    double dailyGoal();
    void setTotalCalories(double totalCalories);
    double getTotalCalories();
    void setDailyGoal(double dailyGoal);


signals:

private:
    double m_dailyGoal=20;
    double m_totalCalories;


};

#endif // USER_H
