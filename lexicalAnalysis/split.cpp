
#include"htmlToken.h"
#include "split.h"

#include<iostream>
#include <ctype.h>

void Split::ProcessDataState(char var)
{
	if (var=='<')
	{
		state=TagOpenState;
		tokenEnty.PushData(var);
		tokenEnty.SetType(HtmlToken::kUninitialized);
	}
	else if (CanPrint(var)) {
		state = CharContentState;
		tokenEnty.SetType(HtmlToken::kCharacter);
		tokenEnty.PushData(var);
	}
}

void Split::ProcessTagOpenState(char var)
{
	if (CanPrint(var)) {
		state = TagNameState;
		tokenEnty.SetType(HtmlToken::kStartTag);
		tokenEnty.PushData(var);
	}
}

void Split::ProcessTagNameState(char var)
{
	if (var == ' ') {
	state = BeforeAttributeNameState;
	tokenEnty.PushData(var);
	}
	else if (CanPrint(var)) {
		tokenEnty.PushData(var);
	}
	
}
void Split::ProcessEndTagOpenState(char var)
{
}
void Split::ProcessBeforeAttributeNameState(char var)
{
	if (isprint(var)) {
		tokenEnty.PushKey(var);
		tokenEnty.PushData(var);
		state = AttributeNameState;
	}
	
}
void Split::ProcessAttributeNameState(char var)
{
	if (var == '=') {
	tokenEnty.PushData(var);
	tokenEnty.AppendAttributeKeyList();
	state = BeforeAttributeValueState;
	}
	else if (CanPrint(var)) {
		tokenEnty.PushKey(var);
		tokenEnty.PushData(var);
	}
	
}
void Split::ProcessBeforeAttributeValueState(char var)
{
	if (var=='"') {
		tokenEnty.PushData(var);
		state = AttributeValueDoubleQuotedState;
	}
}
void Split::ProcessAttributeValueDoubleQuotedState(char var)
{
	
	if (var == '"') {	
		state = AfterAttributeValueQuotedState;
		tokenEnty.AppendAttributeValueList();
		tokenEnty.PushData(var);
	}
	else if (CanPrint(var)) {
		tokenEnty.PushValue(var);
		tokenEnty.PushData(var);
	}
	
}
void Split::PeocessAttributeValueState(char var)
{
	
	if (CanPrint(var)) {
		tokenEnty.PushValue(var);
		tokenEnty.PushData(var);
	}
}
void Split::ProcessAfterAttributeValueQuotedState(char var)
{
	
	if (var == '>') {
		state = DataState;
		tokenEnty.PushData(var);
		token_list.push_back(tokenEnty);
		
		tokenEnty.reset();
		
	}
	else if (var == ' ') {
		state = BeforeAttributeNameState;
		tokenEnty.PushData(var);
	}
}

void Split::ProcessCharContentState(char var)
{
	if (var == '<') {
		state = DataState;
		tokenEnty.PushData(var);
		token_list.push_back(tokenEnty);
		tokenEnty.reset();
	}
	else if (var == ' ') {
		tokenEnty.PushData(var);
		state = SpaceInCharContentState;
	}
	else if (CanPrint(var)) {
		tokenEnty.PushData(var);
	}
}

void Split::ProcessSpaceInCharContentState(char var)
{
	if (var == '<') {
		state = DataState;
		
		token_list.push_back(tokenEnty);
		tokenEnty.reset();
	}
	else if (CanPrint(var)) {
		tokenEnty.PushData(var);
	}
}

bool Split::CanPrint(char var)
{
	return (isprint(var)&&(var!=' '));
}

void Split::PrintToken()
{
	for (auto var:token_list) {
		
		std::cout << var.getData() << " type:" << var.getType();
		if (!var.getKey().empty()) {
			std::cout << " attribute:";
			std::vector<std::string>& keys(var.getKey());
			std::vector<std::string>& values(var.getValue());
			for (int i = 0; i < var.getKey().size(); i++) {
				std::cout << "["<<keys[i]<<":"<< values[i]<<"]";
			}
		}
		std::cout << std::endl;
		
	}
}
