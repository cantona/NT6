// fumo-dao.c 伏魔刀

#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name("伏魔刀", ({ "fumo dao", "dao" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把銀光雪亮的伏魔刀，刀刃間隱隱有血光流動，鋒利無匹，
映面生寒。此刀數百年前由達摩老祖攜入中原，一路用之除妖滅魔，
乃是佛家無上降魔法寶。\n");
                set("value", 100000);
                set("unique", 1);
                set("material", "steel");
                set("wield_msg", HIY "只聽「錚」的一聲，伏魔刀脱鞘飛出，自行躍入$N掌中。
瞬時天際間風雲變色，電閃雷鳴，瀰漫着一片無邊殺意。\n" NOR);
                set("unwield_msg", HIY "伏魔刀自$N掌中飛起，在半空中一轉，「唰」地躍入刀鞘。\n" NOR);
        }
        init_blade(500);
        setup();
}