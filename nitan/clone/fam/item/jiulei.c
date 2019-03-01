#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + HIM "九雷玄音紗" NOR, ({"xuanyin sha", "xuanyin", "sha"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "薄如蟬翼的紗綢，雖然輕若鴻毛，卻是堅韌似鐵。\n" NOR);
                set("unit", "張");
                set("value", 9000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + HIM "九雷玄音紗" NOR);
                set("can_make", ({ "護甲", "戰衣", "腰帶", "護腕", "靴子", "鞭" }));
                set("power_point", 60);
        }
}

int query_autoload()
{
        return 1;
}
