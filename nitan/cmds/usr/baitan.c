#include <ansi.h>
inherit F_CLEAN_UP;

int baitan(object me);
int halt_baitan(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where;

        where = environment(me);

        if( !query("is_vendor", me) )
                return notify_fail("只有從事商業的人才能擺攤。\n");

        if (! present("shang ling", me))
                return notify_fail("你的商令不在身上，如今世道亂，小心為妙。\n");

        if (me->is_fighting())
                return notify_fail("你還是好好打你的架吧。\n");

        if( query_temp("on_baitan", me) )
                return notify_fail("你現在已經佔了一個攤位，還是適可而止吧。\n");

        if( me->is_busy() || query_temp("pending/deriving", me) )
                return notify_fail("你現在正忙著呢，沒功夫擺攤設點。\n");

        if (me->query_condition("killer"))
                return notify_fail("現在官府正到處查你呢，難得還有心情擺攤？\n");

        if( query("no_trade", where) )
                return notify_fail("這裡常有官兵來巡邏，最好換個地方做生意。\n");

        if( query("no_fight", where) && !query("can_trade", where) )
                return notify_fail("這個地方過于嘈雜，還是換個地方做生意吧。\n");

        message_vision(WHT "$N" WHT "尋了塊空地，一屁股坐了下來，隨後掏"
                       "出一塊布攤開在地。\n" NOR, me);
        tell_object(me, HIC "現在你可以擺上(" HIW "stock" HIC ")貨物或是"
                        "收起(" HIW "unstock" HIC ")某種貨物。\n" NOR);

        set_temp("on_baitan", 1, me);
        delete("vendor_goods", me);
        me->set_short_desc("正在地上擺攤。");

        me->start_busy(bind((: call_other, __FILE__, "baitan" :), me),
                       bind((: call_other, __FILE__, "halt_baitan" :), me));
        return 1;
}

int baitan(object me)
{
        switch (random(300))
        {
        case 0:

                message_vision(CYN "$N" CYN "環顧了一下四周，笑眯眯"
                               "地招呼著眾人。\n" NOR, me);
                break;

        case 1:
                message_vision(CYN "$N" CYN "吆喝道：走過路過不要錯"
                               "過，大家快來看看貨。\n" NOR, me);
                break;

        case 2:
                message_vision(CYN "$N" CYN "吆喝道：大家來看看，我"
                               "這裡貨物齊全，包您滿意。\n" NOR, me);
                break;
        case 3:
                message_vision(CYN "$N" CYN "吆喝道：來來來，現在所"
                               "有物品賤價出售，別錯過。\n" NOR, me);
                break;
        }

        return 1;
}

int halt_baitan(object me)
{
        message_vision(WHT "$N" WHT "提起攤布的四個角，把貨物一股腦的收了"
                       "起來，站起身來。\n" NOR, me);

        delete_temp("on_baitan", me);
        delete("vendor_goods", me);
        me->set_short_desc(0);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : baitan

擺攤設點，兜售貨物。

HELP);
        return 1;
}
