#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + CYN "鎮龍石" NOR, ({"zhenlong shi", "zhenlong", "shi"}));
        set_weight(8000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN "傳說此石乃是歷代皇朝用于鎮住龍脈所用，大非尋常。\n" NOR);
                set("unit", "塊");
                set("value", 9000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + CYN "鎮龍石" NOR);
                set("can_make", ({ "劍", "刀", "錘", "短兵", "簫", "棍", "杖" }));
                set("power_point", 60);
        }
}

int query_autoload()
{
        return 1;
}
