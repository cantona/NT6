// cleanup.c

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob, where, *ob_list;
        int old_size, i;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! str) return notify_fail("指令格式：cleanup <檔名>\n"); 

        str=resolve_path(query("cwd", me),str);
        ob_list = children(str);
        old_size = sizeof(ob_list);
        ob_list->clean_up();
        for (i = 0; i < sizeof(ob_list); i++)
                if (ob_list[i] && clonep(ob_list[i]) && ! environment(ob_list[i]))
                        destruct(ob_list[i]);
        ob_list -= ({ 0 });
        write(sprintf("清除 %d 個物件。\n", old_size - sizeof(ob_list)));
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：cleanup <檔名>

對所有指定檔名的物件呼叫 clean_up，並且清除所有被復制出來的，但是又沒有
被放在另一個物件中的散失物件。
HELP );
        return 1;
}