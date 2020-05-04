#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <memory>

using namespace std;

class Unit {
protected:
    string name;
    string type = "UNK";
    int position;
    int maxHp;
    int hp;
    int dodge;
    int prot = 0;
    int speed;
    int accMod;
    int baseCrit;
    int minDmg;
    int maxDmg;
    int stunResist;
    bool alive = true;
    bool stun = false;
    int protRound = 0;
public:
    Unit(){}

    void virtual dying() {}

    string getName() {
        return name;
    }

    string getType() {
        return type;
    }

    int getHp(){
        return hp;
    }
    int getDodge() {
        return dodge;
    }
    int getProt(){
        return prot;
    }
    int getSpeed() {
        return speed;
    }
    int getAccMod() {
        return accMod;
    }
    int getBaseCrit(){
        return baseCrit;
    }
    int getMinDmg() {
        return minDmg;
    }
    int getMaxDmg() {
        return maxDmg;
    }
    int getStunResist() {
        return stunResist;
    }

    int getPosition() {
        return position;
    }

    void increaseSpeed(int speedIncrement) {
        speed = speed + speedIncrement;
    }

    void increaseHp(int hpIncrement) {
        hp = hp + hpIncrement;
        if(hp > maxHp){
            hp = maxHp;
        }
    }

    void setName(string nam){
        name = nam;
    }

    void setProt(int prot) {
        this->prot = prot;
    }
    void setSpeed(int sped){
        speed = sped;
    }

    void setPosition(int pst){
        position = pst;
    }

    void setHp(int hpp){
        hp = hpp;
    }


    bool isAlive() {
        return alive;
    }

    bool isStun() {
        return stun;
    }

    void setStun(int stun) {
        this->stun = stun;
    }

    int getProtRound() {
        return protRound;
    }

    void setProtRound(int protRound) {
        this->protRound = protRound;
    }

    void getDamage(int damage) {
        hp = hp - damage;
        if(hp <= 0 ) {
            hp = 0;
            dying();
        }
    }

};
class Hero: public Unit{
protected:
    int deathBlowResist;
public:
    Hero(){}

    void printInfo(){

        cout<<maxHp;

    }
    void attack() {

    }
    void dying(){
        if(hp == 0){
            int randomNumber = rand() % 101;
            if(deathBlowResist >= randomNumber){
                cout << "Hero " << name << " didn't die this time." << endl;
            }
            else{
                alive = false;
                cout << "Hero " << name << " died." << endl;
                //hero olur karakter dummy olarak atanir.
            }
        }
    }
};
class Crusader: public Hero {
public:
    int protRound = 0;
    Crusader(string na,int pst){
        name = na;
        type = "crusader";
        position = pst;
        maxHp = 33;
        hp = 33;
        dodge = 5;
        prot = 0;
        speed = 1;
        accMod = 0;
        baseCrit = 3;
        minDmg = 6;
        //maxDmg = 12;
        maxDmg = 1000; //deneme
        deathBlowResist=67;
        stunResist = 40;
    }
    void useSkill(int choice){
        if(choice == 1){
            //Smite
        }
        else if(choice == 2){
            //stunning blow
        }
        else if(choice == 3){
            //hooly lance
        }
        else if(choice == 4){
            //bulwark of faith
        }
        else{

        }
    }
    int getProtRound() {
        return getProtRound();
    }

    void setProtRound(int protRound) {
        this->protRound = protRound;
    }

};
class Vestal : public Hero{
public:
    Vestal(string na,int pst):Hero(){
        name = na;
        position = pst;
        maxHp = 24;
        hp = 24;
        dodge = 0;
        prot = 0;
        speed = 4;
        accMod = 0;
        baseCrit = 1;
        minDmg = 4;
        //maxDmg = 8;
        maxDmg = 1000; // deneme
        deathBlowResist = 77;
        stunResist = 30;
    }
    void useSkill(int choice){
        if(choice == 1){
            //Mace Bash
        }
        else if(choice == 2){
            //Dazzling Light
        }
        else if(choice == 3){
            //Divine Grace
        }
        else if(choice == 4){
            //Divine comfort
        }
        else{

        }
    }


};

