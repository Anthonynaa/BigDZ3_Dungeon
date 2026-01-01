#ifndef ENEMY_H_
#define ENEMY_H_

#include <string>

#include "creature.h"

class Enemy : public Creature {
 public:
  Enemy(const std::string& name, int max_hp, int attack, int defense,
        int gold_reward, bool is_boss);

  int DealDamage() const override;

  int GetGoldReward() const;
  bool IsBoss() const;

 private:
  int gold_reward_;
  bool is_boss_;
};

#endif
