/**
 * @FILE: 
 * @BRIEF: 
 * @Copyright (C) 2011 .
 * @AUTHOR: WX
 * @DATE: 2011-02-28
 * @VERSION: 1.0
 * @REF:this file depends by STL and WIN API.
 */

#include <windows.h>
#include <iostream>
#include <string>
#include <list>



using namespace std;

#define ENABLE_DEBUG_OUTPUT

#define Debug_OutPut(s) \
{\
    cout << s << endl;\
}



#define MyFileApi(_fun_)  (File_##_fun_)


/**
 * @BRIEF: Get Sub Dir (without recursion )
 * @AUTHOR: WX
 * @DATE: 2011-02-28
 * @PARAM string searchPathRoot:root dir for search
 * @PARAM list<string> & pathlist:Sting List For Store The All SubDir FullPath Of Search  Result
 * @RETURN int:The Count Of Search Result
 */
int MyFileApi(SearchSubDir)(string searchPathRoot,list<string> &pathlist)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind=NULL;
	int count = 0;
	string  fullPath;

	searchPathRoot += "\\";
	fullPath = searchPathRoot + "*.*";
	hFind=FindFirstFile(fullPath.c_str(),&FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
#ifdef ENABLE_DEBUG_OUTPUT	
		cout << "Error:" << fullPath << "Find Nothing" <<endl;
#endif
		return 0;
	}

	do
	{
		if ('.' == FindFileData.cFileName[0])
		{
			continue;
		}
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			count++;
			fullPath = searchPathRoot + FindFileData.cFileName;
			pathlist.push_back(fullPath);
#ifdef ENABLE_DEBUG_OUTPUT	
			Debug_OutPut(fullPath);
#endif
		}
	} while(FindNextFile(hFind, &FindFileData));
	FindClose(hFind);

	return count;
}


/**
 * @BRIEF: Get Sub Dir With  Depth limit
 * @AUTHOR: WX
 * @DATE: 2011-02-28
 * @PARAM string searchPath:root dir for search
 * @PARAM list<string> &Searchlist:Sting List For Store The All SubDir FullPath Of Search  Result
 * @PARAM  maxDepth:the max Depth of Search Level.(if maxDepth eque 0,that meaning without any limit)
 * @RETURN int:The Count Of Search Result
 */
int  MyFileApi(FindAllSubDir)(string searchPath,list<string> &Searchlist,int maxDepth)
{
	string tmpPath;
	int i,j,SubDirCount,count;
	list<string> pathlist;
	list<string>::iterator  pathIterator;

	pathlist.push_front(searchPath);
	SubDirCount = 0;
	count = 0;
	for (i=0;(i<maxDepth) || (0 == maxDepth);i++)
	{
		SubDirCount = 0;
		while (!pathlist.empty())
		{
			pathIterator = pathlist.begin();
			SubDirCount += MyFileApi(SearchSubDir)(*pathIterator,Searchlist);
			pathlist.pop_front();
		}
		if ((!Searchlist.empty()) && (SubDirCount > 0))
		{
			count += SubDirCount;
			pathIterator = Searchlist.end();
			
			for (j=0;j<SubDirCount;j++)
			{
				pathIterator--;
				pathlist.push_front(*pathIterator);
			}
		}
		else
		{
#ifdef ENABLE_DEBUG_OUTPUT	
			cout << "############# Find Finished ["<< count << "]Dirs ############" <<endl;
#endif
			break;
		}
	}

	return count;
}


int main()
{
	list<string> pathlist;

	File_FindAllSubDir("C:",pathlist,0);//C:\\TestDir
	
	return 0;
}
