#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "天蠶絲" NOR, ({ "tiancan si", "tiancan", "si" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一根天蠶絲，晶瑩剔透、珍貴非常。\n" NOR);
                set("base_unit", "根");
                set("unit", "根");
                set("base_value", 100000);
                set("base_weight", 1);
        }
        setup();
}
int query_autoload()
{        
        return 1;
}