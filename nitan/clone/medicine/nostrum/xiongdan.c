// xiongdan.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
        remove_call_out("destdan");
        call_out("destdan", 10);
}

void destdan()
{
        object ob;
        message_vision("$N慢慢被風吹着，一會就不再新鮮了。\n",this_object());
        ob = new("/clone/medicine/vegetable/xiongdan");
        ob->move(environment(this_object()));
        destruct(this_object());
}

void create()
{
        set_name(HIG"新鮮熊膽"NOR, ({"dan", "xiong dan"}));
        set("unit", "副");
        set("long", "這是一副碧綠色的新鮮熊膽，熱氣騰騰的，十分誘人。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int force_limit, neili_limit;
        object me = this_player();

        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if( neili_limit <= force_limit)addn("max_neili", 2, me);
        set("neili",query("max_neili",  me), me);
        set("qi",query("eff_qi",  me), me);
        message_vision("$N吃下一副新鮮熊膽，只覺得精神健旺，體內真力源源滋生，氣血充盈。\n",me);

        destruct(this_object());
        return 1;
}