// tuofengbai.c

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(GRN"駝峯柏"NOR, ({"tuofeng bai"}));
        set_weight(700000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個株皇宮中的珍貴樹木。\n");
                set("unit", "株");
                set("no_get", 1);
        }
}
