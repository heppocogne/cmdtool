# cmdtool
easy, simple command line parser

# sample code

`
//sample.exe -f myfile -vec 100 200 400 800

cmdtool::parser cmdline(argc,argv,'-'); // '-' is a key prefix(optional)

if(cmdline.hasKey("f")) //single value
{
  //f=myfile
  std::cout<<"f="<<cmdline.get<std::string>("f")<<std::endl;
}

if(cmdline.hasKey("vec")) //array
{
  //100, 200, 400, 800,
  std::vector<int> vec_int=cmdline.get_vector<int>("v");
  std::cout<<"vec=";
  for(const auto& value:vec_int)
    std::cout<<value<<", ";
  std::cout<<std::endl;
}
`
