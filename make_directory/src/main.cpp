
#include "choco.hpp"

class MakeDirectory{

    private:

	std::vector<Filesystem::ParsedArgs> parsed_arguements;

	void make_directory_init(){

	    for (Filesystem::ParsedArgs &currentArgs : parsed_arguements){

		if (currentArgs.flags.value() & Filesystem::VERBOSE_FLAG){

		    make_directory_verbose(currentArgs.arguements);
		    continue;

		}

		if (currentArgs.flags.value() & Filesystem::QUIET_FLAG){

		    make_directory_quiet(currentArgs.arguements);
		    continue;

		}

		make_directory_quiet(currentArgs.arguements);

	    }

	}

	void make_directory_quiet(std::vector<std::string> arguements){

	    for (std::basic_string<char> arguement : arguements){

		if (make_directory_execution(static_cast<std::filesystem::path> (arguement)) == 'y'){

		}

	    }

	}

	void make_directory_verbose(std::vector<std::string> arguements){

	    for (std::basic_string<char> arguement : arguements){

		if (make_directory_execution(static_cast<std::filesystem::path> (arguement)) == 'y'){

		    Filesystem::tree(static_cast<std::filesystem::path>(arguement));

		}

	    }

	}

	const char make_directory_execution(std::filesystem::path arguement){

	    if (Filesystem::fileExist(arguement)){

		std::println("This {} directory path exist", arguement.string());

		char desicion;

		do{

		    std::print("Do you still want to create a new one?(y/n) ");
		    desicion = std::getchar();

		    switch(desicion){

			case 'y':
			    std::filesystem::create_directories(arguement);
			    return desicion;

			case 'n':
			    return desicion;

			default:
			    std::print("\njust pick y or n!");
			    break;

		    }

		}while(Filesystem::is_running);

	    }

	    std::filesystem::create_directories(arguement);

	    return 'y';

	}

    public:

	MakeDirectory(std::vector<Filesystem::ParsedArgs> parsedArgs)

	    : parsed_arguements(parsedArgs)

	{
	    make_directory_init();
	};


};

int main(int argc, char *argv[]){

    try{

	const int initialPos = 1;
	std::vector<std::basic_string<char>> arguements;

	for (int i = initialPos; i < argc; i++){

	    arguements.push_back(argv[i]);

	}

	std::vector<Filesystem::ParsedArgs> parsedArgs = Filesystem::dispatchParsedArgs(arguements);

	MakeDirectory makeDirectory(parsedArgs);

    }catch(std::exception &error){

	std::cerr << error.what() << std::endl;

	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
