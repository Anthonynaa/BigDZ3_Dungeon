#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <string>
#include <vector>

#include "battle.h"
#include "dungeon.h"
#include "hero.h"
#include "hero_factory.h"

class Game {
 public:
  Game();

  void Run();

 private:
  void ShowMainMenu();

  void ShowRecruitMenu();
  void RecruitHero();
  void RefreshRecruitList();
  void DismissHero();

  void ShowPartyMenu();

  void HealHeroes();

  void ShowDungeonMenu();
  void EnterDungeon(std::shared_ptr<Dungeon> dungeon);

  bool IsGameOver() const;
  bool HasWon() const;

  int gold_;
  std::vector<std::shared_ptr<Hero>> party_;
  std::vector<std::shared_ptr<Hero>> recruit_list_;

  static constexpr int kMaxPartySize = 4;
  static constexpr int kRecruitCost = 100;
  static constexpr int kRefreshRecruitCost = 50;
  static constexpr int kHealCost = 50;
  static constexpr int kStartingGold = 250;
};

#endif
