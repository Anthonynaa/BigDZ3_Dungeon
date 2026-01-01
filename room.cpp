#include "room.h"

Room::Room(RoomType type, const std::string& name,
           const std::string& description)
    : type_(type), name_(name), description_(description) {}

RoomType Room::GetType() const { return type_; }

const std::string& Room::GetName() const { return name_; }

const std::string& Room::GetDescription() const { return description_; }

void Room::SetEnemies(std::vector<std::shared_ptr<Enemy>> enemies) {
  enemies_ = std::move(enemies);
}

const std::vector<std::shared_ptr<Enemy>>& Room::GetEnemies() const {
  return enemies_;
}
