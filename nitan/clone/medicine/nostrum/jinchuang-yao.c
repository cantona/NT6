// jinchuang-yao.c 金創藥

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

        set_name("金創藥", ({"jin chuangyao", "jin"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包別具靈效的金創藥，專治內外傷等。\n");
                set("value", 2000);
                set("no_drop", "這樣東西不能離開你。\n");
        }
        set("pour_type", "1");
        set("shaolin",1);
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
                return notify_fail("你現在不需要用金創藥。\n");
        
        if ( (int)me->query_condition("bonze_drug" ) > 0 )
        {
                this_player()->receive_damage("qi", 50);
                message_vision(HIR "$N吃下一包金創藥，只覺胸口煩惡欲嘔，四肢乏力，原來服食太急太多，藥效適得其反！\n" NOR, me);
        }
        else
        {
                this_player()->receive_curing("qi", 50);
                message_vision(HIC "$N吃下一包金創藥，只覺精神振作，氣色看起來好多了。\n" NOR, me);
        }
        me->apply_condition("bonze_drug", 15);
        destruct(this_object());
        return 1;
}
