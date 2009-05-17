// tools_addin.cpp: implementation of the tools_addin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tools_addin.h"
#include "..\public\wtlfileex.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tools_addin::tools_addin()
{

}

tools_addin::~tools_addin()
{

}

int	tools_addin::get_version()
{
	return 0x0100;
}
const char *	tools_addin::get_addin_name()
{
	return "VFC Tools 0.8 Beta1";
}
int	tools_addin::get_line_column(const char * file, int line)
{
	return 0;
}

inline void string_to_array(LPCTSTR text, CSimpleArray<CString> & array, LPCTSTR separator = _T("\r\n"), bool trimSpaces = false)
{
    CString search = text;
    int seplen = CString(separator).GetLength();
    while (true)
    {
        int idx = search.Find(separator);
        if (idx == -1)
        {
            if (trimSpaces)
            {
                search.TrimLeft();
                search.TrimRight();
            }
            if (!search.IsEmpty())
                array.Add(search);
            break;
        }
        CString part = search.Left(idx);
        search.Delete(0, idx + seplen);
        if (trimSpaces)
        {
            part.TrimLeft();
            part.TrimRight();
        }
        if (!part.IsEmpty())
            array.Add(part);
    }
}

bool tools_addin::insert_block(const char * file, int line, int column, const char * text)
{
	CTextFile in;
	if (!in.Open(file))
	{
		return false;
	}
	CSimpleArray<CString> array;
	CString str;
	while(in.ReadLine(str))
	{
		array.Add(str);
	}
	in.Close();

	CFile out;
	if (!out.Open(file,CFile::modeWrite,NULL))
	{
		return false;
	}
	str = "";
	for (int i = 0; i < array.GetSize(); i++)
	{
		if (i == line)
		{
			CString tmp = text;
			tmp.TrimLeft("\r\n");
			str += tmp;
			str += _T("\r\n");
		}
		str += array[i];
		str += _T("\r\n");
	}
	if (line >= i)
	{
		str += text;
		str += _T("\r\n");
	}
	out.Write(str,str.GetLength());
	out.Close();

	return true;
}

bool tools_addin::replace_text(const char * file, int line, const char * old, const char * text)
{
	CTextFile in;
	if (!in.Open(file))
	{
		return false;
	}
	CSimpleArray<CString> array;
	CString str;
	int i = 1;
	while(in.ReadLine(str))
	{
		if (i == line)
		{
			str.Replace(old,text);
		}
		array.Add(str);
		i++;
	}
	in.Close();

	CFile out;
	if (!out.Open(file,CFile::modeWrite,NULL))
	{
		return false;
	}
	str = "";
	for (i = 0; i < array.GetSize(); i++)
	{
		str += array[i];
		str += _T("\r\n");
	}
	out.Write(str,str.GetLength());
	out.Close();
	return true;
}

bool tools_addin::goto_line(const char * file, int line)
{
	return true;
}

int	tools_addin::get_project_file_count()
{
	return m_dsp.source.GetSize();
}

const char *	tools_addin::get_project_files(int i)
{
	return (LPCTSTR)m_dsp.source[i];
}

const char * tools_addin::get_project_path()
{
	return m_dsp.root_path;
}

const char *	tools_addin::get_project_name()
{
	return m_projName;
}

bool tools_addin::add_project_file(const char * file)
{
	return false;
}

bool tools_addin::ExecVFCWizard()
{
	if (m_fc.pvfc)
 	{
		m_fc.pvfc->load_project(m_projName,NULL);
		return true;
	}
	return false;
}

bool tools_addin::LoadVSProject(const CString &proj)
{
	int pos = proj.ReverseFind(_T('\\'));
	if (pos != -1)
		m_projName = proj.Right(proj.GetLength()-pos-1);
	else
		m_projName = _T("NoName");
	m_dsp.load_vcproj(proj);
	return false;
}
