#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "靈魂石" NOR, ({ "soul stone", "soul", "stone" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "一塊擁有神祕魔力的靈魂石，和裝備一起冶煉可讓裝備通靈性。\n" NOR);
                set("unit", "塊");
                set("value", 500000);
                set("no_sell", 1);
        }
        setup();
}
