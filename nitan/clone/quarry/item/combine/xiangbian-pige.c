#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "鑲邊皮革" NOR, ({ "xiangbian pige", "xiangbian", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM  "這是一張薄而通透的皮革，做甲衣時，是用來鑲邊的絕佳材料。\n" NOR);
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