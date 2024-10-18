#include "start.h"
 
std::string filename;
std::string path_to_find;


static
std::string& handler_filename(std::string& fn)
{
	fn.erase(std::remove(fn.begin(), fn.end(), ' '), fn.end());
	return fn;
}


static
std::pair<int, std::string> handler_param(int count, char** param)
{
	try
	{
		if (count < 2) 
		{
			std::string fname = static_cast<std::string> ("");
			return std::make_pair(EXIT_SUCCESS, fname);
		}

		else if (std::string(param[1]).compare("wto"))
		{
			std::string fname = static_cast<std::string> (param[2]);
			return std::make_pair(1, fname);
		}
		else if (std::string(param[1]).compare("wato"))
		{
			std::string fname = static_cast<std::string> (param[2]);
			return std::make_pair(2, fname);
		}
		else
		{
			return std::make_pair(EXIT_SUCCESS, "");;
		}
	}
	catch(const std::logic_error& ex)
	{
		std::cout << ex.what() << std::endl;
		throw ex;
	}
}

static 
int check_help(int count, char** param)
{
    try 
    {
        if (count > 1) 
        {
            std::string temp = static_cast<std::string>(param[1]);
            if (temp.compare("--help") == 0)
            {
                std::cout << "Usage: <program> [options]\n";
				std::cout << "IF NOT OPTIONS - OUTPUT TO CONSOLE\n";
                std::cout << "OPTIONS: \n";
                std::cout << "--help - display this help message\n";
                std::cout << "write to file:\n";
				std::cout << "program wto filename - create and write to file\n";
                std::cout << "program wato filename - create and appending to file\n";
                return EXIT_SUCCESS; 
            }
        }
        return EXIT_FAILURE;
    }
    catch (const std::logic_error& ex)
    {
        std::cout << ex.what() << std::endl;
        throw ex;
    }
}



int start(int count, char** param) 
{
	try 
	{
		if (check_help(count, param) == 0) {return EXIT_SUCCESS;}
		

		std::string choice_operation;
		std::string buffer;
		std::pair<int, std::string> code_fname = handler_param(count, param); // maybe l_e;

		for ( ; ; )
		{

			CLEAR;
			print_logo();
			std::cout << "\n\n";

			std::cout << "\n[+][1] find (result: found [filename] or not found [filename])\n";
			std::cout << "[+][2] ligacy_find(first result) (result - [path-to->file])\n";
			std::cout << "[+][3] ligacy_find (all result)\n";
			std::cout << "[+][4] all included in filename \n\n";

			std::cout << "Enter: filename: ";
			std::getline(std::cin, filename);
			std::cout << "enter directory to search. '.' - this dir, 'all' or '/' - all dir: ";
			std::getline(std::cin, path_to_find);

			std::cout << "OPERATION(default: legacy_find): ";
			std::getline(std::cin, choice_operation);

			std::cout << "\n";
			
			filename = handler_filename(filename); // strip 

			file my_file(filename, path_to_find);

			if (choice_operation == "1")
			{
				std::thread th_find([&my_file, &code_fname] () {
					int des = jokkeu_find(my_file, code_fname);
					if (des == 1)
					{
						std::cout << "[-] Exception in jokkeu_find\n ";
						exit(EXIT_FAILURE);
					}
				});

				std::thread th_console(std::ref(console_loading));

				th_find.join();
				th_console.join();
				
			}
			else if (choice_operation == "2")
			{
				std::thread th_find([&my_file, &code_fname] () {
					int des = jokkeu_find_and_path_to_file_first_result(my_file, code_fname);
					if (des == 1)
					{
						std::cout << "[-] Exception in jokkeu_find_and_path_to_file_first_result\n ";
						exit(EXIT_FAILURE);
					}
				});

				std::thread th_console(std::ref(console_loading));

				th_find.join();
				th_console.join();
	
			}
			else if (choice_operation == "3")
			{
				std::thread th_find([&my_file, &code_fname] () {
					int des = jokkeu_all_finds_and_path(my_file, code_fname);
					if (des == 1)
					{
						std::cout << "[-] Exception in jokkeu_all_finds_and_path\n ";
						exit(EXIT_FAILURE);
					}
				});

				std::thread th_console(std::ref(console_loading));

				th_find.join();
				th_console.join();
				
			}
			else if (choice_operation == "4")
			{

				std::thread th_find([&my_file, &code_fname] () {
					int des = included_in_filename(my_file, code_fname);
					if (des == 1)
					{
						std::cout << "[-] Exception in included_in_filename\n ";
						exit(EXIT_FAILURE);
					}
				});

				std::thread th_console(std::ref(console_loading));

				th_find.join();
				th_console.join();
			}
			else
			{
				std::cout << "Wrong operation.\n";
			}


			std::cout << "Operation[(N)ext/(E)xit]\n";
			std::getline(std::cin, buffer);

			for (auto &c : buffer) c = tolower(c);

			if (buffer == "n") 
			{
				continue;
			}
			else if (buffer == "e") 
			{
				break;
			}
			else 
			{
				std::cout << "Wrong operation.\n";
				continue;
			}
		}
	}
	catch (const std::logic_error& ex)
	{
		std::cout << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...) 
	{}

	std::cout << std::endl;
	return EXIT_SUCCESS;
}
