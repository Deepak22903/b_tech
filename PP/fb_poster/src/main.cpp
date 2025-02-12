#include "../include/header.h"

int main() {
  cout << "Generating prompt for image..." << endl;
  string prompt = generatePrompt();
  cout << "Prompt generated successfully!" << endl;
  cout << "Generating image..." << endl;
  string img_path = generateImage(prompt);
  cout << "Image generated successfully with path : " << img_path << endl;
  cout << "Publishing to facebook..." << endl;
  string post_id = post_to_fb(img_path);
  cout << "Post added with post_id : " << post_id << endl;

  return 0;
}
