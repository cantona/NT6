#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "drink");
}

void create()
{
        set_name(HIW "孟婆湯" NOR, ({"mengpo tang", "soup", "tang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一碗熱氣騰騰的孟婆湯，散發着濃烈的草藥氣味。\n");
                set("unit", "碗");
                set("only_do_effect", 1);
        }
        setup();
}

int do_eat(string arg)
{
        object ob;
        object me = this_player();
        int max;

        if( me->is_busy() )
                return notify_fail("急什麼，小心別噎着了。\n");

        set_temp("last_eat/mengpo_tang", time(), me);

        message_vision(HIW "$N" HIW "一仰頭，將孟婆湯全部喝了下去，精神為之一振。\n" NOR, me);

        set("jingli",query("max_jingli",  me), me);
        set("neili",query("max_neili",  me), me);
        set("jing",query("max_jing",  me), me);
        set("qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);

        max = me->max_food_capacity();
        set("food", max, me);
        max = me->max_water_capacity();  
        set("water", max, me);
        me->clear_condition();

        if( me->is_ghost() && query("reborn_offer", me) && 
            query("reborn_offer", me) == "finish" )
                me->reincarnate(); 

        me->start_busy(1);
        destruct(this_object());
        return 1;
}