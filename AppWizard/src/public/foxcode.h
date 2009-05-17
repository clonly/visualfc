#ifndef __FOXCODE_H__
#define __FOXCODE_H__

namespace fox
{
	/*
	code_file * next = &file;
	while (next)
	{
		//process next->path;
		next = next->next;
	}
	*/
	struct code_file
	{
		TCHAR	path[MAX_PATH];
		code_file * next;
		code_file()
		{
			next = NULL;
			path[0] = '\0';
		}
		~code_file()
		{
			if (next != NULL)
			{
				delete next;
			}
			path[0] = '\0';
		}
		void push(LPCTSTR _path)
		{
			if (lstrlen(path) == 0)
			{
				lstrcpyn(path,_path,MAX_PATH);
				return;
			}

			if (next == NULL)
			{
				next = new code_file();
			}

			next->push(_path);
		}
	};
}; //namespace fox
#endif //__FOXCODE_H__