// Connect.h : CConnect ������

#pragma once
#include "resource.h"       // ������

#include <atlapp.h>
#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlsplit.h>
#include <atlmisc.h>

#include "../public/fc_core.h"

/*
#include "../public/foxlib.h"
#include "../public/foxuilib.h"
#include "../public/plugin.h"
#include "../public/wtlfile.h"
using namespace fox;

struct  fox_plugin{
	plugin::manager		m_plugins;
	dynamic_t<ui::vs_item>	p_item;

	BOOL LoadPlugins()
	{
		if (!m_plugins.load(GetModulePath(_AtlModule.GetResourceInstance())) )
			return FALSE;
		
		for (unsigned int i = 0; i < m_plugins.ar.size(); i++)
		{
			CString lib = m_plugins.ar[i].path;
			lib += _T("\\");
			lib += m_plugins.ar[i].runtime.library;
			if (lstrcmpi(m_plugins.ar[i].plugin.classname,_T("fox.ui.item")) == 0)
			{
				p_item.load(lib);
			}
			
		}
	
		return TRUE;
	}
	void  CloseItem()
	{
		if (p_item.empty())
			return;
		if (p_item->handle())
			::DestroyWindow(p_item->handle());
	}
};
*/
using namespace AddInDesignerObjects;
//using namespace EnvDTE;
using namespace EnvDTE80;
using namespace Microsoft_VisualStudio_CommandBars;

/// <summary>����ʵ����ӳ���Ķ���</summary>
/// <seealso class='IDTExtensibility2' />
class ATL_NO_VTABLE CConnect : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConnect, &CLSID_Connect>,
	public IDispatchImpl<EnvDTE::IDTCommandTarget, &EnvDTE::IID_IDTCommandTarget, &EnvDTE::LIBID_EnvDTE, 7, 0>,
	public IDispatchImpl<_IDTExtensibility2, &IID__IDTExtensibility2, &LIBID_AddInDesignerObjects, 1, 0>,
	public fox::vs2005_addin
{
public:
	/// <summary>ʵ����ӳ������Ĺ��캯�����뽫���ĳ�ʼ���������ڴ˷����ڡ�</summary>
	fc_core	   m_fc;
	CConnect()
	{
		m_fc.load(_AtlModule.GetResourceInstance(),this);
		m_fc.create();
	}
	~CConnect()
	{
		m_fc.free();
	}
	CAtlArray<CString>	m_files;
	virtual size_t get_file_count(const char * proj)
	{
		return m_files.GetCount();
	}
	virtual const char * get_files(const char * proj, int i)
	{
		return (LPCTSTR)m_files[i];
	}
	virtual bool goto_line(const char * file, int line);
	virtual int  get_line_column(const char * file, int line);
	virtual bool insert_block(const char * file, int line, int column, const char * text);
	virtual bool replace_text(const char * file, int line, const char * old, const char * text);


DECLARE_REGISTRY_RESOURCEID(IDR_ADDIN)
DECLARE_NOT_AGGREGATABLE(CConnect)

BEGIN_COM_MAP(CConnect)
	COM_INTERFACE_ENTRY(IDTExtensibility2)
	COM_INTERFACE_ENTRY(IDTCommandTarget)
	COM_INTERFACE_ENTRY2(IDispatch, IDTExtensibility2)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
//IDTExtensibility2 �ľ���ʵ��:

	/// <summary>ʵ�� IDTExtensibility2 �ӿڵ� OnConnection �������������ڼ�����ӳ����֪ͨ��</summary>
	/// <param term='application'>����Ӧ�ó���ĸ�����</param>
	/// <param term='connectMode'>������ӳ���ļ��ط�ʽ��</param>
	/// <param term='addInInst'>��ʾ����ӳ���Ķ���</param>
	/// <seealso class='IDTExtensibility2' />
	STDMETHOD(OnConnection)(IDispatch * Application, ext_ConnectMode ConnectMode, IDispatch *AddInInst, SAFEARRAY **custom);

	/// <summary>ʵ�� IDTExtensibility2 �ӿڵ� OnDisconnection ��������������ж����ӳ����֪ͨ��</summary>
	/// <param term='disconnectMode'>������ӳ����ж�ط�ʽ��</param>
	/// <param term='custom'>�ض�������Ӧ�ó���Ĳ������顣</param>
	/// <seealso class='IDTExtensibility2' />
	STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY **custom );

	/// <summary>ʵ�� IDTExtensibility2 �ӿڵ� OnAddInsUpdate ����������ӳ��򼯺��ѷ�������ʱ����֪ͨ��</summary>
	/// <param term='custom'>�ض�������Ӧ�ó���Ĳ������顣</param>
	/// <seealso class='IDTExtensibility2' />	
	STDMETHOD(OnAddInsUpdate)(SAFEARRAY **custom );

	/// <summary>ʵ�� IDTExtensibility2 �ӿڵ� OnStartupComplete ��������������Ӧ�ó�������ɼ��ص�֪ͨ��</summary>
	/// <param term='custom'>�ض�������Ӧ�ó���Ĳ������顣</param>
	/// <seealso class='IDTExtensibility2' />
	STDMETHOD(OnStartupComplete)(SAFEARRAY **custom );

	/// <summary>ʵ�� IDTExtensibility2 �ӿڵ� OnBeginShutdown ��������������ж������Ӧ�ó����֪ͨ��</summary>
	/// <param term='custom'>�ض�������Ӧ�ó���Ĳ������顣</param>
	/// <seealso class='IDTExtensibility2' />
	STDMETHOD(OnBeginShutdown)(SAFEARRAY **custom );
	
