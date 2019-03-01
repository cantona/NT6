

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL + GRN "鬆葉" NOR, ({ "penglai songye" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "片");
                set("value", 1);
                set("long", YEL + GRN "這是一片從長鬆樹上落下的鬆葉。\n" NOR);
        }

        setup();
}

int query_autoload()
{
        return 1;
}