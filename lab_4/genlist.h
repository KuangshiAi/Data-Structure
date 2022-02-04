#pragma once
typedef struct GenListNode
{
	int utype;
	GenListNode* tlink;
	union {
		int ref;
		char value;
		GenListNode* hlink;
	}info;
}GenListNode;