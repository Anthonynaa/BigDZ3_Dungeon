#include "enemy_factory.h"

#include <cstdlib>
#include <vector>

namespace {

constexpr int kBaseHp = 50;
constexpr int kHpPerLevel = 30;

constexpr int kBaseAttack = 20;
constexpr int kAttackPerLevel = 10;

constexpr int kBaseDefense = 3;
constexpr int kDefensePerLevel = 2;

constexpr int kBaseGold = 50;
constexpr int kGoldPerLevel = 50;

const std::vector<std::string> kEnemyNames = {"Goblin", "Skeleton"};

}  // namespace

std::shared_ptr<Enemy> EnemyFactory::CreateRandomEnemy(int dungeon_level) {
  const int max_hp = kBaseHp + dungeon_level * kHpPerLevel;
  const int attack = kBaseAttack + dungeon_level * kAttackPerLevel;
  const int defense = kBaseDefense + dungeon_level * kDefensePerLevel;
  const int gold_reward = kBaseGold + dungeon_level * kGoldPerLevel;

  const std::string name = kEnemyNames[std::rand() % kEnemyNames.size()];

  return std::make_shared<Enemy>(name, max_hp, attack, defense, gold_reward,
                                 false);
}

std::shared_ptr<Enemy> EnemyFactory::CreateBossEnemy() {
  constexpr int kBossHp = 500;
  constexpr int kBossAttack = 50;
  constexpr int kBossDefense = 20;
  constexpr int kBossGold = 1000;

  return std::make_shared<Enemy>("Dragon", kBossHp, kBossAttack, kBossDefense,
                                 kBossGold, true);
}
