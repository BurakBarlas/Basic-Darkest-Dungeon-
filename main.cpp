#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <memory>
#include <algorithm>

using namespace std;
#include "Unit.h"

class Hero : public Unit {
protected:
    int deathBlowResist;
public:
    Hero() {}

    void attack() {

    }
    void dying() {
        if (hp == 0) {
            int randomNumber = rand() % 101;
            if (deathBlowResist >= randomNumber) {
                cout << "Hero " << name << " didn't die this time." << endl;
            }
            else {
                alive = false;
                cout << "Hero " << name << " died." << endl;
                //hero olur karakter dummy olarak atanir.
            }
        }
    }
};
class Crusader : public Hero {
public:
    Crusader(string na, int pst) {
        name = na;
        type = "Crusader";
        position = pst;
        maxHp = 33;
        hp = 33;
        dodge = 5;
        prot = 0;
        speed = 1;
        temporalSpeed = 1;
        accMod = 0;
        baseCrit = 3;
        minDmg = 6;
        maxDmg = 12;
        deathBlowResist = 67;
        stunResist = 40;
    }

};

class Vestal : public Hero {
public:
    Vestal(string na, int pst) :Hero() {
        name = na;
        type = "Vestal";
        position = pst;
        maxHp = 24;
        hp = 24;
        dodge = 0;
        prot = 0;
        speed = 4;
        temporalSpeed = 4;
        accMod = 0;
        baseCrit = 1;
        minDmg = 4;
        maxDmg = 8;
        deathBlowResist = 77;
        stunResist = 30;
    }
};

class Monster : public Unit {
protected:
    Monster() {}
    void dying() {
        alive = false;
        cout << "Monster " << name << " died." << endl;
    }
};
class Bone_Soldier : public Monster {
public:
    Bone_Soldier(string na, int pst) :Monster() {
        name = na;
        type = "Bone Soldier";
        position = pst;
        maxHp = 10;
        hp = 10;
        dodge = 10;
        prot = 15;
        speed = 2;
        temporalSpeed = 2;
        accMod = 0;
        baseCrit = 0;
        minDmg = 3;
        maxDmg = 8;
        stunResist = 25;
    }

};

class Bone_Defender :public Monster {
public:
    Bone_Defender(string na, int pst) :Monster() {
        name = na;
        type = "Bone Defender";
        position = pst;
        maxHp = 22;
        hp = 22;
        dodge = 8;
        prot = 45;
        speed = 1;
        temporalSpeed = 1;
        accMod = 0;
        baseCrit = 0;
        minDmg = 2;
        maxDmg = 4;
        stunResist = 45;
    }
};

class StunSkill {
protected:
    StunSkill() {}

};
class Skill {
protected:
    int position;
    int target;
public:

};
class MoveSkill : public Skill {
public:
    MoveSkill() {}

    static void  Move_Skill_Forward1(const shared_ptr<Unit>& Forward1) {
        Forward1->setPosition((Forward1->getPosition()) - 1);
        cout << Forward1->getName() << " moves 1 step forward!" << endl;
    }
    static void Move_Skill_Backward1(const shared_ptr<Unit>& Backward1) {
        Backward1->setPosition((Backward1->getPosition()) + 1);
        cout << Backward1->getName() << " moves 1 step backward!" << endl;
    }

};
bool comparatorHero(const shared_ptr<Hero>& lhs, const shared_ptr<Hero>& rhs) {
    return lhs->getPosition() < rhs->getPosition();
}

bool comparatorMonster(const shared_ptr<Monster>& lhs, const shared_ptr<Monster>& rhs) {
    return lhs->getPosition() < rhs->getPosition();
}
class AttackSkill : public Skill {
protected:
    int dmgMod;
    int baseAcc;
    double critMod;
    int stunEffect;
    int stunBase;

public:

    AttackSkill() {}

    void attackFunc(shared_ptr<Unit> attacker, shared_ptr<Unit> defender) {
        int randomNumber = rand() % 101;
        int hitChange = baseAcc + attacker->getAccMod() - defender->getDodge();
        if (hitChange >= randomNumber) { // saldirir ve crit hesaplamasi yapilir
            double criticalChance = attacker->getBaseCrit() + critMod;
            randomNumber = rand() % 101;

            if (criticalChance >= randomNumber) { // crit vurur
                double critHit = attacker->getMaxDmg() * 1.5;
                cout << attacker->getName() << ", CRIT damage : " << critHit << endl;
                defender->getDamage(critHit);

                int stunChange = 20 + stunBase - defender->getStunResist();
                randomNumber = rand() % 101;

                if (randomNumber <= stunChange && stunEffect == 1) {
                    defender->setStun(true);
                    cout << defender->getName() << " stunned." << endl;
                }
                else {
                    // stun yemez
                }
            }
            else {
                double dmg = rand() % (attacker->getMaxDmg() - attacker->getMinDmg()) + attacker->getMinDmg();
                double rawDmg = dmg * (100 + dmgMod) / 100.0;
                double actualDmg = rawDmg - rawDmg * (defender->getProt() / 100.0);
                cout << attacker->getName() << ", NORMAL damage : " << actualDmg << endl;
                defender->getDamage(actualDmg);

                int stunChange = stunBase - defender->getStunResist();
                randomNumber = rand() % 101;

                if (randomNumber <= stunChange && stunEffect == 1) {
                    defender->setStun(true);
                    cout << defender->getName() << " stunned." << endl;
                }
                else {
                    // stun yemez
                }

            } // normal vurur
        }
        else {
            cout << attacker->getName() << " missed the Hit!" << endl; // missing
        }
        cout << defender->getName() << "(Hp : " << defender->getHp() << ")" << endl;
        // return defender->getHp();
    }
};

