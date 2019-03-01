//bing1.c 一秀餅
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIG "一秀餅" NOR, ({"bing1", "yixiubing"}));
        set("unit", "塊");
        set("long", "這是一塊脆香的一秀餅。\n");
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
        if (!id(arg)) return notify_fail("你要吃什麼？\n");
        if( query("owner") != query("id", me) )
        {
                write(HIR"你只能吃自個贏來的餅。\n"NOR);
                return 1;
        }
        if(arg=="bing1"||arg=="yixiubing")
        {
                message_vision(HIY "$N三口兩口吃下一塊$n。\n" NOR, this_player(), this_object());
                addn("combat_exp", 68, me);
                addn("potential", 18, me);
                destruct(this_object());
        }
        return 1;
}
void owner_is_killed()
{
        destruct(this_object());
}