// baiyunwan.c 白雲熊膽丸

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW"白雲熊膽丸"NOR, ({"baiyun xiongdanwan", "wan"}));
        set("unit", "粒");
        set("vegetable", 26);
        set("nostrum", 92);
        set("level", 40);
        set("pour_type", "1");
        set("long", "這是一粒白雲熊膽丸，雪白透亮。\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) && 
                query("neili", me) >= query("max_neili", me) )
        {
                message_vision("$N沒必要吃白雲熊膽丸。\n",me);
        }
        else
        {
                set("eff_jing",query("max_jing",  me), me);
                set("jing",query("eff_jing",  me), me);
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                set("neili",query("max_neili",  me), me);
                message_vision("$N吃下一粒白雲熊膽丸，只覺得周身熱乎乎的，十分舒坦。\n",me);
                destruct(this_object());
        }
        return 1;
}