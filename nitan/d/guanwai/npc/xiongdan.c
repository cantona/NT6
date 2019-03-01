// xiongdan.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        remove_call_out("destdan");
        call_out("destdan", 10);
}

void destdan()
{
        object ob;
        message_vision("$N慢慢被風吹著，一會就不再新鮮了。\n",this_object());
        ob = new("/d/guanwai/npc/xiongdan1");
        ob->move(environment(this_object()));
        destruct(this_object());
}

void create()
{
        set_name(HIG"新鮮熊膽"NOR, ({"dan", "xiong dan"}));
        set("unit", "副");
        set("long", "這是一副新鮮熊膽，熱氣騰騰的，十分誘人。\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if (!id(arg))  return notify_fail("你要吃什麼？\n");
        if (me->is_fighting()) return notify_fail("戰鬥中不能吃東西！\n");
        if (me->is_busy()) return notify_fail("你正忙著呢！\n");
        if(arg=="dan")
        {
                addn("max_neili", 2, me);
                set("neili",query("max_neili",  me), me);
                set("qi",query("eff_qi",  me), me);
                message_vision("$N吃下一副新鮮熊膽，只覺得精神健旺，體內真力源源滋生，氣血充盈。\n",me);

                destruct(this_object());
        }
        return 1;
}
