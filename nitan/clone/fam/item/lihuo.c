#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "離" HIR "火" HIC "玄" HIW "冰" HIC "玉" NOR,
                ({"lihuo yu", "lihuo", "yu"}));
        set_weight(3400);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "此乃不世寶玉，玉身一半奇熱，另一半卻奇寒，且能自動分水離火。\n" NOR);
                set("unit", "塊");
                set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", HIC "離" HIR "火" HIC "玄" HIW "冰" HIC "玉" NOR);
                set("can_make", "all");
                set("not_make", ({ "護甲", "戰衣", "腰帶", "護腕", "靴子", "鞭" }));
                set("power_point", 90);
        }
}

int query_autoload()
{
        return 1;
}
