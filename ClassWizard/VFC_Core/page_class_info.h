#ifndef _PAGE_CLASS_INFO_H_
#define _PAGE_CLASS_INFO_H_


class page_class_info : public ui_page_dialog_t<page_class_info,IDD_PAGE_CLASSINFO>,
						public page_base_t<page_class_info>
{
public:
	BEGIN_DLGRESIZE_MAP(page_class_info)
		DLGRESIZE_CONTROL(IDC_INFO_STATIC, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_INFO_BASECLASS, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_INFO_RESOURCE, DLSZ_SIZE_X)
	END_DLGRESIZE_MAP()

	const char * page_name()
	{
		return "Class Info";
	}

	void OnInit()
	{
	}
	void OnClassChange(Token * tkcls)
	{
		if (tkcls)
			SetDlgItemText(IDC_INFO_BASECLASS,tkcls->m_AncestorsString);
		else
			SetDlgItemText(IDC_INFO_BASECLASS,_T(""));
	}
	void OnResDialogChange(CResDialog * dlg)
	{
		if (dlg)
			SetDlgItemText(IDC_INFO_RESOURCE,dlg->m_ID);
		else
			SetDlgItemText(IDC_INFO_RESOURCE,_T(""));
	}
};


#endif