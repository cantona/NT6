#include <ansi.h>

inherit ITEM;

void setup()
{}

void create()
{
               set_name("鐵哨", ({"tie shao","shao" }));
        
                set("unit", "個");
                set("long", "這是一個黑黝黝的鐵哨子，看不出有什麼不同。\n");
                set("value", 0);
              set("no_drop", "這樣東西不能離開你。\n");
              set_weight(500);

        
        setup();
}
