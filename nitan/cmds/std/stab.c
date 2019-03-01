// stab.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj;

        if (! arg)
                return notify_fail("你要用什麼物品？\n");

        if (! objectp(obj = present(arg, me)))
                return notify_fail("你身上沒有這樣東西。\n");

        notify_fail("你翻來復去的弄了一會兒，也沒能折騰好" + obj->name() + "。\n");
        return obj->do_stab(me);
}

int help(object me)
{
        write(@HELP
指令格式 : stab <物品名稱>
 
這個指令可以讓你將某樣東西插在地面上，比如標志牌什麼的。
 
HELP );
        return 1;
}