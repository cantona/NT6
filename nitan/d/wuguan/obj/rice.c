inherit ITEM;
inherit F_FOOD;
#include <ansi.h>;

void create()
{
        set_name(HIW "小米飯" NOR, ({ "rice" }));
        set_weight(280);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一碗香噴噴的小米飯。\n" NOR);
                set("unit", "碗");
                set("value", 0);
                set("food_remaining", 15);
                set("food_supply", 10);
        }
}