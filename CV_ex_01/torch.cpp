#include <torch/torch.h>
#include <iostream>
#include <memory>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: example-app <path-to-exported-script-module>\n";
		return -1;
	}
	
	torch::jit::script::Module module;
	try
	{
		module = torch::jit::load(argv[1]);
	}
	catch (const c10::Error& e)
	{
		std::cerr << "Error loading the model\n";
		return -1;
	}
	
	std::cout << "ok\n";
}