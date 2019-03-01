// hulu.c

inherit ITEM;
inherit F_LIQUID;
#include <ansi.h>;

void create()
{
        set_name(HIG"青葫蘆"NOR, ({ "qing hulu", "hulu" }) );
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一個碧綠色的葫蘆。\n"
);
                set("unit", "個");
                set("value", 80);
                set("max_liquid", 60);
        }

        // The liquid contained in the container is independent, we set a copy
        // in each cloned copy.
        set("liquid", ([
                "type": "water",
                "name": "甘泉水",
                "remaining": 60,
        ]) );
}