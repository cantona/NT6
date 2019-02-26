// hide.c 隱藏兵器

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;
        int i;

        if (! str)
                return notify_fail("你要隱藏什麼物品？\n");

/*
        if( !stringp(query("can_summon/"+str, me)) )
                return notify_fail("你不知道如何隱藏這個物品。\n");
*/

        if (! objectp(ob = present(str, me)) &&
            ! objectp(ob = present(str, environment(me))))
                return notify_fail("你身邊沒有這個物品。\n");

        if (! ob->hide_anywhere(me))
        {
                message_vision(HIM "$N" HIM "舉着" + ob->name() +
                               HIM "，口中唸唸有詞。\n然而"
                               "什麼也沒有發生 :)\n", me);
        }

        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : hide <物品的ID>

此指令可讓你隱藏某些物品，讓它們暫時消失。
HELP
    );
    return 1;
}
