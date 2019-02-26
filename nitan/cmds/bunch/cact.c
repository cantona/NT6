// cact.c
// 一個動作函數只能由一個唯一的動詞引導
// 要不分析命令陣列太麻煩，也沒什麼實際意義。
// by Find.

#include <ansi.h>
#include <bunch.h>

protected void decide_action_do(string str, object who, object env, mixed *acts);
protected void delete_action(string str, object who, object env, mixed *acts);
protected void set_action_verb(string str, object who, object env, mixed *acts);
protected void select_action_class(string str, object who, object env, string verb);
protected void move_get_limit(string str, object who, object env, string verb, mapping actarg, mapping exits);
protected void move_get_arg(string str, object who, object env, string verb, mapping actarg, mapping exits);
protected void move_get_fail_msg(string str, object who, object env, string verb, mapping actarg, mapping exits);
protected void move_get_dest(string str, object who, object env, string verb, mapping actarg, mapping exits);
protected void move_get_here_msg(string str, object who, object env, string verb, mapping actarg, mapping exits, string dir);
protected void move_get_dest_msg(string str, object who, object env, string verb, mapping actarg, mapping exits, string dir);

protected string list_msg(mixed * acts)
{
	string *cmds = ({});
	int n;

	if(!n = sizeof(acts))
		return "";

	for(int i=0;i<n;i++)
		cmds += ({ acts[i][0] });

	return implode(cmds, ",") + "\n";
}

int main(object me, string arg)
{
	object env;
	mixed *acts;
	string out;
	int n;

	if(!me || (me != this_player(1)) || !objectp(env = environment(me)))
		return 0;

	seteuid(getuid(this_object()));

	if(!BUNCH_D->valid_modify_room(me, env))
		return 0;

	acts = filter_array(me->query_commands(), (: $1[2] == $(env) :));

	if(!n = sizeof(acts))
	{
		tell_object(me, "請設你要加入動作的動詞[3-10英文字母](q 退出)：\n");
		input_to( (: set_action_verb :), me, env, acts);
		return 1;
	}

	out = "目前此地已經定義的動作：\n";

	out += list_msg(acts);

	out += "請選擇操作：\n(1). 刪除一個動作。\n";

	if(n < max_action_per_room)
		out += "(2). 加入一個動作。\n(q). 退出：";
	else
		out += "(q). 退出：";

	write(out);
	input_to((: decide_action_do :), me, env, acts);
	return 1;
}

protected void decide_action_do(string str, object who, object env, mixed *acts)
{
	string out;

	if(!who || !env)
		return;

	if( sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')) )
	{
		tell_object(who,"ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))	// 刪除
	{
		tell_object(who, "請輸入欲刪除動作的動詞(q 退出)：\n");
		input_to( (: delete_action :), who, env, acts);
		return;
	}

	if(sizeof(str) && (str[0] == '2'))
	{
		if(sizeof(acts) >= max_action_per_room)
		{
			tell_object(who, sprintf("這裏已經設定了%s個動作，不能再設定了。\n非法操作錯誤。\n", chinese_number(max_action_per_room)));
			return;
		}
		tell_object(who, "請設你要加入動作的動詞[3-10英文字母](q 退出)：\n");
		input_to( (: set_action_verb :), who, env, acts);
		return;
	}

	out = "目前此地已經定義的動作：\n";

	out += list_msg(acts);

	out += "請選擇操作：\n(1). 刪除一個動作。\n";

	if(sizeof(acts) < max_action_per_room)
		out += "(2). 加入一個動作。\n(q). 退出：";
	else
		out += "(q). 退出：";

	input_to((: decide_action_do :), who, env, acts);
}

// 刪除動作
protected void delete_action(string str, object who, object env, mixed *acts)
{
	string func, fname, content, f_sect, m_sect, e_sect, result, sf_sect, se_sect;
	int i, n;

	if(!who || !env)
		return;

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "請輸入欲刪除動作的動詞(q 退出)：\n");
		input_to( (: delete_action :), who, env, acts);
		return;
	}

	if(!n = sizeof(acts))
	{
		tell_object(who, "此地沒有定義任何動作。\n異常錯誤。\n");
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who,"ok.\n");
		return;
	}

	for(i=0;i<n;i++)
	{
		if(acts[i][0] == str)
		{
			func = acts[i][3];
			break;
		}
	}

	if(!func)
	{
		tell_object(who, "此地沒有定義這個動作。\n");
		return;
	}

	if(environment(who) != env)
	{
		tell_object(who, "你的位置發生了變化，修改被停止。\n");
		return;
	}

	if(!content = read_file(fname = base_name(env) +".c"))
	{
		tell_object(who, "無法讀入檔案文件。\n");
		return;
	}

	if(!BUNCH_D->parse_function_body(ref content, "int", func, ref f_sect, ref m_sect, ref e_sect, 1))
	{
		tell_object(who, "無法剖析目的房間檔案，修改被停止。\n");
		return;
	}

	content = sprintf("%s\n%s\n", f_sect, e_sect);

	if(!BUNCH_D->parse_function_body(ref content, "void", "init", ref f_sect, ref m_sect, ref e_sect, 0))
	{
		tell_object(who, "無法剖析目的房間檔案(2)，修改被停止。\n");
		return;
	}

	if(!BUNCH_D->parse_set_value(ref m_sect, func, ref sf_sect, ref se_sect, "add_action"))
	{
		tell_object(who, "無法剖析目的房間檔案(3)，修改被停止。\n");
		return;
	}

	if((sf_sect == "") && (se_sect == ""))
	{
		content = sprintf("%s\n%s\n", f_sect, e_sect);
		if(!BUNCH_D->parse_function_body(ref content, "void", "init", ref f_sect, ref m_sect, ref e_sect, 1))
		{
			tell_object(who, "無法剖析目的房間檔案(2)，修改被停止。\n");
			return;
		}

		content = sprintf("%s\n%s\n", f_sect, e_sect);
	}
	else
		content = sprintf("%s\n%s%s%s\n",
			f_sect, sf_sect==""?"":sf_sect+"\n",
			se_sect==""?"":se_sect+"\n", e_sect);

	if(!BUNCH_D->parse_set_value(ref content, sprintf("%s_action_func", str), ref f_sect, ref e_sect))
	{
		tell_object(who, "無法剖析目的房間檔案(4)，修改被停止。\n");
		return;
	}

	result = sprintf("// Room: %s\n\n%s\n%s\n", fname, f_sect, e_sect);

	if(!write_file(fname, result, 1))
	{
		tell_object(who, "無法寫入文件內容，修改失敗。\n");
		return;
	}

	if( !BUNCH_D->update_room(env) )
	{
		tell_object(who, "無法載入房間，修改失敗。\n");
		return;
	}

	tell_object(who, "刪除成功。\n");
}

