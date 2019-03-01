inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "邪帝舍利" NOR, ({"xiedi sheli", "xiedi", "sheli" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "傳說乃邪帝蚩尤所化，散放著五彩光芒。\n" NOR);
                set("unit", "顆");
                set("value", 5000);
                set("enchase/name", "邪帝舍利");
                set("enchase/point", 1);
                  set("enchase/type", "def");
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

