// fumo-zhang.c 伏魔杖

#include <weapon.h>
#include <ansi.h>

inherit STAFF;
inherit F_NOCLONE;

void create()
{
        set_name("伏魔杖", ({ "fumo zhang", "zhang" }));
        set_weight(10000);
        set("unit", "把");
        set("long", @LONG
這是一把銀光雪亮的伏魔杖，流蘇閃動，耀人耳目。此乃數百年前由
達摩老祖攜入中原，一路用之除妖滅魔，乃是佛家無上降魔法寶。
LONG );
        set("value", 1000000);
        set("no_sell", 1);
        set("material", "steel");
        set("wield_msg", HIY "只聽「錚」的一聲，伏魔杖騰空而出，自行躍入$N掌中。
瞬時天際間風雲變色，電閃雷鳴，瀰漫着一片無邊殺意。\n" NOR);
        set("unwield_msg", HIY "伏魔杖自$N掌中飛起，在半空中一轉，「唰」地靠在$N身後。\n" NOR);
        init_staff(200);
        set("stable", 100);
        setup();
        check_clone();
}