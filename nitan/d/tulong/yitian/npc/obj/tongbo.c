#include <weapon.h>
#include <ansi.h>
inherit HAMMER;
void create()
{
        set_name(YEL "銅鈸" NOR,  ({ "tong bo", "tong", "bo" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "一柄用熟銅打造的鈸。\n");
                set("value", 2000);
                set("material", "gold");
        }
        init_hammer(20);
        setup();
}
