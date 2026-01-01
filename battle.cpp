#include "battle.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

namespace {
int ReadIntSafe() {
  int value;
  while (!(std::cin >> value)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter a number: ";
  }
  return value;
}
}  // namespace

Battle::Battle(std::vector<std::shared_ptr<Hero>> heroes,
               const std::vector<std::shared_ptr<Room>>& rooms)
    : heroes_(std::move(heroes)) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  SetupEnemies(rooms);
}

void Battle::SetupEnemies(const std::vector<std::shared_ptr<Room>>& rooms) {
  enemies_.clear();
  for (const auto& room : rooms) {
    for (const auto& enemy : room->GetEnemies()) {
      enemies_.push_back(enemy);
    }
  }
}

void Battle::StartBattle() {
  std::cout << "\n=== BATTLE START ===\n";

  while (!AllHeroesDead() && !AllEnemiesDead()) {
    // ===== HERO PHASE =====
    for (const auto& hero : heroes_) {
      if (!hero->IsAlive()) continue;
      if (AllEnemiesDead()) break;
      HeroTurn(hero);
    }

    // ===== REMOVE DEAD ENEMIES =====
    enemies_.erase(std::remove_if(enemies_.begin(), enemies_.end(),
                                  [](const std::shared_ptr<Enemy>& e) {
                                    return !e->IsAlive();
                                  }),
                   enemies_.end());

    if (AllEnemiesDead()) break;

    // ===== ENEMY PHASE =====
    for (const auto& enemy : enemies_) {
      if (!enemy->IsAlive()) continue;
      if (AllHeroesDead()) break;
      EnemyTurn(enemy);
    }

    // ===== REMOVE DEAD HEROES =====
    heroes_.erase(std::remove_if(heroes_.begin(), heroes_.end(),
                                 [](const std::shared_ptr<Hero>& h) {
                                   return !h->IsAlive();
                                 }),
                  heroes_.end());

    std::cout << "\n--- END OF ROUND ---\n";
  }

  if (AllHeroesDead()) {
    std::cout << "\nAll heroes have fallen...\n";
  } else {
    std::cout << "\nVictory! All enemies defeated!\n";
  }
}

void Battle::HeroTurn(const std::shared_ptr<Hero>& hero) {
  std::cout << "\n"
            << hero->GetName() << " | HP: " << hero->GetCurrentHp()
            << " | MP: " << hero->GetCurrentMp() << "\n";

  std::cout << "1. Attack\n2. Use Ability\n";
  int choice = ReadIntSafe();

  if (choice == 1) {
    std::cout << "Choose enemy:\n";
    for (size_t i = 0; i < enemies_.size(); ++i) {
      std::cout << i + 1 << ". " << enemies_[i]->GetName()
                << " (HP: " << enemies_[i]->GetHp() << ")\n";
    }

    int idx = ReadIntSafe() - 1;
    if (idx >= 0 && idx < static_cast<int>(enemies_.size())) {
      int dmg = hero->DealDamage();
      enemies_[idx]->TakeDamage(dmg);
      std::cout << hero->GetName() << " deals " << dmg << " damage to "
                << enemies_[idx]->GetName() << "\n";
    }
  } else if (choice == 2) {
    if (!hero->CanUseAbility()) {
      std::cout << "Not enough MP!\n";
      return;
    }

    hero->UseAbility();

    if (hero->GetRole() == HeroRole::CLERIC) {
      auto it = std::find_if(heroes_.begin(), heroes_.end(), [](const auto& h) {
        return h->IsAlive() && h->GetCurrentHp() < h->GetMaxHp();
      });
      if (it != heroes_.end()) {
        int heal = 30 + 8 * hero->GetLevel();
        (*it)->RestoreHp(heal);
        std::cout << (*it)->GetName() << " healed for " << heal << "\n";
      }
    }
  }
}

void Battle::EnemyTurn(const std::shared_ptr<Enemy>& enemy) {
  auto it = std::find_if(heroes_.begin(), heroes_.end(),
                         [](const auto& h) { return h->IsAlive(); });
  if (it == heroes_.end()) return;

  int dmg = enemy->DealDamage();
  (*it)->TakeDamage(dmg);

  std::cout << enemy->GetName() << " attacks " << (*it)->GetName() << " for "
            << dmg << " damage\n";
}

bool Battle::AllHeroesDead() const {
  return std::none_of(heroes_.begin(), heroes_.end(),
                      [](const auto& h) { return h->IsAlive(); });
}

bool Battle::AllEnemiesDead() const {
  return std::none_of(enemies_.begin(), enemies_.end(),
                      [](const auto& e) { return e->IsAlive(); });
}
