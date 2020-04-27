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
    void virtual attack(){}

    int getSpeed(){
        return speed;
    }
    string getName(){
        return name;
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
    void dying(){
        if(maxHp == 0){
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
        if(maxHp == 0){
           // karakter dummy olarak atanir.
        }
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



class attack: public attackSkill,public Unit {
protected:
    int randomNumber = rand() % 101;
    int hitChange = baseAcc + accMod - dodge;
public:
    void attackFunc() {
        int randomNumber = rand() % 101;
        int hitChange = baseAcc + accMod - dodge;
        if (hitChange >= randomNumber) { // saldirir ve crit hesaplamasi yapilir
            int criticalChance = baseCrit + critMod;
            randomNumber = rand() % 101;
            if (criticalChance >= randomNumber) { // crit vurur
                double critHit = maxDmg * 1.5;
            } else {
                int dmg = rand() % maxDmg + minDmg;
                double rawDmg = dmg * (100 + dmgMod) / 100.0;
                double actualDmg = rawDmg - rawDmg * (prot / 100.0);
            } // normal vurur
        } else {} // missing
    }


};

void turnOrder(){

}


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
    Bone_Defender firsBoneD("Bone Defender #1");
    Bone_Defender secondBoneD("Bone Defender #2");
    Bone_Soldier firstBoneS("Bone Soldier #1");
    Bone_Soldier secondBoneS("Bone Soldier #2");

    Unit attackOrderArray[8];attackOrderArray[0] = secondVestal;attackOrderArray[1] = firstVestal;
    attackOrderArray[2] = secondCrusader;attackOrderArray[3] = firstCrusader;attackOrderArray[4] = firstBoneS;
    attackOrderArray[5] = firsBoneD;attackOrderArray[6] = secondBoneS;attackOrderArray[7] = secondBoneD;

    Unit temp;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++){
            if(attackOrderArray[j].getSpeed() + randSpeeds[j] >attackOrderArray[j+1].getSpeed() + randSpeeds[j+1]){
                temp=attackOrderArray[j];
                attackOrderArray[j]=attackOrderArray[j+1];
                attackOrderArray[j+1]=temp;
            }
        }


    vector<Hero>heroes;
    vector<Monster>monsters;

    vector<Hero>::iterator heroPtr;
    heroPtr = heroes.begin();

    vector<Monster>::iterator monsterPtr;
    monsterPtr = monsters.begin();


    int numberOfSkill;
    bool gameover = false;
    do {
        cout<<attackOrderArray[0].getName()<<endl;cout<<"'s turn! Select a skill!"<<endl;
        cout<<"--------------------------------"<<endl;
        if(attackOrderArray[0].getName() == "Vestal #1"||attackOrderArray[0].getName() == "Vestal #2"){
            cout<<"1 : Mace Bash (Attack)"<<endl;
            cout<<"2 : Dazzling Light (Attack)"<<endl;
            cout<<"3 : Divine Grace (Utility)"<<endl;
            cout<<"4 : Divine Comfort (Utility)"<<endl;
            cout<<"--------------------------------"<<endl;
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
        }

        else if(attackOrderArray[0].getName() == "Crusader #1"||attackOrderArray[0].getName() == "Crusader #2"){
            cout<<"1 : Smite (Attack)"<<endl;
            cout<<"2 : Stunning Blow (Attack)"<<endl;
            cout<<"3 : Holy Lance (Attack)"<<endl;
            cout<<"4 : Bulwark of Faith (Utility)"<<endl;
            cout<<"--------------------------------"<<endl;
            cout<<"Number of Skill : ";
            cin>>numberOfSkill;

            if(numberOfSkill == 1){
                cout<<"Smite Selected!"<<endl;
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
        }


















        gameover = 1;

    } while (gameover == false);

    return 0;
}
