#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(CYN"無根草"NOR, ({"wugen cao", "wugen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "這是一株無根草，據説有毒。\n");
                set("yaowang", 1);
                set("dig", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}
