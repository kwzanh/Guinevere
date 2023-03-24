#include "knight.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
         << ", level=" << level
         << ", remedy=" << remedy
         << ", maidenkiss=" << maidenkiss
         << ", phoenixdown=" << phoenixdown
         << ", rescue=" << rescue << endl;
}


// Global functions (general functions)
// Count digits in a string
int digitsCount(string txt) {
    int spaceCount = 0;
    for (int i = 0; i < txt.length(); i++) {
        if (isspace(txt[i])) {
            spaceCount++;
        }
    }
    return spaceCount + 1;
}

// Check the prime number
bool check_prime(int n) {
    bool is_prime = true;

    // 0 and 1 are not prime numbers
    if (n == 0 || n == 1) {
        is_prime = false;
    }

    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            is_prime = false;
            break;
        }
    }

    return is_prime;
}


// Combat functions
// Calculate levelO of the opponent
int levelO_cal(int i) {
    int iO = i + 1; // because the the array index starts from 0
    int b = iO % 10;
    int levelO = iO > 6 ? (b > 5 ? b : 5) : b;
    
    return levelO;
}

// Calculate the damage of the opponent
int dmg_cal(int levelO, int opponentCode) {
    opponentCode = opponentCode - 1;
    double baseDmg[5] = {1, 1.5, 4.5, 7.5, 9.5};
    double dmg = baseDmg[opponentCode] * levelO * 10;

    return dmg;
}

// Check the level is max or not
int maxLevel_check(int level) {
    if (level > 10) {
         return level = 10;
    } else {
        return level;
    }
}


// Event 0: Bowser surrenders and gives back the princess
void BowserGG(int & rescue) {
    rescue = 1;
}


// Event 1-5: Mad Bear, Bandit, Lord Lupin, Elf, Troll
void easyOpponents(int i, int & level, int & HP, int & maxHP, int & phoenixdown, int & rescue, int opponentCode) {
    int current_levelO = levelO_cal(i);

    if (level > current_levelO) {
        level += 1;
        level = maxLevel_check(level);
    } else if (level == current_levelO) {
        level += 0;
    } else {
        // combat procedure
        int current_dmg = dmg_cal(current_levelO, opponentCode);
        HP = HP - current_dmg;

        // HP check
        if (HP <= 0) {
            if (phoenixdown <= 0) {
                rescue = 0;
            } else {
                phoenixdown -= 1;
                HP = maxHP;
            }
        }
    }
}


// Event 6: Shaman
void ShamanWitch(int i, int & level, int & HP, int & maxHP, int & phoenixdown, int & remedy, int & rescue, int opponentCode, int & ShamanExpiry) {
    int current_levelO = levelO_cal(i);

    if (level > current_levelO) {
        level += 2;
        level = maxLevel_check(level);
    } else if (level == current_levelO) {
        level += 0;
    } else {
        ShamanExpiry = i + 4;
        
        if (remedy >= 1) {
            remedy -= 1;
        } else {
            if (HP < 5) {
                HP = 1;
            } else {
                HP = HP / 5;
            }
        }
    }
}

void ShamanExpiryCheck(int i, int & HP, int & maxHP, int & ShamanExpiry) {
    if (i == ShamanExpiry) {
        HP = HP * 5;
        if (HP > maxHP) {
            HP = maxHP;
        } else {
            HP = HP;
        }
    } else {
        return;
    }
}


// Event 7: Siren Vajsh
void SirenVajsh(int i, int & level, int & HP, int & maxHP, int & phoenixdown, int & remedy, int & maidenkiss, int & rescue, int opponentCode, int & SirenVajshExpiry, int & beforeFrog) {
    int current_levelO = levelO_cal(i);

    if (level > current_levelO) {
        level += 2;
        level = maxLevel_check(level);
    } else if (level == current_levelO) {
        level += 0;
    } else {
        SirenVajshExpiry = i + 4;

        if (maidenkiss >= 1) {
            level = level;
        } else {
            beforeFrog = level;
            level = 1;
        }
    }
}

void SirenVajshExpiryCheck(int i, int & level, int & SirenVajshExpiry, int & beforeFrog) {
    if (i == SirenVajshExpiry) {
        level = beforeFrog;
    } else {
        return;
    }
}


// Event 11: Mush Mario
void MushMario(int & HP, int & maxHP, int & level, int & phoenixdown) {
    int n1 = ((level + phoenixdown) % 5 + 1) * 3;
    int s1 = 0;
    for (int i = 99; i > (99 - (n1 * 2)); i -= 2) {
        s1 += i;
    }
    HP = HP + (s1 % 100);
    if (check_prime(HP)) {
        HP = HP;
    } else {
        for (int k=1; k < (HP*HP); k++) {
            HP += 1;
            if (check_prime(HP)) {
                break;
            }
        }
    }
} 


