-- by visualfc@gmail.com
-- date 2009.1
-- make iup.wizard use iup.zbox

module("wizard",package.seeall)

require "iuplua"
require "iupid"


local wizard = {}

function wizard.new(o)
	local wiz = {}
	setmetatable(wiz,wizard)
	wizard.__index = wizard

	wiz.main_image = o.main_image
	wiz.head_image = o.head_image

	wiz.index = 0
	wiz.ui_prev = o.ui_prev or "< Prev"
	wiz.ui_next = o.ui_next or "Next >"
	wiz.ui_cancel = o.ui_cancel or "Cancel"
	wiz.ui_finish = o.ui_finish or "Finish"

	wiz.pages = {}
	for k,v in ipairs(o) do
		wiz.pages[#wiz.pages+1] = v
	end

	local index = o.index or 1

	wiz:active_page(index)
	return wiz
end

function iup.wizard(o)
	return wizard.new(o)
end

function wizard:active_page(n)
	local n = n or 1

	if self.dlg == nil then
		self.zbox_wizard = iup.zbox{unpack(self.pages)}
		self.zbox_wizard.alignment = "NW"
		self.dlg =
		iup.dialog
		{
			iup.vbox
			{
				iup.vbox
				{
					iup.hbox
					{
						iup.vbox
						{
							iup.label{title = "",size = "100x3"},
							iup.label{title = "head_title",size = "100x10", font="Times New Roman:BOLD:10", id = "lb_head_title"},
							iup.label{title = "sub_title",size = "100x15", font="Times New Roman::10", id = "lb_sub_title"}
						},
						iup.label{title="",image=self.head_image, alignment = "ARIGHT"}
					},
					iup.label{title="", separator="HORIZONTAL"}
					;expand="HORIZONTAL", bgcolor = "255 255 255"
				},
				iup.hbox
				{
					iup.frame
					{
						iup.label{title="", image = self.main_image},

					},
					self.zbox_wizard
					; margin = "20x20"
				},
				iup.vbox
				{
					iup.label{separator="HORIZONTAL"},
					iup.hbox
					{
						iup.label{title = "build by visualfc@gmail.com"},
						iup.fill{},
						iup.button{title=self.ui_prev, size = "60", active = self.index ~= 1 and "ON" or "OFF", id = "btn_wizard_prev", action = function(btn) self:prev_cb() end },
						iup.button{title=self.ui_next, size = "60", active = self.index ~= #self.pages and "ON" or "OFF", id = "btn_wizard_next", action = function(btn) self:next_cb() end },
						iup.button{title=self.ui_finish, size = "60", active = last_active, action = function(btn) self:finish_cb() end },
						iup.button{title=self.ui_cancel, size = "60", action = function(btn) self:cancel_cb() end },
					}
					;alignment = "ARIGHT", margin="5x5",gap=10,
				}
			}
			; margin = "0x0"
		}
	end

	if n ~= self.index then
		if self.index >= 1 and self.index <= #self.pages then
			self.pages[self.index].visible = "OFF"
		end
		self.index = n
		local page = self.pages[self.index]
		page.visible = "ON"
		lb_head_title.title = "      "..( page.head_title or "Iup Wizard main info")
		lb_sub_title.title = "          "..( page.sub_title or "Iup Wizard sub info" )
		self.dlg.title = page.title or "Iup wizard"
		self.index = n
		if page.active_page_cb then
			page:active_page_cb()
		end
	end

	btn_wizard_prev.active = self.index ~= 1 and "ON" or "OFF"
	btn_wizard_next.active = self.index ~= #self.pages and "ON" or "OFF"
	return self.dlg
end

function wizard:close()
	if self.dlg then
		self.dlg:destroy()
	end
end


function wizard:prev_page()
	self:active_page(self.index-1)
end

function wizard:next_page()
	self:active_page(self.index+1)
end

function wizard:finish_page()
	self:close()
end

function wizard:cancel_page()
	self:close()
end

function wizard:close_cb()
	self:close()
end

function wizard:prev_cb()
	self:prev_page()
end

function wizard:next_cb()
	self:next_page()
end

function wizard:finish_cb()
	self:finish_page()
end

function wizard:cancel_cb()
	self:cancel_page()
end
