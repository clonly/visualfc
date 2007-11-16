#ifndef _PAGE_BASE_T_H_
#define _PAGE_BASE_T_H_

template <typename T>
class page_base_t
{
public:
	codeparser	* pcode;
	QLib::Event<void,Token*> EventGoToLine;
public:
	const char * page_name() 
	{ 
		return "name unkown"; 
	}
//	QLib::Event<void,project_dsp*>		EventProjectChange;
//	QLib::Event<void,Token*>		EventClassChange;
//	QLib::Event<void,CResDialog*>	EventResDialogChange;
//	QLib::Event<void,CResMenu*>		EventResMenuChange;
	void OnClassChange(Token * tkcls)
	{
	}
	void OnResDialogChange(CResDialog * dlg)
	{
	}
	void OnResMenuChange(CResMenu * menu)
	{
	}
	void OnCloseProject()
	{
	}
};
#endif //_PAGE_BASE_T_H_