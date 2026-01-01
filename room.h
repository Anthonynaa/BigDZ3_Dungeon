#ifndef ROOM_H_
#define ROOM_H_

#include <memory>
#include <string>
#include <vector>

#include "enemy.h"

enum class RoomType { kEnemies, kChest, kEmpty };

class Room {
 public:
  Room(RoomType type, const std::string& name, const std::string& description);

  RoomType GetType() const;

  const std::string& GetName() const;
  const std::string& GetDescription() const;

  void SetEnemies(std::vector<std::shared_ptr<Enemy>> enemies);
  const std::vector<std::shared_ptr<Enemy>>& GetEnemies() const;

 private:
  RoomType type_;
  std::string name_;
  std::string description_;
  std::vector<std::shared_ptr<Enemy>> enemies_;
};

#endif
