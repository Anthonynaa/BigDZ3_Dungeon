#ifndef HERO_FACTORY_H_
#define HERO_FACTORY_H_

#include <memory>

#include "hero.h"

class HeroFactory {
 public:
  static std::shared_ptr<Hero> CreateRandomHero();

  static std::shared_ptr<Hero> CreateRandomHero(int level);
};

#endif