// Event 12: Mush Fibonacci
void MushFibo(int & HP) {
    if (HP == 1) {
        return;
    } else {
        int f1 = 1;
        int f2 = 1;
        int fibo;
        for (int i = 1; i < HP; i++) {
            fibo = f1 + f2;
            if (fibo > HP) {
                fibo = fibo - f1;
                break;
            } else {
                f1 = f2;
                f2 = fibo;
            }
        }
        HP = fibo;
    }
}


// Event 15: Pick up Remedy
// If the knight is being affected by Shaman then use immediately
void remedyUse(int & HP, int & maxHP) {
    HP = HP * 5;
    if (HP > maxHP) {
        HP = maxHP;
    }
}

// If the knight is not being affected by Shaman then add 1
void remedyPick(int & remedy) {
   remedy++;
   if (remedy > 99) {
    remedy = 99;
   }
}


// Event 16: Pick up Maiden Kiss
// If the knight is being affected by Siren Vajsh then use immediately
void maidenkissUse(int & level, int & beforeFrog) {
    level = beforeFrog;
}

// If the knight is not being affected by Siren Vajsh then add 1
void maidenkissPick(int & maidenkiss) {
    maidenkiss++;
    if (maidenkiss > 99) {
        maidenkiss = 99;
    }
}


// Event 17: Pick up Phoenix Down
void phoenixdownPick(int & phoenixdown) {
    phoenixdown++;
    if (phoenixdown > 99) {
        phoenixdown = 99;
    }
}


// Event 18: Merlin
// Main event
void Merlin(string pack_name, int & HP, int & maxHP) {
    string potion;
    ifstream merlin;
    int n;
    merlin.open(pack_name);
    merlin >> n;
    for (int k = 0; k < n; k++) {
        merlin >> potion;
        size_t buff1 = potion.find("merlin");
        size_t buff2 = potion.find("Merlin");

        if (buff1 != string::npos || buff2 != string::npos) {
            HP += 3;
            continue;
        } else {
            bool m = 0, e = 0, r = 0, l = 0, i = 0, n = 0;
            for (int j = 0; potion[j] != '\0'; j++) {
                if (potion[j] >= 'A' && potion[j] <= 'Z')
                    potion[j] = potion[j] + 32;
                if (potion[j] == 'm') {
                    m = 1;
                } else if (potion[j] == 'e') {
                    e = 1;
                } else if (potion[j] == 'r') {
                    r = 1;
                } else if (potion[j] == 'l') {
                    l = 1;
                } else if (potion[j] == 'i') {
                    i = 1;    
                } else if (potion[j] == 'n') {
                    n = 1;
                }                                                                                
            }
            if (m && e && r && l && i && n) {
                HP += 2;
            }
        }
    }
    HP = HP > maxHP ? maxHP : HP;
}

// Event 19: Asclepius
void asclepius(string pack_name, int & HP, int & maxHP, int & remedy, int & maidenkiss, int & phoenixdown) {
    int x, y, potion;
    ifstream asclepiusPack;
    asclepiusPack.open(pack_name);
    asclepiusPack >> x >> y;
    int count;
    for (int i = 0; i < x; i++) {
        count = 0;
        for (int j = 0; j < y; j++) {
            asclepiusPack >> potion;
            if (count == 3) {
                continue;
            } if (potion == 16) {
                remedy ++;
                if (remedy > 99) {
                    remedy = 99;
                }
                count++;
            } else if (potion == 17) {
                maidenkiss++;
                if (maidenkiss > 99) {
                    maidenkiss = 99;
                }
                count++;
            } else if (potion == 18) {
                phoenixdown++;
                if (phoenixdown > 99) {
                    phoenixdown = 99;
                }
                count++;
            }
        }
    }
    
}


