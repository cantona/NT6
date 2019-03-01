inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + YEL "天師鬼符" NOR, ({"tianshi guifu", "tianshi", "guifu"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", NOR + YEL "這是一張道符，乃張天師為了降伏鬼怪而制。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
