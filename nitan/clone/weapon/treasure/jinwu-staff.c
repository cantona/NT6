// jinwu-staff.c 金烏杖
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>;
#include <weapon.h>;
inherit STAFF;
inherit F_UNIQUE;

void create()
{
        set_name(YEL"金烏杖"NOR, ({ "jinwu zhang", "staff" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根以雪山金烏精英所鑄的長杖。\n");
                set("value", 5500);
                set("material", "steel");
                set("wield_msg", "$N拿起金烏杖，舞了一圈，只見漫天金光閃耀，絢人眼目。\n");
                set("unwield_msg", "$N轟地一聲將金烏杖插在地上，地動山搖，威勢驚人。。\n");
        }
        init_staff(100);
        setup();
}
