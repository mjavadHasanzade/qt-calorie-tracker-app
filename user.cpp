#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{

}

double User::dailyGoal()
{
    return m_dailyGoal;
}

void User::setTotalCalories(double totalCalories){
    m_totalCalories=totalCalories;
}

double User::getTotalCalories(){
    return m_totalCalories;
}
