// Connect.cpp : Implementation of CConnect
#include "stdafx.h"
#include "AddIn.h"
#include "Connect.h"

extern CAddInModule _AtlModule;

// When run, the Add-in wizard prepared the registry for the Add-in.
// At a later time, if the Add-in becomes unavailable for reasons such as:
//   1) You moved this project to a computer other than which is was originally created on.
//   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
//   3) Registry corruption.
// you will need to re-register the Add-in by building the MyAddin21Setup project 
// by right clicking the project in the Solution Explorer, then choosing install.


// CConnect
STDMETHODIMP CConnect::OnConnection(IDispatch *pApplication, AddInDesignerObjects::ext_ConnectMode ConnectMode, IDispatch *pAddInInst, SAFEARRAY ** /*custom*/ )
{
	HRESULT hr = S_OK;
	pApplication->QueryInterface(__uuidof(EnvDTE::_DTE), (LPVOID*)&m_pDTE);
	pAddInInst->QueryInterface(__uuidof(EnvDTE::AddIn), (LPVOID*)&m_pAddInInstance);

	m_addin.m_pDTE = m_pDTE;
	m_addin.m_fc.load(_AtlModule.GetResourceInstance(),&m_addin);

	if(ConnectMode == 1) //5 == AddInDesignerObjects::ext_cm_UISetup
	{
		HRESULT hr = S_OK;
		CComPtr<EnvDTE::Commands> pCommands;
		CComPtr<Office::_CommandBars> pCommandBars;
		CComPtr<Office::CommandBarControl> pCommandBarControl;
		CComPtr<EnvDTE::Command> pCreatedCommand;
		CComPtr<Office::CommandBar> pMenuBarCommandBar;

    // When run, the Add-in wizard prepared the registry for the Add-in.
    // At a later time, the Add-in or its commands may become unavailable for reasons such as:
    //   1) You moved this project to a computer other than which is was originally created on.
    //   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
    //   3) You add new commands or modify commands already defined.
    // You will need to re-register the Add-in by building the VFCAddinNETSetup project,
    // right-clicking the project in the Solution Explorer, and then choosing install.
    // Alternatively, you could execute the ReCreateCommands.reg file the Add-in Wizard generated in 
    // the project directory, or run 'devenv /setup' from a command prompt.
		IfFailGoCheck(m_pDTE->get_Commands(&pCommands), pCommands);
		int image = ::GetPrivateProfileInt(_T("VFCAddinNET"),_T("image"),59,fc_core::GetModulePath(_AtlModule.GetResourceInstance())+_T("\\visualfc.ini"));
		if(SUCCEEDED(pCommands->AddNamedCommand(m_pAddInInstance, CComBSTR("VisualFC"), CComBSTR("VisualFC"), CComBSTR("VisualFC for WTL/WinxGui Wizard"), VARIANT_TRUE, image, NULL, EnvDTE::vsCommandStatusSupported+EnvDTE::vsCommandStatusEnabled, &pCreatedCommand)) && (pCreatedCommand))
		{
			//Add a button to the tools menu bar.
			IfFailGoCheck(m_pDTE->get_CommandBars(&pCommandBars), pCommandBars);
			IfFailGoCheck(pCommandBars->get_Item(CComVariant(L"Tools"), &pMenuBarCommandBar), pMenuBarCommandBar);
			IfFailGoCheck(pCreatedCommand->AddControl(pMenuBarCommandBar, 1, &pCommandBarControl), pCommandBarControl);
		}
		return S_OK;
	}
Error:
	return hr;
}

STDMETHODIMP CConnect::OnDisconnection(AddInDesignerObjects::ext_DisconnectMode /*RemoveMode*/, SAFEARRAY ** /*custom*/ )
{
	m_addin.m_pDTE = NULL;
	m_addin.m_fc.free();
	
	m_pDTE = NULL;
	return S_OK;
}

STDMETHODIMP CConnect::OnAddInsUpdate (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnStartupComplete (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnBeginShutdown (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::QueryStatus(BSTR bstrCmdName, EnvDTE::vsCommandStatusTextWanted NeededText, EnvDTE::vsCommandStatus *pStatusOption, VARIANT *pvarCommandText)
{
  if(NeededText == EnvDTE::vsCommandStatusTextWantedNone)
	{
	  if(!_wcsicmp(bstrCmdName, L"VFCAddinNET.Connect.VisualFC"))
	  {
		  *pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
	  }
  }
	return S_OK;
}

STDMETHODIMP CConnect::Exec(BSTR bstrCmdName, EnvDTE::vsCommandExecOption ExecuteOption, VARIANT * /*pvarVariantIn*/, VARIANT * /*pvarVariantOut*/, VARIANT_BOOL *pvbHandled)
{
	*pvbHandled = VARIANT_FALSE;
	if(ExecuteOption == EnvDTE::vsCommandExecOptionDoDefault)
	{
		if(!_wcsicmp(bstrCmdName, L"VFCAddinNET.Connect.VisualFC"))
		{
			m_addin.ExecVFCWizard();
			*pvbHandled = VARIANT_TRUE;
			return S_OK;
		}
	}
	return S_OK;
}