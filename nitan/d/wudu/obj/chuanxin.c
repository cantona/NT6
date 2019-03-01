#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC "穿心蓮" NOR, ({"chuanxin lian", "chuanxin", "lian"}));
        set("unit", "朵");
        set("long", HIC "這是一朵碧藍色的蓮花，含劇毒。\n" NOR);
        set("value", 10);
        set_weight(100);
        set("only_do_effect", 1);
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，將穿心蓮塞入了嘴中。\n", me);
        set_temp("die_reason", "吃了穿心蓮去見黑白無常了", me);
        me->die();
        destruct(this_object());
        return 1;
}
