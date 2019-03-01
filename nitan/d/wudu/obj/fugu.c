#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(WHT "腐骨草" NOR, ({"fugu cao", "fugu", "cao"}));
        set("unit", "株");
        set("long", WHT "這是一株普通的小草，葉面發出一股難聞的臭氣。\n" NOR);
        set("value", 10);
        set_weight(100);
        set("only_do_effect", 1);
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，將腐骨草塞入了嘴中。\n", me);
        set_temp("die_reason", "吃了腐骨草去見黑白無常了", me);
        me->die();
        destruct(this_object());
        return 1;
}
