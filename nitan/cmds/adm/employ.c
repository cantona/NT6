// employ.c

#include <ansi.h>
inherit F_CLEAN_UP;

#ifndef DB_D
#define DB_D      "/adm/daemons/dbd.c"
#endif

int main(object me, string arg)
{
        object ob;
        string old_status, new_status;
        int my_level, ob_level, level;
        string *tlist;

        mapping job = ([
                       "新手導師"  :  "teacher.c",
                       "主頁維護"  :  "webmaster.c",
                       "遊戲宣傳"  :  "presell.c",
        ]);

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg || sscanf(arg, "%s %s", arg, new_status) != 2)
                return notify_fail("指令格式：employ <使用者> <職位>\n");

        if (new_status != "新手導師" &&
            new_status != "主頁維護" &&
            new_status != "遊戲宣傳" &&
            new_status != "取消雇傭" )
                return notify_fail("沒有這種職位。\n");

/*
        if (! objectp(ob = present(arg, environment(me))) ||
            ! playerp(ob))
*/
        ob = UPDATE_D->global_find_player(arg); 
        if (! objectp(ob)) 
                return notify_fail("你只能改變使用者的職位。\n");

        if( query("viremploy/job", ob) == new_status )
        {
                UPDATE_D->global_destruct_player(ob, 1); 
                return notify_fail("該玩家已經擔任該職位。\n");
        }

        if (new_status == "取消雇傭")
        {
                  if( !mapp(query("viremploy", ob)) )
                  {
                        UPDATE_D->global_destruct_player(ob, 1); 
                           return notify_fail("該玩家沒有擔任任何職位。\n");
                  }

                  CHANNEL_D->do_channel(this_object(), "rumor",
                             ob->name()+"("+query("id", ob)+")所擔任"
                             "的職位："+query("viremploy/job", ob)+"被取消了！\n");

                // 新手導師需要移除記錄
                if( query("viremploy/job", ob) == "新手導師" )
                {
                        tlist = DB_D->query_data("virlist/teacher");
                        if (sizeof(tlist))
                        {
                                if( member_array(query("id", ob),tlist) != -1 )
                                {
                                        tlist-=({query("id", ob)});
                                        DB_D->set_data("virlist/teacher", tlist);
                                }
                        }
                }

                delete("viremploy", ob);
                delete("flowers", ob);
                SECURITY_D->remove_grant(query("id", ob),"home");
                tell_object(ob, HIG + me->name(1) + "收回了你 home 的權限。\n" NOR);
                ob->save();
                UPDATE_D->global_destruct_player(ob, 1); 

                return 1;
        }

        CHANNEL_D->do_channel(this_object(), "rumor",
                             ob->name()+"("+query("id", ob)+")被任命為"+HIG+
                             new_status + NOR + "。\n");

        set("viremploy/job", new_status, ob);
        delete("flowers", ob);

        // 新手導師需要記錄
        if (new_status == "新手導師")
        {
                tlist = DB_D->query_data("virlist/teacher");
                if (sizeof(tlist))
                {
                        tlist+=({query("id", ob)});
                        DB_D->set_data("virlist/teacher", tlist);
                }
                else
                {
                        DB_D->set_data("virlist/teacher",({query("id", ob)}));
                }
        }

        set("viremploy/workroom", job[new_status], ob);
        SECURITY_D->grant(query("id", ob),"home");
        tell_object(ob, HIG + me->name(1) + "授予了你 home 的權限。\n" NOR);

        ob->save();
        UPDATE_D->global_destruct_player(ob, 1); 

        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : employ <某人> (權限等級)

用來提升權限等級, [主頁維護、遊戲宣傳、新手導師、巫師助理]

           employ <某人> 取消雇傭

取消該虛擬工作人員的職位。

HELP );
    return 1;
}
