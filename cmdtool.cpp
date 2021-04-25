#include "cmdtool.h"


using namespace cmdtool;

int parser::getIdx(const std::string& key)const
{
	const auto key2=prefix+key;
	for(int i=0;i<argc;++i)
	{
		if(argv[i]==key2)
			return i;
	}
	return -1;
}

bool parser::hasKey(const std::string& key)const
{
	return 0<=getIdx(key);
}

bool parser::isKey(const int idx)const
{
	if(0<=idx && idx<argc)
	{
		return prefix==std::string(argv[idx].begin(),argv[idx].begin()+prefix.length());
	}
	else
		return false;
}

template<>
std::string parser::get<std::string>(const std::string& key)const
{
	const std::vector<std::string> vec=get_vector<std::string>(key);
	if(0<vec.size())
		return vec[0];
	else
		return "";
}

template<>
std::string parser::get<std::string>(const int idx)const
{
	if(0<=idx && idx<argc)
		return argv[idx];
	else
		return "";
}