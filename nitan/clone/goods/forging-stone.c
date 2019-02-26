#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "鍛造石" NOR, ({ "forging stone", "forging", "stone" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "一塊擁有神祕魔力的鍛造石，和裝備一起鍛造可升級裝備。\n" NOR);
                set("unit", "塊");
                set("value", 500000);
                set("no_sell", 1);
        }
        setup();
}
