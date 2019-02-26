// chuan.c 橄欖核船

#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIC "橄欖核船" NOR, ({"ganlanhe chuan", "chuan"}) );
        set_weight(100);
        set("taskobj", 1);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", @LONG
橄欖核船雕刻精緻，中艙客四人，二人在後，一搖擼，一鈕濱，窗櫺皆可開
闔，眉目如畫，外用退光漆盒，如藥制橄欖形，紅絲結絡，可以佩身。
LONG
                );
                set("unit", "個");
                set("value", 0);
                set("armor_prop/armor",1);
                set("wear_msg", "$N把一個$n系在腰間。\n");
                set("unequip_msg","$N從腰間解下一個$n，拿在手裏把玩。\n");
        }
        setup();
}
