// Code of JHSH
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"精鐵"NOR, ({ "jing tie", "tie" }) );
        set_weight(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一塊用烏金礦石打煉出來的精鐵，是製造兵器的好材料。\n");
                set("unit", "塊");
//                set("no_drop",1);

        }

}