// Main function
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    // read data from input file and store 3 lines to an array
    fstream inputData;
    inputData.open(file_input, ios::in);
    string line;
    string data[] = {};
    int line_count = 0;
    if (inputData.is_open()) {
        while (getline(inputData, data[line_count])) {
            line_count++;
        }
        inputData.close();
    }

    // knight's statistics input
    string knight_data = data[0];
    int knight_stat[] = {};
    int b = 0;
    stringstream iknight(knight_data);
    while (iknight.good() && b < digitsCount(knight_data)) {
        iknight >> knight_stat[b];
        ++b;
    }

    // assign to suitable variables
    HP = knight_stat[0];
    level = knight_stat[1];
    remedy = knight_stat[2];
    maidenkiss = knight_stat[3];
    phoenixdown = knight_stat[4];
    int maxHP = HP;

    // split line 2 into an array for route data
    string sroute = data[1];
    int route[] = {};
    int c = 0;
    stringstream iroute(sroute);
    while (iroute.good() && c < digitsCount(sroute)) {
        iroute >> route[c];
        ++c;
    }
    int routeLength = digitsCount(sroute);

    // external packs
    string externalPackNames = data[2];
    string exPacks[3] = {};
    stringstream exP(externalPackNames);
    int d = 0;
    while (exP.good()) {
        string name;
        getline(exP, name, ',');
        exPacks[d] = name;
        d++;
    }
    string file_mush_ghost = exPacks[0];
    string file_asclepius_pack = exPacks[1];
    string file_merlin_pack = exPacks[2];

    int ShamanExpiry = -1;
    int SirenVajshExpiry = -1;
    int beforeFrog = level;
    bool Lancelot;
    int MerlinAvail = 1;
    int AsclepiusAvail = 1;

    // Check if the knight is Arthur
    if (maxHP == 999) {
        // check the occurence of 0 and return suitable rescue status
        for (int j = 0; j < routeLength + 1; j++) {
            if (route[j] == 0) {
                rescue = 1;
                break;
            } else {
                rescue = 0;
            }
        }
    } else {
        // Check if the knight is Lancelot
        if (check_prime(maxHP)) {
            Lancelot = true;
        } else {
            Lancelot = false;
        }

        // Loop through every events stored in the array
        for (int i = 0; i < routeLength; i++) {
            if (rescue == 0) {
                break;
            } else if (rescue == 1) {
                break;
            } else {
                // check the expiry of Shaman and Siren Vajsh effects
                ShamanExpiryCheck(i, HP, maxHP, ShamanExpiry);
                SirenVajshExpiryCheck(i, level, SirenVajshExpiry, beforeFrog);

                // check the event code with the suitable case
                int currentEvent = route[i];
                switch (currentEvent) {
                    case 0: // Bowser GG (event code = 0)
                        BowserGG(rescue);
                        break;
    
                    case 1: // Mad Bear (event code = 1)
                    case 2: // Bandit (event code = 2)
                    case 3: // Lord Lupin (event code = 3)
                    case 4: // Elf (event code = 4)
                    case 5: // Troll (event code = 5)
                        if (Lancelot) { // if the knight is Lancelot then always win
                            level += 1;
                            break;
                        } else {
                            easyOpponents(i, level, HP, maxHP, phoenixdown, rescue, route[i]);
                            break;
                        }
                            
                    // Shaman (event code = 6)
                    case 6:
                        if (i >= (SirenVajshExpiry - 3) && i < SirenVajshExpiry) { // if the knight is affected by Siren Vajsh then skip
                            break;
                        } else {
                            ShamanWitch(i, level, HP, maxHP, phoenixdown, remedy, rescue, route[i], ShamanExpiry);
                            break;
                        }

                    // Siren Vajsh (event code = 7)
                    case 7:
                        if (i >= (ShamanExpiry - 3) && i < ShamanExpiry) { // if the knight is affected by Shaman then skip
                            break;
                        } else {
                            SirenVajsh(i, level, HP, maxHP, phoenixdown, remedy, maidenkiss, rescue, route[i], SirenVajshExpiry, beforeFrog);
                            break;
                        }

                    // Mush Mario (event code = 11)
                    case 11:  
                        MushMario(HP, maxHP, level, phoenixdown);
                        break;

                    // Mush Fibonacci (event code = 12)
                    case 12:
                        MushFibo(HP);
                        break;

                    // Remedy (event code = 15)
                    case 15:
                        if (i >= (ShamanExpiry - 3) && i < ShamanExpiry) {
                            remedyUse(HP, maxHP);
                            break;
                        } else {
                            remedyPick(remedy);
                            break;
                        }

                    // Maiden Kiss (event code = 16)
                    case 16:
                        if (i >= (SirenVajshExpiry - 3) && i < SirenVajshExpiry) {
                            maidenkissUse(level, beforeFrog);
                            break;
                        } else {
                            maidenkissPick(maidenkiss);
                            break;
                        }

                    // Phoenix Down (event code = 17)
                    case 17:
                        phoenixdownPick(phoenixdown);
                        break;

                    // Merlin (event code = 18)
                    case 18:
                        switch (MerlinAvail) {
                            case 1:
                                if (file_merlin_pack == "<file_merlin_pack>") {
                                    Merlin(file_merlin_pack, HP, maxHP); 
                                    MerlinAvail = 0;
                                    break;
                                } else {
                                    break;
                                }
                            case 0:
                                break;
                        }
                            
                    // Asclepius (event code = 19)
                    case 19:
                        switch (AsclepiusAvail) {
                            case 1:
                                if (file_asclepius_pack == "<file_asclepius_pack>") {
                                    asclepius(file_asclepius_pack, HP, maxHP, remedy, maidenkiss, phoenixdown);
                                    AsclepiusAvail = 0;
                                    break;
                                } else {
                                    break;
                                }
                            case 0:
                                break;
                        }

                    // Bowser (event code = 99)
                    case 99:
                        if (maxHP == 999) {
                            level = 10;
                            break;
                        } else if (Lancelot == true && level >= 8) {
                            level = 10;
                            break;
                        } else if (level == 10) {
                            break;
                        }
                    default:
                        break;
                }
            }         
        }
    }
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
}

