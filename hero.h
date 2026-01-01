#ifndef HERO_H_
#define HERO_H_

#include <string>

#include "creature.h"

enum class HeroRole { WARRIOR, MAGE, ARCHER, CLERIC };

class Hero : public Creature {
 public:
  Hero(const std::string& name, HeroRole role, int level, int max_hp,
       int max_mp, int attack, int defense);

  HeroRole GetRole() const;
  int GetLevel() const;

  int GetCurrentHp() const;
  int GetMaxHp() const;

  int GetCurrentMp() const;
  int GetMaxMp() const;

  int DealDamage() const override;

  bool CanUseAbility() const;
  void UseAbility();

  void RestoreHp(int amount);
  void RestoreMp(int amount);

 private:
  HeroRole role_;
  int level_;

  int max_mp_;
  int current_mp_;
};

#endif
