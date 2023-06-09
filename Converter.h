#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

typedef struct {
	char data;
	int weight;//节点的权值
	int parent, lchild, rchild; //节点的双亲，左孩子，右孩子的下标
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
	//省略获取二进制文件对象直接自己创建；

	//读取二进制文件到字符串code
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

	//根据code和哈夫曼树译码，返回文本字符串 text
	void decode(HuffmanTree tree) {
		int n = tree[0].weight;//字符集的大小
		int root = 2 * n - 1;//根结点应该在最后位置即tree[2*n-1]
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
				cout << "检测到异常字符：" << c;
			}
			if (tree[cur_node].lchild == -1 && tree[cur_node].rchild == -1) {
				text += tree[cur_node].data;
				cur_node = root;
			}
		}
	}

	//将字符串写入到文件
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