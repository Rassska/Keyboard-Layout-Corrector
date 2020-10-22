#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <uchar.h>

class LayoutCorrector
{
private:
    int SizeOfHashTable_ = 1e5 + 7;
    std::vector <std::vector <std::wstring>> RussWordsHashTable_;
    std::vector <std::vector <std::wstring>> EngWordsHashTable_;
    std::map <wchar_t, wchar_t> characterMatchings_;
    
    std::string PathForRussDict_;
    std::string PathForEngDict_;


public:
    LayoutCorrector() = default;
    LayoutCorrector(const std::string& PathForRussDict, const std::string& PathForEngDict);

    int HashCalc(std::wstring currStr) const;
    bool checkIsOpenDicts () const;
    void initializeHashTables ();
    std::wstring GetCorrectWord (std::wstring InputWord);
    ~LayoutCorrector() {}

};
