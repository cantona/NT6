// qizi.c

#include <weapon.h>

inherit COMBINED_ITEM;



void create()
{
	set_name("棋子", ({ "qi zi", "zi" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",	"一把做工精細的雲子。\n");
		set("unit", "把");
	}
	set_amount(100);
	setup();
}
