// clong.c

#include <ansi.h>
#include <bunch.h>

protected void get_room_long(string str, object who, object env, string ldesc);
protected void change_room_long(object who, object env, string ldesc);

int main(object me, string arg)
{
        object env;
        string content;

        if(!me || (me != this_player(1)) || !objectp(env = environment(me)))
                return 0;

        seteuid(getuid(this_object()));

        if(!BUNCH_D->valid_modify_room(me, env))
                return 0;

        if(!content = read_file(base_name(env)+".c"))
                return notify_fail("無法讀取當前檔案");

        write(sprintf("請為%s設定新的描述：
·為了房間的美觀，每一行請不要超過%s箇中文字
·第一行的內容長度比其它行的長度少兩個中文字寬才能對齊
·描述內容不能超過%s行\n請輸入('.'結束輸入，'q'退出)：\n------------------------------------------------------\n",
                query("short", env),chinese_number(room_desc_l/2),chinese_number(room_desc_h)));

        input_to( (: get_room_long :), me, env, "" );
        return 1;
}

protected void get_room_long(string str, object who, object env, string ldesc)
{
        if(!who || !env)
                return;

        if(!stringp(str) || (str == ""))
        {
                input_to( (: get_room_long :), who, env, ldesc );
                return;
        }

        if( (str[0] == 'q')
        || (str[0] == 'Q') )
        {
                tell_object(who, "終止房間修改。\n");
                return;
        }

        if(str[0] == '.')       // 結束輸入
        {
                if( (ldesc == "") || (sizeof(ldesc) < 10) )
                {
                        tell_object(who,"你沒有設定足夠的描述內容\n房屋修改失敗\n");
                        return;
                }

                if( sizeof(explode(ldesc, "\n")) > room_desc_h)
                {
                        tell_object(who, sprintf(HBCYN HIG"·描述內容不能超過%s行\n房屋修改失敗。\n"NOR, chinese_number(room_desc_h)));
                        return;
                }

                change_room_long(who, env, ldesc);
                return;
        }

        if(strsrch(str, '\n'))
        {
                int n;
                array tmp;

                n = sizeof(tmp = explode(str, "\n"));
                for(int i=0; i<n; i++)
                        if(strlen(tmp[i]) > room_desc_l)
                        {
                                tell_object(who, sprintf(HBCYN HIG"每一行不能超過%s箇中文字，請重新輸入上一次輸入的內容：\n"NOR, chinese_number(room_desc_l/2)));
                                input_to( (: get_room_long :), who, env, ldesc );
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
                        input_to( (: get_room_long :), who, env, ldesc );
                        return;
                }

                if( sizeof(explode(ldesc, "\n")) > (room_desc_h -1) )
                {
                        tell_object(who, sprintf(HBCYN HIG"·描述內容不能超過%s行\n房屋創建失敗。\n"NOR, chinese_number(room_desc_h)));
                        return;
                }
        }

        ldesc += str + "\n";
        input_to( (: get_room_long :), who, env, ldesc );
}

protected void change_room_long(object who, object env, string ldesc)
{
        string newf, fname, content, f_sect, e_sect;

        if(!who || !env || !ldesc)
                return;

        if(environment(who) != env)
        {
                tell_object(who, "你的位置發生了變化，修改被停止。\n");
                return;
        }

        if(!content = read_file(fname = base_name(env)+".c"))
        {
                tell_object(who, "無法讀取當前檔案，修改失敗。\n");
                return;
        }
        /*
        if(!BUNCH_D->parse_set_value(ref content, "long", ref f_sect, ref e_sect))
        {
                tell_object(who, "無法剖析當前檔案，修改失敗。\n");
                return;
        }
        */
        newf = sprintf("// Room: %s\n\n%s\n\tset(\"long\", @LONG\n%sLONG\n);\n%s\n",
                fname, f_sect, ldesc, e_sect);

        if(!write_file(fname, newf, 1))
        {
                tell_object(who, "無法寫入檔案，修改失敗。\n");
                return;
        }

        if( !BUNCH_D->update_room(env) )
        {
                tell_object(who, "重新載入房間錯誤，修改失敗。\n");
                return;
        }
        tell_object(who, "修改成功。\n");
}
