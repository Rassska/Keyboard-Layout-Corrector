#include <bits/stdc++.h>
#include "LayoutCorrector.h"


int main () {
    
    std::string RussPath = "/home/rasul/dev/projects/LayoutCorrector/hugeRussDict/RussianWords(UTF-8).txt";
    std::string EngPath = "/home/rasul/dev/projects/LayoutCorrector/hugeEngDict/EnglishWords(UTF-8).txt";


    LayoutCorrector MyCorr (RussPath, EngPath);
    MyCorr.initializeHashTables();
    std::wstring test;
    std::wcin >> test;
    std::wcout << MyCorr.GetCorrectWord(test) << std::endl;
    
    
  
}