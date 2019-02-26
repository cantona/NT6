#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG "毒囊" NOR, ({"du nang", "dunang", "du", "nang"}));
        set("unit", "個");
        set("long", HIG "這是一個毒蟲的毒囊，囊中充滿了毒液，發着磷光。\n" NOR);
        set("value", 100);
        set_weight(10);
        set("only_do_effect", 1);
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，將毒囊的毒液盡數倒入嘴中。\n", me);
        me->set_temp("die_reason", "吃了毒囊去見黑白無常了");
        me->die();
        destruct(this_object());
        return 1;
}

