// Code of ShenZhou
//  poison: shedan.c
// Jay 3/18/96
// ryu added effect_in_liquid

inherit PILL;
#include <ansi.h>;
int cure_ob(string);


void create()
{
        set_name("毒蛇膽", ({"shedan", "dan"}));
        set("unit", "粒");
        set("long", "這是一隻綠瑩瑩的毒蛇膽。\n");
        set("value", 200);
        set("medicine", 1);
        setup();
}

/*
int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什麼？\n");
        return notify_fail("你找死啊。\n");
}
*/


void init()
{
        add_action("do_pour", "drop");
}
int cure_ob(object me)
{
   message_vision("$N吃下一粒" + name() + "。\n", me);
   if ((int)me->query_condition("snake_poison") > 7) {
      me->apply_condition("snake_poison", (int)me->query_condition("snake_poison") - 5);
   }

   destruct(this_object());
   return 1;
}
int effect_in_liquid(object ob)
{
        if( query("liquid/type", ob) == "alcohol"){
        addn("qi", 10*query("liquid/drunk_apply", ob), this_player());
        message_vision(MAG"$N感到一股真氣緩緩注入丹田，混身上下暖哄哄的。\n"NOR, this_player());
        }
        return 0;
}