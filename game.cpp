#include "game.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

Game::Game() : gold_(kStartingGold) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  recruit_list_.clear();
  party_.clear();
}

static void IgnoreRemainingInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::Run() {
  bool exit_game = false;
  while (!exit_game) {
    ShowMainMenu();

    int choice = 0;
    if (!(std::cin >> choice)) {
      std::cout << "Invalid input.\n";
      IgnoreRemainingInput();
      continue;
    }

    switch (choice) {
      case 1:
        ShowRecruitMenu();
        break;
      case 2:
        ShowPartyMenu();
        break;
      case 3:
        HealHeroes();
        break;
      case 4:
        ShowDungeonMenu();
        break;
      case 5:
        exit_game = true;
        break;
      default:
        std::cout << "Invalid option.\n";
        break;
    }

    if (IsGameOver()) {
      std::cout << "Game Over! You have no heroes and insufficient gold.\n";
      break;
    }
    if (HasWon()) {
      std::cout << "Congratulations! You defeated the Dragon!\n";
      break;
    }
  }
}

void Game::ShowMainMenu() {
  std::cout << "\n=== Main Menu ===\n";
  std::cout << "Gold: " << gold_ << "\n";
  std::cout << "1. Recruit Heroes\n";
  std::cout << "2. Manage Party\n";
  std::cout << "3. Heal Heroes (" << kHealCost << " gold per hero)\n";
  std::cout << "4. Choose Dungeon\n";
  std::cout << "5. Exit\n";
  std::cout << "Choose an option: ";
}

void Game::ShowRecruitMenu() {
  std::cout << "\n=== Recruit Menu ===\n";

  if (recruit_list_.empty()) {
    RefreshRecruitList();
  }

  for (size_t i = 0; i < recruit_list_.size(); ++i) {
    auto& hero = recruit_list_[i];
    std::cout << i + 1 << ". " << hero->GetName() << " (Level "
              << hero->GetLevel() << ", Role: ";
    switch (hero->GetRole()) {
      case HeroRole::WARRIOR:
        std::cout << "Warrior";
        break;
      case HeroRole::MAGE:
        std::cout << "Mage";
        break;
      case HeroRole::ARCHER:
        std::cout << "Archer";
        break;
      case HeroRole::CLERIC:
        std::cout << "Cleric";
        break;
    }
    std::cout << ", Attack: " << hero->DealDamage()
              << ", HP: " << hero->GetCurrentHp()
              << ", MP: " << hero->GetCurrentMp() << ")\n";
  }

  std::cout << recruit_list_.size() + 1 << ". Refresh List ("
            << kRefreshRecruitCost << " gold)\n";
  std::cout << recruit_list_.size() + 2 << ". Return to Main Menu\n";

  int choice = 0;
  if (!(std::cin >> choice)) {
    std::cout << "Invalid input.\n";
    IgnoreRemainingInput();
    return;
  }

  if (choice >= 1 && choice <= static_cast<int>(recruit_list_.size())) {
    int idx = choice - 1;
    if (party_.size() >= static_cast<size_t>(kMaxPartySize)) {
      std::cout << "Party is full! Dismiss a hero first.\n";
      return;
    }
    if (gold_ < kRecruitCost) {
      std::cout << "Not enough gold to recruit.\n";
      return;
    }
    party_.push_back(recruit_list_[idx]);
    gold_ -= kRecruitCost;
    std::cout << recruit_list_[idx]->GetName() << " has been recruited!\n";
    recruit_list_.erase(recruit_list_.begin() + idx);
  } else if (choice == static_cast<int>(recruit_list_.size()) + 1) {
    RefreshRecruitList();
  } else {
  }
}

void Game::RecruitHero() {}

void Game::RefreshRecruitList() {
  if (!recruit_list_.empty() && gold_ < kRefreshRecruitCost) {
    std::cout << "Not enough gold to refresh.\n";
    return;
  }

  if (!recruit_list_.empty()) {
    gold_ -= kRefreshRecruitCost;
  }

  recruit_list_.clear();
  for (int i = 0; i < kMaxPartySize; ++i) {
    recruit_list_.push_back(HeroFactory::CreateRandomHero());
  }
  std::cout << "Recruit list refreshed.\n";
}

void Game::ShowPartyMenu() {
  std::cout << "\n=== Party Menu ===\n";
  if (party_.empty()) {
    std::cout << "Your party is empty.\n";
    return;
  }

  for (size_t i = 0; i < party_.size(); ++i) {
    auto& hero = party_[i];
    std::cout << i + 1 << ". " << hero->GetName() << " (Level "
              << hero->GetLevel() << ", HP: " << hero->GetCurrentHp()
              << ", MP: " << hero->GetCurrentMp() << ")\n";
  }

  std::cout << party_.size() + 1 << ". Dismiss a Hero\n";
  std::cout << party_.size() + 2 << ". Return to Main Menu\n";

  int choice = 0;
  if (!(std::cin >> choice)) {
    std::cout << "Invalid input.\n";
    IgnoreRemainingInput();
    return;
  }

  if (choice == static_cast<int>(party_.size()) + 1) {
    DismissHero();
  }
}

