#include "creature.h"

#include <algorithm>

Creature::Creature(const std::string& name, int max_hp, int attack, int defense)
    : name_(name),
      max_hp_(max_hp),
      hp_(max_hp),
      attack_(attack),
      defense_(defense),
      defense_multiplier_(1.0) {}

void Creature::TakeDamage(int damage) {
  if (damage <= 0) {
    return;
  }

  const int effective_defense =
      static_cast<int>(defense_ * defense_multiplier_);

  const int reduced_damage = std::max(0, damage - effective_defense);

  hp_ = std::max(0, hp_ - reduced_damage);
}

bool Creature::IsAlive() const { return hp_ > 0; }

const std::string& Creature::GetName() const { return name_; }

int Creature::GetHp() const { return hp_; }

int Creature::GetAttack() const { return attack_; }

int Creature::GetDefense() const { return defense_; }

void Creature::SetDefenseMultiplier(double multiplier) {
  defense_multiplier_ = multiplier;
}

void Creature::ResetDefenseMultiplier() { defense_multiplier_ = 1.0; }
