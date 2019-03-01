#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(NOR + WHT "黑龍鞭" NOR, ({ "heilong bian", "heilong", "bian", "whip" }) );
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", WHT "一支通體漆黑的長鞭，看上去倒是很堅韌。\n" NOR);
                set("unit", "根");
                set("value", 800000);
                set("no_sell", "這鞭…這不是史…大爺的東西嗎？你…把他怎麼了？");
                set("material", "steel");
                set("wield_msg", WHT "$N" WHT "從腰間取出一卷漆黑的長鞭，凌空揮舞個圈子。\n" NOR);
                set("unwield_msg", WHT "$N" WHT "一聲輕哼，將手中黑龍鞭盤好，放回腰間。\n" NOR);
                set("stable", 100);
        }
        init_whip(80);
        setup();
}