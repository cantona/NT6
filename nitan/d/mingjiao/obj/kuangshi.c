// Code of ShenZhou
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIB"烏金礦石"NOR, ({ "wujin kuangshi", "kuangshi" }) );
        set_weight(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一塊黑黝黝的烏金礦石，是煉制兵器的好材料。\n");
                set("unit", "塊");
//                                set("no_drop",1);

        }

}