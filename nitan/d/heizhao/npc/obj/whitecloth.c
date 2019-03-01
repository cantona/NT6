// item: whitecloth.c

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(HIW"白布"NOR, ({"bai bu", "bu"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", 
"這是一塊白布，上面繪著一張地圖，圖旁注著兩行字道：“依圖
中所示路徑而行，路盡處系一大瀑布，旁有茅舍。到達時拆紅色
布囊。”\n");
                set("unit", "塊");
                set("value", 1);
        }
}
