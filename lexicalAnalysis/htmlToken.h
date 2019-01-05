#pragma once
#include<string>
#include<vector>

//定义一个token的数据结构
class HtmlToken {
public:
	enum TokenType
	{
		kUninitialized,//不确定类型
		DOCTYPE,//文档类型
		kStartTag,//标签的开始
		kEndTag,//标签的结束
		kComment,//注释
		kCharacter,//标签的内容
		kEndOfFile,//文档结束
	};
	struct Attribute
	{
		std::string key;
		std::string value;
	};
	void SetType(TokenType t) { _type = t; }
	void SetLength(unsigned t) { _length=t; }
	void SetData(std::string t) { _data = t; }
	void PushData(char t) { _data.append(1,t); }
	void AppendAttributeKeyList() {
		list_key.push_back(tmp_key);
		tmp_key.clear();
	}
	void AppendAttributeValueList() {
		list_value.push_back(tmp_value);
		tmp_value.clear();
	}
	void PushKey(char t) {
		tmp_key.append(1,t);
	}
	void PushValue(char t) {
		tmp_value.append(1,t);
	}
	void reset() {
		_type = kUninitialized;
		_data.clear();
		_length = 0;
		list_key.clear();
		list_value.clear();
		tmp_key.clear();
		tmp_value.clear();
	}
	TokenType getType() { return _type; }
	std::string& getData() { return _data; }
	std::vector<std::string>& getKey() { return list_key; };
	std::vector<std::string>& getValue() { return list_value; };
private:
	TokenType _type;
	unsigned _length;
	std::string _data;
	std::vector<std::string> list_key;
	std::vector<std::string> list_value;
	std::string tmp_key;
	std::string tmp_value;
};