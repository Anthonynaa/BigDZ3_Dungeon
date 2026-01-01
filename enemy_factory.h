#ifndef ENEMY_FACTORY_H_
#define ENEMY_FACTORY_H_

#include <memory>
#include <string>

#include "enemy.h"

class EnemyFactory {
 public:
  static std::shared_ptr<Enemy> CreateRandomEnemy(int dungeon_level);

  static std::shared_ptr<Enemy> CreateBossEnemy();
};

#endif
