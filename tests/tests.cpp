#include <gtest/gtest.h>

#include "../src/main.h"

TEST(RuleCheck, ConstructorCheck) {
  Rule r1("A->kEEk");
  Rule r2("L->xDDQ");
  Rule r3("B->");

  ASSERT_EQ(r1.left, 'A');
  ASSERT_EQ(r1.right, "kEEk");
  ASSERT_EQ(r2.left, 'L');
  ASSERT_EQ(r2.right, "xDDQ");
  ASSERT_EQ(r3.left, 'B');
  ASSERT_EQ(r3.right, "");
}

TEST(EarleyCheck, CorrectBracketSequences) {
  std::unordered_set<char> nonterm_pool = {'S'};
  std::unordered_set<char> term_pool = {'(', ')', '[', ']'};
  std::vector<Rule> rules_pool = {Rule("S->(S)"), Rule("S->[S]"), Rule("S->SS"),
                                  Rule("S->")};
  char start_nonterminal = 'S';

  std::vector<std::string> queries = {"",         "([])", "()()",  "()[]",
                                      "()[([])]", ")",    "()()]", "([)]"};
  Input data{nonterm_pool.size(), term_pool.size(), rules_pool.size(),
             nonterm_pool,        term_pool,        rules_pool,
             start_nonterminal,   queries.size(),   queries};

  auto answers = ReceiveAnswers(data);
  std::vector<std::string> expected_answers = {"YES", "YES", "YES", "YES",
                                               "YES", "NO",  "NO",  "NO"};
  ASSERT_EQ(answers, expected_answers);
}

TEST(EarleyCheck, SomeGrammar) {  // w = a^i b^j c^k : i <= j + k
  std::unordered_set<char> nonterm_pool = {'X', 'S'};
  std::unordered_set<char> term_pool = {'a', 'b', 'c'};
  std::vector<Rule> rules_pool = {Rule("S->aSc"), Rule("S->Sc"), Rule("S->X"),
                                  Rule("X->aXb"), Rule("X->Xb"), Rule("X->")};
  char start_nonterminal = 'S';
  std::vector<std::string> queries = {"",     "aab",   "bbccc", "cc",  "ac",
                                      "aabc", "aaacb", "ba",    "cabb"};
  Input data{nonterm_pool.size(), term_pool.size(), rules_pool.size(),
             nonterm_pool,        term_pool,        rules_pool,
             start_nonterminal,   queries.size(),   queries};

  auto answers = ReceiveAnswers(data);
  std::vector<std::string> expected_answers = {"YES", "NO", "YES", "YES", "YES",
                                               "YES", "NO", "NO",  "NO"};
  ASSERT_EQ(answers, expected_answers);
}