class Monster: public Unit {
protected:
    Monster(){}
    void dying(){
        alive = false;
        cout << "Monster " << name << " died." << endl;
    }
};
class Bone_Soldier: public Monster{
public:
    Bone_Soldier(string na,int pst):Monster(){
        name = na;
        position = pst;
        maxHp = 10;
        hp = 10;
        dodge = 10;
        prot = 15;
        speed = 2;
        accMod = 0;
        baseCrit = 0;
        minDmg = 3;
        maxDmg = 8;
        stunResist = 25;
    }
    void useSkill(int choice){
        if(choice == 1){
            //graveyard slash
        }
        else if(choice == 2){
            //graveyard stumble
        }
        else{

        }
    }

};
class Bone_Defender:public Monster{
public:
    Bone_Defender(string na,int pst):Monster(){
        name = na;
        position = pst;
        maxHp = 22;
        hp = 22;
        dodge = 8;
        prot = 45;
        speed = 1;
        accMod = 0;
        baseCrit = 0;
        minDmg = 2;
        maxDmg = 4;
        stunResist = 45;
    }
    void useSkill(int choice){
        if(choice == 1){
            //Axeblade
        }
        else if(choice == 2){
            //Dead weight
        }
        else if(choice == 3){
            //Knitting Bones
        }
        else{

        }
    }
};




class StunSkill{
protected:
    StunSkill(){}

};
class Skill {
protected:
    int position;
    int target;
public:

};
class MoveSkill: public Skill{

};

class AttackSkill: public Skill{
protected:
    int dmgMod;
    int baseAcc;
    double critMod;
    int stunEffect;
    int stunBase;
public:

    AttackSkill(){}

    void attackFunc(shared_ptr<Unit> attacker,shared_ptr<Unit> defender) {
        int randomNumber = rand() % 101;
        int hitChange = baseAcc + attacker->getAccMod() - defender->getDodge();

        if (hitChange >= randomNumber) { // saldirir ve crit hesaplamasi yapilir
            double criticalChance = attacker->getBaseCrit() + critMod;
            randomNumber = rand() % 101;

            if (criticalChance >= randomNumber) { // crit vurur
                double critHit = attacker->getMaxDmg() * 1.5;
                cout<<attacker->getName()<<", CRIT damage : "<<critHit<<endl;
                defender->getDamage(critHit);

                int stunChange = 20 + stunBase - defender->getStunResist();
                randomNumber = rand() % 101;

                if(randomNumber <= stunChange) {
                    defender->setStun(true);
                }
                else{
                    // stun yemez
                }


            }
            else {
                int dmg = rand() % (attacker->getMaxDmg() - attacker->getMinDmg()) + attacker->getMinDmg();
                double rawDmg = dmg * (100 + dmgMod) / 100.0;
                double actualDmg = rawDmg - rawDmg * (defender->getProt() / 100.0);
                cout << attacker->getName() << ", NORMAL damage : " << actualDmg<<endl;
                defender->getDamage(actualDmg);

                int stunChange = stunBase - defender->getStunResist();
                randomNumber = rand() % 101;

                if(randomNumber <= stunChange) {
                    defender->setStun(true);
                }
                else{
                    // stun yemez
                }

            } // normal vurur
        } else {
            cout <<attacker->getName()<<" missed the Hit!"<<endl; // missing
        }

        // return defender->getHp();
    }
    int getDmgMod(){
        return dmgMod;
    }
    int getBaseAcc(){
        return baseAcc;
    }
    int getCritMod() {
        return critMod;
    }

};
class Smite: public AttackSkill{
public:
    Smite(){
        dmgMod = 0;
        baseAcc = 85;
        critMod = 0;
        stunEffect = 0;
    }

};
class Stunning_Blow: public AttackSkill, public StunSkill{
public:
    Stunning_Blow(){
        dmgMod = -50;
        baseAcc = 90;
        critMod = 0;
        stunBase = 100;
        stunEffect = 1;
    }
};
class Holy_Lance: public AttackSkill, public MoveSkill{
public:
    Holy_Lance(){
        dmgMod = 0;
        baseAcc = 85;
        critMod = 6.5;
        stunEffect = 0;

    }
};
class Mace_Bash: public AttackSkill{
public:
    Mace_Bash(){
        dmgMod = 0;
        baseAcc = 85;
        critMod = 0;
        stunEffect = 0;
    }
};
class Dazzling_Light: public AttackSkill, public StunSkill{
public:
    Dazzling_Light(){
        dmgMod = -75;
        baseAcc = 90;
        critMod = 5;
        stunBase = 100;
        stunEffect = 1;
    }
};
class Graveyard_Slash: public AttackSkill{
public:
    Graveyard_Slash(){
        dmgMod = 0;
        baseAcc = 85;
        critMod = 6;
        stunEffect = 0;
    }
};
class Graveyard_Stumble: public AttackSkill, public MoveSkill{
public:
    Graveyard_Stumble(){
        dmgMod = -50;
        baseAcc = 45;
        critMod = 0;
        stunEffect = 0;
    }
};
class Axeblade: public AttackSkill{
public:
    Axeblade(){
        dmgMod = 0;
        baseAcc = 72;
        critMod = 6;
        stunEffect = 0;
    }
};
class Dead_Weight: public AttackSkill, public StunSkill{
public:
    Dead_Weight(){
        dmgMod = -25;
        baseAcc = 82;
        critMod = 6;
        stunBase = 100;
        stunEffect = 1;
    }
};
class UtilitySkill: public Skill{
protected:
    int minHp = 0;
    int maxHp = 0;
    int prot = 0;
    int protRound = 0;
public:
    void utilityFunc(shared_ptr<Unit> healer,shared_ptr<Unit> target) {
        if (target->isAlive() == true) {
            if (maxHp) {
                double randomNumber = rand() % (maxHp - minHp) + minHp;
                cout << randomNumber;
                target->increaseHp(randomNumber);
            }
            if (prot) {
                target->setProt(healer->getProt() + prot);
                cout<<"Using Bulwark of Faith on "<< target->getName() <<", +20 protection for 3 round."<<endl;
                protRound = 3;
            }
            else {
            }
        }
    }
    // string effect gelecek +20 Prot for 3 round
};

