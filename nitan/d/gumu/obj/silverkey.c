// Room: /d/gumu/obj/silverkey.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ITEM;

void create()
{
        set_name(HIW"銀鑰匙"NOR, ({"yin yaoshi","silver key","key"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit","把");
                set("long","這是一把白銀打制的鑰匙，上書古墓字樣，似乎和古墓的某些秘密有關。\n");
                set("value", 400);
                setup();
        }
}
