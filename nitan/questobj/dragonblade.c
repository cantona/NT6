// dragonblade.c 屠龍刀

#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(BLU"屠龍刀"NOR, ({ "dragon_blade", "blade", "dao" }));
        set_weight(10000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "此刀由郭靖黃蓉夫婦打造，是天下神兵。\n");
                set("material", "steel");
                set("value",0);
                set("wield_msg", HIB "猛見黑光一閃，屠龍刀躍入$N掌中。瞬時天地間彌漫著\n一片黑暗的殺意中。\n" NOR);
                set("unwield_msg", HIB "$N掌中刀氣漸斂，天地間的肅殺之氣慢慢散去。\n" NOR);
        }
        setup();
}
