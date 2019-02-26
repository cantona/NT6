// clone.c

inherit F_CLEAN_UP;

int main(object me, string file)
{
        object obj;
        string err, msg;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(getuid());

        if( !file)file=query("cwf", me);
        if (! file)
                return notify_fail("你要複製什麼物件？\n");

        file=resolve_path(query("cwd", me),file);
        if (sscanf(file, "%*s.c") != 1) file += ".c";
        set("cwf", file, me);

        if (file_size(file) < 0)
                return notify_fail("沒有這個檔案(" + file + ")。\n");

        if (! SECURITY_D->valid_read(file, me, "clone"))
        {
                write("你沒有權限操作這個對象。\n");
                return 1;
        }

        if (! find_object(file))
        {
                err = catch(call_other(file, "???"));
                if (err)
                {
                        write("載入失敗：" + err + "\n");
                        return 1;
                }
        }

        if (! me->is_admin() && query("id", me) !="luoyun")
        {
                switch (SECURITY_D->query_site_privilege("clone"))
                {
                case "gift":
                        if (! sscanf(file, "/clone/special/%*s") &&
                            ! sscanf(file, "/clone/gift/%*s"))
                                return notify_fail("你不能複製這個物品。\n");
                        break;

                case "all":
                        break;

                default:
                        return notify_fail("你不能複製物品。\n");
                }

                if (! me->is_admin())
                        message_system(sprintf("%s(%s)複製了物品：%s(%s)。\n",
                                               me->name(1),query("id", me),
                                               filter_color(file->name(1)),query("id", get_object(file))));
        }

        seteuid(geteuid(me));

        err = catch(obj = new(file));
        if (err)
        {
                write("複製失敗：" + err + "\n");
                return 1;
        }

        if (! objectp(obj))
        {
                write("你無法複製該物品。\n");
                return 1;
        }

        msg = "只見$N伸手凌空一指，變出了$n。\n";

        log_file("static/clone", sprintf("%s %-9s clone %s\n",
                                         log_time(), geteuid(me),
                                         base_name(obj)));
        if( !obj->is_character() && !query("no_get", obj) && obj->move(me) )
        {
                write(query("name", obj)+"複製成功，放在你的物品欄。\n");
                message_vision(msg + "\n", me, obj);
                return 1;
        }
        if (obj->move(environment(me)))
        {
                write(query("name", obj)+"複製成功，放在這個房間。\n");
                message_vision(msg + "\n", me, obj);
                return 1;
        }

        destruct(obj);
        return notify_fail("無法複製不能移動的物件(" + file + ")。\n");
}

int help(object me)
{
        write(@HELP
指令格式 : clone <檔名>

利用此指令可複製任何能移動之物件(含人物)。

該命令在可以被授權使用的信息包括：gift、all。
HELP );
        return 1;
}
