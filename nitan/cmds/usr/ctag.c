// ctag.c

int help(object me);

protected mapping valid_tags = ([
        "outdoor" : "outdoors",
        "no_fight" : "no_fight",
        "no_magic" : "no_magic",
        "start" : "valid_startroom",
]);

protected mapping c_msg = ([
        "outdoors" : "戶外標記",
        "no_fight" : "安全區標記",
        "no_magic" : "不能騎坐騎標記",
        "valid_startroom" : "起始點標記",
]);

protected void delete_room_tag(string str, object who, object env, string tag);
protected void add_room_tag(string str, object who, object env, string tag);

int main(object me, string arg)
{
        object env;
        array tags;
        int n;

        if(!me || (me != this_player(1)) || !objectp(env = environment(me)))
                return 0;

        seteuid(getuid(this_object()));

        if(!BUNCH_D->valid_modify_room(me, env))
                return 0;

        if(!stringp(arg)
        || (arg == "")
        || ( (n = member_array(arg, tags = keys(valid_tags))) == -1) )
                return help(me);

        if( query(valid_tags[tags[n]], env) )
        {
                write(sprintf("這裡已經設定了%s，是否要清除？[y/n]：", c_msg[valid_tags[tags[n]]]));
                input_to( (: delete_room_tag :), me, env, valid_tags[tags[n]] );
        }
        else
        {
                write(sprintf("這裡沒有設定%s，是否要設定？[y/n]：", c_msg[valid_tags[tags[n]]]));
                input_to( (: add_room_tag :), me, env, valid_tags[tags[n]] );
        }

        return 1;
}

protected void delete_room_tag(string str, object who, object env, string tag)
{
        string fname, content, f_sect, e_sect, result;

        if(!who || !env)
                return;

        if(!sizeof(str) || str[0] != 'y')
        {
                tell_object(who, "ok.\n");
                return;
        }

        if(environment(who) != env)
        {
                tell_object(who, "你的位置發生了變化，修改被停止。\n");
                return;
        }

        if(undefinedp(c_msg[tag]))
        {
                tell_object(who, "出現異常錯誤，修改被停止。\n");
                return;
        }

        if(!content = read_file(fname = base_name(env) + ".c"))
        {
                tell_object(who, "無法讀取文件內容，修改失敗。\n");
                return;
        }
        /*
        if(BUNCH_D->parse_set_value(ref content, tag, ref f_sect, ref e_sect))
        {
                result = sprintf("// Room: %s\n\n%s\n%s\n", fname, f_sect, e_sect);

                if(!write_file(fname, result, 1))
                {
                        tell_object(who, "無法寫入文件內容，修改失敗。\n");
                        return;
                }
        }
        */
        if( !BUNCH_D->update_room(env) )
        {
                tell_object(who, "無法載入房間，修改失敗。\n");
                return;
        }

        tell_object(who, "清除成功。\n");
}

protected void add_room_tag(string str, object who, object env, string tag)
{
        string fname, content, f_sect, m_sect, e_sect, result, id;

        if(!who || !env)
                return;

        if(!sizeof(str) || str[0] != 'y')
        {
                tell_object(who, "ok.\n");
                return;
        }

        if(environment(who) != env)
        {
                tell_object(who, "你的位置發生了變化，修改被停止。\n");
                return;
        }

        if(undefinedp(c_msg[tag]))
        {
                tell_object(who, "出現異常錯誤，修改被停止。\n");
                return;
        }

        if(!id = who->query_BUNCH_id())
        {
                tell_object(who, "你的幫派記錄錯亂。\n修改失敗。\n");
                return;
        }

        if(!content = read_file(fname = base_name(env) + ".c"))
        {
                tell_object(who, "無法讀取文件內容，修改失敗。\n");
                return;
        }

        /*
        if(!BUNCH_D->parse_function_body(ref content, "void", "create", ref f_sect, ref m_sect, ref e_sect, 0))
        {
                tell_object(who, "無法剖析文件內容，修改失敗。\n");
                return;
        }
        */

        result = sprintf("// Room: %s\n\n%s\n\tset(\"%s\", %s);\n%s\n%s\n",
                fname, f_sect, tag, tag=="outdoors"?sprintf("\"%s\"",id):"1", m_sect, e_sect);

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

        tell_object(who, "設置成功。\n");
}

int help(object me)
{
write(@HELP

幫助信息。

HELP
    );
        return 1;
}
