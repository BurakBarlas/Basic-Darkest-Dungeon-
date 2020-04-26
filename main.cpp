#include <iostream>

using namespace std;

class Unit {

};
class Hero: public Unit{

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

};
class AttackSkill: public Skill{

};
class Smite: public AttackSkill{

};
class Stunning_Blow: public AttackSkill, public StunSkill{

};
class UtilitySkill: public Skill{

};
class Divine_Grace: public UtilitySkill{

};
class MoveSkill: public Skill{

};







int main() {

    return 0;
}
