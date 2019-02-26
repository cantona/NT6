// yuping.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("青銅鼎", ({ "qingtong ding", "ding" }));
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "這是一隻古代的青銅鼎，上面雕着精美的花紋。\n");
                set("value", 10000);
                set("material", "copper");
        }
        setup();
}