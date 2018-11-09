#include<cmath>
#include<iostream>
#include<iomanip>
#include<string>

using namespace std;;

class path;

int roll(int mod);
int rollfight(int atkmod, int defmod);
void passives(path* Opp2, int* hp, int r);

class path
{
public:

	int HP;
	int AP;
	int MP;
	int ab;
	int rollmod;
	bool magickabl;
	bool cursed;
	bool shadows;
	string name;

	path Clone() {
		path cop;
		cop.HP = HP;
		cop.AP = AP;
		cop.MP = MP;
		cop.ab = ab;
		cop.rollmod = rollmod;
		cop.magickabl = magickabl;
		cop.cursed = cursed;
		cop.shadows = shadows;
		cop.name = name;

		return cop;
	}
	void display() {
		cout << endl << endl << name << endl << "HP " << HP << endl << "AP " << AP << endl << "MP " << MP << endl << endl;
	}
	void ability(path* Opponent) {
		//knight ability
		magickabl = 0;
		if (ab == 1) {
			int r = rollfight(rollmod, Opponent->rollmod);
			if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
			else cout << endl << "failure" << endl << endl;
			passives(Opponent, &HP, r);

		}

		//beserker ability
		if (ab == 2) {
			if (AP>2) {
				AP = AP - 3;
				for (int i = 1; i <= 4; i++) {
					int r = rollfight(rollmod, Opponent->rollmod);
					if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
					else cout << endl << "failure" << endl << endl;
				}

			}
			else if (AP>0) {
				for (; AP >= 0; AP--) {
					int r = rollfight(rollmod, Opponent->rollmod);
					if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
					else cout << endl << "failure" << endl << endl;
				}
				AP = 0;
			}
			else {
				int r = rollfight(rollmod, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
			}
		}

		//crusader ability
		if (ab == 3) {
			if (MP>1) {
				MP = MP - 2;
				int r = rollfight(rollmod, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - 5; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
				magickabl = 1;
				passives(Opponent, &HP, r);
			}

			else if (MP >= 1) {
				MP = MP - 1;
				int r = rollfight(rollmod, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - 3; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
				magickabl = 1;
				passives(Opponent, &HP, r);
			}
			else {
				int r = rollfight(rollmod, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
				passives(Opponent, &HP, r);
			}
		}

		//Witch Hunter Ability
		if (ab == 4) {
			if (Opponent->magickabl == 1 && AP>0) { Opponent->HP = Opponent->HP - 2; AP = AP - 1; }
			int r = rollfight(rollmod, Opponent->rollmod);
			if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
			else cout << endl << "failure" << endl << endl;
			passives(Opponent, &HP, r);
		}

		//Infiltrator
		if (ab == 5) {
			if (MP>1) {
				MP = MP - 2;
				shadows = 1;
			}
			if (shadows == 1) {
				int r = rollfight(rollmod + 2, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - 2; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
				magickabl = 1;
				shadows = 0;
				passives(Opponent, &HP, r);
			}
			else {
				int r = rollfight(rollmod, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
				passives(Opponent, &HP, r);
			}
		}

		//Ranger
		if (ab == 6) {
			int r = 2;
			if (AP>0) {
				int r = rollfight(rollmod + 2, Opponent->rollmod);
				AP = AP - 1;
			}
			else {
				int r = rollfight(rollmod, Opponent->rollmod);
			}
			if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
			else cout << endl << "failure" << endl << endl;
			passives(Opponent, &HP, r);

		}

		//Sorceror
		if (ab == 7) {
			if (MP>2) {
				MP = MP - 3;
				int r = rollfight(rollmod, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - 4; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
				magickabl = 1;
				passives(Opponent, &HP, r);
			}

			else if (MP>0) {
				int nhp = 1;
				for (; MP>0; MP = MP - 1) {
					nhp = nhp + 1;
				}
				int r = rollfight(rollmod, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - nhp; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
				magickabl = 1;
				passives(Opponent, &HP, r);
			}
			else {
				int r = rollfight(rollmod, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
				passives(Opponent, &HP, r);
			}
		}

		//Cleric
		if (ab == 8) {
			if (MP>0 && HP<4) {
				HP = HP + 2;
				MP = MP - 1;
				magickabl = 1;
			}
			else {
				int r = rollfight(rollmod, Opponent->rollmod);
				if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
				else cout << endl << "failure" << endl << endl;
				passives(Opponent, &HP, r);
			}
		}

		//Spellblade
		if (ab == 9) {
			if (Opponent->cursed == 1) { Opponent->cursed = 0; Opponent->rollmod = Opponent->rollmod + 2; }

			int r = rollfight(rollmod, Opponent->rollmod);
			if (r == 1) { Opponent->HP = Opponent->HP - 1; cout << endl << "success" << endl << endl; }
			else cout << endl << "failure" << endl << endl;

			if (MP>0) {
				Opponent->cursed = 1;
				Opponent->rollmod = Opponent->rollmod - 2;
				magickabl = 1;
				MP = MP - 1;
			}

			passives(Opponent, &HP, r);
		}
	}

};

void fight(path* Opp1, path* Opp2);

path Knig();
path Bese();
path Crus();
path Witc();
path Infi();
path Rang();
path Sorc();
path Cler();
path Spel();

void simfight(path* Opp1, path* Opp2, double iterations);
void pickapath(int num, path* Temp);

/*
____________________________________________________________________

Main
Function
____________________________________________________________________
*/

int main()
{
	for (char ans = 'y'; ans != 'n';) {
		cout << "Hello! And welcome to Ofalo's sentinel fight simulation 1.0!" << endl << "Please pick a calling as the first Opponent!" << endl << "Type the number and press enter" << endl << endl;
		cout << "1. Knight" << endl;
		cout << "2. Beserker" << endl;
		cout << "3. Crusader" << endl;
		cout << "4. Witch Hunter" << endl;
		cout << "5. Infiltrator" << endl;
		cout << "6. Ranger" << endl;
		cout << "7. Sorceror" << endl;
		cout << "8. Cleric" << endl;
		cout << "9. Spellblade" << endl << endl;
		int a;
		cin >> a;

		path Opponent1;
		path Opponent2;

		pickapath(a, &Opponent1);

		cout << endl << "Please pick a calling as the Second Opponent!" << endl << "Type the number and press enter" << endl << endl;
		cout << "1. Knight" << endl;
		cout << "2. Beserker" << endl;
		cout << "3. Crusader" << endl;
		cout << "4. Witch Hunter" << endl;
		cout << "5. Infiltrator" << endl;
		cout << "6. Ranger" << endl;
		cout << "7. Sorceror" << endl;
		cout << "8. Cleric" << endl;
		cout << "9. Spellblade" << endl << endl;
		int b;
		cin >> b;

		pickapath(b, &Opponent2);

		cout << endl << endl << "How many times would you like to simulate this fight?" << endl << endl;
		int iteration;
		cin >> iteration;

		simfight(&Opponent1, &Opponent2, iteration);

		cout << endl << endl << "Would you like to run again? (y/n)" << endl << endl;

		for (bool flag = 0; flag != 1;) {
			//cin>>ans;
			scanf_s("%c", &ans);
			if (ans == 'n') {
				cout << endl << "Understandable have a nice day" << endl << endl;
				flag = 1;
			}
			/*
			else if(ans!='y'){
			cout<<endl<<"I don't understand what you mean, please type 'y' for yes or 'n' for no..."<<endl<<endl;
			}
			*/
			else if (ans == 'y') {
				cout << endl << "RUN IT AGAIN CHARLIE!!!" << endl << endl;
				flag = 1;
			}
		}
	}

	return 0;
}


/*
____________________________________________________________________

Function
Library
____________________________________________________________________
*/


void pickapath(int num, path* Temp) {
	for (bool flag = 0; flag != 1;) {
		if (num == 1) {
			*Temp = Knig();
			cout << endl << "You have picked " << Temp->name << endl;
			flag = 1;
		}
		else if (num == 2) {
			*Temp = Bese();
			cout << endl << "You have picked " << Temp->name << endl;
			flag = 1;
		}
		else if (num == 3) {
			*Temp = Crus();
			cout << endl << "You have picked " << Temp->name << endl;
			flag = 1;
		}
		else if (num == 4) {
			*Temp = Witc();
			cout << endl << "You have picked " << Temp->name << endl;
			flag = 1;
		}
		else if (num == 5) {
			*Temp = Infi();
			cout << endl << "You have picked " << Temp->name << endl;
			flag = 1;
		}
		else if (num == 6) {
			*Temp = Rang();
			cout << endl << "You have picked " << Temp->name << endl;
			flag = 1;
		}
		else if (num == 7) {
			*Temp = Sorc();
			cout << endl << "You have picked " << Temp->name << endl;
			flag = 1;
		}
		else if (num == 8) {
			*Temp = Cler();
			cout << endl << "You have picked " << Temp->name << endl;
			flag = 1;
		}
		else if (num == 9) {
			*Temp = Spel();
			cout << endl << "You have picked " << Temp->name << endl;
			flag = 1;
		}
		else {
			cout << endl << "You picked a wrong number my dude" << endl << endl;
			cin >> num;
		}
	}
}

void simfight(path* Opp1, path* Opp2, double iterations) {
	double v1 = 0, v2 = 0;
	for (int i = 0; i<iterations; i++) {
		path Opp10 = Opp1->Clone();
		path Opp20 = Opp2->Clone();
		fight(&Opp10, &Opp20);
		if (Opp10.HP>0) v1 = v1 + 1;
		else v2 = v2 + 1;

	}
	double cwins = v1 / iterations;
	double bwins = v2 / iterations;
	cout << endl << endl << endl << Opp1->name << " win rate: " << cwins << endl << Opp2->name << " win rate: " << bwins << endl << endl;


}

int roll(int mod) {
	int numb = rand() % 10 + 1 + mod;
	return numb;
}

int rollfight(int atkmod, int defmod) {
	int r1 = roll(atkmod), r2 = roll(defmod);
	if (r1>r2) return 1;		//success atk
	else return 0;			//success def
}

void passives(path* Opp2, int* hp, int r) {
	if (Opp2->ab == 1 && r == 0) {
		
		if (Opp2->AP>2) {
			Opp2->AP = Opp2->AP - 3;
			*hp = *hp - 3;
			//cout << "work1" << endl;
		}

		else if (Opp2->AP>0) {
			for (; Opp2->AP>0; Opp2->AP = Opp2->AP - 1) {
				*hp = *hp - 1;
				//cout << "work1" << endl;
			}
		}
	}
}

void fight(path* Opp1, path* Opp2) {
	Opp1->display();
	Opp2->display();
	cout << endl << endl;

	while (Opp1->HP>0 && Opp2->HP>0) {

		Opp1->ability(Opp2);

		Opp1->display();
		Opp2->display();

		cout << endl << endl;

		Opp2->ability(Opp1);

		Opp1->display();
		Opp2->display();
	}
	if (Opp1->HP>0) { cout << endl << endl << "VICTORY TO " << Opp1->name << endl << endl; }
	if (Opp2->HP>0) { cout << endl << endl << "VICTORY TO " << Opp2->name << endl << endl; }
}

path Knig() {
	path Knight;
	Knight.HP = 5;
	Knight.AP = 5;
	Knight.MP = 3;
	Knight.ab = 1;
	Knight.rollmod = 0;
	Knight.name = "Knight";

	return Knight;
}

path Bese() {
	path Beserker;
	Beserker.HP = 5;
	Beserker.AP = 5;
	Beserker.MP = 3;
	Beserker.ab = 2;
	Beserker.rollmod = 0;
	Beserker.name = "Beserker";

	return Beserker;
}

path Crus() {
	path Templar;
	Templar.HP = 5;
	Templar.AP = 5;
	Templar.MP = 3;
	Templar.ab = 3;
	Templar.rollmod = 0;
	Templar.name = "Crusader";

	return Templar;
}

path Witc() {
	path Templar;
	Templar.HP = 5;
	Templar.AP = 4;
	Templar.MP = 4;
	Templar.ab = 4;
	Templar.rollmod = 0;
	Templar.name = "Witch Hunter";

	return Templar;
}

path Infi() {
	path Templar;
	Templar.HP = 5;
	Templar.AP = 4;
	Templar.MP = 4;
	Templar.ab = 5;
	Templar.rollmod = 0;
	Templar.name = "Infiltrator";

	return Templar;
}

path Rang() {
	path Templar;
	Templar.HP = 5;
	Templar.AP = 4;
	Templar.MP = 4;
	Templar.ab = 6;
	Templar.rollmod = 0;
	Templar.name = "Ranger";

	return Templar;
}

path Sorc() {
	path Templar;
	Templar.HP = 5;
	Templar.AP = 3;
	Templar.MP = 5;
	Templar.ab = 7;
	Templar.rollmod = 0;
	Templar.name = "Sorceror";

	return Templar;
}

path Cler() {
	path Templar;
	Templar.HP = 5;
	Templar.AP = 3;
	Templar.MP = 5;
	Templar.ab = 8;
	Templar.rollmod = 0;
	Templar.name = "Cleric";

	return Templar;
}

path Spel() {
	path Templar;
	Templar.HP = 5;
	Templar.AP = 3;
	Templar.MP = 5;
	Templar.ab = 9;
	Templar.rollmod = 0;
	Templar.name = "Spell Blade";

	return Templar;
}
