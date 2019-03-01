#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "紅質皮革" NOR, ({ "hongzhi pige", "hongzhi", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG  "這是一張紅色的皮革，是制作甲衣的上好材料。\n" NOR);
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