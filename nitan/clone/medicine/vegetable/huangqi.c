// huangqi.c 黃芪

#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"黃芪"NOR, ({"huang qi", "yao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", YEL"這是一株毛茸茸的開着淡黃色小花的黃芪。\n"NOR);
                set("value", 2500);
        }
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
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if( query("eff_qi", me) == query("max_qi", me) )
        {
                me->receive_damage("qi", 50);
                message_vision(HIR "$N吃下一株黃芪，只覺得頭重腳輕，搖搖欲倒，原來沒病沒痛亂吃藥，藥效適得其反！\n" NOR, me);
        }
        else {
                me->receive_curing("qi", 50);
                message_vision("$N吃下一株黃芪，只覺得渾身熱氣騰騰，頓時舒坦多了！\n", me);
        }

        destruct(this_object());
        return 1;
}