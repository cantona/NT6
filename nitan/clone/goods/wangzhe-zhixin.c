#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "王者之心" NOR, ({ "wangzhe zhixin", "wangzhe", "stone" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這是一顆晶瑩無瑕的寶石，據説擁有着奇幻的力量，是用來綠化套裝的必備材料。\n" NOR); 
                set("unit", "塊");
                set("value", 500000);
                set("no_sell", 1);
                set("auto_load", 1);
        }
        setup();
}
