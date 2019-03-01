#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "藥丸" NOR, ({"yao wan", "yao", "wan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "一顆渾圓的藥丸，乃是烏老大所配制的獨門解藥。\n" NOR);
                set("unit", "顆");
                set("value", 300);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision(HIC "$N" HIC "一仰脖，吞下一顆藥丸。\n" NOR, me);
        if ((int)me->query_condition("lb_poison"))
        {
                me->clear_condition("lb_poison");
                me->start_busy(2);
                tell_object(me, HIY "你感到內息一暢，體內的綠波劇毒開始慢慢消退。\n" NOR);

        }
        destruct(this_object());
        return 1;
}