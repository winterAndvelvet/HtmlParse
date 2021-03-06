// lexicalAnalysis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string>
#include "split.h"
int main()
{
    
	std::string words;
	
	Split lexical(Split::DataState);
	
	words = "<a     href=\"w3c.  org\"   id=\"test\">winter wang <p id=\"hello\">";
	for(int i=0;i<words.length();i++)
	{
			char var = words.at(i);
			switch (lexical.getState())
			{
			case Split::DataState:
				lexical.ProcessDataState(var);
				continue;
			case Split::TagNameState:
				lexical.ProcessTagNameState(var);
				continue;
			case Split::TagOpenState:
				lexical.ProcessTagOpenState(var);
				continue;
			case Split::BeforeAttributeNameState:
				lexical.ProcessBeforeAttributeNameState(var);
				continue;
			case Split::AttributeNameState:
				lexical.ProcessAttributeNameState(var);
				continue;
			case Split::BeforeAttributeValueState:
				lexical.ProcessBeforeAttributeValueState(var);
				continue;
			case Split::AttributeValueDoubleQuotedState:
				lexical.ProcessAttributeValueDoubleQuotedState(var);
				continue;
			case Split::AttributeValueState:
				lexical.PeocessAttributeValueState(var);
				continue;
			case Split::AfterAttributeValueQuotedState:
				lexical.ProcessAfterAttributeValueQuotedState(var);
				continue;
			case Split::CharContentState:
				lexical.ProcessCharContentState(var);
				if (var == '<') { i -= 1; }
				continue;
			case Split::SpaceInCharContentState:
				lexical.ProcessSpaceInCharContentState(var);
				if (var == '<') { i -= 1; }
				continue;
			default:
				break;
			}
		
	}
	
	lexical.PrintToken();
}
