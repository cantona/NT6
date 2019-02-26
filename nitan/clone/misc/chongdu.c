// chongdu.c

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
        set_name(HIR "蟲毒" NOR, ({ "chong du", "chong", "du", "chongdu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這是一粒由毒蟲毒液精製而成的毒藥，毒性相當猛烈。\n" NOR);
                set("base_unit", "粒");
                set("base_value", 100);
                set("base_weight", 10);
                set("poison_type", "poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 180,
                        "id"    : "he tieshou",
                        "name"  : "蟲毒",
                        "duration" : 12,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        message_vision("$N一仰脖，把毒藥全部倒入了嘴中。\n", me);
        set_temp("die_reason", "吃了蟲毒暴斃身亡了", me);
        me->die();

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
