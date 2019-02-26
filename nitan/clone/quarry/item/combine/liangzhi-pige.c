#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "亮質皮革" NOR, ({ "liangzhi pige", "liangzhi", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG  "這是一張通體透亮的皮革，是製作甲衣的上好材料。\n" NOR);
                set("base_unit", "張");
                set("unit", "張");
                set("base_value", 100);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}