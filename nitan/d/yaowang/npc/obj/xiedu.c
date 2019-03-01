#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( BLU "蠍毒" NOR , ({"xie du"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一滴無色透明的蠍毒。\n");
                set("unit", "滴");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}