// 增加 move 類動作
protected void set_action_verb(string str, object who, object env, mixed *acts)
{
	if(!who || !env)
		return;

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "請設你要加入動作的動詞[3-10英文字母](q 退出)：\n");
		input_to( (: set_action_verb :), who, env, acts);
	}

	if(!regexp(str, "^[a-z]+$"))
	{
		tell_object(who, "動作的動詞只能用小寫英文字母。\n操作被終止。\n");
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who,"ok.\n");
		return;
	}

	if((sizeof(str) < 3) || (sizeof(str) > 10))
	{
		tell_object(who, "動作的動詞只能3-10個英文字母。\n操作被終止。\n");
		return;
	}

	if(sizeof(acts))
	{
		for(int i=0;i<sizeof(acts);i++)
			if(acts[i][0] == str)
			{
				tell_object(who, "這個動詞已經在這裏存在了。\n非法操作。\n");
				return;
			}
	}

	tell_object(who, "可設定的動作類型：
  1. 移動類動作。
  2. 開出口類動作
  3. 發現物品類動作
請選擇(q 退出)：\n");

	input_to((: select_action_class :), who, env, str);
}

protected void select_action_class(string str, object who, object env, string verb)
{
	mapping actarg;
	string id;

	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!id = who->query_banghui_id())
	{
		tell_object(who, "你的幫派記錄錯亂。\n修改失敗。\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))	// 移動類
	{
		mapping exits;

		if(!env = BUNCH_D->update_room(env))
		{
			tell_object(who, "無法載入當前房間。\n操作失敗。\n");
			return;
		}

		if(!mapp(exits = env->query("exits")) || !sizeof(exits))
		{
			tell_object(who, "當前房間沒有出口連向其他的房間。\n沒有可設定移動的出口。\n");
			return;
		}
		actarg = allocate_mapping(8);
		actarg["action_class"] = "move";
		actarg["banghui_id"] = id;
		tell_object(who, "對可以使用此動作人的限制：
  1. 只有本幫派的人可以。
  2. 任何人都可以。
請選擇(q 退出)：
");
		input_to((: move_get_limit :), who, env, verb, actarg, exits);
		return;
	}

	if(sizeof(str) && (str[0] == '2'))	// 開出口
	{
		mapping exits;

		if(!env = BUNCH_D->update_room(env))
		{
			tell_object(who, "無法載入當前房間。\n操作失敗。\n");
			return;
		}

		if(!mapp(exits = env->query("exits")) || !sizeof(exits))
		{
			tell_object(who, "當前房間沒有出口連向其他的房間。\n沒有可設定移動的出口。\n");
			return;
		}
		tell_object(who, "目前不行。\n");
		return;
	}

	if(sizeof(str) && (str[0] == '3'))	// 找到物品
	{
		tell_object(who, "目前不行。\n");
		return;
	}

	tell_object(who, "可設定的動作類型：
  1. 移動類動作。
  2. 開出口類動作
  3. 發現物品類動作
請選擇(q 退出)：\n");

	input_to((: select_action_class :), who, env, str);
}

protected void move_get_limit(string str, object who, object env, string verb, mapping actarg, mapping exits)
{
	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))
	{
		actarg["player_limit"] = 1;
		tell_object(who, "請設定此動作必須的參數：
( 0 沒有參數, q 退出)
");
		input_to((: move_get_arg :), who, env, verb, actarg, exits);
		return;
	}

	if(sizeof(str) && (str[0] == '2'))
	{
		actarg["player_limit"] = 2;
		tell_object(who, "請設定此動作必須的參數：
( 0 沒有參數, q 退出)
");
		input_to((: move_get_arg :), who, env, verb, actarg, exits);
		return;
	}

	tell_object(who, "對可以使用此動作人的限制：
  1. 只有本幫派的人可以。
  2. 任何人都可以。
請選擇(q 退出)：
");
	input_to((: move_get_limit :), who, env, verb, actarg, exits);
}

protected void move_get_arg(string str, object who, object env, string verb, mapping actarg, mapping exits)
{
	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '0'))
	{
		string out = "目前這裏的出口：\n";
		actarg["action_arg"] = 0;
		actarg["fail_msg"] = 0;

		foreach(string dir, string dest in exits)
		{
			if(!stringp(dest) || !sizeof(dest))
				continue;
			out += sprintf("  %s 通往 %s\n", dir, explode(dest,"/")[<1]);
		}
		out += "請選擇此動作目的地為哪個出口的目的地？(q 退出)：\n";
		tell_object(who, out);
		input_to((: move_get_dest :), who, env, verb, actarg, exits);
		return;
	}

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "請設定此動作必須的參數：
( 0 沒有參數, q 退出)
");
		input_to((: move_get_arg :), who, env, verb, actarg, exits);
		return;
	}

	actarg["action_arg"] = str;
	tell_object(who, "請設定沒有使用正確的參數的錯誤提示信息[最多15個漢字]\n請輸入(q 退出)：\n");
	input_to((: move_get_fail_msg :), who, env, verb, actarg, exits);
}

protected void move_get_fail_msg(string str, object who, object env, string verb, mapping actarg, mapping exits)
{
	string out;

	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!stringp(str) || !sizeof(str) || (sizeof(str) > 30))
	{
		tell_object(who, "請設定沒有使用正確的參數的錯誤提示信息[最多15個漢字]\n請輸入(q 退出)：\n");
		input_to((: move_get_fail_msg :), who, env, verb, actarg, exits);
		return;
	}

	actarg["fail_msg"] = str[<1]=='\n'?str:str+"\n";
	out = "目前這裏的出口：\n";
	foreach(string dir, string dest in exits)
	{
		if(!stringp(dest) || !sizeof(dest))
			continue;
		out += sprintf("  %s 通往 %s\n", dir, explode(dest,"/")[<1]);
	}
	out += "請選擇此動作目的地為哪個出口的目的地？(q 退出)：\n";
	tell_object(who, out);
	input_to((: move_get_dest :), who, env, verb, actarg, exits);
}

