// fan.c
#include <ansi.h>
inherit ITEM;

void setup()
{}

void create()
{
        set_name("帆布", ({"fan bu", "fan" }));
        set("unit", "塊");
        set("long", "這是一塊黑黝黝的帆布，看不出有什麼用。\n");
        set("value", 0);
        //set("no_drop", "這樣東西不能離開你。\n");
        set_weight(500);

        setup();
}

