-- by visualfc@gmail.com
-- date 2009.1
-- find ui("str") and make to lang_chs.lua

function make_file(name, out_name)
	print(name)
	file = io.open(name,"r")
	assert(file,"Error to load File"..name)

	s = file:read("*all")
	words = {}
	saves = {}
	for w in string.gmatch(s,"ui%s-%(%s-(\".-\")%s-%)") do
		if words[w] == nil then
			saves[#saves+1] = w
			words[w] = [[""]]
		end
	end

	file:close()

	file = io.open(out_name,"r")
	--assert(file,"Error to read file"..out_name)
	old = ""
	if file then
		old = file:read("*all")
	end
	--print(old)
	for w,w1 in string.gmatch(old,"lang%[(\".-\")%]%s-=%s-(\".-\")") do
		if w1 ~= "" then
			words[w] = w1
		end
	end

	file = io.open(out_name,"w")
	assert(file,"Error to write file"..out_name)

	file:write("-- build by visualfc@gmail.com\n")
	file:write("-- lang file for "..name.."\n\n")
	file:write("local lang = {}\n")
	for k,v in ipairs(saves) do
		file:write(string.format("lang[%s] = %s\n",v,words[v]))
	end
	file:write(
[[

--ui("test str")
function ui(str)
	if lang[str] ~= nil and lang[str] ~= "" then
		return lang[str]
	else
		return str
	end
end

]])
end

make_file("..\\wiz_main.wlua","lang_chs.lua")
