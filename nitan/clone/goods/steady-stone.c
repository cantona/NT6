#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "強化石" NOR, ({ "steady stone", "steady", "stone" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "一塊擁有神秘魔力的強化石，和裝備一起冶煉可強化裝備基本屬性。\n" NOR);
                set("unit", "塊");
                set("value", 500000);
                set("no_sell", 1);
        }
        setup();
}
