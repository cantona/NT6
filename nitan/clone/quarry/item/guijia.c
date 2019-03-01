#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + YEL "龜甲" NOR, ({ "gui jia", "gui", "jia" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "烏龜的甲殼，不錯的鑄造材料。\n" NOR);
                set("base_unit", "塊");
                set("unit", "塊");
                set("base_value", 10000);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}