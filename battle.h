#ifndef BATTLE_H_
#define BATTLE_H_

#include <memory>
#include <vector>

#include "enemy.h"
#include "hero.h"
#include "room.h"

class Battle {
 public:
  Battle(std::vector<std::shared_ptr<Hero>> heroes,
         const std::vector<std::shared_ptr<Room>>& rooms);

  void StartBattle();

 private:
  void SetupEnemies(const std::vector<std::shared_ptr<Room>>& rooms);
  void HeroTurn(const std::shared_ptr<Hero>& hero);
  void EnemyTurn(const std::shared_ptr<Enemy>& enemy);

  bool AllHeroesDead() const;
  bool AllEnemiesDead() const;

  std::vector<std::shared_ptr<Hero>> heroes_;
  std::vector<std::shared_ptr<Enemy>> enemies_;
};

#endif
