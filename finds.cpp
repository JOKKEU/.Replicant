#include "finds.h"
#define fs std::filesystem


fs::path start_path;

static 
file& init(file& file_find)
{
	if (file_find.get_path() == "all") {start_path = "/";}
	else if (file_find.get_path() == ".") 
	{
		start_path = fs::absolute(fs::current_path());
	}
	else {start_path = file_find.get_path();}
	return file_find; 
}


int jokkeu_find(file& file_find, std::pair<int, std::string>& wfile)
{
	try
	{
		file nfile = init(file_find);

		if (!fs::exists(start_path) || !fs::is_directory(start_path))
		{
			std::cout << "\033[31m""The path does not exist or is not a directory.\n" << "\033[31m";
			std::cout << "\033[0m";
			utils_thread::loading = false;
			return EXIT_FAILURE;
		}

		bool file_found = false;
		bool cout_flag = true;

		for (const auto& entry : fs::recursive_directory_iterator(start_path, fs::directory_options::skip_permission_denied))
		{
			if (nfile.get_name() == entry.path().filename().string())
			{
				std::cout << "\033[32m" << "***\nFILE IS FOUND***\n" << "\033[32m";
				std::cout << "\033[0m";
				
				if (wfile.first == 0)
				{
					std::cout << entry.path().filename().string() << std::endl;
					file_found = true;
					break;
				}
				else if (wfile.first == 1)
				{
					if (cout_flag) 
					{
						//std::cout << "write to file...\n";
						cout_flag = false;
					}
					std::ofstream out;
					out.open(wfile.second, std::ios::out | std::ios::trunc);
					if (out.is_open())
					{
						out << entry.path().filename().string() << std::endl;
						out.close();
					}
					else
					{
						std::cout << "Error: Could not open file for writing\n";
						utils_thread::loading = false;
						return EXIT_FAILURE;
					}
					utils_thread::loading = false;
					return EXIT_SUCCESS;
				}
				else if (wfile.first == 2)
				{
					if (cout_flag) 
					{
							//std::cout << "write to file...\n";
							cout_flag = false;
					}
					std::ofstream out(wfile.second, std::ios::app);
					if (out.is_open())
					{
						out << entry.path().filename().string() << std::endl;
						out.close();
					}
					else
					{
						std::cout << "Error: Failed to open file for appending\n";
						utils_thread::loading = false;
						return EXIT_FAILURE;
					}
					utils_thread::loading = false;
					return EXIT_SUCCESS;
				}
				else 
				{
					std::cout << "failed to recognize file operation\n\n";
					utils_thread::loading = false;
					return EXIT_FAILURE;
				}

			}
		}

		if (!file_found)
		{
			std::cout << "\033[31m" <<"\n***FILE IS NOT FOUND***\n" << "\033[31m";
			std::cout << "\033[0m";
			utils_thread::loading = false;
	        return EXIT_FAILURE;
		}
	utils_thread::loading = false;
	return EXIT_SUCCESS;
	}
	catch(const fs::__cxx11::filesystem_error& ex)
	{
		std::cout << "\033[31m" <<"Permission denied. PS. run with root rights.\n"<< "\033[31m";
		std::cout << "\033[31m";
		std::cout << ex.what() << "\n";
		utils_thread::loading = false;
		exit(EXIT_FAILURE);
	}

}

