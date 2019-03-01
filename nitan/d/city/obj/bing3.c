//bing3.c 四進餅
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIG "四進餅" NOR, ({"bing3", "sijingbing"}));
        set("unit", "個");
        set("long", "這是一個濃香的四進餅。\n");
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
        if(arg=="bing3"||arg=="sijingbing")
        {
                addn("combat_exp", 468, me);
                addn("potential", 168, me);
                message_vision(HIY "$N三口兩口吃下一塊$n。\n" NOR, this_player(), this_object());
                destruct(this_object());
        }
        return 1;
}
void owner_is_killed()
{
        destruct(this_object());
}