inherit ITEM;
inherit F_LIQUID;
#include <ansi.h> 
void create()
{
        set_name(HIG"酒壇"NOR, ({"jiutan"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個青瓷酒攤，花紋精細，裡面想來裝的也是美酒。\n");
                set("unit", "個");
                set("value", 100);
                set("max_liquid", 10);
        } 
        set("liquid", ([
                "type": "alcohol",
                "name": "竹葉青",
                "remaining": 1500,
                "drunk_apply": 6,
        ]) );
        setup();
}     
