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
class AttackSkill: public Skill{
    int dmgMod;
    int baseAcc;
    int critMod;
    string stunEffect;
    int stunBase;
};
class Smite: public AttackSkill{

};
class Stunning_Blow: public AttackSkill, public StunSkill{

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



class attack: public Skill,public Unit{

};


void turnOrder(){

}


int main() {

    return 0;
}
