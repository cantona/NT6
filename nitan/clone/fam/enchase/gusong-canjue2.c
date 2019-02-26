inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + YEL "古鬆殘钁" NOR, ({"gusong canjue", "gusong", "canjue"}));
        set_weight(2000);
        set("long", NOR + YEL "看似普通的玉石，卻藴藏着奇異的能量。\n" NOR);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "古鬆殘钁");
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

