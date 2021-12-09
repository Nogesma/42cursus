#include <iostream>
#include <fstream>
#include <algorithm>

std::string *cpy(std::string *s1, std::string s2, size_t n, size_t j)
{
	s1->erase(n, j);
	s1->insert(n, s2);

	return (s1);
}

std::string* replacestr(std::string *buffer, std::string s1, std::string s2)
{
	size_t j;
	size_t start;

	for (size_t i = 0; i < buffer->length(); i++)
	{
		j = 0;
		start = i;
		while ((*buffer)[i] == s1[j] && j < s1.length())
		{
			i++;
			j++;
			if (j == s1.length())
			{
				cpy(buffer, s2, start, j);
				i = start + s2.length();
			}
		}
	}
	return (buffer);
}

int		main( int ac, char **av )
{
	if (ac != 4) return (1);

	std::string filename = av[1];
	std::string s1 = av[2];
	std::string s2 = av[3];

	size_t numberOfNewlines = std::count(s1.begin(), s1.end(), '\n');
	std::cout << numberOfNewlines << std::endl;

	std::string buffer;
	std::string line;

	std::ifstream file (filename);
	std::ofstream replace (filename + ".replace");

	if ( file.is_open() )
	{
		buffer = "";
		while ( --numberOfNewlines > 1 )
		{
			std::getline(file, line);
			if( file.eof() ) break;
			buffer += line;
			buffer += '\n';
		}
		while ( true )
		{
			std::getline(file, line);
			if( file.eof() ) break;
			buffer += line;
			buffer += '\n';
			replacestr(&buffer, s1, s2);
//			std::cout << line << std::endl;
//			std::cout << buffer << std::endl << std::endl;
			size_t nl = buffer.find('\n');
			if (nl == std::string::npos)
				nl = buffer.length();
			replace << buffer.substr(0, nl + 1);
			buffer.erase(0, nl + 1);
		}
		replace << buffer;
		file.close();
		replace.close();
	}
}
