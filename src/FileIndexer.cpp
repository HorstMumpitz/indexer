#include "FileIndexer.hpp" 

using namespace std ;

// FileIndexer::FileIndexer(string file)
// {
// 	mFile = file;
// }


// void FileIndexer::IndexFile(){
// 	cout << nFile;
// }

FileIndexer::FileIndexer(string file)
{
	mFile = file;
}

void FileIndexer::PrintPositionVector(vector<Entry> positions) 
{
    vector<Entry>::iterator itvec;
    for(itvec = positions.begin(); itvec != positions.end(); ++itvec) {
        Entry pos = *itvec;
        cout << "(" << pos.first << "," << pos.second << ")" ;
    }
    cout << ")" <<endl;
}

void FileIndexer::PrintWordIndex(string word) 
{
    MyMap::iterator it = indexMap.find(word);
     if(it != indexMap.end()) 
     {
        PrintPositionVector((*it).second);
     } else 
     {
        cout << "Das Wort ist nicht im Index vorhanden" ; 
     }

            
}

void FileIndexer::PrintWordsIndexes(string word) 
{

    MyMap::iterator it ;
    MyMap result; 
    if(word.size() == 0) {
        PrintResult();
    } else {
        for(it = indexMap.begin(); it != indexMap.end(); ++it) 
        {
            string sub = (*it).first.substr(0,word.size());
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
           if(word == sub)
            {
                result.insert(make_pair((*it).first,(*it).second)) ;   
            } 
        }
        if(result.size() == 0)
        {
            cout << "Es sind keine Wörter mit diesen Anfangsbuchstaben vorhanden" ;
        } else 
        {
            PrintResult(result) ;    
        }
    }
    
}

void FileIndexer::PrintResult() {
	PrintResult(indexMap);	
}
	

void FileIndexer::PrintResult(MyMap mmap){
    MyMap::iterator iter = mmap.begin();
    while(iter != mmap.end())
    {     
    	cout << (*iter).first << "(";
    	PrintPositionVector(((*iter).second));
         ++iter;
    }
}

MyMap FileIndexer::IndexFile(){
	ifstream ifs(mFile.data()) ;
    if (!ifs)
    {
        cout << "Eingabedatei \"" << mFile << "\" konnte nicht geoeffnet werden!" << endl ;
        exit(EXIT_FAILURE) ;
    }
    string line;
    int i = 1;
    Parser myParser;
    while(getline(ifs, line)) {
    	stringstream ss(line) ;
    	int j = 1 ;
        vector<string> lineWords = myParser.parse_input_line(line) ;
        vector<string>::iterator lwi;
        bool replace;
        for(lwi = lineWords.begin(); lwi != lineWords.end(); ++lwi) {
            vector<Entry> words;
            Entry position (i,j);
            string word = *lwi ;
            words = indexMap[word];        
            words.push_back(position);
            indexMap[word] = words;
            j++;
        }
    	i++;
    }
    ifs.close() ;
    
   return indexMap;
}

