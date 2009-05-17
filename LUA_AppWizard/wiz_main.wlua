-- WTL AppWizard 2.0rc1
-- build by visualfc@gmail.com
-- time 2009.1

package.cpath = package.cpath..";./?.dll;./lua/?.dll"
package.path = package.path..";./?.lua;./lua/?.lua;./?.wlua;./lua/?.wlua"

require "iuplua"
require "iupluaim51"
require "iupid"

require "iupwizard"
require "vswizard"

function dofile_noerror(filename)
	local f,ret = loadfile(filename)
	if f then
		return f()
	else
		print(ret)
	end
end

local app_path = vswizard.get_module_path()
local local_lang = local_lang or ""
--[[
local local_lang = string.upper(vswizard.get_local_lang())

if local_lang == "CHS" then
	dofile(app_path.."\\Resource\\lang_chs.lua")
end
--]]
local ui = ui or function(str) return str end

gui_info = {}

--default value
gui_info.PROJECT_VS60 = true
gui_info.PROJECT_VS2005 = true
gui_info.WTL_APPTYPE_SDI = true
gui_info.WTL_USE_MANIFEST = true
gui_info.WTL_USE_UNICODE = true
gui_info.WTL_USE_REBAR = true
gui_info.WTL_USE_TOOLBAR = true
gui_info.WTL_USE_CMDBAR = true
gui_info.WTL_USE_STATUSBAR = true
gui_info.WTL_USE_VIEW = true
gui_info.WTL_VIEWTYPE_GENERIC = true

local main_image = iup.LoadImage(app_path.."\\Resource\\main.png")
local head_image = iup.LoadImage(app_path.."\\Resource\\header.png")


function get_wizard_lang()
	local file = io.open(app_path .. "\\Templates\\lang.inf","r")
	local langs = {}
	for line in file:lines() do
		langs[line] = vswizard.get_local_info(line)
	end
	return langs
end

function enum_handle(h,proc)
	local i = 1
	while(h[i]) do
		if type(h[i]) ~= "string" then
			proc(h[i])
			enum_handle(h[i],proc)
		end
		i = i+1
	end
end

function init_page(page)
	enum_handle(page, function (h)
					if h.key and gui_info[h.key] then
						h.value = "ON"
					end
				end )
end

function save_page(page)
	enum_handle(page, function (h)
					if h.key then
						if h.value == "ON" then
							gui_info[h.key] = true
						else
							gui_info[h.key] = nil
						end
					end
				end)
end

function action_toggle_key(btn)
	if btn.value == "ON" then
		gui_info[btn.key] = true
	else
		gui_info[btn.key] = nil
	end
end

function action_radio_type(btn)
	if btn.value == "ON" then
		gui_info[btn.key] = true
	else
		gui_info[btn.key] = nil
	end
	if toggle_apptype_dlg.value == "ON" then
		toggle_frame_dialog.active = "ON"
		toggle_modal_dialog.active = "ON"
		if toggle_frame_dialog.value == "ON" and toggle_apptype_dlg.value == "ON" then
			toggle_frame_dialog_addvfc.active = "ON"
			toggle_modal_dialog.active = "OFF"
			toggle_modal_dialog.value = "OFF"
		else
			toggle_frame_dialog_addvfc.active = "OFF"
			toggle_modal_dialog.active = "ON"
		end
	else
		toggle_frame_dialog.active = "OFF"
		toggle_modal_dialog.active = "OFF"
		toggle_frame_dialog_addvfc.active = "OFF"
		toggle_frame_dialog.value = "OFF"
		toggle_frame_dialog_addvfc.value = "OFF"
		toggle_modal_dialog.value = "OFF"
	end
end

function action_radio_sdk(btn)
	gui_info.sdk = btn.sdk
end

