// saw.c

#include <ansi.h>

inherit ITEM;

int is_saw() { return 1; }

void create()
{
        set_name("鋼鋸", ({ "gang ju", "ju", "saw" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("value", 800);
                set("unit", "條");
                set("material", "steel");
                set("long", "這是一條黑黝黝的鋼鋸，一般用來伐木。\n");
        }
        setup();
}