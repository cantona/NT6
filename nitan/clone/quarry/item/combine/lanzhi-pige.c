#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "藍質皮革" NOR, ({ "lanzhi pige", "lanzhi", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC  "這是一張藍色的皮革，是制作甲衣的上好材料。\n" NOR);
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