#include "earley.cpp"

Input ReadData() {
  Input data;
  std::cin >> data.nonterm_cnt >> data.term_cnt >> data.rules_cnt;

  char nonterm;
  char term;
  std::string rule;
  std::string query;

  for (size_t i = 0; i < data.nonterm_cnt; ++i) {
    std::cin >> nonterm;
    data.nonterm_pool.insert(nonterm);
  }
  for (size_t i = 0; i < data.term_cnt; ++i) {
    std::cin >> term;
    data.term_pool.insert(term);
  }
  for (size_t i = 0; i < data.rules_cnt; ++i) {
    std::cin >> rule;
    Rule cur(rule);
    data.rules_pool.push_back(cur);
  }
  std::cin >> data.nonterm_start >> data.queries_cnt;
  for (size_t i = 0; i < data.queries_cnt; ++i) {
    std::cin >> query;
    data.queries.push_back(query);
  }
  return data;
}

std::vector<std::string> ReceiveAnswers(const Input& data) {
  EarleyParser early_parser(data);
  std::vector<std::string> ans;
  for (size_t i = 0; i < data.queries_cnt; ++i) {
    if (early_parser.IsInGrammar(data.queries[i])) {
      ans.push_back("YES");
    } else {
      ans.push_back("NO");
    }
  }
  return ans;
}

void PrintAnsewers(const std::vector<std::string>& answers) {
  for (size_t i = 0; i < answers.size(); ++i) {
    std::cout << answers[i] << "\n";
  }
}