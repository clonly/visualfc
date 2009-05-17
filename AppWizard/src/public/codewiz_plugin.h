#ifndef __CODEWIZ_PLUGIN_H__
#define __CODEWIZ_PLUGIN_H__

#include "./simple_plugin.h"
#include "./foxcode.h"

namespace fox
{
	struct codewiz_args
	{
		codewiz_args()
		{
			codewiz_name[0] = '\0';
			codewiz_info[0] = '\0';
			project_name[0] = '\0';
			project_path[0] = '\0';
			template_path[0] = '\0';
			idd[0] = '\0';
			idd_num = 0;
			idd_array = NULL;
		}
		char codewiz_name[MAX_PATH];
		char codewiz_info[MAX_PATH];
		char project_name[MAX_PATH];
		char project_path[MAX_PATH];
		char template_path[MAX_PATH];
		char idd[MAX_PATH];
		int			 idd_num;
		const char ** idd_array;
		fox::code_file return_files;
	};

	struct codewiz_config : fox::simple_plugin::config_base
	{
		codewiz_config()
		{
			guid = _T("codewiz");
		}
		bool bEnableIDD;
		bool bEnableCPP;
		bool bConstruction;
		bool bDestruction;

		bool empty()
		{
			return name.IsEmpty() != FALSE;
		}
		void load(LPCTSTR lpszIniFile, LPCTSTR lpszAppName = _T("plugin"))
		{
			config_base::load(lpszIniFile,lpszAppName);

			fox::simple_plugin::load_cfg lc;
			lc.cfgApp = lpszAppName;
			lc.cfgPath = lpszIniFile;

			bConstruction = lc.load_cfg_bool(_T("construction"),true);
			bDestruction = lc.load_cfg_bool(_T("destruction"),true);
			bEnableIDD = lc.load_cfg_bool(_T("enable_idd"),false);
			bEnableCPP = lc.load_cfg_bool(_T("enable_cpp"),true);
		}
	};
};

#endif //__PLUGIN_H__