// Pill: bicanfeng.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(GRN"碧蠶粉"NOR, ({"bican fen", "fen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一袋劇毒的毒藥, 如果用來煉暗器有見血封喉之效. \n");
                set("unit", "袋");
                set("value", 20000);
        }
        set("pour_type", "1");
        setup();
}

int init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

int do_eat(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        message_vision("$N仰頭把一小袋" + name() + "都嚥了下去。\n", me);
        set_temp("die_reason", "服下碧蠶粉，自殺身亡了", me);
        me->die();
        destruct(this_object());
        return 1;
}