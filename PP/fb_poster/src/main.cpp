#include "../include/header.h"

int main() {
  auto now = chrono::system_clock::now();
  time_t now_time = chrono::system_clock::to_time_t(now);
  tm local_time = *localtime(&now_time);
  ostringstream oss;
  oss << put_time(&local_time, "%B %d,%Y");
  string date = oss.str();
  cout << date << endl;
  cout << "Generating prompt for image..." << endl;
  string prompt = generatePrompt();
  cout << "Generating image..." << endl;
  generateImage(prompt);

  return 0;
}
