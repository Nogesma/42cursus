#include <iostream>
#include <fstream>
#include <algorithm>

std::string *cpy(std::string *s1, std::string s2, size_t n, size_t j)
{
	s1->erase(n, j);
	s1->insert(n, s2);

	return (s1);
}

std::string* replace_str(std::string *buffer, std::string s1, std::string s2)
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

	std::string buffer;
	std::string line;

	std::ifstream file (filename);
	std::ofstream replace (filename + ".replace");

	if ( file.is_open() )
	{
		buffer = "";
		while ( true )
		{
			std::getline(file, line);
			buffer += line;
			if( file.eof() ) break;
			buffer += '\n';
		}
		replace_str(&buffer, s1, s2);
		replace << buffer;
		file.close();
		replace.close();
	}
}
