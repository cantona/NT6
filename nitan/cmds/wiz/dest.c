// dest.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string option, target, msg;
        object obj;
        int opt_clone;
        object *obs;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg)
                return notify_fail("指令格式 : dest <物件之名稱或檔名>\n");

        if (sscanf(arg, "%s %s", option, target) == 2 &&
            option == "-c")
        {
                opt_clone = 1;
        } else
        {
                target = arg;
                opt_clone = 0;
        }

        obj = find_object(target);
        if (! obj) obj = present(target, me);
        if (! obj) obj = present(target, environment(me));
        if (! obj) obj = find_object(target);
        if (! obj) obj = find_object(resolve_path(query("cwd", me), target));
        if (! obj) return notify_fail("沒有這樣物件....。\n");

        seteuid(getuid());

        if (! me->is_admin() && query("id",me) != "luoyun")
        {
                switch (SECURITY_D->query_site_privilege("dest"))
                {
                case "all":
                        break;

                case "noneuser":
                        if (playerp(obj))
                                return notify_fail("你不能對玩家施展法力。\n");
                        break;

                case "user":
                        if (! playerp(obj))
                                return notify_fail("你只能對玩家施展法力。\n");
                        break;

                default:
                        return notify_fail("你不能使用該命令。\n");
                }
        }

        if (! is_root(me)) seteuid(geteuid(me));

        if (playerp(obj) && wiz_level(me) < wiz_level("(arch)"))
        {
                write("你沒有權限摧毀玩家。\n");
                return 1;
        }

        if (! SECURITY_D->valid_write(base_name(obj), me, "dest"))
        {
                write("你沒有權限操作這個對象。\n");
                return 1;
        }

        if (opt_clone)
        {
                if (clonep(obj))
                {
                        write("該對象是複製對象，沒有派生對象，無法執行 -c 選項。\n");
                        return 1;
                }

                if (obj == find_object(USER_OB))
                {
                        write("你不能清除使用者的派生對象。\n");
                        return 1;
                }

                if (obj == find_object(LOGIN_OB))
                {
                        write("你不能清除使用者連接信息的派生對象。\n");
                        return 1;
                }

                obs = children(base_name(obj));
                foreach (obj in obs)
                {
                        write("你摧毀了" + obj->name(1) + "(" +
                              file_name(obj) + ")。\n");
                        destruct(obj);
                }
                write("Ok.\n");
                return 1;
        }

        if (me == obj)
                message_vision("$N召喚出一個黑洞，一頭鑽了進去。\n", me);
        else
        if (environment(me) == environment(obj))
                message_vision("$N召喚出一個黑洞，一腳把將$n踢了進去。\n", me, obj);

        destruct(obj);
        if (obj) write("你無法將這個物件摧毀。\n"); else
        if (me) write("Ok.\n");

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : dest [-c] <物件之名稱或檔名>

利用此一指令可將一個物件 object 從記憶體中清除，若清除物件，
則下一次參考到這個物件的時候會重新將它編譯。

如果使用了 -c 參數，則將清除該檔案派生出的所有對象。

該命令在可以被授權使用的信息包括：noneuser、user、all。

參考資料： destruct()
HELP );
        return 1;
}
