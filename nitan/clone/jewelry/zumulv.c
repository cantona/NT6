// zhumulv.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"祖母綠"NOR, ({ "zumu lv", "zumulv" }) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一粒亮綠的寶石，真是人間稀世珍寶。\n");
                set("unit", "粒");
                set("value", 200000 );
        }

}
