// grant.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int opt_clear, opt_del;
        int i;
        string *opts, *gr;                
        string user;
        object ob;
        string msg;

        if (! is_root(me) && ! SECURITY_D->valid_grant(me, "(admin)"))
                return notify_fail("只有管理員才能使用授權命令。\n");

        if (! me->is_admin())
        {
                switch (SECURITY_D->query_site_privilege("grant"))
                {
                case "enable":
                        break;

                default:
                        return notify_fail("你不能為其他玩家授權。\n");
                }
        }

        if (! arg)
        {
                gr = SECURITY_D->query_grant_users();
                if (! arrayp(gr) || sizeof(gr) < 1)
                {
                        write("目前系統中沒有人被授予額外使用命令的權利。\n");
                        return 1;
                }

                msg = "目前系統中被授與可以額外使用命令的用户有：\n";
                msg += implode(gr, "、") + "。\n";
                write(msg);
                return 1;
        }

        arg = replace_string(arg, ";", " ");
        arg = replace_string(arg, ",", " ");
        opts = explode(arg, " ");
        for (i = 0; i < sizeof(opts); i++)
        {
                if (opts[i] == "")
                        continue;

                if (opts[i] == "-c") opt_clear = 1; else
                if (opts[i] == "-d") opt_del   = 1; else
                if (! stringp(user)) user = opts[i]; else
                if (file_size("/grant/" + opts[i]) < 0)
                        return notify_fail("請參見/grant下面的"
                                           "可授權命令，目前並沒有 " + opts[i] +
                                           " 這個項目。\n");
                else continue;

                opts[i] = 0;
        }

        opts -= ({ 0, "" });
        if (! stringp(user))
                return notify_fail("你要給誰授權？\n");

        ob = find_player(user);

        if (opt_clear)
        {
                // 清除某一個玩家所有的權限
                write("清除了 " + user + " 的所有授予的命令使用權限。\n");
                if (SECURITY_D->remove_grant(user, "*") && objectp(ob))
                        tell_object(ob, HIG + me->name(1) + "收回了所有授予你的命令使用權限。\n");
                return 1;
        }

        if (! sizeof(opts))
        {
                // 顯示一個玩家所有的權限
                gr = SECURITY_D->query_grant(user);
                if (! arrayp(gr) || sizeof(gr) < 1)
                {
                        write("目前 " + user + " 並沒有被授予任何命令使用權限。\n");
                        return 1;
                }

                msg = "目前 " + user + " 授予的命令使用權限有：\n";
                for (i = 0; i < sizeof(gr); i++)
                {
                        msg += WHT + gr[i] + NOR;
                        if (i < sizeof(gr) - 1)
                        {
                                msg += "、";
                                if ((i + 1) % 8 == 0) msg += "\n";
                        }
                }
                msg += "。\n";
                write(msg);
                return 1; 
        }

        for (i = 0; i < sizeof(opts); i++)
        {
                if (opt_del)
                {
                        if (! me->is_admin())
                                message_system(me->name(1) + "收回了 " + user +
                                               " 使用 " + opts[i] + " 的權限。\n");
                        write("清除了 " + user + " 使用 " + opts[i] +
                              " 的權限。\n");
                        if (SECURITY_D->remove_grant(user, opts[i]) && objectp(ob))
                                tell_object(ob, HIG + me->name(1) +
                                            "收回了你 " + opts[i] +
                                            " 的權限。\n");
                } else
                {
                        if (! me->is_admin())
                                message_system(me->name(1) + "授予 " + user +
                                               " 使用 " + opts[i] + " 的權限。\n");
                        write("授予了 " + user + " 使用 " + opts[i] +
                              " 的權限。\n");
                        if (SECURITY_D->grant(user, opts[i]) && objectp(ob))
                                tell_object(ob, HIG + me->name(1) +
                                            "授予了你 " + opts[i] +
                                            " 的權限。\n");
                }
        }

        // 保存授權信息
        SECURITY_D->save();

        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: grant [-d | -c] <玩家> <命令> <命令> ....

給一個玩家授權使用某些命令。當然，該玩家必須能夠呼叫到這些命
令才可以，另外並不是所有的命令都可以授權的，具體可以參見目錄
/grant下面的文件。

使用 -d 參數可以去掉一個玩家對某些命令的使用權限，使用 -c 參
數則可以清除一個玩家所有已經授予的使用權限。

如果除了<玩家>以外不加任何命令參數和選項參數，則顯示該玩家目
前的授權狀況。

如果沒有任何參數，則現實當前系統中被授權過的使用者。你可以查
詢 /grant 目錄下的文件瞭解有那些命令可以通過授權使用。注意：
授權只是讓該使用者可以使用該命令，但是究竟能否使用還要看該命
令所在的位置。

該命令可以授權的信息：enable

HELP );
        return 1;
}