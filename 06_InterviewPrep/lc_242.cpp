/*
Given: 
- two strings, s and t

Task: 
- Return true if t is an anagram of s, false otherwise

Constraints;
- s and t are always lowercase

Idea: 
- Can compare every element and make sure they're all the same
- Add all the values of one word to a set, and check that every other letter in the other 
is in the set. Also validate the length to make sure they're the same. 

Pseudocode:

bool isAnagram(s, t)
    define set 
    if length or s and t are not equal
        return false
    for letter in s
        add letter to set
    for letter in t
        if letter is not in set
            return false
    return true

In hindsight that might be wrong, because then we can't validate the actual # of characters. 
It might be possible to have a word with the same length but different frequencies of individual
letters. 

So we need to use a map and store the frequency count as the value. Our new logic is that
if it either does not exist in the map OR it exists in the map with decrement value 0 we know
it is not an anagram.

bool isAnagram(s, t)
    define map 
    if length or s and t are not equal
        return false
    for letter in s
        if not in map
            add to map and set value to 1
        else if in map then increment value by 1
    for letter in t
        if letter is not in map
            return false
        else if letter is in map 
            if value is 0 
                return false
            else
                decrement value by 1
    return true

this new logic should be robust

*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

bool isAnagram_set(string s, string t) {
    
    if (s.size() != t.size()) {
        cout << "Size difference found, False" << endl;
        return false;
    }
    unordered_set<char> set;
    for (char c : s) {
        set.insert(c);
    }
    for (char c : t) {
        if(set.find(c) == set.end()) { // if new letter found
            cout << "Found new character " << c << endl;
            return false;
        }
    }
    return true;
}

bool isAnagram(string s, string t) {
    unordered_map<char, int> map;
    if (s.size() != t.size()) {
        //cout << "Size difference found, False" << endl;
        return false;
    }
    for (char c : s) {
        if (map.find(c) == map.end()) {
            map[c] = 1;
        } else {
            //cout << "Incrementing map[" << c << "] = " << map[c] << endl;
            map[c] += 1;
        }
    }
    for (char c : t) {
        if (map.find(c) == map.end()) {
            //cout << "Character not found: " << c << endl;
            return false;
        } else {
            if (map[c] == 0) {
                //cout << "Character found but out of occurrences: " << c << endl;
                return false;
            } else {
                //cout << "Character found, decrementing: map[" << c << "] = " << map[c] << endl; 
                map[c] -= 1;
                //cout << map[c] << endl;
            }
        }
    }
    return true;
}

/*
Cleaned up version
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) {
        return false;
    }
    
    unordered_map<char, int> map;
    for (char c : s) {
        map[c]++;
    }
    
    for (char c : t) {
        if (map[c] == 0) {
            return false;
        }
        map[c]--;
    }
    
    return true;
}
*/

int main() {
    string s = "anagram";
    string t = "nagaram";
    cout << isAnagram(s, t) << endl;
    return 0;
}
