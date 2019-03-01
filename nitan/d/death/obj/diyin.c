#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(RED "地陰血脈" NOR, ({ "diyin xuemai", "diyin", " xuemai"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "一塊奇異的礦石,散發出隱隱血光。\n" NOR);
                set("unit", "塊");
                set("value", 20000);
        }
}