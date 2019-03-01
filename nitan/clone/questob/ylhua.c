// ylhua.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("銀鏤花", ({ "yinlou hua", "hua" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", "這是一張用銀箔雕刻的花，栩栩如生。\n");
                set("value", 4000);
                set("material", "silver");
        }
        setup();
}