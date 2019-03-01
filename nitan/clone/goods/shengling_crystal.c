// This program is a part of NT MudLIB
// ab_crystal.c 能力水晶

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM"聖靈水晶"NOR, ({ "shengling crystal", "shengling", "crystal" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "聖靈水晶，可以保証在強化裝備失敗時候不掉星級，帶在身上即可。\n" NOR);
                set("value", 50000);
                set("unit", "塊");
        }
        //set("set_data", 1);
        set("autoload", 1);
        setup();
}
