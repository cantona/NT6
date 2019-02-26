// mroom.c

#include <ansi.h>
#include <bunch.h>

protected void get_room_short(string sdesc, object who, object env, string dir);
protected void get_room_long(string str, object who, object env, string dir, string sdesc, string ldesc);
protected void build_up(object who, object env, string dir, string sdesc, string ldesc, int outdoor);
protected void get_room_outdoor(string str, object who, object env, string dir, string sdesc, string ldesc);

int main(object me, string arg)
{
	object env;

	if(!me || (me != this_player(1)))
		return 0;

	if(!objectp(env = environment(me)))
		return 0;

	seteuid(getuid(this_object()));

	if(!BUNCH_D->valid_modify_room(me, env))
		return 0;

	if(!stringp(arg) || (arg == ""))
		return 0;

	if(undefinedp(r_dir[arg]))
		return notify_fail(sprintf("房間的出口只能從以下方向種選擇：\n%s\n",vdirs));

	if(env->query("exits/"+arg) || env->query("hide_exits/"+arg))
		return notify_fail(sprintf("這裏已經有了 %s 出口。\n",arg));

	write("請輸入新建房間的名稱[2-6個漢字]('q'退出)：\n");
	input_to( (: get_room_short :), me, env, arg);

	return 1;
}

protected void get_room_short(string sdesc, object who, object env, string dir)
{
	int l;

	if(!who || !env || !dir)
		return;

	if(!stringp(sdesc) || (sdesc == ""))
	{
		tell_object(who, "請輸入新建房間的名稱[2-6個漢字]，輸入('q'退出)：\n");
		input_to( (: get_room_short :), who, env, dir);
		return;
	}

	if( (sdesc[0] == 'q')
	|| (sdesc[0] == 'Q') )
	{
		tell_object(who, "終止房間創建。\n");
		return;
	}

	if( ((l = strlen(sdesc)) < 4) || (l > 12) )
	{
		tell_object(who, "新建房間的名稱必須為2-6個漢字，輸入('q'退出)：\n");
		input_to( (: get_room_short :), who, env, dir);
		return;
	}

	while(l--)
	{
		int section;

                if( sdesc[l]<128 )
		{
			tell_object(who, "新建房間的名稱必須使用中文，輸入('q'退出)：\n");
			input_to( (: get_room_short :), who, env, dir);
			return;
                }

		if( l%2==0 )
		{
			section = sdesc[l] - 160;

			if( (section < 16)
			|| (section > 87) )
			{
				tell_object(who,"\n新建房間的名稱必須使用常用「漢字」，輸入('q'退出)：\n");
				input_to( (: get_room_short :), who, env, dir);
				return;
			}
		}
	}

	tell_object(who, sprintf("新房間名稱為：%s\n請為%s設定描述：
·為了房間的美觀，每一行請不要超過%s箇中文字
·第一行的內容長度比其它行的長度少兩個中文字寬才能對齊
·描述內容不能超過%s行\n請輸入('.'結束輸入，'q'退出)：\n------------------------------------------------------\n",
		sdesc, sdesc, chinese_number(room_desc_l/2), chinese_number(room_desc_h)));

	input_to( (: get_room_long :), who, env, dir, sdesc, "" );
}

protected void get_room_long(string str, object who, object env, string dir, string sdesc, string ldesc)
{
	if(!who || !env || !dir || !sdesc)
		return;

	if(!stringp(str) || (str == ""))
	{
		input_to( (: get_room_long :), who, env, dir, sdesc, ldesc );
		return;
	}

	if( (str[0] == 'q')
	|| (str[0] == 'Q') )
	{
		tell_object(who, "終止房間創建。\n");
		return;
	}

	if(str[0] == '.')	// 結束輸入
	{
		if( (ldesc == "") || (sizeof(ldesc) < 10) )
		{
			tell_object(who, sprintf("你沒有為%s的描述設定足夠的內容\n房屋創建失敗\n", sdesc));
			return;
		}

		if( sizeof(explode(ldesc, "\n")) > room_desc_h)
		{
			tell_object(who, sprintf(HBCYN HIG"·描述內容不能超過%s行\n房屋創建失敗。\n"NOR, chinese_number(room_desc_h)));
			return;
		}

		tell_object(who,sprintf("%s是否為户外房間？\n(户外房間可以看到氣候變化的描述)\n請選擇[y/n](q退出)：", sdesc));
		input_to( (: get_room_outdoor :), who, env, dir, sdesc, ldesc );
		return;
	}

	if(strsrch(str, '\n'))
	{
		int n;
		string *tmp;

		n = sizeof(tmp = explode(str, "\n"));
		for(int i=0; i<n; i++)
			if(strlen(tmp[i]) > room_desc_l)
			{
				tell_object(who, sprintf(HBCYN HIG"每一行不能超過%s箇中文字，請重新輸入上一次輸入的內容：\n"NOR, chinese_number(room_desc_l/2)));
				input_to( (: get_room_long :), who, env, dir, sdesc, ldesc );
				return;
			}

		if((n + sizeof(explode(ldesc, "\n"))) > room_desc_h)
		{
			tell_object(who, sprintf(HBCYN HIG"·描述內容不能超過%s行\n房屋創建失敗。\n"NOR, chinese_number(room_desc_h)));
			return;
		}
	}

	else
	{
		if(strlen(str) > room_desc_l)
		{
			tell_object(who, sprintf(HBCYN HIG"每一行不能超過%s箇中文字，請重新輸入上一次輸入的內容：\n"NOR, chinese_number(room_desc_l/2)));
			input_to( (: get_room_long :), who, env, dir, sdesc, ldesc );
			return;
		}

		if( sizeof(explode(ldesc, "\n")) > (room_desc_h -1) )
		{
			tell_object(who, sprintf(HBCYN HIG"·描述內容不能超過%s行\n房屋創建失敗。\n"NOR, chinese_number(room_desc_h)));
			return;
		}
	}

	ldesc += str + "\n";
	input_to( (: get_room_long :), who, env, dir, sdesc, ldesc );
}

