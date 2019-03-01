#include <weapon.h>
#include <ansi.h>
inherit BLADE;


void create()
{
	set_name(GRN"碧刀"NOR, ({"bi dao","blade"}) );
	set_weight(2000);
        set("long","一把形狀奇特的短刀，血槽極粗，隱隱有一股綠光透出。\n" NOR);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value",15000);
                set("cant_sell","你這把刀是誰給的？！小店可不敢收哇！\n");
		set("material", "steel");
	}
	init_blade(35);
	set("wield_msg", "$N「唰」的一聲抽出一把明晃晃的$n握在手中。\n");
	set("unwield_msg", "$N將手中的$n插入腰間。\n");
	setup();
}
