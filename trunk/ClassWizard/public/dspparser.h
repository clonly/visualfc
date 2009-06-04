#ifndef _DSPPARSER_H__
#define _DSPPARSER_H__

//time 2007-4-24
//copyright QWL1996@GMAIL.COM
#include "../public/wtlfileex.h"

class dspparser
{
public:
	CSimpleArray<CString>	source;
	CString					root_path;
public:
	bool load_cbp(LPCTSTR lpszFileName);
	bool load_dsp(LPCTSTR lpszFileName);
	bool load_vcproj(LPCTSTR lpszFileName);
};

inline CString get_file_root(const CString & filename)
{
	int i = filename.ReverseFind(_T('\\'));
	if (i != -1) 
	{
		return filename.Left(i+1);
	}
	return _T("");
}

inline CString get_file_ext(const CString & filename)
{
	int i = filename.ReverseFind(_T('.'));
	if (i != -1) 
	{
		return filename.Right(filename.GetLength()-i);
	}
	return _T("");
}

inline bool dspparser::load_vcproj(LPCTSTR lpszFileName)
{
	source.RemoveAll();
	root_path = get_file_root(lpszFileName);
	CTextFile file;
	if (file.Open(lpszFileName,CFile::modeRead | CFile::shareDenyNone) == FALSE)
	{
		return false;
	}
	CString line;
	CString tmp;
	const int len = strlen("RelativePath=");///sizeof(char);
	while(file.ReadLine(line))
	{
		line.TrimLeft();
		line.TrimRight();
		if (line.Left(len) == _T("RelativePath=")) 
		{
			tmp = line.Right(line.GetLength()-len);
			int left = tmp.Find(_T('\"'));
			int right = tmp.ReverseFind(_T('\"'));
			if (left != -1 && right != -1)
			{
				tmp = tmp.Mid(left+1,right-left-1);
				source.Add(root_path+tmp);
			}
		}
	}
	file.Close();
	return true;
}

inline bool dspparser::load_dsp(LPCTSTR lpszFileName)
{
	source.RemoveAll();
	root_path = get_file_root(lpszFileName);
	CTextFile file;
	if (file.Open(lpszFileName,CFile::modeRead | CFile::shareDenyNone) == FALSE)
	{
		return false;
	}
	CString line;
	CString tmp;
	while(file.ReadLine(line))
	{
		if (line.Left(7) == _T("SOURCE=")) 
		{
			tmp = line.Right(line.GetLength()-7);
			if (tmp.Left(1) == _T("\""))
			{
				tmp.TrimLeft(_T("\""));
				tmp.TrimRight(_T("\""));
			}
			else 
			{
				tmp = root_path+tmp;
			}
			source.Add(tmp);
		}
	}
	file.Close();
	return true;
}

inline bool dspparser::load_cbp(LPCTSTR lpszFileName)
{
	source.RemoveAll();
	root_path = get_file_root(lpszFileName);
	CTextFile file;
	if (file.Open(lpszFileName,CFile::modeRead | CFile::shareDenyNone) == FALSE)
	{
		return false;
	}
	CString line;
	CString tmp;
	const int len = strlen("filename=");///sizeof(char);
	int pos = -1;
	while(file.ReadLine(line))
	{
		line.TrimLeft();
		line.TrimRight();
		pos = line.Find(_T("filename="));
		if (pos != -1)
		{
			tmp = line.Right(line.GetLength()-pos-len);
			int left = tmp.Find(_T('\"'));
			int right = tmp.ReverseFind(_T('\"'));
			if (left != -1 && right != -1)
			{
				tmp = tmp.Mid(left+1,right-left-1);
				source.Add(root_path+tmp);
			}
		}
	}
	file.Close();
	return true;
}

#endif //_DSPPARSER_H__