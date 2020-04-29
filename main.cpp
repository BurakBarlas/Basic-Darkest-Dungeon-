#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <stdio.h>

using namespace std;

class Unit {
protected:
    string name;
    int position;
    int maxHp;
    int hp;
    int dodge;
    int prot;
    int speed;
    int accMod;
    int baseCrit;
    int minDmg;
    int maxDmg;
    int stunResist;
    bool alive = true;
public:
    Unit(){}

    void virtual dying() {}
    string getName() {
        return name;
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

    int getPosition() {
        return position;
    }

    void setName(string nam){
    name = nam;
    }

    void setSpeed(int sped){
    speed = sped;
    }

    void setPosition(int pst){
    position = pst;
    }

    bool isAlive() {
        return alive;
    }

    void getDamage(int damage) {
        hp = hp - damage;
        if(hp <= 0){
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
                //bir sey olmaz hero yasamaya devam eder.
            }
            else{
                alive = false;
                //hero olur karakter dummy olarak atanir.
            }
        }
    }
};
class Crusader: public Hero {
public:
    Crusader(string na,int pst){
        name = na;
        position = pst;
        maxHp = 33;
        hp = 33;
        dodge = 5;
        prot = 0;
        speed = 1;
        accMod = 0;
        baseCrit = 3;
        minDmg = 6;
        maxDmg = 12;
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
    void virtual attack(){
        // attack classi buradan cagirlacak

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
        maxDmg = 8;
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
        // karakter dummy olarak atanir.

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
    string stunEffect;
    int stunBase;
public:

    AttackSkill(){}

    void attackFunc(Unit attacker, Unit defender) {
            int randomNumber = rand() % 101;
            int hitChange = baseAcc + attacker.getAccMod() - defender.getDodge();

            if (hitChange >= randomNumber) { // saldirir ve crit hesaplamasi yapilir
                double criticalChance = attacker.getBaseCrit() + critMod;
                randomNumber = rand() % 101;

                if (criticalChance >= randomNumber) { // crit vurur
                    double critHit = attacker.getMaxDmg() * 1.5;
                    defender.getDamage(critHit);
                }
                else {
                    int dmg = rand() % attacker.getMaxDmg() + attacker.getMinDmg();
                    double rawDmg = dmg * (100 + dmgMod) / 100.0;
                    double actualDmg = rawDmg - rawDmg * (defender.getProt() / 100.0);
                    defender.getDamage(actualDmg);
                } // normal vurur
            } else {
                cout << "missing"; // missing
            }
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
    }

};
class Stunning_Blow: public AttackSkill, public StunSkill{
public:
    Stunning_Blow(){
        dmgMod = -50;
        baseAcc = 90;
        critMod = 0;
        stunBase = 100;
    }
};
class Holy_Lance: public AttackSkill, public MoveSkill{
public:
    Holy_Lance(){
        dmgMod = 0;
        baseAcc = 85;
        critMod = 6.5;
    }
};
class Mace_Bash: public AttackSkill{
public:
    Mace_Bash(){
        dmgMod = 0;
        baseAcc = 85;
        critMod = 0;
    }
};
class Dazzling_Light: public AttackSkill, public StunSkill{
public:
    Dazzling_Light(){
        dmgMod = -75;
        baseAcc = 90;
        critMod = 5;
        stunBase = 100;
    }
};
class Graveyard_Slash: public AttackSkill{
public:
    Graveyard_Slash(){
        dmgMod = 0;
        baseAcc = 85;
        critMod = 6;
    }
};
class Graveyard_Stumble: public AttackSkill, public MoveSkill{
public:
    Graveyard_Stumble(){
        dmgMod = -50;
        baseAcc = 45;
        critMod = 0;
    }
};
class Axeblade: public AttackSkill{
public:
    Axeblade(){
        dmgMod = 0;
        baseAcc = 72;
        critMod = 6;
    }
};
class Dead_Weight: public AttackSkill, public StunSkill{
public:
    Dead_Weight(){
        dmgMod = -25;
        baseAcc = 82;
        critMod = 6;
        stunBase = 100;
    }
};
class UtilitySkill: public Skill{
    int position;
    string Target;
    // string effect gelecek +20 Prot for 3 round
};

class Bulwark_Of_Faith: public UtilitySkill{

};
class Divine_Grace: public UtilitySkill{

};
class Divine_Comfort: public UtilitySkill{

};
class Knitting_Bones: public UtilitySkill{

};





int main() {
    srand (time(0));
    int randSpeed;
    randSpeed = rand() % 8 + 1  ;

    int randSpeed2;
    randSpeed2 = rand() % 8 + 1  ;

    int randSpeed3;
    randSpeed3 = rand() % 8 + 1  ;

    int randSpeed4;
    randSpeed4 = rand() % 8 + 1  ;

    int randSpeed5;
    randSpeed5 = rand() % 8 + 1  ;

    int randSpeed6;
    randSpeed6 = rand() % 8 + 1  ;

    int randSpeed7;
    randSpeed7 = rand() % 8 + 1  ;

    int randSpeed8;
    randSpeed8 = rand() % 8 + 1  ;

    int randSpeeds[8] = {randSpeed,randSpeed2,randSpeed3,randSpeed4,randSpeed5,randSpeed6,randSpeed7,randSpeed8};

    Vestal firstVestal("Vestal #1",3);
    Vestal secondVestal("Vestal #2",4);
    Crusader firstCrusader("Crusader #1",1);
    Crusader secondCrusader("Crusader #2",2);
    Bone_Defender firstBoneD("Bone Defender #1",2);
    Bone_Defender secondBoneD("Bone Defender #2",4);
    Bone_Soldier firstBoneS("Bone Soldier #1",1);
    Bone_Soldier secondBoneS("Bone Soldier #2",3);

    //Crusader Skills
    Smite Skill_Smite;//Attack
    Stunning_Blow Skill_Stunning_Blow;//Attack
    Holy_Lance Holy_Lance;//Attack + Move
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
    Dead_Weight Dead_Weight;//Attack
    Knitting_Bones Skill_Knitting_Bones;//Utility (Heal)





    Unit attackOrderArray[8];attackOrderArray[0] = secondVestal;attackOrderArray[1] = firstVestal;
    attackOrderArray[2] = secondCrusader;attackOrderArray[3] = firstCrusader;attackOrderArray[4] = firstBoneS;
    attackOrderArray[5] = firstBoneD;attackOrderArray[6] = secondBoneS;attackOrderArray[7] = secondBoneD;

    int speedtemp = 0;
    Crusader temp("temp",0);
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++){
            if(attackOrderArray[j].getSpeed() + randSpeeds[j] >attackOrderArray[j+1].getSpeed() + randSpeeds[j+1]){
                temp.setName(attackOrderArray[j].getName());
                temp.setSpeed(attackOrderArray[j].getSpeed());
                temp.setPosition(attackOrderArray[j].getPosition());
                attackOrderArray[j].setName(attackOrderArray[j+1].getName());
                attackOrderArray[j].setSpeed(attackOrderArray[j+1].getSpeed());
                attackOrderArray[j].setPosition(attackOrderArray[j+1].getPosition());
                attackOrderArray[j+1].setName(temp.getName());
                attackOrderArray[j+1].setSpeed(temp.getSpeed());
                attackOrderArray[j+1].setPosition(temp.getPosition());
                speedtemp = randSpeeds[j];
                randSpeeds[j] = randSpeeds[j+1];
                randSpeeds[j+1] = speedtemp;
		}
	}


    vector<Hero>heroes;
    vector<Monster>monsters;

    vector<Hero>::iterator heroPtr;
    heroPtr = heroes.begin();

    vector<Monster>::iterator monsterPtr;
    monsterPtr = monsters.begin();

    heroes.push_back(secondVestal);heroes.push_back(firstVestal);heroes.push_back(secondCrusader);heroes.push_back(firstCrusader);
    monsters.push_back(firstBoneS);monsters.push_back(firstBoneD);monsters.push_back(secondBoneS);monsters.push_back(secondBoneD);

    int numberOfRound = 1;
    int numberOfSkill;
    bool gameover = false;
do {
    cout<<"---R O U N D  "<<numberOfRound<<"---"<<endl;
    cout<<endl;

    for(int i = 7;i>=0;i--){

        cout<<attackOrderArray[i].getName()<<"'s turn! "<<"Select a skill!"<<endl;
        /*for(int j = 0;j<8;j++){
            cout<<attackOrderArray[j].getName()<<" ";
            cout<<attackOrderArray[j].getSpeed()+randSpeeds[j]<<endl;

        }*//*Test için duruyor*/
        if(attackOrderArray[i].getName() == "Vestal #1"||attackOrderArray[i].getName() == "Vestal #2"){
        if(attackOrderArray[i].getPosition() == 1){
            int target;
            cout<<"1 : Mace Bash (Attack)"<<endl;
            cout<<attackOrderArray[i].getName()<<" at Position 1"<<endl;
            cout<<"Mace Bash Selected automatically!"<<endl;
            cout<<"Select a target to attack!"<<endl;
            cout<<"1-"<<monsters[0].getName()<<"("<<monsters[0].getHp()<<")"<<endl;
            cout<<"2-"<<monsters[1].getName()<<"("<<monsters[1].getHp()<<")"<<endl;
            cout<<"Number of Target : ";
            cin>>target;
            cout<<"Using Mace Bash to attack to "<<monsters[target-1].getName()<<"(Hp : "<<monsters[target-1].getHp()<<")"<<endl;

        }
        else if(attackOrderArray[i].getPosition() == 2){
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
        else if(attackOrderArray[i].getPosition() == 3 || attackOrderArray[i].getPosition() == 4){
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
            cout<<"1-"<<monsters[0].getName()<<"(Hp : "<<monsters[0].getHp()<<")"<<endl;
            cout<<"2-"<<monsters[1].getName()<<"(Hp : "<<monsters[1].getHp()<<")"<<endl;
            cout<<"Number of Target : ";
            cin>>target;
            if(target==3||target==4){
                cout<<"Number of Target selected 1 automatically because your selection is not an option! "<<endl;
                target = 1;

            }
            cout<<"Using Mace Bash to attack to "<<monsters[target-1].getName()<<"(Hp : "<<monsters[target-1].getHp()<<")"<<endl;
        }
        else if(numberOfSkill == 2){
            int target;
            cout<<"Dazzling Light Selected!"<<endl;
            cout<<"Select a target to attack!"<<endl;
            cout<<"1-"<<monsters[0].getName()<<"(Hp : "<<monsters[0].getHp()<<")"<<endl;
            cout<<"2-"<<monsters[1].getName()<<"(Hp : "<<monsters[1].getHp()<<")"<<endl;
            cout<<"3-"<<monsters[2].getName()<<"(Hp : "<<monsters[2].getHp()<<")"<<endl;
            cout<<"Number of Target : ";
            cin>>target;
            if(target==4){
                cout<<"Number of Target selected 1 automatically because your selection is not an option! "<<endl;
                target = 1;

            }
            cout<<"Using Mace Bash to attack to "<<monsters[target-1].getName()<<"(Hp : "<<monsters[target-1].getHp()<<")"<<endl;
        }
        else if(numberOfSkill == 3){
            int target;
            cout<<"Divine Grace Selected!"<<endl;
            cout<<"Select a target to heal!"<<endl;
            cout<<"1-"<<heroes[0].getName()<<"(Hp : "<<heroes[0].getHp()<<")"<<endl;
            cout<<"2-"<<heroes[1].getName()<<"(Hp : "<<heroes[1].getHp()<<")"<<endl;
            cout<<"3-"<<heroes[2].getName()<<"(Hp : "<<heroes[2].getHp()<<")"<<endl;
            cout<<"4-"<<heroes[3].getName()<<"(Hp : "<<heroes[3].getHp()<<")"<<endl;
            cout<<"Number of Target : ";
            cin>>target;
            int healAmount = rand() % 2 + 4;
            cout<<"Using Mace Bash to heal to "<<heroes[target-1].getName()<<"(Hp : "<<heroes[target-1].getHp()<<")"<<" by "<<healAmount<<endl;
        }
        else if(numberOfSkill == 4){
            int healAmount = rand() % 3 + 1;
            cout<<"Divine Comfort Selected!"<<endl;
            cout<<"Healing all Heroes by "<<healAmount<<endl;
        }
        cout<<"----------------------------------------"<<endl;
        }

        else if(attackOrderArray[i].getName() == "Crusader #1"||attackOrderArray[i].getName() == "Crusader #2"){
        if(attackOrderArray[i].getPosition() == 1 || attackOrderArray[i].getPosition() == 2){
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
            cout<<"2-"<<monsters[1].getName()<<"(Hp : "<<monsters[1].getHp()<<")"<<endl;
            cout<<"3-"<<monsters[2].getName()<<"(Hp : "<<monsters[2].getHp()<<")"<<endl;
            cout<<"4-"<<monsters[3].getName()<<"(Hp : "<<monsters[3].getHp()<<")"<<endl;
            cout<<"Number of Target : ";
            cin>>target;
            if(target==1){
                cout<<"Number of Target selected 2 automatically because your selection is not an option! "<<endl;
                target = 2;

            }
            cout<<"Using Holy Lance to attack to "<<monsters[target-1].getName()<<"(Hp : "<<monsters[target-1].getHp()<<")"<<endl;
        }

        if(numberOfSkill == 1){
            int target;
            cout<<"Smite Selected!"<<endl;
            cout<<"Select a target to attack!"<<endl;
            cout<<"1-"<<monsters[0].getName()<<"(Hp : "<<monsters[0].getHp()<<")"<<endl;
            cout<<"2-"<<monsters[1].getName()<<"(Hp : "<<monsters[1].getHp()<<")"<<endl;
            cout<<"Number of Target : ";
            cin>>target;
            if(target==3||target==4){
                cout<<"Number of Target selected 1 automatically because your selection is not an option! "<<endl;
                target = 1;

            }
            cout<<"Using Smite on "<<monsters[target-1].getName()<<"(Hp : "<<monsters[target-1].getHp()<<")"<<endl;

        }
        else if(numberOfSkill == 2){
            int target;
            cout<<"Stunning Blow Selected!"<<endl;
            cout<<"Select a target to attack!"<<endl;
            cout<<"1-"<<monsters[0].getName()<<"(Hp : "<<monsters[0].getHp()<<")"<<endl;
            cout<<"2-"<<monsters[1].getName()<<"(Hp : "<<monsters[1].getHp()<<")"<<endl;
            cout<<"Number of Target : ";
            cin>>target;
            if(target==3||target==4){
                cout<<"Number of Target selected 1 automatically because your selection is not an option! "<<endl;
                target = 1;

            }
            cout<<"Using Stunning Blow on "<<monsters[target-1].getName()<<"(Hp : "<<monsters[target-1].getHp()<<")"<<endl;
        }
        else if(numberOfSkill == 3){
            cout<<"Bulwark of Faith Selected!"<<endl;
            cout<<"Using Bulwark of Faith on "<<attackOrderArray[i].getName()<<", +20 protection for 3 round."<<endl;

        }
        cout<<"----------------------------------------"<<endl;
        }

        else if(attackOrderArray[i].getName()=="Bone Defender #1"||attackOrderArray[i].getName() == "Bone Defender #2"){

            int numOfSkill = rand() % 3 + 1;
            int target = rand() % 2 + 1;
            int healMonster = rand() % 4 + 1;
            int randHealAmount = rand() % 1 + 3;
            if(numOfSkill==1){
                cout<<attackOrderArray[i].getName()<<" is selected AxeBlade to attack to "<<heroes[4-target].getName()<<endl;
            }
            else if(numOfSkill==2){
                cout<<attackOrderArray[i].getName()<<" is selected Dead Weight to attack to "<<heroes[4-target].getName()<<endl;
            }
            else if(numOfSkill==3){
                cout<<attackOrderArray[i].getName()<<" is selected Knitting Bones to heal to "<<monsters[healMonster].getName()<<" by " <<randHealAmount<<endl;
            }
            cout<<"----------------------------------------"<<endl;

        }

        else if(attackOrderArray[i].getName()=="Bone Soldier #1"||attackOrderArray[i].getName() == "Bone Soldier #2"){

            int numOfSkill = rand() % 2 + 1;
            int target = rand() % 2 + 1;
            int target2 = rand() % 3 + 1;

            if(numOfSkill==1){
                cout<<attackOrderArray[i].getName()<<" is selected Graveyard Slash to attack to "<<heroes[4-target2].getName()<<endl;
            }
            else if(numOfSkill==2){
                cout<<attackOrderArray[i].getName()<<" is selected Dead Weight to attack to "<<heroes[4-target].getName()<<endl;
                cout<<"And "<<attackOrderArray[i].getName()<<" moves 1 step forward!"<<endl;
            }
            cout<<"----------------------------------------"<<endl;
        }



    }










if(heroes[0].getHp()+heroes[1].getHp()+heroes[2].getHp()+heroes[3].getHp() == 0 ||
   monsters[0].getHp()+monsters[1].getHp()+monsters[2].getHp()+monsters[3].getHp() == 0){
    gameover = true;
   }

numberOfRound++;

} while (gameover == false);



    return 0;
}
