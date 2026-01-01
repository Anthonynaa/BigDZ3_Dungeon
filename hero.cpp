#include "hero.h"

#include <algorithm>

Hero::Hero(const std::string& name, HeroRole role, int level, int max_hp,
           int max_mp, int attack, int defense)
    : Creature(name, max_hp, attack, defense),
      role_(role),
      level_(level),
      max_mp_(max_mp),
      current_mp_(max_mp) {}

HeroRole Hero::GetRole() const { return role_; }
int Hero::GetLevel() const { return level_; }

int Hero::GetCurrentHp() const { return GetHp(); }
int Hero::GetMaxHp() const { return max_hp_; }

int Hero::GetCurrentMp() const { return current_mp_; }
int Hero::GetMaxMp() const { return max_mp_; }

int Hero::DealDamage() const { return GetAttack(); }

bool Hero::CanUseAbility() const {
  int cost = 0;
  switch (role_) {
    case HeroRole::WARRIOR:
      cost = 10 + 2 * level_;
      break;
    case HeroRole::MAGE:
      cost = 15 + 3 * level_;
      break;
    case HeroRole::ARCHER:
      cost = 12 + 2 * level_;
      break;
    case HeroRole::CLERIC:
      cost = 20 + 3 * level_;
      break;
  }
  return current_mp_ >= cost;
}

void Hero::UseAbility() {
  if (!CanUseAbility()) return;

  int cost = 0;
  switch (role_) {
    case HeroRole::WARRIOR:
      cost = 10 + 2 * level_;
      break;
    case HeroRole::MAGE:
      cost = 15 + 3 * level_;
      break;
    case HeroRole::ARCHER:
      cost = 12 + 2 * level_;
      break;
    case HeroRole::CLERIC:
      cost = 20 + 3 * level_;
      break;
  }

  current_mp_ -= cost;
}

void Hero::RestoreHp(int amount) {
  if (amount <= 0 || !IsAlive()) return;
  hp_ = std::min(max_hp_, hp_ + amount);
}

void Hero::RestoreMp(int amount) {
  if (amount <= 0) return;
  current_mp_ = std::min(max_mp_, current_mp_ + amount);
}