protected void move_get_dest(string str, object who, object env, string verb, mapping actarg, mapping exits)
{
	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}
	
	if(!stringp(str) || !sizeof(str))
	{
		string out;

		out = "目前這裏的出口：\n";
		foreach(string dir, string dest in exits)
		{
			if(!stringp(dest) || !sizeof(dest))
				continue;
			out += sprintf("  %s 通往 %s\n", dir, explode(dest,"/")[<1]);
		}
		out += "請選擇此動作目的地為哪個出口的目的地？(q 退出)：\n";
		tell_object(who, out);
		input_to((: move_get_dest :), who, env, verb, actarg, exits);
		return;
	}

	if(undefinedp(exits[str]))
	{
		tell_object(who, "沒有這個出口。\n操作失敗。\n");
		return;
	}

	if(!in_same_dir(base_name(env), exits[str]))
	{
		tell_object(who, "你沒有修改目的檔案的權利。\n修改失敗。\n");
		return;
	}

	actarg["move_dest"] = exits[str];
	tell_object(who, "請設定動作人離開這個房間的信息['$N' 代表動作人](q 退出)：\n");

	input_to((: move_get_here_msg :), who, env, verb, actarg, exits, str);
}

protected void move_get_here_msg(string str, object who, object env, string verb, mapping actarg, mapping exits, string dir)
{
	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!stringp(str) || (sizeof(str) < 10))
	{
		tell_object(who, "<顯示信息至少要有 5 個漢字長>\n請設定動作人離開這個房間的信息['$N' 代表動作人](q 退出)：\n");
		input_to((: move_get_here_msg :), who, env, verb, actarg, exits, dir);
		return;
	}


	if(sizeof(str) > 50)
	{
		tell_object(who, "<顯示信息不能超過 25 個漢字長>\n請設定動作人離開這個房間的信息['$N' 代表動作人](q 退出)：\n");
		input_to((: move_get_here_msg :), who, env, verb, actarg, exits, dir);
		return;
	}

	actarg["here_msg"] = str[<1]=='\n'?str:str+"\n";

	tell_object(who, "請設定動作人到達目的房間的信息['$N' 代表動作人](q 退出)：\n");

	input_to((: move_get_dest_msg :), who, env, verb, actarg, exits, dir);
}

