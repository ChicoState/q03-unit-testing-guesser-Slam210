#include "Guesser.h"
#include <string>
#include <algorithm>

using namespace std;

/*
  Returns an whole number representing the distance between the guess,
  provided as an argument, and the secret. The distance represents the number
  of characters that would have to be changed at the same location to match
  the other string. When the two strings are identical, the distance is 0,
  but for each letter different, the distance increases by 1. When the
  strings are different lengths, each of the extra characters in the longer
  string also counts as an increase in 1 to the distance, up to the length of
  the secret; in other words, if m_secret has a 10 characters and the guess
  has 100, the distance is 10.
*/
unsigned int Guesser::distance(string guess)
{
    size_t len = min(guess.length(), m_secret.length());
    unsigned int dist = 0;

    // Calculate the distance
    for (size_t i = 0; i < len; ++i)
    {
        if (guess[i] != m_secret[i])
        {
            ++dist;
        }
    }

    // Account for extra characters in the longer string
    dist += abs(int(guess.length()) - int(m_secret.length()));

    // If total is greater than length of secret return length of secret
    if (dist > m_secret.length())
    {
        return m_secret.length();
    }

    return dist;
}

/*
  Constructor requires that the secret phrase is provided its value as
  an argument. This secret will not change for the lifespan of an instance
  of any Guesser object and must have a length of 32 characters or less,
  otherwise, it will be truncated at that length.
*/
Guesser::Guesser(string secret)
{
    // Truncate the secret phrase if its length exceeds 32 characters
    m_secret = secret.substr(0, 31);
    m_remaining = 3; // Initialize remaining guesses to 3
}

/*
  Determines and returns whether the provided guess matches the secret
  phrase. However, the function also returns false if the secret is locked,
  which happens if either (or both):
    (A) there are no remaining guesses allowed
    (B) the function detects brute force, as indicated by a guess that has a
        distance greater than 2 from the secret
  See the remaining() and distance() functions for specifications regarding
  determining how many guesses are remaining and the distance between a guess
  and the secret.
*/

// Guess is absurdly off return false but have remaining act as normal
// Guess 3 times but have it wrong, remaining stays at 0 and locks the user out
// Guess correctly, reset remaining to 3
bool Guesser::match(string guess)
{
    // Check if the secret is locked
    if (m_remaining == 0)
    {
        return false; // Secret is locked, no more guesses allowed
    }

    size_t len = m_secret.length();

    // Check for strings with 2 or less characters
    if (len <= 2)
    {
        if (m_secret != guess)
        {
            return false;
        }
        return true;
    }

    // Check if guess is brute force
    if (distance(guess) > 2)
    {
        --m_remaining; // Decrement remaining guesses
        return false;  // Guess is brute force
    }

    // Check if the guess matches the secret phrase
    if (guess == m_secret)
    {
        m_remaining = 3; // Reset remaining guesses
        return true;     // Match found
    }

    --m_remaining; // Incorrect guess so decrement remaining guesses

    return false; // No match found
}

/*
  Returns the number of guesses remaining. A Guesser object allows up to
  three (3) consecutive guesses without a match. If three guesses are made
  without any being a true match, the secret is locked. However, whenever
  an unlocked secret is guessed with a true match, the guesses remaining
  reset to three (3).
*/

unsigned int Guesser::remaining()
{
    return m_remaining;
}
