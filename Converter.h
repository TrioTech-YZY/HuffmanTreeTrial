#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

typedef struct {
	char data;
	int weight;//�ڵ��Ȩֵ
	int parent, lchild, rchild; //�ڵ��˫�ף����ӣ��Һ��ӵ��±�
} HNode, * HuffmanTree;


class Converter {
private:
	string code;
	string text;
	HuffmanTree huffmantree;

public:
	Converter() {}

	Converter(HuffmanTree tree) {
		huffmantree = tree;
	}
	//ʡ�Ի�ȡ�������ļ�����ֱ���Լ�������

	//��ȡ�������ļ����ַ���code
	void setCode(string fileName) {
		ifstream fin(fileName, ios_base::binary);

		code.clear();

		char buffer[1001];
		while (fin.read(buffer, 1000)) {
			buffer[fin.gcount()] = '\0';
			string str(buffer);
			code += str;
		}
		fin.close();
	}

	//����code�͹����������룬�����ı��ַ��� text
	void decode(HuffmanTree tree) {
		int n = tree[0].weight;//�ַ����Ĵ�С
		int root = 2 * n - 1;//�����Ӧ�������λ�ü�tree[2*n-1]
		int cur_node = root;

		text.clear();

		for (char c : code) {
			if (c == '0') {
				cur_node = tree[cur_node].lchild;
			}
			else if (c == '1') {
				cur_node = tree[cur_node].rchild;
			}
			else {
				cout << "��⵽�쳣�ַ���" << c;
			}
			if (tree[cur_node].lchild == -1 && tree[cur_node].rchild == -1) {
				text += tree[cur_node].data;
				cur_node = root;
			}
		}
	}

	//���ַ���д�뵽�ļ�
	void flush(string fileName) {
		ofstream fout(fileName);
		fout << text;
		fout.close();
	}

	string getText() {
		return text;
	}
	string getCode() {
		return code;
	}
};