void Game::DismissHero() {
  if (party_.empty()) {
    std::cout << "No heroes to dismiss.\n";
    return;
  }

  int choice = 0;
  std::cout << "Choose a hero to dismiss (1-" << party_.size() << "): ";
  if (!(std::cin >> choice)) {
    std::cout << "Invalid input.\n";
    IgnoreRemainingInput();
    return;
  }

  if (choice < 1 || choice > static_cast<int>(party_.size())) {
    std::cout << "Invalid selection.\n";
    return;
  }

  std::cout << party_[choice - 1]->GetName() << " has been dismissed.\n";
  party_.erase(party_.begin() + (choice - 1));
}

void Game::HealHeroes() {
  if (party_.empty()) {
    std::cout << "No heroes to heal.\n";
    return;
  }

  for (auto& hero : party_) {
    if (gold_ < kHealCost) {
      std::cout << "Not enough gold to heal.\n";
      return;
    }
    hero->RestoreHp(hero->GetMaxHp());
    hero->RestoreMp(hero->GetMaxMp());
    gold_ -= kHealCost;
  }
  std::cout << "All heroes have been healed.\n";
}

void Game::ShowDungeonMenu() {
  std::cout << "\n=== Dungeon Menu ===\n";
  std::vector<std::shared_ptr<Dungeon>> dungeons;

  dungeons.push_back(std::make_shared<Dungeon>("Goblin Cave", 2, 200, false));
  dungeons.push_back(std::make_shared<Dungeon>("Magic Forest", 3, 350, false));
  dungeons.push_back(std::make_shared<Dungeon>("Undead Castle", 4, 500, false));
  dungeons.push_back(
      std::make_shared<Dungeon>("Temple of Darkness", 4, 650, false));
  dungeons.push_back(std::make_shared<Dungeon>("Dragon's Lair", 5, 1000, true));

  for (size_t i = 0; i < dungeons.size(); ++i) {
    std::cout << i + 1 << ". " << dungeons[i]->GetName()
              << " (Reward: " << dungeons[i]->GetGoldReward() << " gold)\n";
  }

  std::cout << dungeons.size() + 1 << ". Return to Main Menu\n";

  int choice = 0;
  if (!(std::cin >> choice)) {
    std::cout << "Invalid input.\n";
    IgnoreRemainingInput();
    return;
  }

  if (choice >= 1 && choice <= static_cast<int>(dungeons.size())) {
    EnterDungeon(dungeons[choice - 1]);
  }
}

void Game::EnterDungeon(std::shared_ptr<Dungeon> dungeon) {
  if (party_.empty()) {
    std::cout << "You have no heroes to enter the dungeon.\n";
    return;
  }

  dungeon->GenerateRooms();
  const auto& rooms = dungeon->GetRooms();

  for (size_t i = 0; i < rooms.size(); ++i) {
    auto& room = rooms[i];
    std::cout << "\nEntering room " << (i + 1) << ": " << room->GetName()
              << "\n";
    std::cout << room->GetDescription() << "\n";

    if (room->GetType() == RoomType::kEnemies) {
      std::vector<std::shared_ptr<Hero>> party_copy = party_;
      std::vector<std::shared_ptr<Room>> single_room = {room};
      Battle battle(std::move(party_copy), single_room);
      battle.StartBattle();

      party_.erase(std::remove_if(party_.begin(), party_.end(),
                                  [](const std::shared_ptr<Hero>& h) {
                                    return !h->IsAlive();
                                  }),
                   party_.end());

      if (party_.empty()) {
        std::cout << "Your party was wiped. Returning to guild.\n";
        return;
      }
    } else if (room->GetType() == RoomType::kChest) {
      constexpr int kChestMin = 50;
      constexpr int kChestMax = 100;
      int gained = kChestMin + (std::rand() % (kChestMax - kChestMin + 1));
      gold_ += gained;
      std::cout << "You found a chest and gained " << gained << " gold.\n";
    } else {
      std::cout << "The room is empty.\n";
    }
  }

  gold_ += dungeon->GetGoldReward();
  std::cout << "Dungeon cleared! You received " << dungeon->GetGoldReward()
            << " gold reward.\n";
}

bool Game::IsGameOver() const { return party_.empty() && gold_ < kRecruitCost; }

bool Game::HasWon() const { return false; }
