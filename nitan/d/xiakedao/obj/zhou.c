// zhou.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("臘八粥", ({ "zhou"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "碗");
                set("long", "這是一碗珍貴的補品臘八粥。\n");
                set("value", 20000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int neili_limit;
        int neili;

        neili=query("max_neili", me);
        neili_limit = me->query_neili_limit();

        if (neili < neili_limit)
        {
                neili += random(50) + 1;
                if (neili >= neili_limit) neili = neili_limit;
                addn("neili", 25-random(50), me);
                message_vision(HIY "$N" HIY "吃下一碗臘八粥，頓然間"
                               "只覺一股熱氣直沁心肺...\n" NOR, me);
        } else
                message_vision(HIY "$N" HIY "吃下一碗臘八粥，不怎麼甜，有點苦...\n" NOR,
                               me);

        destruct(this_object());
        return 1;
}