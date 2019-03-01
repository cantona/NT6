inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "《安守閣地圖》" NOR, ({"anshouge tu", "anshouge", "tu"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", HIW "這是一張繪有扶桑安守閣地形的圖紙。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
