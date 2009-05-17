copy_list = {
"iup.dll",
"im.dll",
"iupim.dll",
"iuplua51.dll",
"iupluaim51.dll",
"..\\lua5.1.dll",
"..\\lua51.dll",
"..\\lua.exe",
"..\\wlua.exe",
}

function make(file,lua_path)
	local f = io.open(file,"w")
	assert(f,"error to crate "..file)
	local cmds = {}
	cmds[1] = "@echo on"
	for k, v in ipairs(copy_list) do
		cmds[#cmds+1] = "copy ".. lua_path .. "\\" .. v
	end
	cmds[#cmds+1] = "pause"
	cmds[#cmds+1] = "del "..file
	f:write( table.concat(cmds,"\n"))
	f:close()
end

make("make.bat",[[c:\lua\5.1\clibs]])