//IDTCommandTarget �ľ���ʵ��:

	/// <summary>ʵ�� IDTCommandTarget �ӿڵ� QueryStatus �������˷����ڸ��¸�����Ŀ�����ʱ����</summary>
	/// <param term='commandName'>Ҫȷ����״̬����������ơ�</param>
	/// <param term='neededText'>������������ı���</param>
	/// <param term='status'>���������û������е�״̬��</param>
	/// <param term='commandText'>neededText ������Ҫ����ı���</param>
	/// <seealso class='Exec' />
	STDMETHOD(QueryStatus)(BSTR CmdName, EnvDTE::vsCommandStatusTextWanted NeededText, EnvDTE::vsCommandStatus *StatusOption, VARIANT *CommandText);

	/// <summary>ʵ�� IDTCommandTarget �ӿڵ� Exec �������˷����ڵ��ø�����ʱ���á�</summary>
	/// <param term='commandName'>Ҫִ�е���������ơ�</param>
	/// <param term='executeOption'>����������Ӧ������С�</param>
	/// <param term='varIn'>�ӵ��÷����ݵ���������Ĳ�����</param>
	/// <param term='varOut'>���������򴫵ݵ����÷��Ĳ�����</param>
	/// <param term='handled'>֪ͨ���÷��������Ƿ��ѱ�����</param>
	/// <seealso class='Exec' />
	STDMETHOD(Exec)(BSTR CmdName, EnvDTE::vsCommandExecOption ExecuteOption, VARIANT *VariantIn, VARIANT *VariantOut, VARIANT_BOOL *Handled);

private:
	CComPtr<DTE2> m_pDTE;
	CComPtr<EnvDTE::AddIn> m_pAddInInstance;
	HRESULT GetActiveProject(EnvDTE::ProjectPtr& pProj);
	HRESULT GetSelectedProject(EnvDTE::ProjectPtr& pProj);
	bool ExecWTLWizard(void);
	bool ExecWINXWizard(void);
	HRESULT GetOpenFileDocument(EnvDTE::DocumentPtr & pDoc, const char * file);
	HRESULT SaveAllDocuments();
};


OBJECT_ENTRY_AUTO(__uuidof(Connect), CConnect)
