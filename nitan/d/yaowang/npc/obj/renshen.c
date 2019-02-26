#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL"人蔘"NOR, ({"ren shen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "棵");
                set("long", "這是一棵人蔘，足有七兩多重。\n");
                set("yaowang", 1);
                set("dig", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}
