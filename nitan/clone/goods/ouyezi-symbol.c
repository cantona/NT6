#include <ansi.h>
inherit ITEM;

int query_autoload() { return 1; }
void create()
{
        set_name(HIM "歐冶子聖符" NOR, ({ "ouyezi symbol", "symbol" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "歐冶子聖符可以將改造裝備的成功率提升到90%。\n" NOR);
                set("unit", "張");
                set("value", 500000);
        }
        setup();
}

