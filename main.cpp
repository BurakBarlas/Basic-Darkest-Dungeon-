#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Unit {
protected:
    int maxHp;
    int dodge;
    int prot;
    int speed;
    int accMod;
    int baseCrit;
    int minDmg;
    int maxDmg;
    int stunResist;

};
class Hero: public Unit{
    int deathBlowResist;
};
class Crusader: public Hero {
    void attack(Unit attackedUnit);
};

class Monster: public Unit {

};
class Bone_Soldier: public Monster{

};
class Bone_Defender:public Monster{

};




class StunSkill{

};
class Skill{
public:
    int position;
    int target;

};
class attackSkill: public Skill{
protected:
    int dmgMod;
    int baseAcc;
    int critMod;
    string stunEffect;
    int stunBase;
};
class Smite: public attackSkill{

};
class Stunning_Blow: public attackSkill, public StunSkill{

};
class UtilitySkill: public Skill{
    int position;
    string Target;
    // string effect gelecek +20 Prot for 3 round
};
class Divine_Grace: public UtilitySkill{

};
class MoveSkill: public Skill{

};



class attack: public attackSkill,public Unit{
protected:
    int randomNumber = rand() % 100;
    int hitChange = baseAcc + accMod - dodge;
public:
    void attackFunc(){
        if(hitChange >= randomNumber){ // saldirir ve crit hesaplamasi yapilir
            int criticalChance = baseCrit + critMod;
            randomNumber = rand() % 100;
            if(criticalChance >= randomNumber){ // crit vurur
                double critHit = maxDmg*1.5;
            }
            else{
                int dmg = rand() % maxDmg + minDmg;
                double rawDmg = dmg*(100 + dmgMod)/100.0;
                double actualDmg = rawDmg - rawDmg*(prot/100.0);
            } // normal vurur
        }
        else{} // missing
    }
};


void turnOrder(){

}


int main() {

    return 0;
}
