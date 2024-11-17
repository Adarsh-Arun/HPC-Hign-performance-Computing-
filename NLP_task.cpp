// first install required library given below.
//sudo apt-get install libboost-all-dev


#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <boost/algorithm/string.hpp>  // For tokenization
#include <cctype>

// Custom implementation of Porter Stemmer
std::string porterStemmer(const std::string &word);

// List of stop words
std::set<std::string> stop_words = {"the", "is", "in", "at", "of", "on", "and", "a", "are", "to", "with", "for"};

// Function to tokenize the text
std::vector<std::string> tokenize(const std::string &text) {
    std::vector<std::string> tokens;
    std::string word;
    std::istringstream stream(text);
    while (stream >> word) {
        boost::algorithm::to_lower(word);  // Convert to lowercase
        tokens.push_back(word);
    }
    return tokens;
}

// Function to remove stopwords
std::vector<std::string> removeStopWords(const std::vector<std::string> &tokens) {
    std::vector<std::string> filtered_tokens;
    for (const auto &word : tokens) {
        if (stop_words.find(word) == stop_words.end()) {
            filtered_tokens.push_back(word);
        }
    }
    return filtered_tokens;
}

// Function to stem words using the Porter Stemmer
std::vector<std::string> stemWords(const std::vector<std::string> &tokens) {
    std::vector<std::string> stemmed_tokens;
    for (const auto &word : tokens) {
        stemmed_tokens.push_back(porterStemmer(word));  // Apply stemming
    }
    return stemmed_tokens;
}

// Example Porter Stemmer implementation (simplified)
std::string porterStemmer(const std::string &word) {
    // This is a basic implementation of Porter Stemmer's rules for stemming.
    std::string stemmed_word = word;
    if (stemmed_word.length() > 4 && stemmed_word.substr(stemmed_word.length() - 3) == "ing") {
        stemmed_word = stemmed_word.substr(0, stemmed_word.length() - 3);  // Removing "ing"
    }
    else if (stemmed_word.length() > 2 && stemmed_word.substr(stemmed_word.length() - 2) == "ed") {
        stemmed_word = stemmed_word.substr(0, stemmed_word.length() - 2);  // Removing "ed"
    }
    return stemmed_word;
}

int main() {
    // Sample text
    std::string text = "The quick brown foxes are running faster than the lazy dogs.";

    // Step 1: Tokenization
    std::vector<std::string> tokens = tokenize(text);
    std::cout << "Tokens: ";
    for (const auto &token : tokens) {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    // Step 2: Stop-word removal
    std::vector<std::string> filtered_tokens = removeStopWords(tokens);
    std::cout << "Filtered Tokens: ";
    for (const auto &token : filtered_tokens) {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    // Step 3: Stemming
    std::vector<std::string> stemmed_tokens = stemWords(filtered_tokens);
    std::cout << "Stemmed Tokens: ";
    for (const auto &token : stemmed_tokens) {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    return 0;
}


