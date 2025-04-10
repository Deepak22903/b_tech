#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

const int ALPHABET_SIZE = 26;

struct TrieNode {
  std::unique_ptr<TrieNode> children[ALPHABET_SIZE];
  bool isEndOfWord;

  TrieNode() : isEndOfWord(false) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
      children[i] = nullptr;
    }
  }
};

class Trie {
private:
  std::unique_ptr<TrieNode> root;

  void findWordsFromNode(TrieNode *node, std::string currentPrefix,
                         std::vector<std::string> &suggestions, int limit) {
    if (node == nullptr || (limit > 0 && suggestions.size() >= limit)) {
      return;
    }

    if (node->isEndOfWord) {
      suggestions.push_back(currentPrefix);
      if (limit > 0 && suggestions.size() >= limit)
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
      if (node->children[i] != nullptr) {
        char nextChar = 'a' + i;
        findWordsFromNode(node->children[i].get(), currentPrefix + nextChar,
                          suggestions, limit);
        if (limit > 0 && suggestions.size() >= limit)
          return;
      }
    }
  }

  TrieNode *findPrefixNode(const std::string &prefix) {
    TrieNode *currentNode = root.get();
    for (char ch : prefix) {
      // Assuming prefix is already lowercase 'a'-'z'
      if (ch < 'a' || ch > 'z')
        return nullptr;
      int index = ch - 'a';
      if (currentNode->children[index] == nullptr) {
        return nullptr;
      }
      currentNode = currentNode->children[index].get();
    }
    return currentNode;
  }

public:
  Trie() { root = std::make_unique<TrieNode>(); }

  // Converts string to lowercase
  std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return s;
  }

  void insert(std::string word) {
    word = toLower(word);
    TrieNode *currentNode = root.get();
    for (char ch : word) {
      if (ch < 'a' || ch > 'z')
        continue; // Ignore non-lowercase alpha
      int index = ch - 'a';

      if (currentNode->children[index] == nullptr) {
        currentNode->children[index] = std::make_unique<TrieNode>();
      }
      currentNode = currentNode->children[index].get();
    }
    currentNode->isEndOfWord = true;
  }

  bool search(std::string word) {
    word = toLower(word);
    TrieNode *currentNode = root.get();
    for (char ch : word) {
      if (ch < 'a' || ch > 'z')
        return false;
      int index = ch - 'a';
      if (currentNode->children[index] == nullptr) {
        return false;
      }
      currentNode = currentNode->children[index].get();
    }
    return (currentNode != nullptr && currentNode->isEndOfWord);
  }

  std::vector<std::string> autoSuggest(std::string prefix, int limit = 2) {
    prefix = toLower(prefix);
    std::vector<std::string> suggestions;
    TrieNode *prefixNode = findPrefixNode(prefix);

    if (prefixNode == nullptr) {
      return suggestions; // Prefix not found
    }

    // Use -1 limit for findWordsFromNode if we want all suggestions from that
    // point
    findWordsFromNode(prefixNode, prefix, suggestions, limit > 0 ? limit : -1);

    return suggestions;
  }

  // Helper to get all words (calls findWordsFromNode without limit)
  std::vector<std::string> getAllWords() {
    std::vector<std::string> allWords;
    findWordsFromNode(root.get(), "", allWords, -1); // -1 indicates no limit
    return allWords;
  }
};

// Function to display menu and get user choice
int displayMenu() {
  int choice;
  std::cout << "\n--- Trie Menu ---" << std::endl;
  std::cout << "1. Insert Word" << std::endl;
  std::cout << "2. Search Word" << std::endl;
  std::cout << "3. Auto-Suggest Prefix" << std::endl;
  std::cout << "4. Print All Words" << std::endl;
  std::cout << "0. Exit" << std::endl;
  std::cout << "Enter your choice: ";

  while (!(std::cin >> choice)) {
    std::cout << "Invalid input. Please enter a number: ";
    std::cin.clear(); // Clear error flags
    // Ignore rest of the line
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  // Consume the newline character left by std::cin >> choice
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return choice;
}

int main() {
  Trie dictionaryTrie;

  // Pre-populate with some words
  dictionaryTrie.insert("engineering");
  dictionaryTrie.insert("engineer");
  dictionaryTrie.insert("university");
  dictionaryTrie.insert("universal");
  dictionaryTrie.insert("course");
  dictionaryTrie.insert("coep");
  dictionaryTrie.insert("computer");
  dictionaryTrie.insert("college");

  int choice;
  std::string inputWord;
  std::string inputPrefix;

  do {
    choice = displayMenu();

    switch (choice) {
    case 1: // Insert
      std::cout << "Enter word to insert: ";
      std::getline(std::cin, inputWord); // Use getline for potential spaces
      if (!inputWord.empty()) {
        dictionaryTrie.insert(inputWord);
        std::cout << "'" << inputWord << "' inserted." << std::endl;
      } else {
        std::cout << "Cannot insert an empty word." << std::endl;
      }
      break;

    case 2: // Search
      std::cout << "Enter word to search: ";
      std::getline(std::cin, inputWord);
      if (!inputWord.empty()) {
        if (dictionaryTrie.search(inputWord)) {
          std::cout << "'" << inputWord << "' found in the dictionary."
                    << std::endl;
        } else {
          std::cout << "'" << inputWord << "' not found." << std::endl;
        }
      } else {
        std::cout << "Cannot search for an empty word." << std::endl;
      }
      break;

    case 3: // Auto-Suggest
      std::cout << "Enter prefix for auto-suggestion: ";
      std::getline(std::cin, inputPrefix);
      if (!inputPrefix.empty()) {
        // Optional: Ask for limit? Using default 2 for now.
        int limit = 2;
        std::vector<std::string> suggestions =
            dictionaryTrie.autoSuggest(inputPrefix, limit);
        std::cout << "Suggestions for '" << inputPrefix << "' (up to " << limit
                  << "):" << std::endl;
        if (suggestions.empty()) {
          std::cout << "(None)" << std::endl;
        } else {
          for (const std::string &s : suggestions) {
            std::cout << "- " << s << std::endl;
          }
        }
      } else {
        std::cout << "Cannot suggest for an empty prefix." << std::endl;
      }
      break;

    case 4: // Print All
      std::cout << "All words in the dictionary:" << std::endl;
      { // Scope for suggestions variable
        std::vector<std::string> allWords = dictionaryTrie.getAllWords();
        if (allWords.empty()) {
          std::cout << "(Dictionary is empty)" << std::endl;
        } else {
          for (const std::string &s : allWords) {
            std::cout << "- " << s << std::endl;
          }
        }
      } // End scope
      break;

    case 0: // Exit
      std::cout << "Exiting program." << std::endl;
      break;

    default:
      std::cout << "Invalid choice. Please try again." << std::endl;
      break;
    }
  } while (choice != 0);

  return 0;
}
