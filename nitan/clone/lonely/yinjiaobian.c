#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(HIW "銀蛟鞭" NOR, ({ "yinjiao bian", "yinjiao", "bian", "whip" }) );
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "一根純銀所鑄的長鞭，鞭身生滿了倒刺，很是堅韌。\n" NOR);
                set("unit", "根");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "$N" HIW "從腰間取出一卷銀光閃閃的長鞭，凌空揮舞個圈子。\n" NOR);
                set("unwield_msg", HIW "$N" HIW "一聲輕哼，將手中銀蛟鞭盤好，放回腰間。\n" NOR);
                set("stable", 100);
        }
        init_whip(120);
        setup();
}