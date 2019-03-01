inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIR "麒麟鑰匙" NOR, ({"qilin key", "key", "qilin"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
        	set("unit", "把");
		set("long", HIR "這是一把通體火紅的鑰匙，測試期間可代替斬妖勛章來打開火麒麟洞的封印。\n");
		set("value", 1);
	}
        setup();
}