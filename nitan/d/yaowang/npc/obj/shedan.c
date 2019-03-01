#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( HIG "蛇膽" NOR , ({"she dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個濃綠色的蛇膽。\n");
                set("unit", "個");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}