local page1 = iup.vbox
{
	iup.vbox
	{
		iup.label{title=ui("Project Name")},
		iup.text{expand="HORIZONTAL",id="text_project_name"},
		iup.label{title=ui("Location")},
		iup.hbox
		{
			iup.text{expand="HORIZONTAL",id="text_location"},
			iup.fill{},
			iup.button{title=ui("Browse"),active="YES",id="btn_browse"},
			alignment = "ARIGHT"
		},
		iup.label{title=ui("Project Path")},
		iup.text{expand="HORIZONTAL",id="text_project"},
		margin="0"
	},
	iup.hbox
	{
		iup.vbox
		{
			iup.toggle{title = ui("Make .dsp for VS60"), key = "PROJECT_VS60",  action = action_toggle_key, id = "toggle_vs60"},
			iup.toggle{title = ui("Make .vcproj for VS2002"), key= "PROJECT_VS2002", action = action_toggle_key, id = "toggle_vs2002"},
			iup.toggle{title = ui("Make .vcproj for VS2003"), key= "PROJECT_VS2003", action = action_toggle_key, id = "toggle_vs2003"},
			iup.toggle{title = ui("Make .vcproj for VS2005"), key= "PROJECT_VS2005", action = action_toggle_key, id = "toggle_vs2005"},
			iup.toggle{title = ui("Make .vcproj for VS2008"), key= "PROJECT_VS2008", action = action_toggle_key, id = "toggle_vs2008"},
			iup.hbox
			{
				iup.toggle{title = ui("WTL_USE_SDK_ATL3 for VCExpress"), key = "WTL_USE_SDK_ATL3", action = action_toggle_key},
				margin="20x2"
			}
		},
		iup.fill{size="10x"},
		iup.radio
		{
			iup.vbox
			{
				iup.toggle{title=ui("WINVER undefine"),key="WTL_SDKTYPE_NODEF", action = action_toggle_key},
				iup.toggle{title=ui("WINVER = 0x0400"),key="WTL_SDKTYPE_0400", action = action_toggle_key},
				iup.toggle{title=ui("WINVER = 0x0500"),key="WTL_SDKTYPE_0500", action = action_toggle_key},
				iup.toggle{title=ui("WINVER = 0x0600"),key="WTL_SDKTYPE_0600", action = action_toggle_key},
			}
			; id = "radio_sdktype"
		};
		expand = "HORIZONTAL",
		margin="0x10",
	};
	title = ui("ATL/WTL AppWizard 8.0 - Step 1 of 3"),
	head_title = ui("Application Name"),
	sub_title=ui("Set Projects Application Name"),
	margin="10x10",
	head_image = head_image,
}

function btn_browse:action()
	dlg = iup.filedlg{dialogtype="DIR"}
	dlg:popup()
	if dlg.status == "0" then
		text_location.value = dlg.value
	end
end

function text_project_name:action(c,after)
	if string.sub(text_location.value,-1) == "\\" then
		text_project.value = text_location.value .. after
	else
		text_project.value = text_location.value .. "\\" .. after
	end
end

