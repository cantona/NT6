inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "龍凰紫珠" NOR, ({"longhuang zizhu", "longhuang", "zizhu"}));
        set_weight(2000);
        set("long", HIM "這一顆紫色的珠子，晶瑩剔透，珠子中央刻繪着龍鳳呈祥的圖案。\n" NOR);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "龍凰紫珠");
                set("enchase/point", 7);
                set("enchase/type", "medal2");
                set("enchase/cur_firm", 100);
                set("nine_object", 1); // 九孔鑲嵌物品標記
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

