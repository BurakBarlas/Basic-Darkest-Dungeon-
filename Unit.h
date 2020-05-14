//
// Created by Barlas on 5/13/2020.
//
#include <iostream>

#ifndef UNTITLED54_UNIT_H
#define UNTITLED54_UNIT_H

class Unit {
protected:
    std::string name;
    std::string type;
    int position;
    int maxHp = 0;
    int hp;
    int dodge;
    int prot = 0;
    int speed;
    int temporalSpeed;
    int accMod;
    int baseCrit;
    int minDmg;
    int maxDmg;
    int stunResist;
    bool alive = true;
    bool stun = false;
    int protRound = 0;
public:
    Unit();

    void virtual dying() = 0;

    std::string getName();
    std::string getType();
    int getHp();
    int getDodge();
    int getProt();
    int getSpeed();
    int getTemporalSpeed();
    int getAccMod();
    int getBaseCrit();
    int getMinDmg();
    int getMaxDmg();
    int getStunResist();
    int getPosition();

    void increaseSpeed(int speedIncrement);

    void increaseHp(int hpIncrement);

    void setProt(int prot);

    void setTemporalSpeed(int temporalSpeed);

    void setPosition(int pst);

    bool isAlive();

    bool isStun();

    void setStun(int stun);

    int getProtRound();

    void setProtRound(int protRound);

    void getDamage(int damage);

};


#endif //UNTITLED54_UNIT_H
