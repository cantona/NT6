#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "白虎皮" NOR, ({ "baihu pi", "pi"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一張從神獸白虎身上剝下的皮，雪白無暇，無比的堅韌。\n" NOR);
                set("unit", "張");
                set("value", 1000000);
              set("item_origin", 1);
              set("material_attrib", "silk");
              set("material_name", HIW "白虎毛皮" NOR);
              set("can_make", ({ "甲" }));
              set("power_point", 120);
        }
}
