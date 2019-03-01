#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("玉蜂蜜", ({ "yufeng mi", "yufeng", "mi"}));
        set_weight(750);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一罐玉蜂釀成的蜜，可解玉蜂毒。\n" NOR);
                set("unit", "罐");
                set("value", 500);
                set("no_sell", 1);
                set("mi_count", 5);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if (query("mi_count") < 1)
        {
                write("罐子裡的玉蜂蜜已經被喝得一滴不剩了。\n");
                return 1;
        }

        if( query("water", me) >= me->max_water_capacity( )
            && query("food", me) >= me->max_food_capacity() )
        {
                write("你已經吃太飽了，再也塞不下任何東西了。\n");
                return 1;
        }

        message_vision("$N拿起罐子，咕嘟咕嘟嚥下幾口玉蜂蜜。\n" NOR, me);
        addn("food", 50, me);
        addn("water", 50, me);

        if ((int)me->query_condition("yufengdu"))
        {
                me->clear_condition("yufengdu");
                tell_object(me, HIC "你只覺體內殘存的玉蜂毒慢慢"
                                    "消退，氣脈隨之一暢。\n" NOR);
        }
        addn("mi_count", -1);
        return 1;
}