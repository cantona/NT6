#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(GRN "斷腸草" NOR, ({"duanchang cao", "duanchang", "cao"}));
        set("unit", "株");
        set("long", GRN "這是一株閃爍着磷光的小草。\n" NOR);
        set("value", 10);
        set_weight(100);
        set("only_do_effect", 1);
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，將斷腸草塞入了嘴中。\n", me);
        set_temp("die_reason", "吃了斷腸草去見黑白無常了", me);
        me->die();
        destruct(this_object());
        return 1;
}
