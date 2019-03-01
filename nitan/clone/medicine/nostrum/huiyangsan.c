// huiyangsan.c 回陽九龍散

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(RED"回陽九龍散"NOR, ({"huiyangjiulong san", "san"}));
        set("unit", "包");
        set("vegetable", 14);
        set("nostrum", 46);
        set("level", 90);
        set("long", "這是一包回陽九龍散，是崆峒派的療傷聖藥。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if (!present(this_object(), this_player()))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) && 
                query("neili", me) >= query("max_neili", me) )
        {
                message_vision("$N沒必要吃回陽九龍散。\n",me);
        }
        else
        {
                me->receive_recuring("jing", 200);
                me->receive_recuring("qi", 300);
//                me->set("neili", me->query("max_neili"));
                addn("neili", 150, me);
                message_vision("$N吃下一包回陽九龍散，感到全身一陣暖洋洋的，十分舒服。\n",me);
                destruct(this_object());
        }
        return 1;
}