local page2 = iup.vbox
{
	iup.hbox
	{
		iup.vbox
		{
			iup.label{title=ui("Select Application Type")},
			iup.radio
			{
				iup.vbox
				{
					iup.toggle{title=ui("SDI Application"),key="WTL_APPTYPE_SDI", action = action_radio_type},
					iup.toggle{title=ui("Multiple Threads SDI"),key="WTL_APPTYPE_MTSDI", action = action_radio_type},
					iup.toggle{title=ui("MDI Application"),key="WTL_APPTYPE_MDI", action = action_radio_type},
					iup.toggle{title=ui("Tab View Application"),key="WTL_APPTYPE_TABVIEW", action = action_radio_type},
					iup.toggle{title=ui("Explorer Application"),key="WTL_APPTYPE_EXPLORER", action = action_radio_type},
					iup.toggle{title=ui("Dialog Based"),key="WTL_APPTYPE_DLG", action = action_radio_type, id = "toggle_apptype_dlg"},
				},
				margin="0"
			},
			margin="0x0",
			gap=9
		},
		iup.fill{size="20x"},
		iup.vbox
		{
			iup.label{title = ui("Select project options")},
			iup.label{title=""},
			iup.vbox
			{
				iup.toggle{title=ui("Enable ActiveX Control Hosting"),key="WTL_ENABLE_AX", action = action_toggle_key},
				iup.toggle{title=ui("Create as a COM Server"),key="WTL_COM_SERVER", action = action_toggle_key},
				iup.toggle{title=ui("Generic .cpp Files"),key="WTL_USE_CPP_FILES", action = action_toggle_key},
				iup.toggle{title=ui("Add Common Control Manifest"),key="WTL_USE_MANIFEST", action = action_toggle_key},
				iup.toggle{title=ui("Unicode character set"),key="WTL_USE_UNICODE", action = action_toggle_key},
				iup.label{title=""},
				iup.label{title = ui("Resource Language")},
				iup.list{dropdown = "YES", id = "list_language"}
			},
			gap=0,
			margin="0x0"
		},
		margin = "0"
	},
	iup.vbox
	{
		iup.toggle{title=ui("Modal Dialog"), active = "NO", key = "WTL_APPTYPE_DLG_MODAL", action = action_radio_type, id = "toggle_modal_dialog"},
		iup.toggle{title=ui("Frame Dialog (using vfcframe library)"), active = "NO", key = "WTL_APPTYPE_DLG_FRAME", action = action_radio_type,
					id = "toggle_frame_dialog"},
		iup.vbox
		{
			iup.toggle{title=ui("check it add vfcframe.h to projects"), active = "NO", key = "WTL_USE_ADDVFCFILES", action = action_radio_type,
			id = "toggle_frame_dialog_addvfc"},
			margin = "20x"
		},
		margin ="20"
	};
	title = ui("ATL/WTL AppWizard 8.0 - Step 2 of 3"),
	head_title = ui("Application Type"),
	sub_title=ui("Selection Application Type"),
	margin="10x10",
	head_image = head_image
}

local page3 = iup.vbox
{
	iup.vbox
	{
		iup.label{title=ui("Select UI features")},
		iup.label{title=""},
		iup.toggle{title=ui("Toolbar"), key = "WTL_USE_TOOLBAR",action = action_toggle_key, id = "toggle_toolbar"},
		iup.toggle{title=ui("Rebar"), key = "WTL_USE_REBAR", action = action_toggle_key, id = "toggle_rebar"},
		iup.toggle{title=ui("Command Bar"), key = "WTL_USE_CMDBAR", action = action_toggle_key, id = "toggle_cmdbar"},
		iup.toggle{title=ui("Status Bar"),key = "WTL_USE_STATUSBAR", action = action_toggle_key, id = "toggle_sbar"},
		iup.fill{},
		iup.toggle{title=ui("Use a View Window"), key = "WTL_USE_VIEW", action = action_toggle_key, id = "toggle_useview"},
		iup.label{title=ui("View Type"), key = "_WTL_LABEL_KEY"},
		iup.list
		{
			ui("Generic Window"),ui("Form (Dialog Based)"),ui("ListBox"),
			ui("Edit"),ui("List View"),ui("Tree View"),ui("Rich Edit"),
			ui("HTML Page"),ui("Scroll Window"),
			dropdown="YES",value=1,
			id = "list_viewtype",
		},
		iup.fill{},
		iup.toggle{title=ui("Host ActiveX Controls"), active = "OFF", value = "OFF", key = "WTL_HOST_AX", id = "toggle_host_ax"}
	};
	margin="10x10",
	title = ui("ATL/WTL AppWizard 8.0 - Step 3 of 3"),
	head_title = ui("User Interface Features"),
	sub_title=ui("Selection Application User Interface Features"),
	head_image = head_image
}


