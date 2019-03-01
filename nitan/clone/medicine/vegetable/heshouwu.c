// heshouwu.c 何首烏

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(WHT"何首烏"NOR, ({"he shouwu"}));
        set_weight(800);
        set("vegetable", 4);
        set("nostrum", 1);
        set("unit", "支");
        set("long", "這是一支已成人形的何首烏，看來可以入藥。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if( query("max_jingli", me) <= 200 )
        {
                write("你吃下了一支何首烏，只覺得精神健旺之極。\n");
                addn("max_jingli", 2, me);
                addn("jingli", 2, me);
        }
        else {
                write("你吃下了一支何首烏，但是好象沒什麼用。\n");
        }
        destruct(this_object());
        return 1;
}