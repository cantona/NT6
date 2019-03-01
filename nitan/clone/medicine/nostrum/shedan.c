// shedan.c 蟒蛇膽
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
        remove_call_out("decay");
        call_out("decay", 180);
}

void create()
{
        set_name(HIG"蟒蛇膽"NOR, ({"dan", "she dan"}));
        set("unit", "副");
        set("long", "這是一副蟒蛇膽，碧綠如藍。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int taoism_limit, jingli_limit;
        object me = this_player();

        taoism_limit = me->query_skill("taoism", 1)*10;
        jingli_limit=query("max_jingli", me);
        
        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if( jingli_limit <= taoism_limit)addn("max_jingli", 1, me);
        set("qi",query("eff_qi",  me), me);
        message_vision("$N吃下一副蟒蛇膽，只覺得耳聰目明，精力陡長。\n",me);
        destruct(this_object());
        return 1;
}

void decay()
{
        object where = environment(this_object());
        if ( interactive(where) )
                message("vision", BLU"蟒蛇膽啪的一聲破了，弄得你一身甚是腥臭。\n"NOR, 
                        where); 
        else
                message("vision", BLU"蟒蛇膽啪的一聲破了，蛇血流了一地。\n"NOR,
                        where);
        destruct(this_object());
}