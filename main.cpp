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
public:
    Unit(){
    }

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

    void setName(string nam){
    name = nam;
    }

    void setSpeed(int sped){
    speed = sped;
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
                //hero olur karakter dummy olarak atanir.
            }
        }
    }
};
class Crusader: public Hero {
public:
    Crusader(string na){
        name = na;
        maxHp = 33;
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
    void virtual attack(){
        // attack classi buradan cagirlacak

    }
};
class Vestal : public Hero{
public:
    Vestal(string na):Hero(){
        name = na;
        maxHp = 24;
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



};

class Monster: public Unit {
protected:
    Monster(){}
    void dying(){

           // karakter dummy olarak atanir.

    }
};
class Bone_Soldier: public Monster{
public:
    Bone_Soldier(string na):Monster(){
        name = na;
        maxHp = 10;
        dodge = 10;
        prot = 15;
        speed = 2;
        accMod = 0;
        baseCrit = 0;
        minDmg = 3;
        maxDmg = 8;
        stunResist = 25;
    }


};
class Bone_Defender:public Monster{
public:
    Bone_Defender(string na):Monster(){
        name = na;
        maxHp = 22;
        dodge = 8;
        prot = 45;
        speed = 1;
        accMod = 0;
        baseCrit = 0;
        minDmg = 2;
        maxDmg = 4;
        stunResist = 45;
    }

};




class StunSkill{
    StunSkill();

};
class Skill{
protected:
    int position;
    int target;
public:

};
class attackSkill: public Skill{
protected:
    int dmgMod;
    int baseAcc;
    int critMod;
    string stunEffect;
    int stunBase;
public:
    void attackFunc(Unit attacker, Unit defender, Skill attack) {
        int randomNumber = rand() % 101;
        int hitChange = baseAcc + attacker.getAccMod() - defender.getDodge();
        if (hitChange >= randomNumber) { // saldirir ve crit hesaplamasi yapilir
            int criticalChance = attacker.getBaseCrit() + critMod;
            randomNumber = rand() % 101;
            if (criticalChance >= randomNumber) { // crit vurur
                double critHit = attacker.getMaxDmg() * 1.5;
                defender.getDamage(critHit);
            }
            else {
                int dmg = rand() % attacker.getMaxDmg() + attacker.getMinDmg();
                double rawDmg = dmg * (100 + dmgMod) / 100.0;
                double actualDmg = rawDmg - rawDmg * (defender.getProt() / 100.0);
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


    Vestal firstVestal("Vestal #1");
    Vestal secondVestal("Vestal #2");
    Crusader firstCrusader("Crusader #1");
    Crusader secondCrusader("Crusader #2");
    Bone_Defender firstBoneD("Bone Defender #1");
    Bone_Defender secondBoneD("Bone Defender #2");
    Bone_Soldier firstBoneS("Bone Soldier #1");
    Bone_Soldier secondBoneS("Bone Soldier #2");



    Unit attackOrderArray[8];attackOrderArray[0] = secondVestal;attackOrderArray[1] = firstVestal;
    attackOrderArray[2] = secondCrusader;attackOrderArray[3] = firstCrusader;attackOrderArray[4] = firstBoneS;
    attackOrderArray[5] = firstBoneD;attackOrderArray[6] = secondBoneS;attackOrderArray[7] = secondBoneD;

    int speedtemp = 0;
    Crusader temp("temp");
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++){
            if(attackOrderArray[j].getSpeed() + randSpeeds[j] >attackOrderArray[j+1].getSpeed() + randSpeeds[j+1]){
                temp.setName(attackOrderArray[j].getName());
                temp.setSpeed(attackOrderArray[j].getSpeed());
                attackOrderArray[j].setName(attackOrderArray[j+1].getName());
                attackOrderArray[j].setSpeed(attackOrderArray[j+1].getSpeed());
                attackOrderArray[j+1].setName(temp.getName());
                attackOrderArray[j+1].setSpeed(temp.getSpeed());

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
        cout<<"1 : Mace Bash (Attack)"<<endl;
        cout<<"2 : Dazzling Light (Attack)"<<endl;
        cout<<"3 : Divine Grace (Utility)"<<endl;
        cout<<"4 : Divine Comfort (Utility)"<<endl;
        cout<<"Number of Skill : ";
        cin>>numberOfSkill;
        if(numberOfSkill == 1){
            cout<<"Mace Bash Selected!"<<endl;
        }
        else if(numberOfSkill == 2){
            cout<<"Dazzling Light Selected!"<<endl;
        }
        else if(numberOfSkill == 3){
            cout<<"Divine Grace Selected!"<<endl;
        }
        else if(numberOfSkill == 4){
            cout<<"Divine Comfort Selected!"<<endl;
        }
        cout<<"----------------------------------------"<<endl;
        }

        else if(attackOrderArray[i].getName() == "Crusader #1"||attackOrderArray[i].getName() == "Crusader #2"){
        cout<<"1 : Smite (Attack)"<<endl;
        cout<<"2 : Stunning Blow (Attack)"<<endl;
        cout<<"3 : Holy Lance (Attack)"<<endl;
        cout<<"4 : Bulwark of Faith (Utility)"<<endl;
        cout<<"Number of Skill : ";
        cin>>numberOfSkill;

        if(numberOfSkill == 1){
            int target;
            cout<<"Smite Selected!"<<endl;
            cout<<"Select a target to attack!"<<endl;
            cout<<"1-"<<monsters[0].getName()<<endl;
            cout<<"2-"<<monsters[1].getName()<<endl;
            cout<<"Number of Target : ";
            cin>>target;
            cout<<"Using Smite on "<<monsters[target-1].getName()<<endl;
        }
        else if(numberOfSkill == 2){
            cout<<"Stunning Blow Selected!"<<endl;
        }
        else if(numberOfSkill == 3){
            cout<<"Holy Lance Selected!"<<endl;
        }
        else if(numberOfSkill == 4){
            cout<<"Bulwark of Faith Selected!"<<endl;
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
