// zicao.c 紫草
// By Alf, Last Update 2001.11

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(HIM"紫草"NOR, ({"zi cao", "zicao"}));
    set_weight(40);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "這是崑崙山中出產的紫草，食之據説能延年益壽。\n");
        set("unit", "株");
        set("value", 80);
    }
}

void init()
{
    add_action("do_eat", "eat");
}

int do_eat(string arg)
{
    object me = this_player();
    if (me->is_busy())
        return notify_fail("別急，慢慢吃，小心別噎着了。\n");
    if (!id(arg))
        return notify_fail("你要吃什麼？\n");
    if(arg=="zi cao" || "zicao") 
    {
        set_temp("nopoison", 1, this_player());
        set("eff_jing",query("max_jing",  this_player()), this_player());
        set("jing",query("max_jing",  this_player()), this_player());
        set("eff_qi",query("max_qi",  this_player()), this_player());
        set("qi",query("max_qi",  this_player()), this_player());
        set("food", this_player()->max_food_capacity(), this_player());
        set("water", this_player()->max_water_capacity(), this_player());
        message_vision(HIM"$N服下一株紫草，只覺得全身暖洋洋的，精力大見旺盛。\n"NOR,me);
        me->start_busy(1);
        destruct(this_object());
    }
    return 1;
}

