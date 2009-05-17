-- build by visualfc@gmail.com
-- time 2009.1

require "vswizard"

local app_path = vswizard.get_module_path()
local_lang = string.upper(vswizard.get_local_lang())

if local_lang == "CHS" then
	dofile(app_path.."\\Resource\\lang_chs.lua")
end

dofile(app_path.."\\wiz_main.wlua")
