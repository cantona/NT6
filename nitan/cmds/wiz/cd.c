// cd.c
// updated by doing

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string dir;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg)
                arg = user_path(query("id", me));
        dir = resolve_path(query("cwd", me), arg);

        seteuid(geteuid(me));
        if (file_size(dir) != -2)
                return notify_fail("沒有這個目錄。\n");

        if (! MASTER_OB->valid_read(dir, me, "cd"))
                return notify_fail("你沒有權限訪問該目錄。\n");

        if (dir[strlen(dir)-1]!='/') dir += "/";
        set("cwd", dir, me);
        write("當前目錄變更為：" + dir + "\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : cd <子目錄名>, cd .. , and cd

將目前參考的目錄移至指定的子目錄或回到上一主目錄; 亦可直接回到自己工作目錄。
HELP );
        return 1;
}