protected void move_get_dest_msg(string str, object who, object env, string verb, mapping actarg, mapping exits, string dir)
{
	string adac_str, func_str, fname, content, result, f_sect, m_sect, e_sect;

	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!stringp(str) || (sizeof(str) < 10))
	{
		tell_object(who, "<顯示信息至少要有 5 個漢字長>\n請設定動作人到達目的房間的信息['$N' 代表動作人](q 退出)：\n");
		input_to((: move_get_here_msg :), who, env, verb, actarg, exits, dir);
		return;
	}


	if(sizeof(str) > 50)
	{
		tell_object(who, "<顯示信息不能超過 25 個漢字長>\n請設定動作人到達目的房間的信息['$N' 代表動作人](q 退出)：\n");
		input_to((: move_get_here_msg :), who, env, verb, actarg, exits, dir);
		return;
	}

	actarg["dest_msg"] = str[<1]=='\n'?str:str+"\n";

	if(environment(who) != env)
	{
		tell_object(who, "你的位置發生了變化，操作終止。\n");
		return;
	}

	adac_str = sprintf("\tadd_action(\"%s_action_func\", \"%s\");", verb, verb);
	func_str = sprintf("int %s_action_func(string arg)
{
	object me = this_player();
	mapping act_arg;
	if(!mapp(act_arg = query(\"%s_action_func\")) || !sizeof(act_arg))
		return notify_fail(\"出現錯誤。\n\");
	if( (act_arg[\"player_limit\"] == 1)
	&& (me->query_banghui_id() != act_arg[\"banghui_id\"]) )
		return 0;
	if(act_arg[\"action_arg\"] && (arg != act_arg[\"action_arg\"]))
	{
		write(act_arg[\"fail_msg\"]);
		return 1;
	}
	message_vision(act_arg[\"here_msg\"], me);
	if(!me->move(act_arg[\"move_dest\"]))
		return notify_fail(\"過不去。\n\");
	message_vision(act_arg[\"dest_msg\"], me);
	return 1;
}", verb, verb);

	if(!content = read_file(fname = base_name(env) + ".c"))
	{
		tell_object(who, "無法讀取檔案內容。\n操作失敗。\n");
		return;
	}

	if(!BUNCH_D->parse_function_body(ref content, "void", "init", ref f_sect, ref m_sect, ref e_sect, 0))
	{
		if(!BUNCH_D->parse_function_body(ref content, "void", "create", ref f_sect, ref m_sect, ref e_sect, 0))
		{
			tell_object(who, "無法剖析文件內容，修改失敗。\n");
			return;
		}

		result = sprintf("// Room: %s\n\n%s\n\tset(\"%s_action_func\", %O);\n%s\n%s\nvoid init()\n{\n%s\n}\n%s\n",
			fname, f_sect, verb, actarg, m_sect, e_sect, adac_str, func_str);
	}
	else
	{
		content = sprintf("%s\n%s\n%s\n%s\n", f_sect, adac_str, m_sect, e_sect);
		if(!BUNCH_D->parse_function_body(ref content, "void", "create", ref f_sect, ref m_sect, ref e_sect, 0))
		{
			tell_object(who, "無法剖析文件內容，修改失敗。\n");
			return;
		}
		result = sprintf("// Room: %s\n\n%s\n\tset(\"%s_action_func\", %O);\n%s\n%s\n%s\n",
			fname, f_sect, adac_str, m_sect, e_sect, func_str);
	}

	if(!write_file(fname, result, 1))
	{
		tell_object(who, "無法寫入文件內容，修改失敗。\n");
		return;
	}

	if( !env = BUNCH_D->update_room(env) )
	{
		tell_object(who, "無法載入房間，修改失敗。\n");
		return;
	}

	if(BUNCH_D->break_an_exit(who, env, dir))
		tell_object(who, "動作加入成功。\n");
}

// 開出口類動作
