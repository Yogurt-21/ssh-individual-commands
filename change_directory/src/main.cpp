
#include "choco.hpp"

class ChangeDirectory{

    private:

	std::vector<Filesystem::ParsedArgs> parsed_arguements;

	void valid(){

	    if (parsed_arguements.at(0).arguements.size() > 1){

		throw std::runtime_error("what are you trying to do?\nyou can't go two paths at the same time");
	    }

	}

	void change_directory_init(){

	    valid();

	    for (Filesystem::ParsedArgs &currentArgs : parsed_arguements){

		change_directory_quiet(currentArgs.arguements);

	    }

	}

	void change_directory_quiet(std::vector<std::string> arguements){

	    for (std::basic_string<char> arguement : arguements){

		change_directory_execution(static_cast<std::filesystem::path> (arguement));

	    }

	}


	void change_directory_execution(std::filesystem::path arguement){

	    if (!Filesystem::fileExist(arguement)){

		throw std::runtime_error("path doesn't exist");

	    }

	    std::filesystem::path current_path = std::filesystem::current_path();

	    current_path /= arguement;

	    std::filesystem::current_path(current_path);

	}

    public:

	ChangeDirectory(std::vector<Filesystem::ParsedArgs> parsedArgs)

	    : parsed_arguements(parsedArgs)

	{
	    change_directory_init();
	};


};

int main(int argc, char *argv[]){

    try{

	const int initialPos = 1;
	std::vector<std::basic_string<char>> arguements;

	for (int i = initialPos; i < argc; i++){

	    arguements.push_back(argv[i]);

	}

	//returning vector of strings and flags

	std::vector<Filesystem::ParsedArgs> parsedArgs = Filesystem::dispatchParsedArgs(arguements);

	ChangeDirectory changeDirectory(parsedArgs);
	std::cout << std::filesystem::current_path();
    }catch(std::exception &error){

	std::cerr << error.what() << std::endl;

	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
