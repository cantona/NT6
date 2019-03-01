inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "tun");
}

void create()
{
        set_name("草藥", ({"cao yao","cao","yao"}));
        set("unit", "株");
        set("long", "這是一株普通的草藥。\n");
        setup();
}

int do_eat(string arg)
{
if (!id(arg))  return notify_fail("你要吃什麼？\n");
if(arg=="yao") 
{
tell_object(this_player(), HIG "你只覺一股清香沁入心肺,頓時靈台一片空明,神意清爽！\n" NOR );
set_temp("nopoison", 1, this_player());
set("eff_jingli",query("max_jingli",  this_player()), this_player());
set("jingli",query("max_jingli",  this_player()), this_player());
set("eff_qi",query("max_qi",  this_player()), this_player());
set("qi",query("max_qi",  this_player()), this_player());
destruct(this_object());
}
return 1;
}