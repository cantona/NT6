// hua4.c
//
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIC "翡翠蘭" NOR, ({"hua4", "feicui"}));
        set("unit", "朵");
        set("long", "這是一朵千年難得一見的翡翠蘭，據說能解百毒。\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");
        set_temp("nopoison", 1, this_player());
        set("eff_jing",query("max_jing",  this_player()), this_player());
        set("jing",query("max_jing",  this_player()), this_player());
        set("eff_qi",query("max_qi",  this_player()), this_player());
        set("qi",query("max_qi",  this_player()), this_player());
        tell_object(this_player(), HIG "你只覺一股清香沁入心肺，頓時靈台一片空明，神意清爽！\n" NOR );
        destruct(this_object());
        return 1;
}