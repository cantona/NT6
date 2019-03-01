#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name(HIY "掃帚" NOR, ({ "sao zhou", "sao", "zhou" }));
        set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "把");
                set("long", HIY "這是一把掃帚，普通百姓的日常用品。\n" NOR);
                set("value", 10);
		set("material", "steel");
		set("wield_msg", HIY "$N" HIY "拿出一把掃帚握在手中。\n" NOR);
                set("unwield_msg", HIY "$N" HIY "將手中的掃帚抗在肩上。\n" NOR);
	}
        init_hammer(4);
	setup();
}