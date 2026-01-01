#ifndef CREATURE_H_
#define CREATURE_H_

#include <string>

class Creature {
 public:
  Creature(const std::string& name, int max_hp, int attack, int defense);
  virtual ~Creature() = default;

  virtual void TakeDamage(int damage);
  virtual int DealDamage() const = 0;

  bool IsAlive() const;
  const std::string& GetName() const;

  int GetHp() const;
  int GetAttack() const;
  int GetDefense() const;

  void SetDefenseMultiplier(double multiplier);
  void ResetDefenseMultiplier();

 protected:
  std::string name_;
  int max_hp_;
  int hp_;
  int attack_;
  int defense_;

  double defense_multiplier_;
};

#endif