function list_viewtype:action()
	if self.value == "2" and gui_info["WTL_ENABLE_AX"] then
		toggle_host_ax.active = "ON"
	else
		toggle_host_ax.active = "OFF"
	end
end

function toggle_useview:action()
	if self.value == "ON" then
		gui_info[self.key] = true
		list_viewtype.active = "ON"
	else
		gui_info[self.key] = nil
		list_viewtype.active = "OFF"
	end
	if self.value == "ON" and list_viewtype.value == "2" and gui_info["WTL_ENABLE_AX"] then
		toggle_host_ax.active = "ON"
	else
		toggle_host_ax.active = "OFF"
	end
end

function init_res_lang()
	local infos = get_wizard_lang()
	local index = 1
	for k,v in pairs(infos) do
		list_language[tostring(index)] = v
		index = index+1
	end
	if local_lang == "CHS" then
		list_language.value = "2"
	end
end

function page3:active_page_cb()
	local s1 = "ON"
	if gui_info.WTL_APPTYPE_DLG and not gui_info.WTL_APPTYPE_DLG_FRAME then
		s1 = "OFF"
	end
	toggle_toolbar.active = s1
	toggle_rebar.active = s1
	toggle_cmdbar.active = s1
	toggle_sbar.active = s1

	s1 = "ON"
	if gui_info.WTL_APPTYPE_DLG then
		s1 = "OFF"
	end
	toggle_useview.active = s1
	list_viewtype.active = s1
	s1 = "OFF"
	if not gui_info.WTL_APPTYPE_DLG and list_viewtype.value == "2" and gui_info.WTL_ENABLE_AX then
		s1 = "ON"
	end
	toggle_host_ax.active = s1
end

function save_config()
	local file = io.open(app_path.."\\Resource\\config.lua","w")
	if file then
		file:write(string.format("text_location.value = %q\n",text_location.value))
		file:write(string.format("toggle_vs60.value = %q\n",toggle_vs60.value))
		file:write(string.format("toggle_vs2002.value = %q\n",toggle_vs2002.value))
		file:write(string.format("toggle_vs2003.value = %q\n",toggle_vs2003.value))
		file:write(string.format("toggle_vs2005.value = %q\n",toggle_vs2005.value))
		file:write(string.format("toggle_vs2008.value = %q\n",toggle_vs2008.value))
		file:write(string.format("gui_info[%q] = true\n",radio_sdktype.value.key))
		file:close()
	end
end

local wizard_dlg = iup.wizard
{
	page1, page2, page3, last_finish = false,
	ui_prev = ui("< Prev"),
	ui_next = ui("Next >"),
	ui_cancel = ui("Cancel"),
	ui_finish = ui("Finish"),
	main_image = main_image,
	head_image = head_image
}


function wizard_dlg:finish_cb()
	if text_project.value == "" or text_project_name.value == "" then
		iup.Message(ui("Warning"),ui("Project Path or Name not Valid"))
		return
	end
	if vswizard.path_exists(text_project.value or "" ) then
		iup.Message(ui("Warning"),ui("Project path is exists ")..text_project.value)
		return
	end

	if vswizard.path_exists(text_location.value) == false then
		iup.Message(ui("Warning"),ui("Project Location is not exists ") .. text_location.value)
		return
	end

	save_page(page1)
	save_page(page2)
	save_page(page3)


	--page1
	gui_info.PROJECT_NAME = text_project_name.value
	gui_info.PROJECT_PATH = text_project.value
	gui_info.PROJECT_ENCODE = "Windows-1252";
	local lang_sel = list_language.value or "1"
	local langs = get_wizard_lang()
	local index = 1
	for k,v in pairs(langs) do
		if index == tonumber(lang_sel) then
			gui_info["PROJECT_LANG_"..k] = true
		else
			gui_info["PROJECT_LANG_"..k] = nil
		end
		index = index+1
	end

	if make_project() == true then
		save_config()
		self:close()
	end

