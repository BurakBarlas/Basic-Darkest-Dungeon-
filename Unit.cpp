//
// Created by Barlas on 5/13/2020.
//

#include "Unit.h"
Unit::Unit() {}

std::string Unit::getName() {
        return name;
    }
std::string Unit::getType() {
        return type;
    }
    int Unit::getHp() {
        return hp;
    }
    int Unit::getDodge() {
        return dodge;
    }
    int Unit::getProt() {
        return prot;
    }
    int Unit::getSpeed() {
        return speed;
    }
    int Unit::getTemporalSpeed() {
        return temporalSpeed;
    }
    int Unit::getAccMod() {
        return accMod;
    }
    int Unit::getBaseCrit() {
        return baseCrit;
    }
    int Unit::getMinDmg() {
        return minDmg;
    }
    int Unit::getMaxDmg() {
        return maxDmg;
    }
    int Unit::getStunResist() {
        return stunResist;
    }
    int Unit::getPosition() {
        return position;
    }

    void Unit::increaseSpeed(int speedIncrement) {
        temporalSpeed = temporalSpeed + speedIncrement;
    }

    void Unit::increaseHp(int hpIncrement) {
        hp = hp + hpIncrement;
        if (hp > maxHp) {
            hp = maxHp;
        }
    }

    void Unit::setProt(int prot) {
        this->prot = prot;
    }

    void Unit::setTemporalSpeed(int temporalSpeed) {
        this->temporalSpeed = temporalSpeed;
    }

    void Unit::setPosition(int pst) {
        position = pst;
    }

    bool Unit::isAlive() {
        return alive;
    }

    bool Unit::isStun() {
        return stun;
    }

    void Unit::setStun(int stun) {
        this->stun = stun;
    }

    int Unit::getProtRound() {
        return protRound;
    }

    void Unit::setProtRound(int protRound) {
        this->protRound = protRound;
    }

    void Unit::getDamage(int damage) {
        if(damage == 0){
            damage = 1;
        }
        hp = hp - damage;
        if (hp <= 0) {
            hp = 0;
            dying();
        }
    }
