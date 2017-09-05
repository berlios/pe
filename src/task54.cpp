#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/task.h"
#include "gtest/gtest.h"

enum class Rank {
  HighCard,
  OnePair,
  TwoPairs,
  ThreeOfKind,
  Straight,
  Flush,
  FullHouse,
  FourOfKind,
  StraightFlush,
  RoyalFlush
};

enum class CardValue {
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Ace
};

enum class CardSuit {
  Hearts,
  Spades,
  Diamonds,
  Clubs
};

struct Card {
  CardValue value;
  CardSuit suit;
};

CardValue CharToValue(char c) {
  switch(c) {
    case '2': return CardValue::Two;
    case '3': return CardValue::Three;
    case '4': return CardValue::Four;
    case '5': return CardValue::Five;
    case '6': return CardValue::Six;
    case '7': return CardValue::Seven;
    case '8': return CardValue::Eight;
    case '9': return CardValue::Nine;
    case 'T': return CardValue::Ten;
    case 'J': return CardValue::Jack;
    case 'Q': return CardValue::Queen;
    case 'K': return CardValue::King;
    case 'A': return CardValue::Ace;
    default: NOT_IMPLEMENTED();
  }
}
CardSuit CharToSuit(char c) {
    switch(c) {
    case 'H': return CardSuit::Hearts;
    case 'S': return CardSuit::Spades;
    case 'D': return CardSuit::Diamonds;
    case 'C': return CardSuit::Clubs;
    default: NOT_IMPLEMENTED();
  }
}

class PokerHand {
 public:
   // We expect string in the format "8D 9S TD AS KC".
  PokerHand(const std::string& str) {
    if (str.size() != 14) {
      NOT_IMPLEMENTED();
    }

    cards_[0] = {CharToValue(str[0]), CharToSuit(str[1])};
    cards_[1] = {CharToValue(str[3]), CharToSuit(str[4])};
    cards_[2] = {CharToValue(str[6]), CharToSuit(str[7])};
    cards_[3] = {CharToValue(str[9]), CharToSuit(str[10])};
    cards_[4] = {CharToValue(str[12]), CharToSuit(str[13])};

    std::sort(cards_.begin(), cards_.end(),
              [](const Card& card1, const Card& card2) {
                return card1.value < card2.value;
              });
    CalculateRank();
  }
  bool operator<(const PokerHand& other) const {
    if (rank_ < other.rank_) {
      return true;
    }

    if (rank_ > other.rank_) {
      return false;
    }

    // Payload sizes better be the same.
    for (uint i = 0; i < payload_.size(); ++i) {
      if (payload_[i] < other.payload_[i]) {
        return true;
      }

      if (payload_[i] > other.payload_[i]) {
        return false;
      }
    }

    // We shouldn't reach here.
    return false;
  }

  bool operator>(const PokerHand& other) {
    return other < *this;
  }

  Rank rank() const {
    return rank_;
  }

  const std::array<Card, 5>& cards() const {
    return cards_;
  }
 private:
  void CalculateRank();

  std::array<Card, 5> cards_;

  Rank rank_;

  // payload_ is used to compare hands of equal rank.
  // The payload is compared lexicographically, that is, one element at a time
  // until elements differ.
  std::vector<int> payload_;
};

// To simplify code and logic the checkers below are inclusive.
// For example, a hand "4S 4D 4C 4H 6S" is considered having one pair,
// two pairs, three of a kind and four of a kind at the same time.
// The checks themselves, however, are performed top-down (from highest ranking
// combination to lowest) to find the first checker that accepts
// the combination.
class PokerCombinationCheckerInterface {
 public:
  virtual ~PokerCombinationCheckerInterface() {}

  // Cards are expected to be sorted according to value.
  virtual Rank GetRank() = 0;
  virtual std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) = 0;
};

class HighCardChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::HighCard;
  }

  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    return {true,
            {static_cast<int>(cards[4].value), static_cast<int>(cards[3].value),
             static_cast<int>(cards[2].value), static_cast<int>(cards[1].value),
             static_cast<int>(cards[0].value)}};
  }
};

class OnePairChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::OnePair;
  }
  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    if (cards[0].value == cards[1].value) {
      return {
          true,
          {static_cast<int>(cards[1].value), static_cast<int>(cards[4].value),
           static_cast<int>(cards[3].value), static_cast<int>(cards[2].value)}};
    }
    if (cards[1].value == cards[2].value) {
      return {
          true,
          {static_cast<int>(cards[2].value), static_cast<int>(cards[4].value),
           static_cast<int>(cards[3].value), static_cast<int>(cards[0].value)}};
    }
    if (cards[2].value == cards[3].value) {
      return {
          true,
          {static_cast<int>(cards[3].value), static_cast<int>(cards[4].value),
           static_cast<int>(cards[1].value), static_cast<int>(cards[0].value)}};
    }
    if (cards[3].value == cards[4].value) {
      return {
          true,
          {static_cast<int>(cards[4].value), static_cast<int>(cards[2].value),
           static_cast<int>(cards[1].value), static_cast<int>(cards[0].value)}};
    }

    return {false, {}};
  }
};

class TwoPairsChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::TwoPairs;
  }
  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    if (cards[0].value == cards[1].value && cards[2].value == cards[3].value) {
      return {
          true,
          {static_cast<int>(cards[3].value),
           static_cast<int>(cards[1].value),
           static_cast<int>(cards[4].value)}};
    }
    if (cards[0].value == cards[1].value && cards[3].value == cards[4].value) {
      return {
          true,
          {static_cast<int>(cards[4].value),
           static_cast<int>(cards[1].value),
           static_cast<int>(cards[2].value)}};
    }
    if (cards[1].value == cards[2].value && cards[3].value == cards[4].value) {
      return {
          true,
          {static_cast<int>(cards[4].value),
           static_cast<int>(cards[2].value),
           static_cast<int>(cards[0].value)}};
    }
    return {false, {}};
  }
};

class ThreeOfKindChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::ThreeOfKind;
  }
  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    if (cards[0].value == cards[1].value && cards[1].value == cards[2].value) {
      return {
          true,
          {static_cast<int>(cards[2].value), static_cast<int>(cards[4].value),
           static_cast<int>(cards[3].value)}};
    }
    if (cards[1].value == cards[2].value && cards[2].value == cards[3].value) {
      return {
          true,
          {static_cast<int>(cards[3].value), static_cast<int>(cards[4].value),
           static_cast<int>(cards[0].value)}};
    }
    if (cards[2].value == cards[3].value && cards[3].value == cards[4].value) {
      return {
          true,
          {static_cast<int>(cards[4].value), static_cast<int>(cards[1].value),
           static_cast<int>(cards[0].value)}};
    }
    return {false, {}};
  }
};

class StraightChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::Straight;
  }
  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    for (int i = 0; i < 4; ++i) {
      if (static_cast<int>(cards[i].value) + 1 !=
          static_cast<int>(cards[i + 1].value)) {
        return {false, {}};
      }
    }

    return {true, {static_cast<int>(cards[4].value)}};
  }
};

class FlushChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::Flush;
  }
  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    CardSuit suit = cards[0].suit;
    for (int i = 1; i < 5; ++i) {
      if (cards[i].suit != suit) {
        return {false, {}};
      }
    }

    return {true,
            {static_cast<int>(cards[4].value),
             static_cast<int>(cards[3].value),
             static_cast<int>(cards[2].value),
             static_cast<int>(cards[1].value),
             static_cast<int>(cards[0].value)}};

  }
};

class FullHouseChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::FullHouse;
  }
  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    if (cards[0].value == cards[1].value && cards[2].value == cards[3].value &&
        cards[3].value == cards[4].value) {
      return {true, {static_cast<int>(cards[4].value),
                     static_cast<int>(cards[1].value)}};
    }
    if (cards[0].value == cards[1].value && cards[1].value == cards[2].value &&
        cards[3].value == cards[4].value) {
      return {true, {static_cast<int>(cards[2].value),
                     static_cast<int>(cards[4].value)}};
    }
    return {false, {}};

  }
};

class FourOfKindChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::FourOfKind;
  }
  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    if (cards[0].value == cards[1].value && cards[1].value == cards[2].value &&
        cards[2].value == cards[3].value) {
      return {true, {static_cast<int>(cards[3].value),
                     static_cast<int>(cards[4].value)}};
    }
    if (cards[1].value == cards[2].value && cards[2].value == cards[3].value &&
        cards[3].value == cards[4].value) {
      return {true, {static_cast<int>(cards[4].value),
                     static_cast<int>(cards[0].value)}};
    }
    return {false, {}};

  }
};

class StraightFlushChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::StraightFlush;
  }
  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    StraightChecker s;
    FlushChecker f;

    auto result_straight = s.ScoreHand(cards);
    auto result_flush = f.ScoreHand(cards);

    if (result_straight.first && result_flush.first) {
      return {true, {static_cast<int>(cards[4].value)}};
    }

    return {false, {}};

  }
};

