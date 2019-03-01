// item: yellowobj.c

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(HIY"黃布小囊"NOR, ({"huangbu xiaonan", "xiaonan"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一只黃布小囊，不知道有什麼用處。\n");
                set("unit", "只");
                set("value", 1);
        }
}
