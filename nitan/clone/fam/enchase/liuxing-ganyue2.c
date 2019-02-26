inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "流星趕月" NOR, ({"liuxing ganyue", "liuxing", "ganyue"}));
        set_weight(2000);
        set("long", HIY "人間罕有的寶石，據説乃天上流星墜落後形成。\n" NOR);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("enchase/name", "流星趕月");
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