end

function wizard_dlg:next_cb()

	if self.index == 1 then
		if vswizard.path_exists(text_project.value or "" ) then
			iup.Message(ui("Warning"),ui("Project Location is exists ")..text_project.value)
			return
		end
	end


	save_page(page1)
	save_page(page2)
	save_page(page3)

	self:next_page()
end

function pairssort(t,f)
	local a = {}
	for n in pairs(t) do a[#a+1] = n end
	table.sort(a,f)
	local i = 0
	return function()
		i = i+1
		return a[i],t[a[i]]
	end
end

local info_dialog = {}

function info_dialog:new(o)
	o = o or {}
	setmetatable(o,self)
	self.__index = self
	self.info = o.info or {}

	local text = {}
	local text2 = {}
	for k,v in pairssort(self.info) do
		if v == true then
			text[#text+1] =  k .. " = " .. tostring(v)
		else
			text2[#text2+1] = k .. " = "..tostring(v)
		end
	end
	text[#text+1] = ""
	text[#text+1] = ""

	self.dlg = iup.dialog
	{
		iup.vbox
		{
			iup.multiline{size="300x250", expand="YES", readonly = "YES", value = table.concat(text,"\n") .. table.concat(text2,"\n")},
			iup.fill{},
			iup.label{title=ui("Project Path")},
			iup.text{value=text_project.value, expand = "YES",  expand ="HORIZONTAL", readonly = "YES"},
			iup.hbox
			{
				iup.fill{},
				iup.button{title=ui("OK"), action = function(btn) self.exit_code = "OK" self.dlg:destroy() end},
				iup.button{title=ui("Cancel"), action = function(btn) self.dlg:destroy() end},
				gap = 10
			}
		}
		; title = ui("New Project Infomation"), margin ="10x10"
	}
	return self
end

function info_dialog:popup()
	self.dlg:popup()
end


function make_project()
	local wizard = vswizard.new()
	assert(wizard,"error to load vswizard!")

	local info = {}
	for k,v in pairs(gui_info) do
		info[k] = v
	end

	info.WTL_SDKTYPE_NODEF = true
	local templatePath = app_path .. "\\Templates"
	local templateinf = templatePath .. "\\Templates.inf"

	--add info to VSWizard
	if info["WTL_APPTYPE_DLG"] then
		info["WTL_MAINDLG_FILE"] = "MainDlg";
		info["WTL_USE_VIEW"] = nil
	else
		info["WTL_FRAME_CLASS"] = "CMainFrame";
		info["WTL_FRAME_FILE"] = "MainFrm";
		info["WTL_FRAME_BASE_CLASS"] = "CFrameWindowImpl";

		if info["WTL_APPTYPE_MDI"] then
			info["WTL_CHILD_FRAME_FILE"] = "ChildFrm";
			info["WTL_CHILD_FRAME_CLASS"] = "CChildFrame";
		end
	end

	if info["WTL_APPTYPE_TABVIEW"] or info["WTL_APPTYPE_EXPLORER"] then
		info["WTL_USE_VIEW"] = true
	end

	if ( info["PROJECT_VS2005"] or info["PROJECT_VS2008"]) 	and
		info["WTL_USE_MANIFEST"] then
		info["WTL_USE_EMBEDDED_MANIFEST"] = true
		if info["PROJECT_VS60"] == nil and
			info["PROJECT_VS2002"] == nil and
			info["PROJECT_VS2003"] == nil then
			info["WTL_USE_MANIFEST"] = nil
		end
	end

	local safename = info["PROJECT_NAME"]
	local nicesafename = string.upper(string.sub(safename,1,2))..string.sub(safename,2,-1)
	info["SAFE_PROJECT_NAME"] = safename
	info["NICE_SAFE_PROJECT_NAME"] = nicesafename
	info["UPPERCASE_SAFE_PROJECT_NAME"] = string.upper(nicesafename)

	local st = os.date("*t")
	if st.year >= 2003 then
		info["WTL_CURRENT_YEAR"] = tostring(st.year)
	end



	info["PROJECT_GUID"] = wizard:MakeGUID()

	if ( info["PROJECT_VS2005"] or info["PROJECT_VS2008"]) and info["WTL_USE_MANIFEST"] then
		info["WTL_USE_EMBEDDED_MANIFEST"] = true;
		if not info["PROJECT_VS60"] and not info["PROJECT_VS2002"] and not info["PROJECT_VS2003"] then
			info["WTL_USE_MANIFEST"] = nil
		end
	end

	if info["WTL_COM_SERVER"] then
		info["WTL_APPID"] = wizard:MakeGUID()
		info["WTL_LIBID"] = wizard:MakeGUID()
	end

	if info["WTL_APPTYPE_SDI"] or info["WTL_APPTYPE_MTSDI"] then
		info["WTL_FRAME_BASE_CLASS"] = "CFrameWindowImpl"
	elseif info["WTL_APPTYPE_MDI"] then
		info["WTL_FRAME_BASE_CLASS"] = "CMDIFrameWindowImpl"
		info["WTL_CHILD_FRAME_BASE_CLASS"] = "CMDIChildWindowImpl"
	elseif info["WTL_APPTYPE_DLG"] then
		info["WTL_MAINDLG_CLASS"] = "CMainDlg"
		if info["WTL_ENABLE_AX"] then
			info["WTL_MAINDLG_BASE_CLASS"] = "CAxDialogImpl"
		else
			info["WTL_MAINDLG_BASE_CLASS"] = "CDialogImpl"
		end
		if info["WTL_APPTYPE_DLG_FRAME"] == nil then
			info["WTL_USE_TOOLBAR"] = nil
			info["WTL_USE_REBAR"] = nil
			info["WTL_USE_CMDBAR"] = nil
			info["WTL_USE_STATUSBAR"] = nil
			info["WTL_USE_VIEW"] = nil
		end
	end

	local viewtype = tonumber(list_viewtype.value)

	if info["WTL_USE_VIEW"] then
		info["WTL_VIEW_FILE"] = info["PROJECT_NAME"].."View"
		info["WTL_VIEW_CLASS"] = "C"..nicesafename.."View"
		info["WTL_VIEWTYPE_GENERIC"] = nil
		info["WTL_VIEW_BASE_CLASS"]="CWindowImpl"
		info["WTL_VIEW_STYLES"]="WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN";
		info["WTL_VIEW_EX_STYLES"]="WS_EX_CLIENTEDGE"
		if viewtype == 1 then
			info["WTL_VIEWTYPE_GENERIC"] = true
		elseif viewtype == 2 then
			info["WTL_VIEWTYPE_FORM"] = true;
			if info["WTL_ENABLE_AX"] and info["WTL_HOST_AX"] then
				info["WTL_VIEW_BASE_CLASS"] = "CAxDialogImpl"
			else
				info["WTL_VIEW_BASE_CLASS"] = "CDialogImpl"
			end
		elseif viewtype == 3 then
			info["WTL_VIEWTYPE_LISTBOX"] = true
			info["WTL_VIEW_BASE"] = "CListBox"
			info["WTL_VIEW_STYLES"] = "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT"
		elseif viewtype == 4 then
			info["WTL_VIEWTYPE_EDIT"] = true
			info["WTL_VIEW_BASE"] = "CEdit"
			info["WTL_VIEW_STYLES"] = "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL"
		elseif viewtype == 5 then
			info["WTL_VIEWTYPE_LISTVIEW"] = true
			info["WTL_VIEW_BASE"] = "CListViewCtrl"
			info["WTL_VIEW_STYLES"] = "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT | LVS_SHOWSELALWAYS"
		elseif viewtype == 6 then
			info["WTL_VIEWTYPE_TREEVIEW"] = true
			info["WTL_VIEW_BASE"] = "CTreeViewCtrl"
			info["WTL_VIEW_STYLES"] = "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS"
		elseif viewtype == 7 then
			info["WTL_VIEWTYPE_RICHEDIT"] = true
			info["WTL_VIEW_BASE"] = "CRichEditCtrl"
			info["WTL_VIEW_STYLES"] = "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL | ES_SAVESEL"
		elseif viewtype == 8 then
			info["WTL_VIEWTYPE_HTML"] = true
			info["WTL_VIEW_BASE"] = "CAxWindow"
			info["WTL_ENABLE_AX"] = true
			info["WTL_VIEW_STYLES"] = "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL"
		elseif viewtype == 9 then
			info["WTL_VIEWTYPE_SCROLL"] = true
			info["WTL_VIEW_BASE_CLASS"] = "CScrollWindowImpl"
			info["WTL_VIEW_STYLES"] = "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL"
		end

		if info["WTL_APPTYPE_TABVIEW"] then
			info["WTL_VIEW_EX_STYLES"] = "0"
		end

	end

	info["INSERT_LOCATION_COMMENT"] ="VisualFC AppWizard will insert additional declarations immediately before the previous line."

	for k,v in pairs(info) do
		wizard:AddSymbol(k,v)
	end

	local strfiles = wizard:LoadFileInfo(templateinf)
	local files = {}
	for w in string.gmatch(strfiles,"[^\n\r]+") do
		files[#files+1] = w
	end

	local info_dlg = info_dialog:new{info = info}
	info_dlg:popup()

	if info_dlg.exit_code == "OK" then
		AddFilesToProject(wizard,info["PROJECT_NAME"],info["PROJECT_PATH"],templatePath,files)
		return true
	end
end

function GetTargetName(proj_name,strName)
	strName = string.lower(strName)
	local strTarget = strName

	if string.find(strName,"root") then
		strTarget = string.gsub(strName,"root",proj_name)
		if string.find(strName,".ico") or string.find(strName,".bmp") or string.find(strName,".manifest")  then
			strTarget = "res\\" .. strTarget
		end
		if string.find(strName,".rc") then
			strTarget = proj_name .. (".rc");
		end
	elseif strName == "frame.h" or strName == "frame.cpp" then
		strTarget = string.gsub(strName,"frame","MainFrm")
	elseif string.find(strName,"view") then
		strTarget = proj_name .. strName
	elseif strName == "toolbar.bmp" then
		strTarget = "res\\" .. strName;
	end

	return strTarget;
end

function AddFilesToProject(wizard,proj_name,proj_path,templ_path, files)
	wizard:MakeDir(proj_path)
	wizard:MakeDir(proj_path .."\\res")

	for k,source in ipairs(files) do
		target = GetTargetName(proj_name,source)
		bCopyOnly = false;  --"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
		if string.find(source,".bmp") or
			string.find(source,".ico") or
			string.find(source,".gif") or
			string.find(source,".rtf") or
			string.find(source,".css") then
			bCopyOnly = true;
		end
		if string.sub(target,-2,-1) == ".h" then
			strFileNS = "VFC_" .. string.upper(string.gsub(target,"%.","_")) .. "__"
			wizard:AddSymbol("FILE_NAME_SYMBOL",strFileNS..wizard:MakeIncludeGUID().."_")
		else
			wizard:AddSymbol("FILE_NAME_SYMBOL",false)
		end

		source = templ_path.."\\"..source
		target = proj_path.."\\"..target

		if bCopyOnly then
			wizard:CopyFile(source,target);
		else
			wizard:MakeFile(source,target);
		end
	end
end


function main()

	dofile_noerror(app_path.."\\Resource\\config.lua")
	init_page(page1)
	init_page(page2)
	init_res_lang()
	init_page(page3)
	wizard_dlg.dlg:show(1)

	iup.MainLoop()
end

main()
