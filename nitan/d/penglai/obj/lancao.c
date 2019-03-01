

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "蘭草" NOR, ({ "penglai lancao" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "棵");
                set("value", 1);
                set("long", HIY "這是一棵蘭草，形狀很奇特，似乎在人間未曾見過。\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}