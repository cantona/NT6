// dragonblade.c 屠龍刀
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit BLADE;
inherit F_UNIQUE;

void create()
{
        set_name(BLU"屠龍刀"NOR, ({ "dragon blade", "blade", "dao" }));
        set_weight(30000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "此刀由郭靖黃蓉夫婦打造，是天下神兵。\n");
                set("material", "steel");
                set("no_drop", "如此寶貴的武器再世難求啊。\n");
                set("no_get", "送人？虧你想的出來！\n");
                set("no_put", "珍惜它吧。\n");
                set("value",100);
                set("wield_msg", HIB "猛見黑光一閃，屠龍刀躍入$N掌中。瞬時天地間彌漫著\n一片黑暗的殺意中。\n" NOR);
                set("unwield_msg", HIB "$N掌中刀氣漸斂，天地間的肅殺之氣慢慢散去。\n" NOR);
        }
        init_blade(300);
        setup();
}
