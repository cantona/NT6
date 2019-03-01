#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"乾坤一氣袋"NOR, ({"yiqi dai", "dai" }) );
        set_weight(1000);
        set_max_encumbrance(5000);
        
        if( clonep() )
                set_default_object(__FILE__);
        else{
                set("unit", "個");
                set("long", "這是一個布袋樣的袋子。非綢非革，堅韌異常，摸上去\n"
                        "布紋宛然，顯是粗布所制，但撕上去卻堅韌無比。\n");
                set("value", 10000);
                set("material","silk");
                set("treasure",1);
        }        
        setup();
}
