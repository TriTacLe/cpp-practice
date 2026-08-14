// Exercise 3 task 4. Practice with std::string, points a to h.

#include <iostream>
#include <string>

using namespace std;

int main() {
  // a)
  string word1, word2, word3;
  cout << "Write three words: ";
  cin >> word1 >> word2 >> word3;

  // b) operator+ on string builds a new string
  string sentence = word1 + " " + word2 + " " + word3 + ".";
  cout << "sentence: " << sentence << endl;

  // c) size() and length() are the same function
  cout << "lengths: " << word1.size() << " " << word2.size() << " " << word3.size()
       << ", whole sentence: " << sentence.size() << endl;

  // d) plain assignment copies the string, no pointer involved
  string sentence2 = sentence;

  // e) replace throws out_of_range if the positions do not exist
  if (sentence2.size() > 12)
    sentence2.replace(10, 3, "xxx");
  else
    cout << "sentence too short to replace characters 10 to 12" << endl;
  cout << "sentence:  " << sentence << endl;
  cout << "sentence2: " << sentence2 << endl;

  // f)
  if (sentence.size() >= 5) {
    string sentence_start = sentence.substr(0, 5);
    cout << "sentence:       " << sentence << endl;
    cout << "sentence_start: " << sentence_start << endl;
  }
  else
    cout << "sentence is shorter than 5 characters" << endl;

  // g) find returns string::npos when there is no match
  if (sentence.find("hallo") != string::npos)
    cout << "sentence contains hallo" << endl;
  else
    cout << "sentence does not contain hallo" << endl;

  // h) search on from the position after the last hit, otherwise we keep
  // finding the same one
  int count = 0;
  for (size_t pos = sentence.find("er"); pos != string::npos; pos = sentence.find("er", pos + 1)) {
    cout << "found er at position " << pos << endl;
    count++;
  }
  cout << "occurrences of er: " << count << endl;
}
