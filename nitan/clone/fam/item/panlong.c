#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + HIW "盤龍銀絞絲" NOR, ({"yinjiao si", "yinjiao", "si"}));
        set_weight(3800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "由穹外隕星中提煉出的神秘金屬煉制而成，世所罕見。\n" NOR);
                set("unit", "束");
                set("value", 9000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + HIW "盤龍銀絞絲" NOR);
                set("can_make", ({ "護甲", "頭盔", "護腕" }));
                set("power_point", 60);
        }
}

int query_autoload()
{
        return 1;
}
