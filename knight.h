#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
int digitsCount(string txt);
bool check_prime(int n);
int levelO_cal(int i);
int dmg_cal(int levelO, int opponentCode);
int maxLevel_check(int level);
void BowserGG(int & rescue);
void easyOpponents(int i, int & level, int & HP, int & maxHP, int & phoenixdown, int & rescue, int opponentCode);
void ShamanWitch(int i, int & level, int & HP, int & maxHP, int & phoenixdown, int & remedy, int & rescue, int opponentCode, int & ShamanExpiry);
void ShamanExpiryCheck(int i, int & HP, int & maxHP, int & ShamanExpiry);
void SirenVajsh(int i, int & level, int & HP, int & maxHP, int & phoenixdown, int & remedy, int & maidenkiss, int & rescue, int opponentCode, int & SirenVajshExpiry, int & beforeFrog);
void SirenVajshExpiryCheck(int i, int & level, int & SirenVajshExpiry, int & beforeFrog);
void MushMario(int & HP, int & maxHP, int & level, int & phoenixdown);
void MushFibo(int & HP);
void remedyUse(int & HP, int & maxHP);
void remedyPick(int & remedy);
void maidenkissUse(int & level, int & beforeFrog);
void maidenkissPick(int & maidenkiss);
void phoenixdownPick(int & phoenixdown);
void Merlin(string pack_name, int & HP, int & maxHP);
void asclepius(string pack_name, int & HP, int & maxHP, int & remedy, int & maidenkiss, int & phoenixdown);


#endif // __KNIGHT_H__