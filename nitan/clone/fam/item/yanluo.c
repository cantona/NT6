#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + HIR "閻羅綢" NOR, ({ "yanluo chou", "yanluo", "chou" }));
        set_weight(1200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "閃爍着陣陣紫光的綢緞，不知由何物所織，堅韌有如玄鐵。\n" NOR);
                set("unit", "張");
                set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + HIR "閻羅綢" NOR);
                set("can_make", ({ "護甲", "戰衣", "腰帶", "護腕", "靴子", "鞭" }));
                set("power_point", 90);
        }
}

int query_autoload()
{
        return 1;
}
