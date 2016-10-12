// hw3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <queue>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <io.h>
#include <time.h>
using namespace std;
//结点结构 
class Node{
public:
	Node()
	{
		end = false;
		count = 0;
		pre = NULL;
		letter = ' ';
		for (int i = 0; i<26; i++)
		{
			next[i] = NULL;
		}
	}
	bool end;//是否是终点
	int count; //词频计数
	char letter;
	Node* pre;
	Node *next[26];//26个字母
};
class TrieTree{
public:
	TrieTree()
	{
		root = new Node();
	}
	void insert(string word);
	int searchWord(string word);
	string retrievalWord(Node* node);
	vector<Node*> topNWord(int n);
	void buildTrie(string book);
private:
	Node *root;
	vector<Node*> wordList;
};
void TrieTree::insert(string word)
{
	Node *proot = root;
	for (unsigned int i = 0; i<word.size(); i++)
	{
		if (proot->next[word.at(i) - 'a'] == NULL) {
			proot->next[word.at(i) - 'a'] = new Node();
			proot->next[word.at(i) - 'a']->pre = proot;
			proot->next[word.at(i) - 'a']->letter = word.at(i);
		}
		proot = proot->next[word.at(i) - 'a'];
	}
	if (proot->end == false) {
		proot->end = true;//单词结尾结点 
		proot->count++;
		wordList.push_back(proot);
	}
	else {
		proot->count++;
	}
}
int TrieTree::searchWord(string word) {
	Node *proot = root;
	for (unsigned int i = 0; i<word.size(); i++)
	{
		if (proot->next[word.at(i) - 'a'] == NULL) {
			return 0;
		}
		proot = proot->next[word.at(i) - 'a'];
	}
	if (proot->end == false) {
		return 0;
	}
	else {
		return proot->count;
	}
}
bool cmp(const Node* a, const Node* b) {
	return a->count > b->count;
}
vector<Node*> TrieTree::topNWord(int n) {
	vector<Node*> result;
	sort(wordList.begin(), wordList.end(), cmp);
	for (int i = 0; i < n && i < wordList.size(); i++) {
		result.push_back(wordList[i]);
	}
	return result;
}
string TrieTree::retrievalWord(Node* node) {
	string word = "";
	while (node->pre != NULL) {
		word += node->letter;
		node = node->pre;
	}
	reverse(word.begin(),word.end());
	return word;
}
char toLower(char c) {
	if ('a' <= c && c <= 'z')
		return c;
	else if ('A' <= c && c <= 'Z')
		return c - 'A' + 'a';
}
bool isLetter(char c) {
	if ('a' <= c && c <= 'z')
		return true;
	else if ('A' <= c && c <= 'Z')
		return true;
	else if (c == '_' || c == '\'')
		return true;
	return false;
}
void TrieTree::buildTrie(string book) {
	string word = "";
	for (int i = 0; i<book.size();i++) {
		if (isLetter(book[i])) {
			word += toLower(book[i]);
		}
		else {
			if (word != "") {
				insert(word);
				//cout << word << endl;
				word = "";
			}
		}
	}
	if (word != "")
		insert(word);
}
bool EndWith(const string& str, const string& strEnd) {
	if (str.empty() || strEnd.empty() || strEnd.size() > str.size()) {
		return false;
	}
	return str.compare(str.size() - strEnd.size(), strEnd.size(), strEnd) == 0 ? true : false;
}
void dir(string path, vector<string>& files)
{
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, exdName;

	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) {
		return;
	}
	do {
		if (fileInfo.attrib&_A_SUBDIR && fileInfo.name[0] != '.') {
			//cout << fileInfo.name << " " << (fileInfo.attrib&_A_SUBDIR ? "[folder]" : "[file]") << endl;
			dir(path + "\\" + fileInfo.name, files);
		}
		else{
			string fname(fileInfo.name);
			if (EndWith(fname, ".txt")) {
				//cout << fileInfo.name << endl;
				files.push_back(path + "\\" + fileInfo.name);
			}
		}
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return;
}
int main(int argc, char* argv[])
{
	string dirPath(argv[1]);
	int N = atoi(argv[2]);
	TrieTree T;
	vector<string> files;
	dir(dirPath,files);
	cout << "total txt file: " << files.size() << endl;
	string book = "";
	double time1 = clock();
	for (int i = 0; i < files.size(); i++) {
		//cout << files[i] << endl;
		///cout << i << endl;
		ifstream f(files[i]); 
		string str((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());
		book += str + " ";
	}
	double time2 = clock();
	cout << "read file = " << (double)(time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	double time3 = clock();
	T.buildTrie(book);
	vector<Node*> result = T.topNWord(N);
	double time4 = clock();
	cout << "build tire and find top N = " << (double)(time4 - time3) / CLOCKS_PER_SEC << "s" << endl;
	for (Node* n : result) {
		cout << T.retrievalWord(n) << " " << n->count << endl;
	}
	cout << "total time = " << (double)(time4 - time1) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
