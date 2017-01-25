#include <fstream>
#include <cstring>
#include <cctype>
#include <sstream>

using namespace std;

// generate failure function
void failure_function(char* pat, int size, int* fail)
{
    fail[0] = -1;
    for(int i = 1, j = -1; i < size; i++){
        while(j >= 0 && pat[j + 1] != pat[i]) j = fail[j];
        if(pat[j + 1] == pat[i]) j++;
        fail[i] = j;
    }
}

// match the pattern and the word, return the match times
int match(char* s, int s_size, char* pat, int pat_size, int* fail)
{
    int match_time = 0;
    if(s_size < pat_size) return 0;
    for(int i = 0, j = -1; i < s_size; i++){
        while(j >= 0 && pat[j + 1] != s[i]) j = fail[j];
        if(pat[j + 1] == s[i]) j++;
        if(j == pat_size - 1){
            j = fail[j];
            match_time++;
        } 
    }
    return match_time;
}

int main(int argc, char* argv[])
{
    // require two arguments
    if(argc < 3) return 0; 

    // input and output file
    ifstream input;
    input.open(argv[1]);
    ofstream output;
    output.open(argv[2]);

    // create a char array and read input
    char* str = new char [1000001];
    input.read(str, 1000000);

    // avoid punctuation and space
    int str_size = strlen(str);
    for(int i = 0; i < str_size; i++){
        if(ispunct(str[i]) || isspace(str[i])) str[i] = ' ';
    }

    // get pattern
    char *pat, *s;
    char delim[] = " ";
    pat = s = strtok(str, delim);
    int pat_size = strlen(pat);

    // build failure function
    int* fail = new int [pat_size];
    failure_function(pat, pat_size, fail);

    // freq : the number of the words same as the pattern
    // word_idx : the index of the current word
    int freq = 0, word_idx = 1;
    stringstream out;
    while(s != NULL){
        // match pattern
        int s_size = strlen(s);
        int match_time = match(s, s_size, pat, pat_size, fail);
        
        // output
        if(match_time){
            for(int i = 0; i < match_time; i++) out << word_idx;
            if(s_size == pat_size) freq++;
        }

        // get new word from input
        word_idx++;
        s = strtok(NULL, delim);
    }
    // output result
    output << freq << endl;
    string output_string;
    out >> output_string;
    output << output_string << endl;
    input.close();
    output.close();
    delete [] str;
    return 0;
}
