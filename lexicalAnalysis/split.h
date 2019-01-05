#pragma once
#include<string>
#include<vector>
#include"htmlToken.h"
//class Split
//{
//public:
//
//	enum STATE {
//		INIT,
//		WORD,
//		SINGLEINWORD
//	};
//	Split(STATE s) :state(s) {}
//
//	const static std::string all_word;
//	STATE state;
//	
//	void porcessInit(char);
//	void processWord(char);
//	void processSingleIn(char);
//	std::vector <std::string> getWordList() { return word_list; }
//private:
//	
//	std::string _word;
//	std::vector <std::string> word_list;
//};
class Split
{
public:

	enum STATE {
		//通用状态
		DataState,
		TagNameState,
		//起始标签，可能含有属性的状态
		TagOpenState,
		BeforeAttributeNameState,
		AttributeNameState,
		AttributeValueState,
		BeforeAttributeValueState,
		AttributeValueDoubleQuotedState,
		AfterAttributeValueQuotedState,

		CharContentState,
		SpaceInCharContentState,
		//结束标签的状态
		EndTagOpenState，
		
	};
	Split(STATE s) :state(s) {}

	STATE getState() { return state; }

	void ProcessDataState(char);
	void ProcessTagOpenState(char);
	void ProcessTagNameState(char);
	void ProcessEndTagOpenState(char);
	void ProcessBeforeAttributeNameState(char);
	void ProcessAttributeNameState(char);
	void ProcessBeforeAttributeValueState(char);
	void ProcessAttributeValueDoubleQuotedState(char);
	void PeocessAttributeValueState(char);
	void ProcessAfterAttributeValueQuotedState(char);
	void ProcessCharContentState(char);
	void ProcessSpaceInCharContentState(char);

	bool CanPrint(char);
	void PrintToken();
	std::vector <HtmlToken> getTokenLlist() { return token_list; }
private:
	STATE state;
	HtmlToken tokenEnty;
	std::vector <HtmlToken> token_list;
};

