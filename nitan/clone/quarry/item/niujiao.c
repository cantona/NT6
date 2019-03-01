#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "犀牛角" NOR, ({ "xiniu jiao", "xiniu", "jiao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "罕見的成年犀牛角，極品兵器制作原料，非常珍貴。\n" NOR);
                set("base_unit", "根");
                set("unit", "根");
                set("base_value", 500000);
                set("base_weight", 1000);
        }
        setup();
}
int query_autoload()
{
        return 1;
}