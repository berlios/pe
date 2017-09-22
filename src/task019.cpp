#include "base/task.h"
#include "gtest/gtest.h"

enum DayOfWeek {
  Monday = 1,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
  Sunday
};

enum Month {
  January = 1,
  February,
  March,
  April,
  May,
  June,
  July,
  August,
  September,
  October,
  November,
  December
};

static Month NextMonth(Month month) {
  switch (month) {
    case January: {
      return February;
    }
    case February: {
      return March;
    }
    case March: {
      return April;
    }
    case April: {
      return May;
    }
    case May: {
      return June;
    }
    case June: {
      return July;
    }
    case July: {
      return August;
    }
    case August: {
      return September;
    }
    case September: {
      return October;
    }
    case October: {
      return November;
    }
    case November: {
      return December;
    }
    case December: {
      return January;
    }
  }
}

class Date {
public:
  Date(int year, Month month, int day)
      : year_(year),
        month_(month),
        day_(day),
        is_valid_(false) {
    if ((day_ >= 1) && (day_ <= DaysIn(month_, IsLeapYear(year_)))) {
      is_valid_ = true;
    }
  }

  bool IsValid() const {
    return is_valid_;
  }

  void AddDays(int number_of_days) {
    if (!IsValid()) {
      return;
    }
    while (number_of_days > 0) {
      if (day_ + number_of_days > DaysIn(month_, IsLeapYear(year_))) {
        number_of_days -= DaysIn(month_, IsLeapYear(year_)) - day_ + 1;
        day_ = 1;

        month_ = NextMonth(month_);
        if (month_ == January) {
          year_++;
        }
      } else {
        day_ += number_of_days;
        break;
      }
    }
  }

  DayOfWeek DayOfWeek() const {
    int magic_month_numbers[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int corrected_year = year_ - (month_ < 3);
    int result =
        (corrected_year + corrected_year / 4 - corrected_year / 100 +
         corrected_year / 400 + magic_month_numbers[month_ - 1] + day_) % 7;

    enum DayOfWeek days[7] = {Monday, Tuesday,  Wednesday, Thursday,
                              Friday, Saturday, Sunday};
    return days[(result + 6) % 7];
  }

  static bool IsLeapYear(int year) {
    if ((year % 400) == 0) {
      return true;
    }

    if ((year % 4) == 0 && (year % 100) != 0) {
      return true;
    }

    return false;
  }

  bool operator==(const Date &date) const {
    return ((year_ == date.year_) && (month_ == date.month_) &&
            (day_ == date.day_));
  }

  static int DaysIn(Month month, bool is_leap_year) {
    switch (month) {
      case January:
      case March:
      case May:
      case July:
      case August:
      case October:
      case December: {
        return 31;
      }

      case April:
      case June:
      case September:
      case November: {
        return 30;
      }
      case February: {
        if (is_leap_year) {
          return 29;
        } else {
          return 28;
        }
      }
    }
  }
private:
  int year_;
  Month month_;
  int day_;
  bool is_valid_;
};

TEST(Task19, LeapYear) {
  EXPECT_TRUE(Date::IsLeapYear(2004));
  EXPECT_FALSE(Date::IsLeapYear(2001));
  EXPECT_TRUE(Date::IsLeapYear(2000));
  EXPECT_FALSE(Date::IsLeapYear(1700));
  EXPECT_FALSE(Date::IsLeapYear(1800));
  EXPECT_TRUE(Date::IsLeapYear(1600));
}

TEST(Task19, DaysInVariousMonths) {
  EXPECT_EQ(31, Date::DaysIn(January, true));
  EXPECT_EQ(28, Date::DaysIn(February, false));
  EXPECT_EQ(29, Date::DaysIn(February, true));
  EXPECT_EQ(31, Date::DaysIn(March, true));
  EXPECT_EQ(30, Date::DaysIn(April, true));
  EXPECT_EQ(31, Date::DaysIn(May, true));
  EXPECT_EQ(30, Date::DaysIn(June, true));
  EXPECT_EQ(31, Date::DaysIn(July, true));
  EXPECT_EQ(31, Date::DaysIn(August, true));
  EXPECT_EQ(30, Date::DaysIn(September, true));
  EXPECT_EQ(31, Date::DaysIn(October, true));
  EXPECT_EQ(30, Date::DaysIn(November, true));
  EXPECT_EQ(31, Date::DaysIn(December, true));
}

TEST(Task19, Dates) {
  Date date(1990, January, 1);
  EXPECT_TRUE(date.IsValid());
  EXPECT_EQ(Monday, date.DayOfWeek());

  date.AddDays(5);
  EXPECT_TRUE(date.IsValid());
  EXPECT_EQ(date, Date(1990, January, 6));
  EXPECT_EQ(Saturday, date.DayOfWeek());

  date.AddDays(500);
  EXPECT_TRUE(date.IsValid());
  EXPECT_EQ(date, Date(1991, May, 21));
  EXPECT_EQ(Tuesday, date.DayOfWeek());

  EXPECT_EQ(Monday, Date(1900, January, 1).DayOfWeek());
  EXPECT_EQ(Sunday, Date(1988, May, 1).DayOfWeek());
}

TASK(19) {
  Month months[12] = {January, February, March, April, May, June,
                      July, August, September, October, November, December};
  int r = 0;
  for (int year = 1901; year <= 2000; ++year) {
    for (int month = 0; month < 12; ++month) {
      r += (Date(year, months[month], 1).DayOfWeek() == Sunday);
    }
  }

  return r;
}
