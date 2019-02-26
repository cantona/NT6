// more.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string file;
        object ob;
        int    with_line_number = 1;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(geteuid(me));

        if (! arg) return notify_fail("指令格式 : more <檔名>|<物件名> \n");

        if (sscanf(arg, "%s -n", file)) with_line_number = 0;
        else file = arg;

        file = resolve_path(query("cwd", me), file);
        if (file_size(file) < 0)
        {
                ob = present(arg, me);
                if (! ob) ob = present(arg, environment(me));
                if (! ob) return notify_fail("沒有這個檔案。\n");
                file = base_name(ob) + ".c";
        }

        if (! SECURITY_D->valid_read(file, me, "read_file"))
                return notify_fail("沒有這個檔案。\n");

        if (with_line_number)
                me->start_more_file(file);
        else me->start_more(read_file(file));

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : more <檔案名> [-n]

這個指令讓你可以以分頁方式查閲一個文件的內容。如果帶 -n
參數，則表示不顯示行號。

see also: cat
HELP );
        return 1;
}
