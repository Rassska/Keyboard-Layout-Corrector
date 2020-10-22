#include <bits/stdc++.h>
#include "LayoutCorrector.h"
int LayoutCorrector::HashCalc(std::wstring currStr) const {
    int p = 31;
    long long hash = 0;
    long long p_pow = 1;

    for (int i = 0; i < currStr.length(); i++) {
        hash += (currStr[i] - 'a' + 1) * p_pow;
        p_pow *= p;
    }
    int ans = hash % SizeOfHashTable_;
    return abs(ans);
}
LayoutCorrector::LayoutCorrector(const std::string& PathForRussDict, const std::string& PathForEngDict):
    PathForRussDict_(PathForRussDict), PathForEngDict_(PathForEngDict) 

    {
        RussWordsHashTable_.resize(SizeOfHashTable_);
        EngWordsHashTable_.resize(SizeOfHashTable_);

        characterMatchings_.emplace(std::make_pair(L'q', L'й'));   
        characterMatchings_.emplace(std::make_pair(L'w', L'ц'));   
        characterMatchings_.emplace(std::make_pair(L'e', L'у'));   
        characterMatchings_.emplace(std::make_pair(L'r', L'к'));   
        characterMatchings_.emplace(std::make_pair(L't', L'е'));   
        characterMatchings_.emplace(std::make_pair(L'y', L'н'));   
        characterMatchings_.emplace(std::make_pair(L'u', L'г'));   
        characterMatchings_.emplace(std::make_pair(L'i', L'ш'));   
        characterMatchings_.emplace(std::make_pair(L'o', L'щ'));   
        characterMatchings_.emplace(std::make_pair(L'p', L'з'));   
        characterMatchings_.emplace(std::make_pair(L'[', L'х'));    
        characterMatchings_.emplace(std::make_pair(L']', L'ъ'));    
        characterMatchings_.emplace(std::make_pair(L'a', L'ф'));    
        characterMatchings_.emplace(std::make_pair(L's', L'ы'));    
        characterMatchings_.emplace(std::make_pair(L'd', L'в'));    
        characterMatchings_.emplace(std::make_pair(L'f', L'а'));    
        characterMatchings_.emplace(std::make_pair(L'g', L'п'));    
        characterMatchings_.emplace(std::make_pair(L'h', L'р'));    
        characterMatchings_.emplace(std::make_pair(L'j', L'о'));    
        characterMatchings_.emplace(std::make_pair(L'k', L'л'));    
        characterMatchings_.emplace(std::make_pair(L'l', L'д'));    
        characterMatchings_.emplace(std::make_pair(L';', L'ж'));    
        characterMatchings_.emplace(std::make_pair(L'z', L'я'));    
        characterMatchings_.emplace(std::make_pair(L'x', L'ч'));    
        characterMatchings_.emplace(std::make_pair(L'c', L'с'));    
        characterMatchings_.emplace(std::make_pair(L'v', L'м'));    
        characterMatchings_.emplace(std::make_pair(L'b', L'и'));    
        characterMatchings_.emplace(std::make_pair(L'n', L'т'));    
        characterMatchings_.emplace(std::make_pair(L'm', L'ь'));    
        characterMatchings_.emplace(std::make_pair(L',', L'б'));    
        characterMatchings_.emplace(std::make_pair(L'.', L'ю')); 


    
    }
bool LayoutCorrector::checkIsOpenDicts() const{

    bool ans = false;
    try
    {
        std::wcout << "Attempt to open Files!\n";
        std::wifstream RussDict(PathForRussDict_);
        std::wifstream EngDict(PathForEngDict_);
        if (!(RussDict.is_open()) ||!(EngDict.is_open())) {
            throw std::runtime_error("RussDict or EngDict do not exist!");
            
        }
        
        ans = true;
        RussDict.close();
        EngDict.close();

    }
    catch (const std::runtime_error& exp)
    {
        std::cout << exp.what();
    }
    return ans;
}

void LayoutCorrector::initializeHashTables() {

    if (checkIsOpenDicts()) {
        std::wifstream RussDict(PathForRussDict_);
        std::wifstream EngDict(PathForEngDict_);

        std::wstring currLine;
        while(getline(RussDict, currLine)) {
            RussWordsHashTable_[HashCalc(currLine)].push_back(currLine);
        }
        while(getline(EngDict, currLine)) {
            EngWordsHashTable_[HashCalc(currLine)].push_back(currLine);
        }
    }


}

std::wstring LayoutCorrector::GetCorrectWord (std::wstring InputWord) {
    std::wcmatch EngWordResult;
    std::wregex EngWordPattern (L"[a-zA-Z-]+$");
    
    bool IsEngWord = std::regex_match(InputWord.c_str(), EngWordResult,  EngWordPattern);
    
    if (IsEngWord) {
        int hash = HashCalc(InputWord);
        bool isExist = false;
        for (int i = 0; i < EngWordsHashTable_[hash].size(); i++) {
            if (EngWordsHashTable_[hash][i] == InputWord) {
                isExist = true;
                break;
            }
        }
        if (!isExist) {
            for (int i = 0; i < InputWord.size(); i++) {
                std::wcout << characterMatchings_[(InputWord[i])] << '\n';
                InputWord[i] = characterMatchings_[(InputWord[i])];
            }
        } 
        return InputWord;
        
    } else {
        std::wcmatch RussWordResult;
        std::wregex RussWordPattern (L"[а-яА-Я-]+$");
        bool IsRussWord = std::regex_match(InputWord.cbegin(), InputWord.cend(), RussWordPattern);
        
        if (IsRussWord == true) {
            std::wcout << "Hello";
            exit(0);
            int hash = HashCalc(InputWord);
            bool isExist = false;
            for (int i = 0; i < RussWordsHashTable_[hash].size(); i++) {
                std::wcout << RussWordsHashTable_[hash][i] << '\n';
                if (RussWordsHashTable_[hash][i] == InputWord) {
                    isExist = true;
                    break;
                }
            }
            
            return InputWord;

        }
    }
    return InputWord;
}


