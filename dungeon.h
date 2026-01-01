#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <memory>
#include <random>
#include <string>
#include <vector>

#include "enemy_factory.h"
#include "room.h"

class Dungeon {
 public:
  Dungeon(const std::string& name, int num_rooms, int gold_reward,
          bool has_boss);

  void GenerateRooms();

  const std::vector<std::shared_ptr<Room>>& GetRooms() const;

  const std::string& GetName() const;
  int GetGoldReward() const;
  bool HasBoss() const;

 private:
  std::string name_;
  int num_rooms_;
  int gold_reward_;
  bool has_boss_;
  std::vector<std::shared_ptr<Room>> rooms_;
};

#endif
