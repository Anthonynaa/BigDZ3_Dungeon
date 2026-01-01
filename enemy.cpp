#include "enemy.h"

Enemy::Enemy(const std::string& name, int max_hp, int attack, int defense,
             int gold_reward, bool is_boss)
    : Creature(name, max_hp, attack, defense),
      gold_reward_(gold_reward),
      is_boss_(is_boss) {}

int Enemy::DealDamage() const { return GetAttack(); }

int Enemy::GetGoldReward() const { return gold_reward_; }

bool Enemy::IsBoss() const { return is_boss_; }