protected void get_room_outdoor(string str, object who, object env, string dir, string sdesc, string ldesc)
{
	int ot = 0;

	if(!who
	|| !env
	|| !sdesc
	|| !ldesc
	|| !dir )
		return;

	if(stringp(str) && sizeof(str) && ( (str[0] == 'y') || (str[0] == 'Y') ))
		ot = 1;

	build_up(who, env, dir, sdesc, ldesc, ot);
}

// 欲連接的房間必須已存在，並且可以正確載入內存
// 當前房間沒有出口的情況不考慮，這在幫派系統中不會出現
protected int add_exit(object room, string link_to, string dir, string room_dir)
{
	string fname, fcn, f_sect, e_sect, m_sect, content, estr;
	mapping exits;

	if(!objectp(room) || !room->is_room())
		return 0;

	fname = base_name(room)+".c";

	if(file_size(fname) <= 0)
		return 0;

	if(file_size(link_to+".c") <= 0)
		return 0;

	if(!fcn = read_file(fname))
		return 0;

	if(!find_object(link_to))
		load_object(link_to);
	if(!find_object(link_to))
		return 0;

	if(!BUNCH_D->parse_set_value(ref fcn, "exits", ref f_sect, ref e_sect))
		return 0;

	exits = room->query("exits");

	if(!mapp(exits) || !sizeof(exits))
		exits = ([ dir : link_to ]);
	else
		exits += ([ dir : link_to ]);

	estr = sprintf("%O", exits);
	estr = replace_string(estr, "\""+room_dir, "__DIR__\"");

	if(!BUNCH_D->parse_set_value(ref fcn, "exits", ref f_sect, ref e_sect))
	{
		if(!BUNCH_D->parse_function_body(ref fcn, "void", "create", ref f_sect, ref m_sect, ref e_sect, 0))
			return 0;
		content = sprintf("// Room: %s\n\n%s\n\tset(\"exits\", %s);\n%s\n%s\n",
			fname, f_sect, estr, m_sect, e_sect);
	}
	else
		content = sprintf("// Room: %s\n\n%s\n\tset(\"exits\", %s);\n%s\n",
			fname, f_sect, estr, e_sect);

	if(!write_file(fname, content, 1))
		return 0;
	if( !BUNCH_D->update_room(room) )
		return 0;
	return 1;
}

protected string valid_room_position(string fname)
{
	int l;
	string *f1, *f2;

	if(!stringp(fname))
		return 0;

	if( strlen(fname) <= (l = strlen(dir_pre)) )
		return 0;

	if(fname[0..l-1] != dir_pre)
		return 0;

	f1 = explode(dir_pre, "/");
	f2 = explode(fname, "/");

	if(sizeof(f2) - sizeof(f1) - 2 != 0)
		return 0;

	return f2[sizeof(f1)];
}

protected void build_up(object who, object env, string dir, string sdesc, string ldesc, int outdoor)
{
	string room_dir,fname,bname,nname, roomtext;
	int number;

	if(!who
	|| !env
	|| !sdesc
	|| !ldesc
	|| !dir
	|| (environment(who) != env))
		return;

	// 確定新房間文件名
	fname = base_name(env);

	if(!bname = who->query_banghui_id())
	{
		tell_object(who, "你的幫派記錄錯亂。\n修改失敗。\n");
		return;
	}

	if(undefinedp(r_dir[dir]))
	{
		tell_object(who, "房間出口選擇錯誤。\n創建房屋失敗。\n");
		return;
	}

	room_dir = sprintf("%s%s/", dir_pre, bname);

	number = sizeof(get_dir(room_dir)) + 1;

	while(file_size(nname = sprintf("%s%s_room%d.c", room_dir, bname, number)) > 0)
	{
		number++;
	}

	if(!in_same_dir(fname, nname))
	{
		tell_object(who, "房間目錄對應錯誤。\n修改失敗。\n");
		return;
	}

	fname = replace_string(fname, room_dir, "__DIR__\"");
	// 建新房

	roomtext = sprintf("// Room: %s\n\ninherit ROOM;\nvoid create()\n{\n",nname);
	roomtext += sprintf("\tset(\"short\", \"%s\");\n\tset(\"long\", @LONG\n%sLONG\n);\n", sdesc, ldesc);
	roomtext += sprintf("\tset(\"exits\", ([\n\t\"%s\" : %s\",\n]));\n", r_dir[dir], fname);
	if(outdoor)
		roomtext += sprintf("\tset(\"outdoors\", \"%s\");\n", bname);
	roomtext += "\tsetup();\n}\n";

	if(!write_file(nname, roomtext, 1))
	{
		tell_object(who, "保存房屋發生錯誤。\n創建房屋失敗。\n");
		return;
	}

	// 開出口
	if(!add_exit(env, nname[0..<3], dir, room_dir))
	{
		tell_object(who, "無法開闢出口。\n創建房屋失敗。\n");
		return;
	}

	tell_object(who, sprintf("%s建造成功。\n",sdesc));
}
