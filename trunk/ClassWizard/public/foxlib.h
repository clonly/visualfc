#ifndef __FOXLIB_H__
#define __FOXLIB_H__

//fox lib interface
//2006.10.10
//QWL1996@GMAIL.COM

namespace fox
{
	class vs_addin
	{
	public:
		virtual int				get_version() = 0;
		virtual const char *	get_addin_name() = 0;
		virtual int				get_line_column(const char * file, int line) = 0;
		virtual bool			insert_block(const char * file, int line, int column, const char * text) = 0;
		virtual bool			replace_text(const char * file, int line, const char * old, const char * text) = 0;
		virtual bool			goto_line(const char * file, int line) = 0;
		virtual int				get_project_file_count() = 0;
		virtual const char *	get_project_files(int i) = 0;
		virtual const char *	get_project_path() = 0;
		virtual const char *	get_project_name() = 0;
		virtual bool			add_project_file(const char * file) = 0;
	};

	class vfc_item
	{
	public:
		virtual ~vfc_item() {}
		virtual const char * name() = 0;
		virtual void  set_vsaddin(vs_addin *) = 0;
		virtual void  load_project(const char * project_name, const char * active_file) = 0;
	};	

	namespace ui
	{
		class base
		{
		public:
			virtual ~base() {}
			virtual HWND create(HWND hParent, RECT rc) = 0;
			virtual HWND handle() = 0;
			virtual int get_type() const = 0;
		};

		template <int t_type>
		class base_t : public base
		{
		public:
			virtual int get_type() const
			{
				return t_type;
			}
			static int type() { return t_type; }
		};

		class item : public base_t<0x2000>
		{
		public:
			virtual const char * name() = 0;
		};	
/*		
		
		class item_ex : public item, public CMessageFilter
		{
		public:
			virtual int get_type() const
			{
				return type()+0x0100;
			}
		};
*/		
		class view : public base_t<0x2001>
		{
		public:
			virtual bool add_item(item * p) = 0;
		};	

	} // namespace ui
} // namespace fox

#endif