#include "hero_factory.h"

#include <cstdlib>
#include <vector>

std::shared_ptr<Hero> HeroFactory::CreateRandomHero() {
  int level = 1 + (std::rand() % 5);
  return CreateRandomHero(level);
}

std::shared_ptr<Hero> HeroFactory::CreateRandomHero(int level) {
  HeroRole role = static_cast<HeroRole>(std::rand() % 4);

  const std::vector<std::string> names = {"Aragon", "Luna", "Eldon", "Mira"};
  std::string name = names[std::rand() % names.size()];

  int max_hp = 100 + level * 20;
  int max_mp = 50 + level * 10;
  int attack = 10 + level * 5;
  int defense = 5 + level * 3;

  return std::make_shared<Hero>(name, role, level, max_hp, max_mp, attack,
                                defense);
}
