//bing2.c 二舉餅
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIY "二舉餅" NOR, ({"bing2", "erjubing"}));
        set("unit", "個");
        set("long", "這是一個甜香的二舉餅。\n");
        set("no_get", 1);
        set("no_drop", 1);
        set("no_put", 1);
        set("no_beg", 1);
        set("no_steal", 1);
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if (!id(arg))  return notify_fail("你要吃什麼？\n");
        if( query("owner") != query("id", me) )
        {
                write(HIR"你只能吃自個贏來的餅。\n"NOR);
                return 1;
        }
        if(arg=="bing2"||arg=="erjubing")
        {
                addn("combat_exp", 168, me);
                addn("potential", 68, me);
                message_vision(HIY "$N三口兩口吃下一塊$n。\n" NOR, this_player(), this_object());
                destruct(this_object());
        }
        return 1;
}
void owner_is_killed()
{
        destruct(this_object());
}