class Smite : public AttackSkill {
public:
    Smite() {
        dmgMod = 0;
        baseAcc = 85;
        critMod = 0;
        stunEffect = 0;
    }
    void attack(shared_ptr<Unit> attacker, vector<shared_ptr<Monster>> &defender) {
        int target;
        cout << "Smite Selected!" << endl;
        cout << "Select a target to attack!" << endl;
        cout << "1-" << defender[0]->getName() << "(Hp : " << defender[0]->getHp() << ")" << endl;
        cout << "2-" << defender[1]->getName() << "(Hp : " << defender[1]->getHp() << ")" << endl;
        cout << "Number of Target : ";
        cin >> target;
        cout << endl;
        if (target != 1 && target != 2) {
            cout
                    << "Number of Target selected 1 automatically because your selection is not an option! "
                    << endl;
            target = 1;

        }
        if (defender[target - 1]->isAlive() == false) {
            cout << "Selected target is dead !" << endl;
            for (int t = 0; t < 2; t++) {
                if (defender[t]->isAlive() == true) {
                    target = t + 1;
                    cout << defender[t]->getName() << " is selected as a target." << endl;

                    break;
                }
            }
        }
        if (defender[0]->isAlive() == true || defender[1]->isAlive() == true) {
            cout << "Using Smite on " << defender[target - 1]->getName() << "(Hp : "
                 << defender[target - 1]->getHp() << ")" << endl;

            attackFunc(attacker, defender[target - 1]);
        }
        else {
            cout << "There is no living target you can attack , end of your turn !" << endl;
        }
    }

};
class Stunning_Blow : public AttackSkill, public StunSkill {
public:
    Stunning_Blow() {
        dmgMod = -50;
        baseAcc = 90;
        critMod = 0;
        stunBase = 100;
        stunEffect = 1;
    }
    void attack(shared_ptr<Unit> attacker, vector<shared_ptr<Monster>> &defender) {
        int target;
        cout << "Stunning Blow Selected!" << endl;
        cout << "Select a target to attack!" << endl;
        cout << "1-" << defender[0]->getName() << "(Hp : " << defender[0]->getHp() << ")" << endl;
        cout << "2-" << defender[1]->getName() << "(Hp : " << defender[1]->getHp() << ")" << endl;
        cout << "Number of Target : ";
        cin >> target;
        cout << endl;
        if (target != 1 && target != 2) {
            cout
                    << "Number of Target selected 1 automatically because your selection is not an option! "
                    << endl;
            target = 1;

        }
        if (defender[target - 1]->isAlive() == false) {
            cout << "Selected target is dead !" << endl;
            for (int t = 0; t < 2; t++) {
                if (defender[t]->isAlive() == true) {
                    target = t + 1;
                    cout << defender[t]->getName() << " is selected as a target." << endl;

                    break;
                }
            }
        }
        if (defender[0]->isAlive() == true || defender[1]->isAlive() == true) {
            cout << "Using Stunning Blow on " << defender[target - 1]->getName() << "(Hp : "
                 << defender[target - 1]->getHp() << ")" << endl;
            attackFunc(attacker, defender[target - 1]);
        }
        else {
            cout << "There is no living target you can attack , end of your turn !" << endl;
        }
    }
};
class Holy_Lance : public AttackSkill, public MoveSkill {
public:
    Holy_Lance() {
        dmgMod = 0;
        baseAcc = 85;
        critMod = 6.5;
        stunEffect = 0;
    }
    void attack(shared_ptr<Unit> attacker, vector<shared_ptr<Monster>> &defender, vector<shared_ptr<Hero>> &allies) {
        int target;
        cout << "Holy Lance selected!" << endl;
        cout << "Select a target to attack!" << endl;
        cout << "2-" << defender[1]->getName() << "(Hp : " << defender[1]->getHp() << ")" << endl;
        cout << "3-" << defender[2]->getName() << "(Hp : " << defender[2]->getHp() << ")" << endl;
        cout << "4-" << defender[3]->getName() << "(Hp : " << defender[3]->getHp() << ")" << endl;
        cout << "Number of Target : ";
        cin >> target;
        cout << endl;
        if (target != 2 && target != 3 && target != 4) {
            cout
                    << "Number of Target selected 2 automatically because your selection is not an option! "
                    << endl;
            target = 2;

        }
        if (defender[target - 1]->isAlive() == false) {
            cout << "Selected target is dead !" << endl;
            for (int t = 1; t < 4; t++) {
                if (defender[t]->isAlive() == true) {
                    target = t + 1;
                    cout << defender[t]->getName() << " is selected as a target." << endl;
                    break;
                }
            }
        }
        if (defender[2]->isAlive() == true || defender[1]->isAlive() == true || defender[3]->isAlive() == true) {
            cout << "Using Holy Lance to attack to " << defender[target - 1]->getName()
                 << "(Hp : " << defender[target - 1]->getHp() << ")" << endl;
            attackFunc(attacker, defender[target - 1]);
            cout << defender[target - 1]->getName() << "(Hp : " << defender[target - 1]->getHp() << ")" << endl;

            for (int j = 0; j <= 3; j++) {
                if (attacker->getPosition() == allies[j]->getPosition()) {
                    MoveSkill::Move_Skill_Forward1(allies[j]);
                    MoveSkill::Move_Skill_Backward1(allies[j - 1]);
                }
            }
            sort(allies.begin(), allies.end(), &comparatorHero);
        }
        else {
            cout << "There is no living target you can attack , end of your turn !" << endl;
        }
    }
};
class Mace_Bash : public AttackSkill {
public:
    Mace_Bash() {
        dmgMod = 0;
        baseAcc = 85;
        critMod = 0;
        stunEffect = 0;
    }
    void attack(shared_ptr<Unit> attacker, vector<shared_ptr<Monster>> &defenders) {
        int target;
        cout << "Mace Bash Selected!" << endl;
        cout << "Select a target to attack!" << endl;
        cout << "1-" << defenders[0]->getName() << "(Hp : " << defenders[0]->getHp() << ")" << endl;
        cout << "2-" << defenders[1]->getName() << "(Hp : " << defenders[1]->getHp() << ")" << endl;
        cout << "Number of Target : ";
        cin >> target;
        cout << endl;
        if (target != 1 && target != 2) {
            cout << "Number of Target selected 1 automatically because your selection is not an option! " << endl;
            target = 1;
        }
        if (defenders[target - 1]->isAlive() == false) {
            cout << "Selected target is dead !" << endl;
            for (int t = 0; t < 2; t++) {
                if (defenders[t]->isAlive() == true) {
                    target = t + 1;
                    cout << defenders[t]->getName() << " is selected as a target." << endl;
                    break;
                }
            }
        }
        if (defenders[0]->isAlive() == true || defenders[1]->isAlive() == true) {
            cout << "Using Mace Bash to attack to " << defenders[target - 1]->getName() << "(Hp : "
                 << defenders[target - 1]->getHp() << ")" << endl;
            attackFunc(attacker, defenders[target - 1]);
        }
        else {
            cout << "There is no living target you can attack , end of your turn !" << endl;
        }
    }
};
class Dazzling_Light : public AttackSkill, public StunSkill {
public:
    Dazzling_Light() {
        dmgMod = -75;
        baseAcc = 90;
        critMod = 5;
        stunBase = 100;
        stunEffect = 1;
    }
    void attack(shared_ptr<Unit> attacker, vector<shared_ptr<Monster>> &defenders) {
        int target;
        cout << "Dazzling Light Selected!" << endl;
        cout << "Select a target to attack!" << endl;
        cout << "1-" << defenders[0]->getName() << "(Hp : " << defenders[0]->getHp() << ")" << endl;
        cout << "2-" << defenders[1]->getName() << "(Hp : " << defenders[1]->getHp() << ")" << endl;
        cout << "3-" << defenders[2]->getName() << "(Hp : " << defenders[2]->getHp() << ")" << endl;
        cout << "Number of Target : ";
        cin >> target;
        cout << endl;
        if (target != 1 && target != 2 && target != 3) {
            cout << "Number of Target selected 1 automatically because your selection is not an option! "<< endl;
            target = 1;

        }
        if (defenders[target - 1]->isAlive() == false) {
            cout << "Selected target is dead !" << endl;
            for (int t = 0; t < 3; t++) {
                if (defenders[t]->isAlive() == true) {
                    target = t + 1;
                    cout << defenders[t]->getName() << " is selected as a target." << endl;
                    break;
                }
            }
        }
        if (defenders[0]->isAlive() == true || defenders[1]->isAlive() == true || defenders[2]->isAlive() == true) {
            cout << "Using Dazzling Light to attack to " << defenders[target - 1]->getName() << "(Hp : "
                 << defenders[target - 1]->getHp() << ")" << endl;
            attackFunc(attacker, defenders[target - 1]);
        }
        else {
            cout << "There is no living target you can attack , end of your turn !" << endl;
        }
    }
};
class Graveyard_Slash : public AttackSkill {
public:
    Graveyard_Slash() {
        dmgMod = 0;
        baseAcc = 85;
        critMod = 6;
        stunEffect = 0;
    }
    void attack(shared_ptr<Unit> attacker, vector<shared_ptr<Hero>> &defenders) {
        int target = rand() % 3 + 1;

        cout << attacker->getName() << " is selected Graveyard Slash to attack to " <<defenders[4 - target]->getName() << endl;

        if (defenders[target - 1]->isAlive() == false) {
            for (int t = 0; t < 2; t++) {
                if (defenders[t]->isAlive() == true) {
                    target = t + 1;
                    cout << defenders[t]->getName() << " is selected as a target." << endl;
                    break;
                }
            }
        }
        if (defenders[0]->isAlive() == true || defenders[1]->isAlive() == true || defenders[2]->isAlive() == true) {
            cout << "Using Graveyard Slash to attack to " << defenders[4 - target]->getName() << "(Hp : "
                 << defenders[4 - target]->getHp() << ")" << endl;
            attackFunc(attacker, defenders[4 - target]);
        }
        else {
            cout << "There is no target to attack. " << endl;
        }
    }
};
class Graveyard_Stumble : public AttackSkill, public MoveSkill {
public:
    Graveyard_Stumble() {
        dmgMod = -50;
        baseAcc = 45;
        critMod = 0;
        stunEffect = 0;
    }
    void attack(shared_ptr<Unit> attacker, vector<shared_ptr<Hero>> &defenders) {
        int target = rand() % 2 + 1;

        cout << attacker->getName() << " is selected Graveyard Stumble to attack to " <<defenders[4 - target]->getName() << endl;

        if (defenders[target - 1]->isAlive() == false) {
            for (int t = 0; t < 1; t++) {
                if (defenders[t]->isAlive() == true) {
                    target = t + 1;
                    cout << defenders[t]->getName() << " is selected as a target." << endl;
                    break;
                }
            }
        }
        if (defenders[0]->isAlive() == true || defenders[1]->isAlive() == true) {
            cout << "Using Graveyard Stumble to attack to " << defenders[4 - target]->getName() << "(Hp : "
                 << defenders[4 - target]->getHp() << ")" << endl;
            attackFunc(attacker, defenders[4 - target]);
        }
        else {
            cout << "There is no target to attack. " << endl;
        }
    }
};
class Axeblade : public AttackSkill {
public:
    Axeblade() {
        dmgMod = 0;
        baseAcc = 72;
        critMod = 6;
        stunEffect = 0;
    }
    void attack(shared_ptr<Unit> attacker, vector<shared_ptr<Hero>> &defenders) {
        //int numOfSkill = rand() % 3 + 1;
        int target = rand() % 2 + 1;

        cout << attacker->getName() << " is selected AxeBlade to attack to " <<defenders[4 - target]->getName() << endl;

        if (defenders[target - 1]->isAlive() == false) {
            //cout << "Selected target is dead !" << endl;
            for (int t = 0; t < 1; t++) {
                if (defenders[t]->isAlive() == true) {
                    target = t + 1;
                    cout << defenders[t]->getName() << " is selected as a target." << endl;
                    break;
                }
            }
        }
        if (defenders[0]->isAlive() == true || defenders[1]->isAlive() == true) {
            cout << "Using AxeBlade to attack to " << defenders[4 - target]->getName() << "(Hp : "
                 << defenders[4 - target]->getHp() << ")" << endl;
            attackFunc(attacker, defenders[4 - target]);
        }
        else {
            cout << "There is no target to attack. " << endl;
        }
    }
};
class Dead_Weight : public AttackSkill, public StunSkill {
public:
    Dead_Weight() {
        dmgMod = -25;
        baseAcc = 82;
        critMod = 6;
        stunBase = 100;
        stunEffect = 1;
    }
    void attack(shared_ptr<Unit> attacker, vector<shared_ptr<Hero>> &defenders) {
        int target = rand() % 2 + 1;

        cout << attacker->getName() << " is selected Dead Weight to attack to " <<defenders[4 - target]->getName() << endl;

        if (defenders[target - 1]->isAlive() == false) {
            for (int t = 0; t < 1; t++) {
                if (defenders[t]->isAlive() == true) {
                    target = t + 1;
                    cout << defenders[t]->getName() << " is selected as a target." << endl;
                    break;
                }
            }
        }
        if (defenders[0]->isAlive() == true || defenders[1]->isAlive() == true) {
            cout << "Using Dead Weight to attack to " << defenders[4 - target]->getName() << "(Hp : "
                 << defenders[4 - target]->getHp() << ")" << endl;
            attackFunc(attacker, defenders[4 - target]);
        }
        else {
            cout << "There is no target to attack. " << endl;
        }
    }
};
class UtilitySkill : public Skill {
protected:
    int minHp = 0;
    int maxHp = 0;
    int prot = 0;

public:
    void utilityFunc(shared_ptr<Unit> healer, shared_ptr<Unit> target) {
        if (target->isAlive() == true) {
            if (maxHp) {
                int randomNumber = rand() % (maxHp - minHp) + minHp;
                cout << randomNumber;
                target->increaseHp(randomNumber);
            }
            if (prot) {
                target->setProt(healer->getProt() + prot);
                cout << "Using Bulwark of Faith on " << target->getName() << ", +20 protection for 3 round." << endl;
                target->setProtRound(3);
            }
            else {
            }
        }
    }

