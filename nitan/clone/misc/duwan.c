// duwan.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + RED "毒丸" NOR, ({ "du wan", "du", "wan", "duwan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "這是一粒由毒蟲毒液精製而成的毒藥，毒性猛烈之極。\n" NOR);
                set("base_unit", "顆");
                set("unit", "顆");
                set("base_value", 100);
                set("base_weight", 10);
                set("poison_type", "poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 800,
                        "id"    : "ding chunqiu",
                        "name"  : "毒",
                        "duration": 40,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N一仰脖，把毒藥全部倒入了嘴中。\n", me);
        set_temp("die_reason", "吃了毒藥去見黑白無常了", me);
        me->die();

        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}
