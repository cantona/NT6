// gao.c 龜苓膏

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW"龜苓膏"NOR, ({"guiling gao","gao"}));
        set_weight(3000);
        set("unit", "塊");
        set("long", "這是一塊用烏龜甲和茯苓配置成的龜苓膏，功能延年益壽。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int taoism_limit, jingli_limit;
        object me = this_player();

        taoism_limit = me->query_skill("taoism", 1)*10;
        jingli_limit=query("max_jingli", me);
        
        if (!id(arg)) return notify_fail("你要吃什麼？\n");
        if (!present(this_object(), this_player()))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        me->start_busy(2);
        if ( jingli_limit <= taoism_limit && jingli_limit < 500 )
        {
                write(YEL"你吃下了一塊龜苓膏，只覺得精神健旺之極，精力直欲奔騰而出。\n"NOR);
                addn("max_jingli", 20, me);
                addn("jingli", 20, me);
        }
        else write("你吃下了一塊龜苓膏，但是好象沒什麼用。\n");

        destruct(this_object());
        return 1;
}
