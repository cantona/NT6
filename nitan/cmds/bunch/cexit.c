// cexit.c

#include <ansi.h>
#include <bunch.h>

protected void decide_action_do(string str, object who, object env, mapping exits);
protected void get_del_dir(string str, object who, object env, mapping exits);
protected void get_add_dir(string str, object who, object env, mapping exits);
protected void do_add_exit(string str, object who, object env, mapping exits, string dir);

int main(object me, string arg)
{
	mapping exits;
	object env;
	string out;

	if(!me || (me != this_player(1)) || !objectp(env = environment(me)))
		return 0;

	seteuid(getuid(this_object()));

	if(!BUNCH_D->valid_modify_room(me, env))
		return 0;

	if( !env = BUNCH_D->update_room(env) )
	{
		tell_object(me, "無法目的載入房間，修改失敗。\n");
		return 1;
	}
	exits = env->query("exits");

	if(!exits || !sizeof(exits))
	{
		write("目前這裡沒有任何出口。\n請輸入要加入出口的方向(q 退出)：");
		input_to( (: get_add_dir :), me, env, exits);
		return 1;
	}

	out = "目前這裡已存在的出口：\n";

	foreach(string dir, string dest in exits)
	{
		out += sprintf("  %s 通往 %s\n", dir, explode(dest, "/")[<1]);
	}

	out += "請選擇你要進行的操作：
(1) 刪除一個已存在的出口。\n";

	if(sizeof(exits) >= max_exits)
		out += "(q) 退出。\n";
	else
		out += "(2) 加入一個新出口。\n(q) 退出。\n";

	write(out);
	input_to( (: decide_action_do :), me, env, exits );
	return 1;
}

protected void decide_action_do(string str, object who, object env, mapping exits)
{
	string out;

	if(!objectp(who) || !objectp(env))
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')) )
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))	// 刪除
	{
		tell_object(who, "請輸入要刪除出口的方向(q 退出)：");
		input_to( (: get_del_dir :), who, env, exits);
		return;
	}

	if(sizeof(str) && (str[0] == '2'))	// 加入
	{
		if(mapp(exits) && (sizeof(exits) >= max_exits))
		{
			tell_object(who, sprintf("每個房間最多只能有%s個出口。\n非法操作錯誤。\n", chinese_number(max_exits)));
			return;
		}
		tell_object(who, "請輸入要加入出口的方向(q 退出)：");
		input_to( (: get_add_dir :), who, env, exits);
		return;
	}

	out = "請選擇你要進行的操作：\n(1) 刪除一個已存在的出口。\n";

	if(mapp(exits) && (sizeof(exits) >= max_exits))
		out += "(q) 退出。\n";
	else
		out += "(2) 加入一個新出口。\n(q) 退出。\n";

	tell_object(who, out);
	input_to( (: decide_action_do :), who, env, exits );
}

protected void get_del_dir(string str, object who, object env, mapping exits)
{
	if(!objectp(who) || !objectp(env))
		return;

	if(environment(who) != env)
	{
		tell_object(who, "你的位置發生了變化，修改被停止。\n");
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "請輸入要刪除出口的方向(q 退出)：");
		input_to( (: get_del_dir :), who, env, exits);
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!mapp(exits) || !sizeof(exits))
	{
		tell_object(who, "出現異常錯誤。\n刪除失敗。\n");
		return;
	}

	if(undefinedp(exits[str]))
	{
		tell_object(who, sprintf("沒有 %s 這個出口。\n請輸入要刪除出口的方向(q 退出)：", str));
		input_to( (: get_del_dir :), who, env, exits);
		return;
	}

	if(BUNCH_D->break_an_exit(who, env, str))
		tell_object(who, "刪除出口成功。\n");
}

protected void get_add_dir(string str, object who, object env, mapping exits)
{
	if(!objectp(who) || !objectp(env))
		return;

	if(environment(who) != env)
	{
		tell_object(who, "你的位置發生了變化，修改被停止。\n");
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "請輸入要加入出口的方向(q 退出)：");
		input_to( (: get_add_dir :), who, env, exits);
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(undefinedp(r_dir[str]))
	{
		tell_object(who, sprintf("房間的出口只能從以下方向種選擇：\n%s\n修改失敗。\n",vdirs));
		return;
	}

	if(mapp(exits) && sizeof(exits) && !undefinedp(exits[str]))
	{
		tell_object(who, "此出口已存在。\n修改失敗。\n");
		return;
	}

	if(mapp(exits) && (sizeof(exits) >= max_exits))
	{
		tell_object(who, sprintf("每個房間最多只能有%s個出口。\n操作失敗。\n", chinese_number(max_exits)));
		return;
	}

	tell_object(who, "請確定此出口的目的房間名(q 退出)：");
	input_to( (: do_add_exit :), who, env, exits, str);
}

protected void do_add_exit(string str, object who, object env, mapping exits, string dir)
{
	if(!objectp(who) || !objectp(env))
		return;

	if(environment(who) != env)
	{
		tell_object(who, "你的位置發生了變化，修改被停止。\n");
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "請確定此出口的目的房間名(q 退出)：");
		input_to( (: do_add_exit :), who, env, exits, dir);
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!regexp(str, "^[a-z0-9_]+$"))
	{
		tell_object(who, "房間名裡包含錯誤字符。\n修改失敗。\n");
		return;
	}

	if(BUNCH_D->add_one_exit(who, env, dir, str))
		tell_object(who, "增加出口成功。\n");
}
