// tianwangdan.c 天王保命丹
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("天王保命丹", ({"baoming dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 4000);
                set("long", "這天王保命丹是由三百年老山人蔘、白熊膽、雪蓮等物煉成的靈丹。\n");
                set("medicine", 1);
                set("no_drop", "天王保命丹煉製，哪能亂扔！ \n");
        }

        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) )
        {
                message_vision("$N沒必要吃天王保命丹。\n",me);
        }
        else
        {
                me->receive_curing("jing", 250);
                me->receive_curing("qi", 400);
                message_vision("$N吃下一粒天王保命丹，頓時覺得好多了。\n",me);
                destruct(this_object());
        }
        return 1;
}