class RoyalFlushChecker : public PokerCombinationCheckerInterface {
 public:
  Rank GetRank() override {
    return Rank::RoyalFlush;
  }
  std::pair<bool, std::vector<int>> ScoreHand(
      const std::array<Card, 5>& cards) override {
    StraightChecker s;
    FlushChecker f;

    auto result_straight = s.ScoreHand(cards);
    auto result_flush = f.ScoreHand(cards);

    if (result_straight.first && result_flush.first &&
        cards[4].value == CardValue::Ace) {
      return {true, {}};
    }

    return {false, {}};

  }
};

void PokerHand::CalculateRank() {
  static const std::vector<std::unique_ptr<PokerCombinationCheckerInterface>>
      checks = []() {
        std::vector<std::unique_ptr<PokerCombinationCheckerInterface>> checks;
        checks.emplace_back(new RoyalFlushChecker);
        checks.emplace_back(new StraightFlushChecker);
        checks.emplace_back(new FourOfKindChecker);
        checks.emplace_back(new FullHouseChecker);
        checks.emplace_back(new FlushChecker);
        checks.emplace_back(new StraightChecker);
        checks.emplace_back(new ThreeOfKindChecker);
        checks.emplace_back(new TwoPairsChecker);
        checks.emplace_back(new OnePairChecker);
        checks.emplace_back(new HighCardChecker);
        return checks;
      }();

  for (const auto& checker : checks) {
    auto result = checker->ScoreHand(cards_);
    if (result.first) {
      rank_ = checker->GetRank();
      payload_ = std::move(result.second);
      break;
    }
  }
}

TEST(Poker, Test1) {
  // Pair of Fives.
  PokerHand hand_a("5H 5C 6S 7S KD");
  // Pair of Eights.
  PokerHand hand_b("2C 3S 8S 8D TD");

  EXPECT_EQ(Rank::OnePair, hand_a.rank());
  EXPECT_EQ(Rank::OnePair, hand_b.rank());
  EXPECT_TRUE(hand_a < hand_b);
}

TEST(Poker, Test2) {
  // Highest card Ace.
  PokerHand hand_a("5D 8C 9S JS AC");
  // Highest card Queen.
  PokerHand hand_b("2C 5C 7D 8S QH");

  EXPECT_EQ(Rank::HighCard, hand_a.rank());
  EXPECT_EQ(Rank::HighCard, hand_b.rank());
  EXPECT_TRUE(hand_a > hand_b);
}

TEST(Poker, Test3) {
  // Three Aces.
  PokerHand hand_a("2D 9C AS AH AC");
  // Flush with Diamonds.
  PokerHand hand_b("3D 6D 7D TD QD");

  EXPECT_EQ(Rank::ThreeOfKind, hand_a.rank());
  EXPECT_EQ(Rank::Flush, hand_b.rank());
  EXPECT_TRUE(hand_a < hand_b);
}

TEST(Poker, Test4) {
  // Pair of Queens, Highest card Nine.
  PokerHand hand_a("4D 6S 9H QH QC");
  // Pair of Queens, Highest card Seven.
  PokerHand hand_b("3D 6D 7H QD QS");

  EXPECT_EQ(Rank::OnePair, hand_a.rank());
  EXPECT_EQ(Rank::OnePair, hand_b.rank());
  EXPECT_TRUE(hand_a > hand_b);
}

TEST(Poker, Test5) {
  // Full House, With Three Fours.
  PokerHand hand_a("2H 2D 4C 4D 4S");
  // Full House, with Three Threes.
  PokerHand hand_b("3C 3D 3S 9S 9D");

  EXPECT_EQ(Rank::FullHouse, hand_a.rank());
  EXPECT_EQ(Rank::FullHouse, hand_b.rank());
  EXPECT_TRUE(hand_a > hand_b);
}

TASK(54) {
  std::ifstream file("data/054_poker.txt");

  std::string line;
  int counter = 0;
  while (std::getline(file, line)) {
    if (line.size() != 2 * 10 + 9) {
      NOT_IMPLEMENTED();
    }
    PokerHand hand_a(line.substr(0, 2 * 5 + 4));
    PokerHand hand_b(line.substr(2 * 5 + 5, 2 * 5 + 4));

    if (hand_a > hand_b) {
      ++counter;
    }
  }

  return counter;
}
