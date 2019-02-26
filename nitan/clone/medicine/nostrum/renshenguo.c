// renshenguo.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
        remove_call_out("destguo");
        call_out("destguo", 10);
}
void destguo()
{
        message_vision("$N慢慢滲出水來，一會就腐爛掉了。\n",this_object());
        destruct(this_object());
}

void create()
{
        set_name(HIR"人蔘果"NOR, ({"guo", "renshen guo"}));
        set("unit", "只");
        set("long", "這是一隻人蔘果，已經成型，真的象極了三週不滿的小孩。\n");
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

        if( neili_limit <= force_limit)addn("max_neili", 10, me);
        set("neili",query("max_neili",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("eff_qi",  me), me);
        message_vision("$N吃下一枚人蔘果，只覺得精神健旺，氣血充盈，體內真力源源滋生，甚至不再感到飢餓乾渴！\n",me);
        destruct(this_object());
        return 1;
}