#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(YEL "鋸子" NOR, ({ "ju zi", "ju", "zi" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", YEL "這是一用來鋸木頭的鋸子，普通百姓的日常用品。\n" NOR);
                set("value", 30);
                set("material", "steel");
        	set("wield_msg", YEL "$N" YEL "拿出一把鋸子握在手中。\n" NOR);
                set("unwield_msg", YEL "$N" YEL "將手中的鋸子抗在肩上。\n" NOR);
        }
        init_blade(4);
        setup();
}