int jokkeu_find_and_path_to_file_first_result(file& file_find, std::pair<int, std::string>& wfile)
{
	try
	{
		file& nfile = init(file_find);

		if (!fs::exists(start_path) || !fs::is_directory(start_path))
		{
			std::cout << "\033[31m" << "The path does not exist or is not a directory.\n" << "\033[31m";
			std::cout << "\033[0m";
			utils_thread::loading = false;
			
			return EXIT_FAILURE;
		}

		bool file_found = false;
		bool cout_flag = true;

		for (const auto& entry : fs::recursive_directory_iterator(start_path, fs::directory_options::skip_permission_denied))
			{
				if (nfile.get_name() == entry.path().filename().string())
				{

					if (wfile.first == 0) 
					{
						std::cout << "\033[32m" <<"\n***FILE IS FOUND***\n" << "\033[32m";
						std::cout << "\033[32m" << "(path): " << entry.path() << "\n" << "\033[32m";
						file_found = true;
						std::cout << "\033[0m";
						utils_thread::loading = false;
						return EXIT_SUCCESS;
					}
					else if (wfile.first == 1)
					{
						if (cout_flag) 
						{
							std::cout << "write to file...\n";
							cout_flag = false;
						}
						std::ofstream out;
						out.open(wfile.second, std::ios::out | std::ios::trunc);
						if (out.is_open())
						{
							out << entry.path() << std::endl; 
							out.close();
						}
						else
						{
							std::cout << "Error: Could not open file for writing\n";
							utils_thread::loading = false;
							return EXIT_FAILURE;
						}
						utils_thread::loading = false;
						return EXIT_SUCCESS;
					}

					else if (wfile.first == 2)
					{
						if (cout_flag) 
						{
							//std::cout << "write to file...\n";
							cout_flag = false;
						}	
						std::ofstream out(wfile.second, std::ios::app);
						if (out.is_open())
						{
							out << entry.path() << std::endl;
							out.close();
						}
						else
						{
							std::cout << "Error: Failed to open file for appending\n";
							utils_thread::loading = false;
							
							return EXIT_FAILURE;
						}
						return EXIT_SUCCESS;
					}
					else 
					{
						std::cout << "failed to recognize file operation\n\n";
						utils_thread::loading = false;
						return EXIT_FAILURE;
					}
				}
			}

		if (!file_found)
		{
			std::cout << "\033[31m" << "\n***FILE IS NOT FOUND***\n" << "\033[31m";
			std::cout << "\033[0m";
			utils_thread::loading = false;
			return EXIT_FAILURE;
		}
		utils_thread::loading = false;	
		return EXIT_FAILURE;
	}
	catch(const fs::__cxx11::filesystem_error& ex)
	{
		std::cout << "Permission denied. PS. run with root rights.\n";
		std::cout << ex.what() << "\n";
		utils_thread::loading = false;
		exit(EXIT_FAILURE);
	}
}


int jokkeu_all_finds_and_path(file& file_find, std::pair<int, std::string>& wfile)
{
	try
	{
		std::vector<fs::directory_entry, std::allocator<fs::directory_entry>> all_files;
		file& nfile = init(file_find);

		if (!fs::exists(start_path) || !fs::is_directory(start_path))
		{
			std::cout << "\033[31m" << "The path does not exist or is not a directory.\n" << "\033[31m";
			std::cout << "\033[0m";
			utils_thread::loading = false;
			return EXIT_FAILURE;
		}

		bool cout_flag = true;

		for (const auto& entry : fs::recursive_directory_iterator(start_path, fs::directory_options::skip_permission_denied))
		{
			try
			{
				if (nfile.get_name() == entry.path().filename().string())
				{
					all_files.push_back(entry);
				}
			}
			catch(const fs::filesystem_error& ex)
			{
				utils_thread::loading = false;
				return EXIT_FAILURE;
			}
		}

		size_t sz_vector = all_files.size();
		size_t count = 1;

		if (wfile.first == 0) 
		{
			if (all_files.empty()) {std::cout << "\033[31m" <<"\nfiles not found."<< "\033[31m\n"; std::cout << "\033[0m"; utils_thread::loading = false;  return EXIT_SUCCESS;}

			std::cout << "\033[33m" <<"\nFound: " << sz_vector << "\n"<< "\033[33m";
			for (auto i = all_files.begin(); i != all_files.end(); ++i)
			{

				std::cout << "[" << count << "] " << i->path() << std::endl; 
				++count;
			}
			std::cout << "\033[0m";
			utils_thread::loading = false;
			return EXIT_SUCCESS;
		}
		else if (wfile.first == 1)
		{
			if (cout_flag) 
			{
				//std::cout << "write to file...\n";
				cout_flag = false;
			}
			std::ofstream out;
			out.open(wfile.second, std::ios::out | std::ios::trunc);
			if (out.is_open())
			{
				for (auto i = all_files.begin(); i != all_files.end(); ++i)
				{

					out << "[" << count << "] " << i->path() << std::endl; 
					++count;
				}
				out.close();
				utils_thread::loading = false;
				return EXIT_SUCCESS;
			}
			else
			{
				std::cout << "Error: Could not open file for writing\n";
				utils_thread::loading = false;
				return EXIT_FAILURE;
			}
		}

		else if (wfile.first == 2)
		{
			if (cout_flag) 
			{
				//std::cout << "write to file...\n";
				cout_flag = false;
			}
			std::ofstream out(wfile.second, std::ios::app);
			if (out.is_open())
			{
				for (auto i = all_files.begin(); i != all_files.end(); ++i)
				{

					out << "[" << count << "] " << i->path() << std::endl; 
					++count;
				} 
				out.close();
				utils_thread::loading = false;
				return EXIT_SUCCESS;
			}
			else
			{
				std::cout << "Error: Failed to open file for appending\n";
				utils_thread::loading = false;
				return EXIT_FAILURE;
			}
		}
		else 
		{
			std::cout << "failed to recognize file operation\n\n";
			utils_thread::loading = false;
			return EXIT_FAILURE;
		}

	}
	catch(const fs::__cxx11::filesystem_error& ex)
	{
		std::cout << "Permission denied. PS. run with root rights.\n";
		std::cout << ex.what() << "\n";
		utils_thread::loading = false;
		exit(EXIT_FAILURE);
	}
}


