#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
protected:
    GuesserTest() {}           // Constructor runs before each test
    virtual ~GuesserTest() {}  // Destructor cleans up after tests
    virtual void SetUp() {}    // Sets up before each test (after constructor)
    virtual void TearDown() {} // Clean up after each test, (before destructor)
};

TEST(GuesserTest, guess_matches_secret)
{
    Guesser guesser("secret");
    ASSERT_TRUE(guesser.match("secret"));
}

TEST(GuesserTest, guess_does_not_match_secret)
{
    Guesser guesser("secret");
    ASSERT_FALSE(guesser.match("secr3t"));
}

TEST(GuesserTest, incorrect_guess_two_attempts)
{
    Guesser guesser("secret");
    guesser.match("secr3t");
    ASSERT_FALSE(guesser.match("secr3t"));
}

TEST(GuesserTest, incorrect_guess_three_attempts)
{
    Guesser guesser("secret");
    guesser.match("secr3t");
    guesser.match("secr3t");
    ASSERT_FALSE(guesser.match("secr3t"));
}

TEST(GuesserTest, guess_exceeds_max_length)
{
    Guesser guesser("secret");
    ASSERT_FALSE(guesser.match("guess_that_exceeds_max_length"));
}

TEST(GuesserTest, remaining_guesses_after_one_attempt)
{
    Guesser guesser("secret");
    guesser.match("wrong_guess");
    ASSERT_EQ(guesser.remaining(), 2);
}

TEST(GuesserTest, remaining_guesses_after_two_attempt)
{
    Guesser guesser("secret");
    guesser.match("wrong_guess1");
    guesser.match("wrong_guess2");
    ASSERT_EQ(guesser.remaining(), 1);
}

TEST(GuesserTest, remaining_guesses_after_three_attempts)
{
    Guesser guesser("secret");
    guesser.match("wrong_guess1");
    guesser.match("wrong_guess2");
    guesser.match("wrong_guess3");
    ASSERT_EQ(guesser.remaining(), 0);
}

TEST(GuesserTest, remaining_guesses_after_three_attempts_then_false)
{
    Guesser guesser("secret");
    guesser.match("wrong_guess1");
    guesser.match("wrong_guess2");
    guesser.match("wrong_guess3");
    guesser.match("wrong_guess4");
    ASSERT_EQ(guesser.remaining(), 0);
}

TEST(GuesserTest, remaining_guesses_after_three_attempts_then_correct)
{
    Guesser guesser("secret");
    guesser.match("wrong_guess1");
    guesser.match("wrong_guess2");
    guesser.match("wrong_guess3");
    guesser.match("secret");
    ASSERT_EQ(guesser.remaining(), 0);
}

TEST(GuesserTest, remaining_guesses_after_one_successful_attempt)
{
    Guesser guesser("secret");
    guesser.match("secret");
    ASSERT_EQ(guesser.remaining(), 3);
}

TEST(GuesserTest, incorrect_guess_2_characters)
{
    Guesser guesser("se");
    ASSERT_FALSE(guesser.match("es"));
}

TEST(GuesserTest, correct_guess_2_characters)
{
    Guesser guesser("se");
    ASSERT_TRUE(guesser.match("se"));
}

TEST(GuesserTest, incorrect_guess_1_characters)
{
    Guesser guesser("s");
    ASSERT_FALSE(guesser.match("e"));
}

TEST(GuesserTest, correct_guess_1_characters)
{
    Guesser guesser("s");
    ASSERT_TRUE(guesser.match("s"));
}

TEST(GuesserTest, incorrect_guess_0_characters)
{
    Guesser guesser("");
    ASSERT_FALSE(guesser.match("e"));
}

TEST(GuesserTest, correct_guess_0_characters)
{
    Guesser guesser("");
    ASSERT_TRUE(guesser.match(""));
}

TEST(GuesserTest, proper_truncate)
{
    Guesser guesser("abcdefghijklmnopqrstuvwxyz1234567890");
    ASSERT_TRUE(guesser.match("abcdefghijklmnopqrstuvwxyz12345"));
}

TEST(GuesserTest, proper_truncate_incorrect_match)
{
    Guesser guesser("abcdefghijklmnopqrstuvwxyz1234567890");
    ASSERT_FALSE(guesser.match("abcdefghijklmnopqrstuvwxyz1234567890"));
}

TEST(GuesserTest, constructor_initializes_remaining)
{
    Guesser guesser("secret");
    ASSERT_EQ(guesser.remaining(), 3);
}

TEST(GuesserTest, correct_guesses_reset_remaining)
{
    Guesser guesser("secret");
    guesser.match("secr3t");
    guesser.match("secret");
    ASSERT_EQ(guesser.remaining(), 3);
}
