#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

bool StartsWith(char *pre, char *str);
void SetDictionary();
bool InDictionary(char * value, char **dict);
char* GetWord();
void GetDictionary();

#endif // HEADER_H_INCLUDED
