#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

struct Rule {
  std::string rule;
  std::string right;
  char left;

  Rule(const Rule& other) = default;
  Rule(std::string str) : rule(str) {
    char* rule = const_cast<char*>(str.c_str());
    left = strtok(rule, "-")[0];
    if (str[str.size() - 1] != '>') {
      right = strtok(NULL, ">");
    } else {
      right = "";
    }
  }
};

struct Input {
  int nonterm_cnt;
  int term_cnt;
  int rules_cnt;
  std::unordered_set<char> nonterm_pool;
  std::unordered_set<char> term_pool;
  std::vector<Rule> rules_pool;

  char nonterm_start;
  int queries_cnt;
  std::vector<std::string> queries;
};

class EarleyParser {
 public:
  EarleyParser(const Input& data)
      : nonterm_pool(data.nonterm_pool),
        term_pool(data.term_pool),
        rules_pool(data.rules_pool),
        nonterm_start(data.nonterm_start) {}

  bool IsInGrammar(const std::string& word) {
    level.resize(word.size() + 1);
    Rule fictional_rule(std::string{fictional_start} + "->" + nonterm_start);
    Situation add(fictional_rule, 0, 0);
    level[0].insert(add);

    for (size_t i = 0; i <= word.size(); ++i) {
      if (i != 0) {
        Scan(word[i - 1], i - 1);
      }

      int changing = -1;
      while (changing != level[i].size()) {
        changing = level[i].size();
        Complete(i);
        Predict(i);
      }
    }

    Situation finish(fictional_rule, 1, 0);
    bool result = static_cast<bool>(level[word.size()].count(finish));
    level.clear();

    return result;
  }

 private:
  struct Situation {
    Rule rule;
    int dot;
    int prefix_before;

    Situation(const Situation& other) = default;
    Situation(const Rule& rule, int dot, int prefix_before)
        : rule(rule), dot(dot), prefix_before(prefix_before) {}

    bool operator<(const Situation& other) const {  // for std::set cmp
      if (rule.left != other.rule.left) {
        return rule.left < other.rule.left;
      }
      if (rule.right != other.rule.right) {
        return rule.right < other.rule.right;
      }
      if (dot != other.dot) {
        return dot < other.dot;
      }
      return prefix_before < other.prefix_before;
    }
  };

  const char fictional_start = '$';

  std::unordered_set<char> nonterm_pool;
  std::unordered_set<char> term_pool;
  std::vector<Rule> rules_pool;

  char nonterm_start;
  std::vector<std::set<Situation>> level;

  void Scan(char terminal, int level_pos) {
    if (!term_pool.count(terminal)) {
      throw std::runtime_error("letter is out of alphabet\n");
    }

    for (const Situation& situation : level[level_pos]) {
      if (!(situation.dot < situation.rule.right.size())) {
        continue;
      }
      if (situation.rule.right[situation.dot] == terminal) {
        Situation add(Rule(situation.rule.rule), situation.dot + 1,
                      situation.prefix_before);
        level[level_pos + 1].insert(add);
      }
    }
  }

  void Predict(int level_pos) {
    for (const Situation& situation : level[level_pos]) {
      if (!(situation.dot < situation.rule.right.size())) {
        continue;
      }

      char nonterm_predict = situation.rule.right[situation.dot];
      if (!nonterm_pool.count(nonterm_predict)) {
        continue;
      }

      for (const Rule& rule : rules_pool) {
        if (rule.left == nonterm_predict) {
          Situation add(rule.rule, 0, level_pos);
          level[level_pos].insert(add);
        }
      }
    }
  }

  void Complete(int level_pos) {
    for (const Situation& to_complete : level[level_pos]) {
      if (to_complete.dot != to_complete.rule.right.size()) {
        continue;
      }

      for (const Situation& go_higher : level[to_complete.prefix_before]) {
        if (go_higher.rule.right[go_higher.dot] != to_complete.rule.left) {
          continue;
        }

        Situation add(go_higher.rule.rule, go_higher.dot + 1,
                      go_higher.prefix_before);
        level[level_pos].insert(add);
      }
    }
  }
};