    // string effect gelecek +20 Prot for 3 round
};

class Bulwark_Of_Faith : public UtilitySkill {
public:
    Bulwark_Of_Faith() {
        prot = 20;
        bool active = false;
    }
    void apply(shared_ptr<Unit> healer, shared_ptr<Unit> target) {
        cout << "Bulwark of Faith Selected!" << endl;
        utilityFunc(healer, target);
        target->setProtRound(3);
    }
};
class Divine_Grace : public UtilitySkill {
public:
    Divine_Grace() {
        minHp = 4;
        maxHp = 5;
    }
    void apply(shared_ptr<Unit> attacker, vector<shared_ptr<Hero>> &targets) {
        int target;
        cout << "Divine Grace Selected!" << endl;
        cout << "Select a Ally to heal!" << endl;
        cout << "1-" << targets[0]->getName() << "(Hp : " << targets[0]->getHp() << ")" << endl;
        cout << "2-" << targets[1]->getName() << "(Hp : " << targets[1]->getHp() << ")" << endl;
        cout << "3-" << targets[2]->getName() << "(Hp : " << targets[2]->getHp() << ")" << endl;
        cout << "4-" << targets[3]->getName() << "(Hp : " << targets[3]->getHp() << ")" << endl;
        cout << "Number of Ally : ";
        cin >> target;
        cout << endl;
        if (target != 1 && target != 2 && target != 3 && target != 4) {
            cout << "Number of Ally selected 1 automatically because your selection is not an option! "
                 << endl;
            target = 1;

        }
        if (targets[target - 1]->isAlive() == false) {
            cout << "Selected ally is dead !" << endl;
            for (int t = 0; t < 3; t++) {
                if (targets[t]->isAlive() == true) {
                    target = t + 1;
                    cout << targets[t]->getName() << " is selected as a ally to heal." << endl;

                    break;
                }
            }
        }
        if (targets[target - 1]->isAlive() == true) {
            cout << targets[target - 1]->getName() << " is heald by ";
            utilityFunc(attacker, targets[target - 1]);
            cout << endl;
            cout << targets[target - 1]->getName() << "(Hp : " << targets[target - 1]->getHp() << ")" << endl;
        }
    }
};
class Divine_Comfort : public UtilitySkill {
public:
    Divine_Comfort() {
        minHp = 1;
        maxHp = 3;
    }
    void apply(shared_ptr<Unit> Healer, vector<shared_ptr<Hero>> &targets) {
        int randomNumber = rand() % (3) + 1;
        cout << "Divine Comfort Selected!" << endl;
        cout << "All units healed by " << randomNumber << endl;

        for (int j = 3; j >= 0; j--) {
            if (targets[j]->isAlive() == true) {
                targets[j]->increaseHp(randomNumber);
                cout << targets[j]->getName() << "(Hp : " << targets[j]->getHp() << ")";
                if (j != 0) {
                    cout << " ,";
                }
            }
        }
        cout << endl;
    }
};
class Knitting_Bones : public UtilitySkill {
public:
    Knitting_Bones() {
        minHp = 2;
        maxHp = 3;
    }
    void apply(shared_ptr<Unit> healer, vector<shared_ptr<Monster>> &targets) {
        int target = rand() % 4 + 1;

        cout << healer->getName() << " is selected Knitting Bones to heal to " << targets[target - 1]->getName() << endl;

        cout << targets[target - 1]->getName() << " is healed by ";
        utilityFunc(healer, targets[target - 1]);
        cout << endl;
        cout << targets[target - 1]->getName() << "(Hp : " << targets[target - 1]->getHp()<< ")" << endl;

        int randomNumber = rand() % 2 + 2;


        for (int j = 3; j >= 0; j--) {
            if (targets[j]->isAlive() == true) {
                targets[j]->increaseHp(randomNumber);
                cout << targets[j]->getName() << "(Hp : " << targets[j]->getHp() << ")";
                if (j != 0) {
                    cout << " ,";
                }
            }
        }
        cout << endl;
    }
};

