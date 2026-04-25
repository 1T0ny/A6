//
//  main.cpp
//  ABloomFilter

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class BloomFliter {
    bool bits[1000] = {false};
    vector<string> user;
    
public:
    int hash_Func1(string name);
    int hash_Func2(string name);
    bool linearSearch(string name);
    bool isValid(string name);
    bool mightbeThere(string name);
    void loadCSV(string filename);
    void addUser(string name);
    void Register();
    void displayALL();
    
    void runAutomatedTest();
};
    
    
int BloomFliter::hash_Func1(string name) {
    int asciisum = 0;
    for (int i = 0; i < name.size(); i++) {
        asciisum += name[i];
    }
    return asciisum % 1000;
}

    
int BloomFliter::hash_Func2(string name) {
    int weightSum = 0;
    for (int i = 0; i < name.size(); i++){
        weightSum += name[i];
    }
    return  weightSum % 1000;

}

void BloomFliter::loadCSV(string filename) {
    ifstream file(filename);
    string name;
    if (!file.is_open()) {
        cout << "[Warning] Could Not Open the File: " << filename << ". Starting a new one." << endl;
        return;
    }
    while (getline(file, name)) {
        if (name.size() > 0 && name[name.size() - 1] == '\r') {
            name.pop_back();
        }
        user.push_back(name);
        
        int hash1 = hash_Func1(name);
        int hash2 = hash_Func2(name);
        bits[hash1] = true;
        bits[hash2] = true;
    }
    file.close();
    cout << "[INFO] The file was Successfully Loaded " << user.size() << " users into the username database. " << endl;
}

bool BloomFliter::linearSearch(string name) {
    for (int i = 0; i < user.size(); i++) {
        if (user[i] == name) return true;
    }
    return false;
}

void  BloomFliter::addUser(string name) {
    user.push_back(name);
    
    int hash1 = hash_Func1(name);
    int hash2 = hash_Func2(name);
    bits[hash1] = true;
    bits[hash2] = true;
    
    cout << "[INFo] The Username: " << name << " has been added." << endl;
}
bool BloomFliter::isValid(string name) {
    if (name.size() == 0) {
        cout << "[WARNING] The Username cannot be empty" << endl;
        return false;
    }
    if (name.size() == 1) {
        cout << "[WARNING] The Username is to short and has to be greater than 1 character." << endl;
        return false;
    }
    if (name.size() > 20) {
        cout << "[WARNING] The Username is too long and cannot be over 20 characters." << endl;
        return false;
    }
    
    for (int i = 0; i < name.size(); i++) {
        char c = name[i];
        bool LowerLEtter = (c >= 'a' && c <= 'z');
        bool UpperLEtter = (c >= 'A' && c <= 'Z');
        bool Digitt = (c >= '0' && c <= '9');
        
        bool underScore = (c == '_');
        if (!LowerLEtter && !UpperLEtter && !Digitt && !underScore) {
            cout << "[WARNING] The Username must be an word without spaces: " << c << endl;
            return false;
        }
    }
    return true;
}

bool BloomFliter::mightbeThere(string name) {
    int hash1 = hash_Func1(name);
    int hash2 = hash_Func2(name);
    return bits[hash1] && bits[hash2];
}

void BloomFliter::displayALL() {
    for (int i = 0; i < user.size(); i++) {
        if (i > 20) {
            cout << "... " << (user.size() - 20) << " more users are hidden. " << endl;
            break;
        }
        cout << i << ". " << user[i] << endl;
    }
}

void BloomFliter::Register() {
    string yourRecommendedName;
    while (true) {
        cout << "\n-------- Gaming Sign UP --------\n";
        cout << "Please enter a Username you want to use [Type 'Exit' to quite the program please: ";
        getline(cin, yourRecommendedName);
        
        if (yourRecommendedName == "Exit") break;
        
        if (!isValid(yourRecommendedName)) {
            continue;
        }
        
        auto StartBloom = high_resolution_clock::now();
        bool Foundtwo = mightbeThere(yourRecommendedName);
        auto stopBloom = high_resolution_clock::now();
        auto longBloom = duration_cast<nanoseconds>(stopBloom - StartBloom);
        
        auto startLinear = high_resolution_clock::now();
        bool Foundnam = linearSearch(yourRecommendedName);
        auto stopLinear = high_resolution_clock::now();
        auto longLinear = duration_cast<nanoseconds>(stopLinear - startLinear);
        
        cout<< "Bloom Filter tool " << longBloom.count() << " ns." << endl;
        cout << "The Linear Search took " << longLinear.count() << " ns." << endl;
        
        if (Foundtwo) {
            if (Foundnam) {
                cout << "[WARNING] The username " << yourRecommendedName << " is already taken. Please try a different name. \n";
            } else {
                cout << "[INFO] Bloom filter has seen that it was report wrongly. Your name is open. \n";
                addUser(yourRecommendedName);
            }
        } else {
            addUser(yourRecommendedName);
        }
    }
}

void BloomFliter::runAutomatedTest() {
    cout << "\n--- 100AUTOMATED TEST ---\n";
    
    long long totalBloomTime = 0;
    long long totalLinearTime = 0;

    for (int i = 0; i < 100; i++) {
        string testName = "TestUser" + to_string(i);

        auto startBloom = high_resolution_clock::now();
        mightbeThere(testName);
        auto stopBloom = high_resolution_clock::now();
        totalBloomTime += duration_cast<nanoseconds>(stopBloom - startBloom).count();

        auto startLinear = high_resolution_clock::now();
        linearSearch(testName);
        auto stopLinear = high_resolution_clock::now();
        totalLinearTime += duration_cast<nanoseconds>(stopLinear - startLinear).count();
    }
    
    long long avgBloom = totalBloomTime / 100;
    long long avgLinear = totalLinearTime / 100;
    
    cout << "[RESULT] Average Bloom Filter Time:  " << avgBloom << " ns.\n" << endl;
    cout << "[RESULT] Average Linear Search Time: " << avgLinear << " ns.\n" << endl;
    cout << "---------------------------------------\n" << endl;
}

int main() {
    BloomFliter myBloomFilter;
  
    myBloomFilter.loadCSV("/Users/tony/Downloads/Gaming_Usernames_10k (1).csv");

    myBloomFilter.addUser("Lebron");
    myBloomFilter.addUser("Austin");
    myBloomFilter.addUser("Tone");
    myBloomFilter.addUser("Marcus");
    myBloomFilter.addUser("Luke");
    
    myBloomFilter.runAutomatedTest();
    
    myBloomFilter.Register();
    
    return 0;
}