class Bulwark_Of_Faith: public UtilitySkill{
public:
    Bulwark_Of_Faith() {
        prot = 20;
        bool active = false;
    }

//        bool isActive(){
//            return active;
//        }


    //+20 Prot for 3 round

};
class Divine_Grace: public UtilitySkill{
public:
    Divine_Grace(){
        minHp = 4;
        maxHp = 5;
    }
};
class Divine_Comfort: public UtilitySkill{
public:
    Divine_Comfort(){
        minHp = 1;
        maxHp = 3;
    }
};
class Knitting_Bones: public UtilitySkill{
public:
    Knitting_Bones(){
        minHp = 2;
        maxHp = 3;
    }
};





int main() {
    srand (time(0));

    shared_ptr<Vestal> ptrFirstVestal = make_shared<Vestal>("Vestal #1",3);
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


    //Unit attackOrderArray[8];
    //shared_ptr<Unit[]> attackOrderArray = make_shared<Unit[]>(8);
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

    heroes.push_back(ptrFirstVestal);
    heroes.push_back(ptrSecondVestal);
    heroes.push_back(ptrFirstCrusader);
    heroes.push_back(ptrSecondCrusader);

    attackOrderArray[0] = ptrSecondVestal;
    attackOrderArray[1] = ptrFirstVestal;
    attackOrderArray[2] = ptrSecondCrusader;
    attackOrderArray[3] = ptrFirstCrusader;
    attackOrderArray[4] = ptrFirstBoneS;
    attackOrderArray[5] = ptrFirstBoneD;
    attackOrderArray[6] = ptrSecondBoneS;
    attackOrderArray[7] = ptrSecondBoneD;


    int randSpeed;
    shared_ptr<Unit>temp;
    // Increase speeds with random number
    for(int i=0;i<8;i++) {
        randSpeed = rand() % 8 + 1;
        attackOrderArray[i]->increaseSpeed(randSpeed);
        // cout << i << ": " << attackOrderArray[i]->getName() << " " <<attackOrderArray[i]->getSpeed() << " " << endl;
    }

    for(int i=0;i<7;i++) {
        for (int j = 0; j < 7; j++) {
            if (attackOrderArray[j]->getSpeed() >
                attackOrderArray[j + 1]->getSpeed()) {

                temp = attackOrderArray[j];
                attackOrderArray[j] = attackOrderArray[j+1];
                attackOrderArray[j+1] = temp;
            }
        }
    }
    // Test
//    for(int i=0;i<8;i++) {
//        //cout << i << ": " << attackOrderArray[i]->getName() << " " <<attackOrderArray[i]->getHp() << endl;
//        cout << attackOrderArray[i]->getSpeed() << " " ;
//    }

    int numberOfRound = 1;
    int numberOfSkill;
    bool gameover = false;

    do {
        cout<<"---R O U N D  "<<numberOfRound<<"---"<<endl;
        //
        cout<<endl;

        for (int k = 0; k < 7; ++k) {
            if(attackOrderArray[k]->getType() == "crusader" && attackOrderArray[k]->getProtRound() != 0) {
                attackOrderArray[k]->setProtRound(attackOrderArray[k]->getProtRound()-1);
            }
            else{
                attackOrderArray[k]->setProt(0);
            }
        }


        for(int i = 7;i>=0;i--){
            if(attackOrderArray[i]->isAlive() == true && attackOrderArray[i]->isStun() == false){

                cout<<attackOrderArray[i]->getName()<<"'s turn! "<<"Select a skill!"<<endl;
                /*for(int j = 0;j<8;j++){
                    cout<<attackOrderArray[j].getName()<<" ";
                    cout<<attackOrderArray[j].getSpeed()+randSpeeds[j]<<endl;

                }*//*Test için duruyor*/
                if(attackOrderArray[i]->getName() == "Vestal #1" || attackOrderArray[i]->getName() == "Vestal #2"){
                    if(attackOrderArray[i]->getPosition() == 1){
                        int target;
                        cout<<"1 : Mace Bash (Attack)"<<endl;
                        cout<<attackOrderArray[i]->getName()<<" at Position 1"<<endl;
                        cout<<"Mace Bash Selected automatically!"<<endl;
                        cout<<"Select a target to attack!"<<endl;
                        cout<<"1-"<<monsters[0]->getName()<<"("<<monsters[0]->getHp()<<")"<<endl;
                        cout<<"2-"<<monsters[1]->getName()<<"("<<monsters[1]->getHp()<<")"<<endl;
                        cout<<"Number of Target : ";
                        cin>>target;
                        cout<<"Using Mace Bash to attack to "<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                        Skill_Mace_Bash.attackFunc(attackOrderArray[i],monsters[target-1]);
                        cout<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;

                    }
                    else if(attackOrderArray[i]->getPosition() == 2){
                        cout<<"1 : Mace Bash (Attack)"<<endl;
                        cout<<"2 : Dazzling Light (Attack)"<<endl;
                        cout<<"4 : Divine Comfort (Utility)"<<endl;
                        cout<<"Number of Skill : ";
                        cin>>numberOfSkill;
                        if(numberOfSkill==3){
                            cout<<"Number of Skill selected 4 automatically because your selection is not an option! "<<endl;
                            numberOfSkill = 4;

                        }

                    }
                    else if(attackOrderArray[i]->getPosition() == 3 || attackOrderArray[i]->getPosition() == 4){
                        cout<<"2 : Dazzling Light (Attack)"<<endl;
                        cout<<"3 : Divine Grace (Utility)"<<endl;
                        cout<<"4 : Divine Comfort (Utility)"<<endl;
                        cout<<"Number of Skill : ";
                        cin>>numberOfSkill;
                        if(numberOfSkill==1){
                            cout<<"Number of Skill selected 2 automatically because your selection is not an option! "<<endl;
                            numberOfSkill = 2;

                        }

                    }

                    if(numberOfSkill == 1){
                        int target;
                        cout<<"Mace Bash Selected!"<<endl;
                        cout<<"Select a target to attack!"<<endl;
                        cout<<"1-"<<monsters[0]->getName()<<"(Hp : "<<monsters[0]->getHp()<<")"<<endl;
                        cout<<"2-"<<monsters[1]->getName()<<"(Hp : "<<monsters[1]->getHp()<<")"<<endl;
                        cout<<"Number of Target : ";
                        cin>>target;
                        if(target==3||target==4){
                            cout<<"Number of Target selected 1 automatically because your selection is not an option! "<<endl;
                            target = 1;

                        }
                        cout<<"Using Mace Bash to attack to "<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                        //monsters[target-1].setHp(Skill_Mace_Bash.attackFunc(&attackOrderArray[i],&monsters[target-1]));
                        Skill_Mace_Bash.attackFunc(attackOrderArray[i],monsters[target-1]);
                        cout<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                    }
                    else if(numberOfSkill == 2){
                        int target;
                        cout<<"Dazzling Light Selected!"<<endl;
                        cout<<"Select a target to attack!"<<endl;
                        cout<<"1-"<<monsters[0]->getName()<<"(Hp : "<<monsters[0]->getHp()<<")"<<endl;
                        cout<<"2-"<<monsters[1]->getName()<<"(Hp : "<<monsters[1]->getHp()<<")"<<endl;
                        cout<<"3-"<<monsters[2]->getName()<<"(Hp : "<<monsters[2]->getHp()<<")"<<endl;
                        cout<<"Number of Target : ";
                        cin>>target;
                        if(target==4){
                            cout<<"Number of Target selected 1 automatically because your selection is not an option! "<<endl;
                            target = 1;

                        }
                        cout<<"Using Dazzling Light to attack to "<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                        //monsters[target-1].setHp(Skill_Dazzling_Light.attackFunc(&attackOrderArray[i],&monsters[target-1]));
                        Skill_Dazzling_Light.attackFunc(attackOrderArray[i],monsters[target-1]);
                        cout<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                    }
                    else if(numberOfSkill == 3){
                        int target;
                        cout<<"Divine Grace Selected!"<<endl;
                        cout<<"Select a target to heal!"<<endl;
                        cout<<"1-"<<heroes[0]->getName()<<"(Hp : "<<heroes[0]->getHp()<<")"<<endl;
                        cout<<"2-"<<heroes[1]->getName()<<"(Hp : "<<heroes[1]->getHp()<<")"<<endl;
                        cout<<"3-"<<heroes[2]->getName()<<"(Hp : "<<heroes[2]->getHp()<<")"<<endl;
                        cout<<"4-"<<heroes[3]->getName()<<"(Hp : "<<heroes[3]->getHp()<<")"<<endl;
                        cout<<"Number of Target : ";
                        cin>>target;

                        cout << heroes[target-1]->getName() << "Earned Hp: " << endl;
                        Skill_Divine_Grace.utilityFunc(attackOrderArray[i],heroes[target-1]);
                        cout<< heroes[target-1]->getName() << " " <<heroes[target-1]->getHp() <<endl;

                    }
                    else if(numberOfSkill == 4){
                        //int healAmount = rand() % 3 + 1;
                        cout<<"Divine Comfort Selected!"<<endl;
                        cout<<"All units Healed " <<endl;
                    }
                    for (int j = 0; j < 7; ++j) {
                        Skill_Divine_Comfort.utilityFunc(attackOrderArray[i],attackOrderArray[j]);
                        cout << "All units healed. " << endl;
                    }
                    cout<<"----------------------------------------"<<endl;
                }

                else if(attackOrderArray[i]->getName() == "Crusader #1"||attackOrderArray[i]->getName() == "Crusader #2"){
                    if(attackOrderArray[i]->getProtRound() == 0) {
                        attackOrderArray[i]->setProt(0);
                    }
                    if(attackOrderArray[i]->getPosition() == 1 || attackOrderArray[i]->getPosition() == 2){
                        cout<<"1 : Smite (Attack)"<<endl;
                        cout<<"2 : Stunning Blow (Attack)"<<endl;
                        cout<<"3 : Bulwark of Faith (Utility)"<<endl;
                        cout<<"Number of Skill : ";
                        cin>>numberOfSkill;
                        if(numberOfSkill==4){
                            cout<<"Number of Skill selected 1 automatically because your selection is not an option! "<<endl;
                            numberOfSkill = 1;

                        }
                    }
                    else{
                        int target;
                        cout<<"4 : Holy Lance (Attack)"<<endl;
                        cout<<"Holy Lance selected automatically!"<<endl;
                        cout<<"Select a target to attack!"<<endl;
                        cout<<"2-"<<monsters[1]->getName()<<"(Hp : "<<monsters[1]->getHp()<<")"<<endl;
                        cout<<"3-"<<monsters[2]->getName()<<"(Hp : "<<monsters[2]->getHp()<<")"<<endl;
                        cout<<"4-"<<monsters[3]->getName()<<"(Hp : "<<monsters[3]->getHp()<<")"<<endl;
                        cout<<"Number of Target : ";
                        cin>>target;
                        if(target==1){
                            cout<<"Number of Target selected 2 automatically because your selection is not an option! "<<endl;
                            target = 2;

                        }
                        cout<<"Using Holy Lance to attack to "<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                        //monsters[target-1].setHp(Skill_Holy_Lance.attackFunc(&attackOrderArray[i], &monsters[target-1]));
                        Skill_Holy_Lance.attackFunc(attackOrderArray[i], monsters[target-1]);
                        cout<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                    }

                    if(numberOfSkill == 1){
                        int target;
                        cout<<"Smite Selected!"<<endl;
                        cout<<"Select a target to attack!"<<endl;
                        cout<<"1-"<<monsters[0]->getName()<<"(Hp : "<<monsters[0]->getHp()<<")"<<endl;
                        cout<<"2-"<<monsters[1]->getName()<<"(Hp : "<<monsters[1]->getHp()<<")"<<endl;
                        cout<<"Number of Target : ";
                        cin>>target;
                        if(target==3||target==4){
                            cout<<"Number of Target selected 1 automatically because your selection is not an option! "<<endl;
                            target = 1;

                        }
                        cout<<"Using Smite on "<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;

                        Skill_Smite.attackFunc(attackOrderArray[i], monsters[target-1]);
                        cout<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                    }
                    else if(numberOfSkill == 2){
                        int target;
                        cout<<"Stunning Blow Selected!"<<endl;
                        cout<<"Select a target to attack!"<<endl;
                        cout<<"1-"<<monsters[0]->getName()<<"(Hp : "<<monsters[0]->getHp()<<")"<<endl;
                        cout<<"2-"<<monsters[1]->getName()<<"(Hp : "<<monsters[1]->getHp()<<")"<<endl;
                        cout<<"Number of Target : ";
                        cin>>target;
                        if(target==3||target==4){
                            cout<<"Number of Target selected 1 automatically because your selection is not an option! "<<endl;
                            target = 1;

                        }
                        cout<<"Using Stunning Blow on "<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                        // monsters[target-1].setHp(Skill_Stunning_Blow.attackFunc(&attackOrderArray[i], &monsters[target-1]));
                        Skill_Stunning_Blow.attackFunc(attackOrderArray[i], monsters[target-1]);
                        cout<<monsters[target-1]->getName()<<"(Hp : "<<monsters[target-1]->getHp()<<")"<<endl;
                    }
                    else if(numberOfSkill == 3){
                        cout<<"Bulwark of Faith Selected!"<<endl;
                        Skill_Bulwark_Of_Faith.utilityFunc(attackOrderArray[i], attackOrderArray[i]);
                        attackOrderArray[i]->setProtRound(3);
                    }
                    cout<<"----------------------------------------"<<endl;
                }

                else if(attackOrderArray[i]->getName()=="Bone Defender #1"||attackOrderArray[i]->getName() == "Bone Defender #2"){

                    int numOfSkill = rand() % 3 + 1;
                    int target = rand() % 2 + 1;


                    if(numOfSkill==1){
                        cout<<attackOrderArray[i]->getName()<<" is selected AxeBlade to attack to "<<heroes[4-target]->getName()<<endl;

                        // heroes[4-target].setHp(Skill_Axeblade.attackFunc(&attackOrderArray[i],&heroes[4-target]));
                        Skill_Axeblade.attackFunc(attackOrderArray[i],heroes[4-target]);
                        cout<<heroes[4-target]->getName()<<"(Hp : "<<heroes[4-target]->getHp()<<")"<<endl;
                    }
                    else if(numOfSkill==2){
                        cout<<attackOrderArray[i]->getName()<<" is selected Dead Weight to attack to "<<heroes[4-target]->getName()<<endl;

                        // heroes[4-target].setHp(Skill_Dead_Weight.attackFunc(&attackOrderArray[i],&heroes[4-target]));
                        Skill_Dead_Weight.attackFunc(attackOrderArray[i],heroes[4-target]);
                        cout<<heroes[4-target]->getName()<<"(Hp : "<<heroes[4-target]->getHp()<<")"<<endl;
                    }
                    else if(numOfSkill==3){
                        cout<<attackOrderArray[i]->getName()<<" is selected Knitting Bones to heal to "<<monsters[target-1]->getName()<<endl;

                        cout << monsters[target-1]->getName() << "Earned Hp: " << endl;
                        Skill_Knitting_Bones.utilityFunc(attackOrderArray[i],monsters[target-1]);
                        cout<< monsters[target-1]->getName() << " " <<monsters[target-1]->getHp() <<endl;
                    }
                    cout<<"----------------------------------------"<<endl;

                }

                else if(attackOrderArray[i]->getName()=="Bone Soldier #1"||attackOrderArray[i]->getName() == "Bone Soldier #2"){

                    int numOfSkill = rand() % 2 + 1;
                    int target = rand() % 2 + 1;
                    int target2 = rand() % 3 + 1;

                    if(numOfSkill==1){
                        cout<<attackOrderArray[i]->getName()<<" is selected Graveyard Slash to attack to "<<heroes[4-target2]->getName()<<endl;

                        // heroes[4-target].setHp(Skill_Graveyard_Slash.attackFunc(&attackOrderArray[i],&heroes[4-target]));
                        Skill_Graveyard_Slash.attackFunc(attackOrderArray[i],heroes[4-target]);
                        cout<<heroes[4-target]->getName()<<"(Hp : "<<heroes[4-target]->getHp()<<")"<<endl;

                    }
                    else if(numOfSkill==2){
                        cout<<attackOrderArray[i]->getName()<<" is selected Graveyard Stumble to attack to "<<heroes[4-target]->getName()<<endl;

                        // heroes[4-target].setHp(Skill_Graveyard_Stumble.attackFunc(&attackOrderArray[i],&heroes[4-target]));
                        Skill_Graveyard_Stumble.attackFunc(attackOrderArray[i],heroes[4-target]);
                        cout<<heroes[4-target]->getName()<<"(Hp : "<<heroes[4-target]->getHp()<<")"<<endl;

                        cout<<"And "<<attackOrderArray[i]->getName()<<" moves 1 step forward!"<<endl;
                    }
                    cout<<"----------------------------------------"<<endl;
                }

            }

            else if(attackOrderArray[i]->isAlive() == true && attackOrderArray[i]->isStun() == true){
                cout << attackOrderArray[i]->getName() << " stunned for this round." << endl;
                attackOrderArray[i]->setStun(false);
            }
            else {
                cout << "Character:" << attackOrderArray[i]->getName() << " is dead." << endl;
            }
        }

        if(heroes[0]->getHp()+heroes[1]->getHp()+heroes[2]->getHp()+heroes[3]->getHp() == 0 ||
           monsters[0]->getHp()+monsters[1]->getHp()+monsters[2]->getHp()+monsters[3]->getHp() == 0){
            gameover = true;
        }

        numberOfRound++;

    } while (gameover == false);

    cout<<"!End of Game! "<<endl;

    return 0;
}