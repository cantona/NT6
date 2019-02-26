// 18niou.c

#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(YEL"十八泥偶"NOR, ({ "18 niou", "niou" }));
        set_weight(600);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "盒");
                set("long", 
"這是一個小木盒，盒中墊着棉花，並列着三排泥制玩偶，每排六
個，共是一十八個。玩偶製作精巧，每個都是裸體的男人，皮膚
上塗了白堊，畫滿了一條條紅線，更有無數黑點，都是脈絡和穴
道的方位。\n");
                set("value", 0);
                set("material", "mud");
        }
}
