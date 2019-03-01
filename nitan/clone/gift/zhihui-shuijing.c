// 智慧水晶 與同伴系統關聯 參考文件 help mater

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "智慧水晶" NOR, ({ "zhihui shuijing" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "一塊粉色的水晶碎片，你的同伴最喜歡。\n" NOR);
                set("value", 1);
                set("unit", "塊");
        }
        setup();
}

int query_autoload() { return 1; }
