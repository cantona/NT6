// changename.c
// created by doing

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string id, new_name;
        object ob;
        string result;
        string *opts;
        int i;
        int opt_force;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return notify_fail("你要修改哪一個玩家的中文名字？\n");

        // 強制修改名字的標誌
        opt_force = 0;
        opts = explode(arg, " ");
        for (i = 0; i < sizeof(opts); i++)
        {
                if (opts[i] == "-f")
                {
                        opt_force = 1;
                        opts[i] = 0;
                }
        }

        // 判斷完畢選項以後重新判斷參數
        opts -= ({ 0 });
        arg = implode(opts, " ");

        if (sscanf(arg, "%s %s", id, new_name) == 2)
        {
                if (! LOGIN_D->check_legal_name(new_name, 8))
                        return 0;

#ifdef DB_SAVE
                if (!opt_force && DATABASE_D->db_find_user("name", new_name))
                        return notify_fail("已經有玩家叫這個名字了。\n");
#endif               
                ob = UPDATE_D->global_find_player(id);
                if (! objectp(ob))
                        return notify_fail("沒有這個玩家。\n");

                result = NAME_D->change_name(ob, new_name, opt_force);
                if (result)
                {
                        write(result);
                        if (opt_force)
                                write("系統強制修改了 " + id + " 的名字。\n");
                }
                else
                        write("成功的修改了 " + id + " 的名字。\n");
                        
                UPDATE_D->global_destruct_player(ob, 1);
                return 1;
        } else
                return notify_fail("格式：changename [-f] <玩家ID> <新名字>\n");
}

int help(object me)
{
write(@HELP
指令格式 : changename [-f] <玩家ID> <新名字>
 
更改玩家的中文名字，因為所有玩家的中文名字都記錄在系統中，所
以如果直接修改將會造成數據不一致。如果採用了-f參數，則系統會
強制修改名字而不顧及原先是否有重名或是相近的名字。

HELP );
    return 1;
}
