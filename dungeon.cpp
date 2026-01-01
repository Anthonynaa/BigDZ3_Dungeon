#include "dungeon.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace {

constexpr int kMinEnemies = 1;
constexpr int kMaxEnemies = 3;

}  // namespace

Dungeon::Dungeon(const std::string& name, int num_rooms, int gold_reward,
                 bool has_boss)
    : name_(name),
      num_rooms_(num_rooms),
      gold_reward_(gold_reward),
      has_boss_(has_boss) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Dungeon::GenerateRooms() {
  rooms_.clear();

  for (int i = 0; i < num_rooms_; ++i) {
    RoomType type;

    int roll = std::rand() % 100;
    if (roll < 70) {
      type = RoomType::kEnemies;
    } else if (roll < 90) {
      type = RoomType::kChest;
    } else {
      type = RoomType::kEmpty;
    }

    std::string room_name;
    std::string room_desc;

    switch (type) {
      case RoomType::kEnemies:
        room_name = "Enemy Room";
        room_desc = "A group of monsters appears!";
        break;
      case RoomType::kChest:
        room_name = "Treasure Chest";
        room_desc = "You find a chest with gold or healing!";
        break;
      case RoomType::kEmpty:
        room_name = "Empty Room";
        room_desc = "Nothing happens here.";
        break;
    }

    auto room = std::make_shared<Room>(type, room_name, room_desc);

    if (type == RoomType::kEnemies) {
      std::vector<std::shared_ptr<Enemy>> enemies;

      int num_enemies =
          kMinEnemies + (std::rand() % (kMaxEnemies - kMinEnemies + 1));
      for (int j = 0; j < num_enemies; ++j) {
        auto enemy = EnemyFactory::CreateRandomEnemy(i + 1);
        enemies.push_back(std::move(enemy));
      }

      room->SetEnemies(std::move(enemies));
    }

    rooms_.push_back(std::move(room));
  }

  if (has_boss_ && !rooms_.empty()) {
    auto boss_room = std::make_shared<Room>(RoomType::kEnemies, "Boss Room",
                                            "A fearsome boss awaits!");

    std::vector<std::shared_ptr<Enemy>> boss;
    boss.push_back(EnemyFactory::CreateBossEnemy());
    boss_room->SetEnemies(std::move(boss));

    rooms_.back() = std::move(boss_room);
  }
}

const std::vector<std::shared_ptr<Room>>& Dungeon::GetRooms() const {
  return rooms_;
}

const std::string& Dungeon::GetName() const { return name_; }

int Dungeon::GetGoldReward() const { return gold_reward_; }

bool Dungeon::HasBoss() const { return has_boss_; }
