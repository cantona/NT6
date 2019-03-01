#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(BLU"斷腸草"NOR, ({"duanchang cao", "duanchang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "這是一株斷腸草，奇毒無比。\n");
                set("yaowang", 1);
                set("dig", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}
