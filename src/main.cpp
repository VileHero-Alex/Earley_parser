#include "main.h"

int main() {
  Input data(ReadData());
  auto answer = ReceiveAnswers(data);
  PrintAnsewers(answer);
}