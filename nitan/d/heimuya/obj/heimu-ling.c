// heimu-ling.c 黑木令

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(BLK"黑木令"NOR, ({"heimu ling", "heimu", "ling"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "面");
                set("long","這是一塊是塊枯焦的黑色木頭，長約半尺，上
面雕刻有花紋文字，看來十分詭異。\n");
//                set("no_drop", "這樣東西不能離開你。\n");
                set("material", "wood");
        }
}
