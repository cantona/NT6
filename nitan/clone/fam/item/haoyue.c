#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + HIY "皓月金砂" NOR, ({"haoyue jinsha", "haoyue", "jinsha", "sha"}));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "潮汐之季由海淵所採出的金砂，乃武林中人夢寐以求的寶物。\n" NOR);
                set("unit", "袋");
                set("value", 10000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + HIY "皓月金砂" NOR);
                set("can_make", ({ "護甲", "頭盔", "護腕" }));
                set("power_point", 70);
        }
}

int query_autoload()
{
        return 1;
}