int main() {
    srand(time(0));

    shared_ptr<Vestal> ptrFirstVestal = make_shared<Vestal>("Vestal #1", 3);
    shared_ptr<Vestal> ptrSecondVestal = make_shared<Vestal>("Vestal #2", 4);
    shared_ptr<Crusader> ptrFirstCrusader = make_shared<Crusader>("Crusader #1", 1);
    shared_ptr<Crusader> ptrSecondCrusader = make_shared<Crusader>("Crusader #2", 2);
    shared_ptr<Bone_Defender> ptrFirstBoneD = make_shared<Bone_Defender>("Bone Defender #1", 2);
    shared_ptr<Bone_Defender> ptrSecondBoneD = make_shared<Bone_Defender>("Bone Defender #2", 4);
    shared_ptr<Bone_Soldier> ptrFirstBoneS = make_shared<Bone_Soldier>("Bone Soldier #1", 1);
    shared_ptr<Bone_Soldier> ptrSecondBoneS = make_shared<Bone_Soldier>("Bone Soldier #2", 3);

    //Crusader Skills
    Smite Skill_Smite;//Attack
    Stunning_Blow Skill_Stunning_Blow;//Attack
    Holy_Lance Skill_Holy_Lance;//Attack + Move
    Bulwark_Of_Faith Skill_Bulwark_Of_Faith;//Utility
    //Vestal Skills
    Mace_Bash Skill_Mace_Bash;//Attack
    Dazzling_Light Skill_Dazzling_Light;//Attack
    Divine_Grace Skill_Divine_Grace;//Utility (Heal)
    Divine_Comfort Skill_Divine_Comfort;//Utility (Heal)
    //Bone Soldier Skills
    Graveyard_Slash Skill_Graveyard_Slash;//Attack
    Graveyard_Stumble Skill_Graveyard_Stumble;//Attack + Move
    //Bone Defender Skills
    Axeblade Skill_Axeblade;//Attack
    Dead_Weight Skill_Dead_Weight;//Attack
    Knitting_Bones Skill_Knitting_Bones;//Utility (Heal)
    //Move Skills
    MoveSkill Move_Forward1;
    MoveSkill Move_Backward1;

    //Unit attackOrderArray[8];
    shared_ptr<Unit> attackOrderArray[8];

    vector< shared_ptr<Hero> >heroes;
    vector<shared_ptr<Monster>> monsters;

    vector<shared_ptr<Hero>>::iterator heroPtr;
    heroPtr = heroes.begin();

    vector<shared_ptr<Monster>>::iterator monsterPtr;
    monsterPtr = monsters.begin();

    monsters.push_back(ptrFirstBoneS);
    monsters.push_back(ptrFirstBoneD);
    monsters.push_back(ptrSecondBoneS);
    monsters.push_back(ptrSecondBoneD);

    heroes.push_back(ptrFirstCrusader);
    heroes.push_back(ptrSecondCrusader);
    heroes.push_back(ptrFirstVestal);
    heroes.push_back(ptrSecondVestal);

    sort(heroes.begin(), heroes.end(), &comparatorHero);

    attackOrderArray[0] = ptrSecondVestal;
    attackOrderArray[1] = ptrFirstVestal;
    attackOrderArray[2] = ptrSecondCrusader;
    attackOrderArray[3] = ptrFirstCrusader;
    attackOrderArray[4] = ptrFirstBoneS;
    attackOrderArray[5] = ptrFirstBoneD;
    attackOrderArray[6] = ptrSecondBoneS;
    attackOrderArray[7] = ptrSecondBoneD;

    int numberOfRound = 1;
    int numberOfSkill;
    bool gameover = false;

    do {
        cout << "                                       _______________" << endl;
        cout << "______________________________________| R O U N D   " << numberOfRound << " |_______________________________________" << endl;
        cout << endl;

        int randSpeed;
        shared_ptr<Unit>temp;
        // Increase speeds with random number
        for (int i = 0; i < 8; i++) {
            randSpeed = rand() % 8 + 1;
            attackOrderArray[i]->increaseSpeed(randSpeed);
        }

        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (attackOrderArray[j]->getTemporalSpeed() >
                    attackOrderArray[j + 1]->getTemporalSpeed()) {

                    temp = attackOrderArray[j];
                    attackOrderArray[j] = attackOrderArray[j + 1];
                    attackOrderArray[j + 1] = temp;
                }
            }
        }
        for (int l = 0; l < 8; ++l) {
            attackOrderArray[l]->setTemporalSpeed(attackOrderArray[l]->getSpeed());
        }

        for (int k = 0; k < 7; ++k) {
            if (attackOrderArray[k]->getType() == "Crusader" && attackOrderArray[k]->getProtRound() != 0) {
                attackOrderArray[k]->setProtRound(attackOrderArray[k]->getProtRound() - 1);
            }
            else if (attackOrderArray[k]->getType() == "Crusader") {
                attackOrderArray[k]->setProt(0);
            }
        }

        for (int i = 7; i >= 0; i--) {

            int actRandomChance;
            actRandomChance = rand() % 100 + 1;
            // Check game end conditions
            bool allHeroesDied = true;
            bool allMonstersDied = true;
            for (int h = 0; h < heroes.size(); h++) {
                if(heroes[h]->isAlive()) {
                    allHeroesDied = false;
                }
            }
            for (int m = 0; m < monsters.size(); m++) {
                if(monsters[m]->isAlive()) {
                    allMonstersDied = false;
                }
            }
            if(allHeroesDied || allMonstersDied) {
                gameover = true;
                break;
            }

            if (attackOrderArray[i]->isAlive() == true && attackOrderArray[i]->isStun() == false) {

                if (attackOrderArray[i]->getType() == "Vestal" || attackOrderArray[i]->getType() == "Crusader") {
                    cout << "_______________________|Current Positions and Health Amounts of Heroes|_______________________" << endl; cout << endl;
                    cout << "    (4)             (3)              (2)                (1)" << endl;
                    for (int k = 3; k >= 0; k--) {
                        if (k != 0) {
                            cout << heroes[k]->getName() << "(Hp:" << heroes[k]->getHp() << "),";
                        }
                        else {
                            cout << heroes[k]->getName() << "(Hp:" << heroes[k]->getHp() << ")";
                        }
                    }
                    cout << endl;
                    cout << "______________________________________________________________________________________________" << endl; cout << endl;
                }
                else {
                    cout << "______________________|Current Positions and Health Amounts of Monsters|______________________" << endl; cout << endl;
                    cout << "    (1)                    (2)                     (3)                    (4)" << endl;
                    for (int k = 0; k <= 3; k++) {
                        if (k != 3) {
                            cout << monsters[k]->getName() << "(Hp:" << monsters[k]->getHp() << "),";
                        }
                        else {
                            cout << monsters[k]->getName() << "(Hp:" << monsters[k]->getHp() << ")";
                        }
                    }
                    cout << endl;
                    cout << "______________________________________________________________________________________________" << endl; cout << endl;
                }
                cout << attackOrderArray[i]->getName() << " 's turn! " << endl;
                cout << "Select a skill!" << endl;
                cout << endl;
                if (attackOrderArray[i]->getType() == "Vestal") {

                    if (attackOrderArray[i]->getPosition() == 1) {
                        cout << "1 : Mace Bash (Attack)" << endl;
                        cout << "6 : Move Backward 1 (Move)" << endl;
                        cout << "Number of Skill : ";
                        cin >> numberOfSkill;
                        cout << endl;
                        if (numberOfSkill != 1 && numberOfSkill != 6) {
                            if (actRandomChance >= 1 && actRandomChance <= 10) {
                                cout << "Number of Skill selected 6 automatically because your selection is not an option! " << endl;
                                numberOfSkill = 6;
                            }
                            else {
                                cout << "Number of Skill selected 1 automatically because your selection is not an option!" << endl;
                                numberOfSkill = 1;
                            }
                        }
                    }
                    else if (attackOrderArray[i]->getPosition() == 2) {
                        cout << "1 : Mace Bash (Attack)" << endl;
                        cout << "2 : Dazzling Light (Attack)" << endl;
                        cout << "4 : Divine Comfort (Utility)" << endl;
                        cout << "5 : Move 1 step Forward (Move)" << endl;
                        cout << "6 : Move 1 step Backward (Move)" << endl;
                        cout << "Number of Skill : ";

                        cin >> numberOfSkill;
                        cout << endl;
                        if (numberOfSkill != 1 && numberOfSkill != 2 && numberOfSkill != 4 && numberOfSkill != 5 && numberOfSkill != 6) {
                            int randomMove = rand() % 2 + 1;
                            int randomAttack = rand() % 3 + 1;
                            if (actRandomChance >= 1 && actRandomChance <= 10) {
                                if (randomMove == 1) {
                                    cout << "Number of Skill selected 5 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 5;
                                }
                                else {
                                    cout << "Number of Skill selected 6 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 6;
                                }

                            }
                            else {
                                if (randomAttack == 1) {
                                    cout << "Number of Skill selected 1 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 1;
                                }
                                else if (randomAttack == 2) {
                                    cout << "Number of Skill selected 2 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 2;
                                }
                                else {
                                    cout << "Number of Skill selected 4 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 4;
                                }

                            }
                        }

                    }
                    else if (attackOrderArray[i]->getPosition() == 3) {
                        cout << "2 : Dazzling Light (Attack)" << endl;
                        cout << "3 : Divine Grace (Utility)" << endl;
                        cout << "4 : Divine Comfort (Utility)" << endl;
                        cout << "5 : Move 1 step Forward (Move)" << endl;
                        cout << "6 : Move 1 step Backward (Move)" << endl;

                        cout << "Number of Skill : ";
                        cin >> numberOfSkill;
                        cout << endl;
                        if (numberOfSkill != 3 && numberOfSkill != 2 && numberOfSkill != 4 && numberOfSkill != 5 && numberOfSkill != 6) {
                            int randomMove = rand() % 2 + 1;
                            int randomAttack = rand() % 3 + 1;
                            if (actRandomChance >= 1 && actRandomChance <= 10) {
                                if (randomMove == 1) {
                                    cout << "Number of Skill selected 5 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 5;
                                }
                                else {
                                    cout << "Number of Skill selected 6 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 6;
                                }

                            }
                            else {
                                if (randomAttack == 1) {
                                    cout << "Number of Skill selected 2 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 2;
                                }
                                else if (randomAttack == 2) {
                                    cout << "Number of Skill selected 3 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 3;
                                }
                                else {
                                    cout << "Number of Skill selected 4 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 4;
                                }

                            }
                        }
                    }
                    else if (attackOrderArray[i]->getPosition() == 4) {
                        cout << "2 : Dazzling Light (Attack)" << endl;
                        cout << "3 : Divine Grace (Utility)" << endl;
                        cout << "4 : Divine Comfort (Utility)" << endl;
                        cout << "5 : Move 1 step Forward (Move)" << endl;

                        cout << "Number of Skill : ";
                        cin >> numberOfSkill;
                        cout << endl;
                        if (numberOfSkill != 3 && numberOfSkill != 2 && numberOfSkill != 4 && numberOfSkill != 5) {
                            int randomMove = rand() % 2 + 1;
                            int randomAttack = rand() % 3 + 1;
                            if (actRandomChance >= 1 && actRandomChance <= 10) {

                                cout << "Number of Skill selected 5 automatically because your selection is not an option! " << endl;
                                numberOfSkill = 5;
                            }
                            else {
                                if (randomAttack == 1) {
                                    cout << "Number of Skill selected 2 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 2;
                                }
                                else if (randomAttack == 2) {
                                    cout << "Number of Skill selected 3 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 3;
                                }
                                else {
                                    cout << "Number of Skill selected 4 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 4;
                                }

                            }
                        }
                    }
                    //Skills
                    if (numberOfSkill == 1) {
                        Skill_Mace_Bash.attack(attackOrderArray[i], monsters);
                    }
                    else if (numberOfSkill == 2) {
                        Skill_Dazzling_Light.attack(attackOrderArray[i], monsters);
                    }
                    else if (numberOfSkill == 3) {
                        Skill_Divine_Grace.apply(attackOrderArray[i], heroes);
                    }
                    else if (numberOfSkill == 4) {
                        Skill_Divine_Comfort.apply(attackOrderArray[i], heroes);
                    }
                    else if (numberOfSkill == 5) {
                        for (int j = 0; j <= 3; j++) {
                            if (attackOrderArray[i]->getPosition() == heroes[j]->getPosition()) {
                                Move_Forward1.Move_Skill_Forward1(heroes[j]);
                                Move_Backward1.Move_Skill_Backward1(heroes[j - 1]);

                            }
                        }
                        sort(heroes.begin(), heroes.end(), &comparatorHero);
                        cout << endl;
                        for (int k = 3; k >= 0; k--) {
                            if (k != 0) {
                                cout << heroes[k]->getName() << ",";
                            }
                            else {
                                cout << heroes[k]->getName();
                            }
                        }
                        cout << endl;
                        cout << endl;
                    }
                    else if (numberOfSkill == 6) {
                        for (int j = 0; j <= 3; j++) {
                            if (attackOrderArray[i]->getPosition() == heroes[j]->getPosition()) {
                                Move_Backward1.Move_Skill_Backward1(heroes[j]);
                                Move_Forward1.Move_Skill_Forward1(heroes[j + 1]);

                            }
                        }
                        sort(heroes.begin(), heroes.end(), &comparatorHero);
                        cout << endl;
                        for (int k = 3; k >= 0; k--) {
                            if (k != 0) {
                                cout << heroes[k]->getName() << ",";
                            }
                            else {
                                cout << heroes[k]->getName();
                            }
                        }
                        cout << endl;
                        cout << endl;
                    }

                    for (int i = 0; i < 8; i++) {
                        attackOrderArray[i]->setPosition(attackOrderArray[i]->getPosition());
                    }

                    cout << "______________________________________________________________________________________________" << endl; cout << endl;
                }
                else if (attackOrderArray[i]->getType() == "Crusader") {

                    if (attackOrderArray[i]->getProtRound() == 0) {
                        attackOrderArray[i]->setProt(0);
                    }
                    if (attackOrderArray[i]->getPosition() == 1) {
                        cout << "1 : Smite (Attack)" << endl;
                        cout << "2 : Stunning Blow (Attack)" << endl;
                        cout << "3 : Bulwark of Faith (Utility)" << endl;
                        cout << "6 : Move 1 step Backward (Move)" << endl;

                        cout << "Number of Skill : ";
                        cin >> numberOfSkill;
                        if (numberOfSkill != 1 && numberOfSkill != 2 && numberOfSkill != 3 && numberOfSkill != 6) {
                            int randomMove = rand() % 2 + 1;
                            int randomAttack = rand() % 3 + 1;
                            if (actRandomChance >= 1 && actRandomChance <= 10) {
                                cout << "Number of Skill selected 6 automatically because your selection is not an option! " << endl;
                                numberOfSkill = 6;
                            }
                            else {
                                if (randomAttack == 1) {
                                    cout << "Number of Skill selected 1 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 1;
                                }
                                else if (randomAttack == 2) {
                                    cout << "Number of Skill selected 2 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 2;
                                }
                                else {
                                    cout << "Number of Skill selected 3 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 3;
                                }

                            }
                        }
                    }
                    else if (attackOrderArray[i]->getPosition() == 2) {
                        cout << "1 : Smite (Attack)" << endl;
                        cout << "2 : Stunning Blow (Attack)" << endl;
                        cout << "3 : Bulwark of Faith (Utility)" << endl;
                        cout << "5 : Move 1 step Forward (Move)" << endl;
                        cout << "6 : Move 1 step Backward (Move)" << endl;

                        cout << "Number of Skill : ";
                        cin >> numberOfSkill;
                        cout << endl;
                        if (numberOfSkill != 1 && numberOfSkill != 2 && numberOfSkill != 3 && numberOfSkill != 5 && numberOfSkill != 6) {
                            int randomMove = rand() % 2 + 1;
                            int randomAttack = rand() % 3 + 1;
                            if (actRandomChance >= 1 && actRandomChance <= 10) {
                                if (randomMove == 1) {
                                    cout << "Number of Skill selected 5 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 5;
                                }
                                else {
                                    cout << "Number of Skill selected 6 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 6;
                                }

                            }
                            else {
                                if (randomAttack == 1) {
                                    cout << "Number of Skill selected 1 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 1;
                                }
                                else if (randomAttack == 2) {
                                    cout << "Number of Skill selected 2 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 2;
                                }
                                else {
                                    cout << "Number of Skill selected 3 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 3;
                                }

                            }
                        }
                    }
                    else if (attackOrderArray[i]->getPosition() == 3) {
                        cout << "4 : Holy Lance (Attack)" << endl;
                        cout << "5 : Move 1 step Forward (Move)" << endl;
                        cout << "6 : Move 1 step Backward (Move)" << endl;

                        cout << "Number of Skill : ";
                        cin >> numberOfSkill;
                        cout << endl;
                        if (numberOfSkill != 4 && numberOfSkill != 5 && numberOfSkill != 6) {

                            if (actRandomChance >= 1 && actRandomChance <= 10) {
                                int randomMove = rand() % 2 + 1;
                                if (randomMove == 1) {
                                    cout << "Number of Skill selected 5 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 5;
                                }
                                else {
                                    cout << "Number of Skill selected 6 automatically because your selection is not an option! " << endl;
                                    numberOfSkill = 6;
                                }

                            }
                            else {
                                cout << "Number of Skill selected 4 automatically because your selection is not an option! " << endl;
                                numberOfSkill = 4;
                            }
                        }
                    }
                    else if (attackOrderArray[i]->getPosition() == 4) {
                        cout << "4 : Holy Lance (Attack)" << endl;
                        cout << "5 : Move 1 step Forward (Move)" << endl;

                        cout << "Number of Skill : ";
                        cin >> numberOfSkill;
                        cout << endl;
                        if (numberOfSkill != 4 && numberOfSkill != 5) {
                            if (actRandomChance >= 1 && actRandomChance <= 10) {
                                cout << "Number of Skill selected 5 automatically because your selection is not an option! " << endl;
                                numberOfSkill = 5;
                            }
                            else {
                                cout << "Number of Skill selected 4 automatically because your selection is not an option! " << endl;
                                numberOfSkill = 4;
                            }
                        }
                    }
                    //Skills
                    if (numberOfSkill == 1) {
                        Skill_Smite.attack(attackOrderArray[i], monsters);
                    }
                    else if (numberOfSkill == 2) {
                        Skill_Stunning_Blow.attack(attackOrderArray[i], monsters);
                    }
                    else if (numberOfSkill == 3) {
                        Skill_Bulwark_Of_Faith.apply(attackOrderArray[i], attackOrderArray[i]);
                    }
                    else if (numberOfSkill == 4) {
                        Skill_Holy_Lance.attack(attackOrderArray[i], monsters, heroes);
                    }
                    else if (numberOfSkill == 5) {
                        for (int j = 0; j <= 3; j++) {
                            if (attackOrderArray[i]->getPosition() == heroes[j]->getPosition()) {
                                Move_Forward1.Move_Skill_Forward1(heroes[j]);
                                Move_Backward1.Move_Skill_Backward1(heroes[j - 1]);

                            }
                        }
                        sort(heroes.begin(), heroes.end(), &comparatorHero);
                        cout << endl;
                        for (int k = 3; k >= 0; k--) {
                            if (k != 0) {
                                cout << heroes[k]->getName() << ",";
                            }
                            else {
                                cout << heroes[k]->getName();
                            }
                        }
                        cout << endl;
                        cout << endl;
                    }
                    else if (numberOfSkill == 6) {
                        for (int j = 0; j <= 3; j++) {
                            if (attackOrderArray[i]->getPosition() == heroes[j]->getPosition()) {
                                Move_Backward1.Move_Skill_Backward1(heroes[j]);
                                Move_Forward1.Move_Skill_Forward1(heroes[j + 1]);

                            }
                        }
                        sort(heroes.begin(), heroes.end(), &comparatorHero);
                        cout << endl;
                        for (int k = 3; k >= 0; k--) {
                            if (k != 0) {
                                cout << heroes[k]->getName() << ",";
                            }
                            else {
                                cout << heroes[k]->getName();
                            }
                        }
                        cout << endl;
                        cout << endl;
                    }

                    for (int i = 0; i < 8; i++) {
                        attackOrderArray[i]->setPosition(attackOrderArray[i]->getPosition());
                    }


                    cout << "______________________________________________________________________________________________" << endl; cout << endl;
                }
                else if (attackOrderArray[i]->getType() == "Bone Defender") {

                    if (attackOrderArray[i]->getPosition() == 1) {
                        int numOfSkill = rand() % 3 + 1;

                        if (numOfSkill == 1) {
                            Skill_Axeblade.attack(attackOrderArray[i], heroes);
                        }
                        else if (numOfSkill == 2) {
                            Skill_Dead_Weight.attack(attackOrderArray[i], heroes);
                        }
                        else if (numOfSkill == 3) {
                            //Move Back
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Backward1.Move_Skill_Backward1(monsters[j]);
                                    Move_Forward1.Move_Skill_Forward1(monsters[j + 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            cout << endl;
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;
                        }
                    }
                    else if (attackOrderArray[i]->getPosition() == 2) {
                        int numOfSkill = rand() % 4 + 1;

                        if (numOfSkill == 1) {
                            Skill_Axeblade.attack(attackOrderArray[i], heroes);
                        }
                        else if (numOfSkill == 2) {
                            Skill_Dead_Weight.attack(attackOrderArray[i], heroes);
                        }
                        else if (numOfSkill == 3) {
                            //Move Back
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Backward1.Move_Skill_Backward1(monsters[j]);
                                    Move_Forward1.Move_Skill_Forward1(monsters[j + 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            cout << endl;
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;
                        }
                        else if (numOfSkill == 4) {
                            //Move Forward
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Forward1.Move_Skill_Forward1(monsters[j]);
                                    Move_Backward1.Move_Skill_Backward1(monsters[j - 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            cout << endl;
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;
                        }
                    }
                    else if (attackOrderArray[i]->getPosition() == 3) {
                        int numOfSkill = rand() % 4 + 1;
                        if (numOfSkill == 1) {
                            Skill_Dead_Weight.attack(attackOrderArray[i], heroes);
                        }
                        else if (numOfSkill == 2) {
                            Skill_Knitting_Bones.apply(attackOrderArray[i], monsters);
                        }
                        else if (numOfSkill == 3) {
                            //Move Back
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Backward1.Move_Skill_Backward1(monsters[j]);
                                    Move_Forward1.Move_Skill_Forward1(monsters[j + 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                        }
                        else if (numOfSkill == 4) {
                            //Move Forward
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Forward1.Move_Skill_Forward1(monsters[j]);
                                    Move_Backward1.Move_Skill_Backward1(monsters[j - 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            cout << endl;
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;
                        }
                    }
                    else if (attackOrderArray[i]->getPosition() == 4) {
                        int numOfSkill = rand() % 2 + 1;

                        if (numOfSkill == 1) {
                            Skill_Knitting_Bones.apply(attackOrderArray[i], monsters);
                        }
                        else if (numOfSkill == 2) {
                            //Move Forward
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Forward1.Move_Skill_Forward1(monsters[j]);
                                    Move_Backward1.Move_Skill_Backward1(monsters[j - 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            cout << endl;
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;
                        }
                    }
                    //Garanti önemli
                    for (int i = 0; i < 8; i++) {
                        attackOrderArray[i]->setPosition(attackOrderArray[i]->getPosition());
                    }
                    cout << "______________________________________________________________________________________________" << endl; cout << endl;
                }
                else if (attackOrderArray[i]->getType() == "Bone Soldier") {

                    if (attackOrderArray[i]->getPosition() == 1) {
                        int numOfSkill = rand() % 2 + 1;
                        int target = rand() % 2 + 1;
                        int target2 = rand() % 3 + 1;

                        if (numOfSkill == 1) {
                            Skill_Graveyard_Slash.attack(attackOrderArray[i], heroes);
                        }
                        else if (numOfSkill == 2) {
                            //Move Backward
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Backward1.Move_Skill_Backward1(monsters[j]);
                                    Move_Forward1.Move_Skill_Forward1(monsters[j + 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            cout << endl;
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;
                        }

                    }
                    else if (attackOrderArray[i]->getPosition() == 2 || attackOrderArray[i]->getPosition() == 3) {
                        int numOfSkill = rand() % 3 + 1;

                        if (numOfSkill == 1) {
                            Skill_Graveyard_Slash.attack(attackOrderArray[i], heroes);
                        }

                        else if (numOfSkill == 2) {
                            //Move Backward
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Backward1.Move_Skill_Backward1(monsters[j]);
                                    Move_Forward1.Move_Skill_Forward1(monsters[j + 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            cout << endl;
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;
                        }

                        else if (numOfSkill == 3) {
                            //Move Forward
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Forward1.Move_Skill_Forward1(monsters[j]);
                                    Move_Backward1.Move_Skill_Backward1(monsters[j - 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            cout << endl;
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;

                        }

                    }
                    else if (attackOrderArray[i]->getPosition() == 4) {
                        int numOfSkill = rand() % 2 + 1;

                        if (numOfSkill == 1) {
                            Skill_Graveyard_Stumble.attack(attackOrderArray[i], heroes);
                            cout << "And " << attackOrderArray[i]->getName() << " moves 1 step forward!" << endl;
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Forward1.Move_Skill_Forward1(monsters[j]);
                                    Move_Backward1.Move_Skill_Backward1(monsters[j - 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;
                        }
                        else if (numOfSkill == 2) {
                            //Move Forward
                            for (int j = 0; j <= 3; j++) {
                                if (attackOrderArray[i]->getPosition() == monsters[j]->getPosition()) {
                                    Move_Forward1.Move_Skill_Forward1(monsters[j]);
                                    Move_Backward1.Move_Skill_Backward1(monsters[j - 1]);
                                }
                            }
                            sort(monsters.begin(), monsters.end(), &comparatorMonster);
                            cout << endl;
                            for (int k = 0; k <= 3; k++) {
                                if (k != 3) {
                                    cout << monsters[k]->getName() << ",";
                                }
                                else {
                                    cout << monsters[k]->getName();
                                }
                            }
                            cout << endl;
                            cout << endl;
                        }

                    }
                    for (int i = 0; i < 8; i++) {
                        attackOrderArray[i]->setPosition(attackOrderArray[i]->getPosition());
                    }

                    cout << "______________________________________________________________________________________________" << endl; cout << endl;
                }

            } else if (attackOrderArray[i]->isAlive() == true && attackOrderArray[i]->isStun() == true) {
                cout << attackOrderArray[i]->getName() << " stunned for this round." << endl;
                attackOrderArray[i]->setStun(false);
            } else {
                cout << "Character:" << attackOrderArray[i]->getName() << " is dead." << endl;
            }
        }
        numberOfRound++;

    } while (gameover == false);

    cout << "End of Game! " << endl;

    if (heroes[0]->getHp() + heroes[1]->getHp() + heroes[2]->getHp() + heroes[3]->getHp() == 0) {
        cout << "Monsters Won the Battle!" << endl;
    }
    else if (monsters[0]->getHp() + monsters[1]->getHp() + monsters[2]->getHp() + monsters[3]->getHp() == 0) {
        cout << "Heroes Won the Battle!" << endl;
    }

    return 0;
}