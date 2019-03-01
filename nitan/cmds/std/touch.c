// touch.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj;
        function f; 
        int r;

        return notify_fail("該功能已經關閉。\n");
        if (! arg)
                return notify_fail("你要觸摸什麼物品？\n");

        if (! objectp(obj = present(arg, me)) &&
            ! objectp(obj = present(arg, environment(me))))
                return notify_fail("你身上沒有這樣東西，附近也沒有。\n");

        if (obj->is_character())
                return notify_fail("你別亂動" + obj->name() + "了。\n");

        f = query_temp("override/touch", me);
        if (functionp(f)) 
                r = (*f)(me, arg); 
        if (r) return r;

        notify_fail("你摸了一下" + obj->name() + "。\n");
        return obj->do_touch(me);
}

int help(object me)
{
        write(@HELP
指令格式 : touch <物品名稱>
 
這個指令可以讓你撫摸某樣東西，嘗試發揮它的特殊能力。
 
HELP );
        return 1;
}
