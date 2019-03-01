inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "九天玲瓏珠" NOR, ({"linglong zhu", "linglong", "zhu"}));
        set_weight(2000);
        set("long", HIM "看似平凡的珠子，拇指般大小，但卻可以根據時辰的變化放射出不同的顏色，珍奇無比。\n" NOR);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "九天玲瓏珠");
                set("enchase/point", 1);
                set("enchase/type", "surcoat");
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