int included_in_filename(file& inc_string, std::pair<int, std::string>& wfile)
{
	try
	{
		file nfile = init(inc_string);
		std::vector<fs::directory_entry, std::allocator<fs::directory_entry>> all_included;

		bool cout_flag = true;

		for (const auto& entry : fs::recursive_directory_iterator(start_path, fs::directory_options::skip_permission_denied))
		{
			try
			{
				if (static_cast<int>(entry.path().filename().string().find(nfile.get_name())) != -1)
				{
					all_included.push_back(entry);
				}
				
			}
			catch(const fs::filesystem_error& ex)
			{
				utils_thread::loading = false;
				return EXIT_FAILURE;
			}
		}

		size_t count = 1;
		size_t sz_vector = all_included.size();

		if (wfile.first == 0) 
		{
			if (all_included.empty()) {std::cout << "\033[31m" <<"\nfiles not found."<< "\033[31m\n"; std::cout << "\033[0m"; utils_thread::loading = false; return EXIT_SUCCESS;}
			std::cout << "\033[33m" <<"\nFound: " << sz_vector << "\n"<< "\033[33m";

			for (auto i = all_included.begin(); i != all_included.end(); ++i)
			{
				std::cout << "[" << count << "] " << i->path() << std::endl; 
				++count;
			}
			std::cout << "\033[0m";
			utils_thread::loading = false;
			return EXIT_SUCCESS;
		}
		else if (wfile.first == 1)
		{
			if (cout_flag) 
			{
				//std::cout << "write to file...\n";
				cout_flag = false;
			}
			std::ofstream out;
			out.open(wfile.second, std::ios::out | std::ios::trunc);
			if (out.is_open())
			{
				for (auto i = all_included.begin(); i != all_included.end(); ++i)
				{
					out << "[" << count << "] " << i->path() << std::endl; 
					++count;
				}
				out.close();
				utils_thread::loading = false;
				return EXIT_SUCCESS;
			}
			else
			{
				std::cout << "Error: Could not open file for writing\n";
				utils_thread::loading = false;
				return EXIT_FAILURE;
			}
		}

		else if (wfile.first == 2)
		{
			if (cout_flag) 
			{
				//std::cout << "write to file...\n";
				cout_flag = false;
			}
			std::ofstream out(wfile.second, std::ios::app);
			if (out.is_open())
			{
				for (auto i = all_included.begin(); i != all_included.end(); ++i)
				{
					out << "[" << count << "] " << i->path() << std::endl; 
					++count;
				}
				out.close();
				utils_thread::loading = false;
				return EXIT_SUCCESS;
			}
			else
			{
				std::cout << "Error: Failed to open file for appending\n";
				utils_thread::loading = false;
				return EXIT_FAILURE;
			}
		}
		else 
		{
			std::cout << "failed to recognize file operation\n\n";
			utils_thread::loading = false;
			return EXIT_FAILURE;
		}
	}
	catch(const fs::__cxx11::filesystem_error& ex)
	{
		std::cout << "Permission denied. PS. run with root rights.\n";
		std::cout << ex.what() << "\n";
		utils_thread::loading = false;
		exit(EXIT_FAILURE);
	}
}
