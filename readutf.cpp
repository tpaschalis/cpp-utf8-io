// readutf.cpp : Read and Write UTF-8 encoded characters to a text file in Windows
// UTF-8 I/O is straightforward in Linux, but presents problems in Windows systems, arising from different locales.
// This is a simple solution to work with, tested on Microsoft Visual Studio 2017 Community Edition
// Created by and uploaded to GitHub by github.com/tpaschalis

// Permission is granted to use/share this code however you want, but feel free to check my other projects on GitHub.

#include "stdafx.h"
#include <iostream>
#include <fstream>

//#include <string>
//#include <locale>

#include <codecvt>
#include <fcntl.h>
#include <io.h>

int main()
{
	// Write file in UTF-8
	std::wofstream wof;
	wof.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	wof.open(L"example.txt");
	wof << L"This is a test. \n";
	wof << L"Μπορώ να γράψω ελληνικούς χαρακτήρες \n";
	wof << L"Ακόμα μια δοκιμή;;!!11?1 \n";
	wof.close();



	// Read file in UTF-8
	std::ifstream f("utf8text.txt");
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(f.rdbuf());
	std::wistream wf(&conv);

#ifdef _WIN32
	_setmode(_fileno(stdout), _O_WTEXT);
#else
	std::setlocale(LC_ALL, "");
#endif 
	for (wchar_t c; wf.get(c); )
		std::wcout << c ;

	system("pause");
	return 0;
}

