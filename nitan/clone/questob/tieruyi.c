// tieruyi.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("鐵如意", ({ "tie ruyi", "ruyi" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", "這是一個鐵如意，黑不溜秋的，毫不起眼。\n");
                set("value", 1000);
                set("material", "iron");
        }
        setup();
}