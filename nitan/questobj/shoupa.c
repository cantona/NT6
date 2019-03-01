// Feb. 6, 1999 by Winder
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name( MAG"手帕"NOR, ({ "shou pa", "shoupa"}));
        set_weight(300);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("value",0);
                set("long","這是一張繡花手帕。\n");
        }
}