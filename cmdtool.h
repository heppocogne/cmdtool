#ifndef CMDTOOL_INCLUDED
	#define CMDTOOL_INCLUDED
	
	#include <string>
	#include <vector>
	#include <charconv>
	//#include <iostream>
	
	#define _show(_s) do{}while(0)
	
	namespace cmdtool
	{
		class parser
		{
			parser()=delete;
			parser(const& parser)=delete;
		protected:
			const int argc;
			const std::vector<std::string> argv;
			virtual int getIdx(const std::string& key)const;
			virtual bool isKey(const int idx)const;
		public:
			parser(const int _argc, const char** _argv, const char _prefix='-')
				:argc(_argc),argv(_argv, _argv+argc),prefix({_prefix}){}
			parser(const int _argc, const char** _argv, const std::string& _prefix)
				:argc(_argc),argv(_argv, _argv+argc),prefix(_prefix){}
			
			std::string prefix;
			
			template<typename T>
			std::vector<T> get_vector(const std::string& key)const
			{
				std::vector<T> rt_vec;
				const int idx_base=getIdx(key);
				
				_show(idx_base);
				
				if(0<=idx_base)
				{
					for(int i=idx_base+1; i<argc&&!isKey(i); ++i)
						rt_vec.push_back(get<T>(i));
				}
				
				return rt_vec;
			}
			
			template<typename T>
			T get(const std::string& key)const
			{
				const std::vector<T> vec=get_vector<T>(key);
				
				_show(vec.size());
				
				if(0<vec.size())
					return vec[0];
				else
					return static_cast<T>(0);
			}
			
			template<typename T>
			T get(const int idx)const
			{
				if(0<=idx && idx<argc)
				{
					T value;
					const auto res=std::from_chars(argv[idx].c_str(), argv[idx].c_str()+argv[idx].length(), value);
					if(res.ptr!=argv[idx].c_str())
						return value;
				}
				
				return static_cast<T>(0);
			}
			
			virtual bool hasKey(const std::string& key)const;
		};
		
		template<>
		std::string parser::get<std::string>(const int idx)const;
		
		template<>
		std::string parser::get<std::string>(const std::string& key)const;
	};
	
#endif
