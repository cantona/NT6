// 聖化

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object item;

        if (me->is_busy())  
                return notify_fail("你的動作還沒有完成。\n");  

        if (me->is_fighting())  
                return notify_fail("你正在戰鬥呢，還是安心戰鬥吧。\n");  

        if (! arg) return notify_fail("你要聖化什麼物品？\n");

        if (! objectp(item = present(arg, me)))
                return notify_fail("你身上沒有這種物品。\n");

        notify_fail(item->name() + "沒有辦法被聖化。\n");

        // 聖化物品
        return item->do_san(me);
}

int help(object me)
{
write(@HELP
指令格式 : san <物品名稱>
 
這個指令可以讓你聖化某樣物品。當然，這件物品得能夠聖化才可以，
而且你需要有足夠充沛的內力和相當多的精力。聖化以後你會損失一
些內力和精力的上限。

值得注意的是：聖化時如果你的內力水平沒有充分鍛煉到你目前的極
限，則聖化將會有一定的危險，有可能導致你的基本內功受到損傷。
因此在聖化前保証自己的內力接近瓶頸值是可靠的做法。
HELP
    );
    return 1;
}