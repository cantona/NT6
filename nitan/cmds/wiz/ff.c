// ff.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string dest, func, file;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg || sscanf(arg, "%s %s", dest, func) != 2)
                return notify_fail("指令格式：ff <物件> <函數名稱>\n");

        if (dest == "me") ob = me; else
        if (dest == "here") ob = environment(me); else
                            ob = present(dest, me);

        if (! ob) ob = present(dest, environment(me));
        if (! ob) ob = find_object(resolve_path(query("cwd", me), dest));
        if (! ob) return notify_fail("這裡沒有「" + dest + "」。\n");

        file = function_exists(func, ob, 1);
        if (! file)
                write(sprintf("物件 %O 並沒有定義 %s 這個函數。\n", ob, func));
        else
                write(sprintf("物件 %O 的 %s 函數定義在 %s.c。\n", ob, func, file));
        return 1;
}

int help()
{
        write(@TEXT
指令格式：ff <物件> <函數名稱>

這個指令可以找出指定物件中的某個函數定義在哪一個檔案裡。
TEXT );
        return 1;
}
