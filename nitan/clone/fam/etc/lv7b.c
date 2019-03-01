inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(YEL "息壤" NOR, ({"xi rang", "xi", "rang"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "傳說上古時期大禹治水曾使用的奇異土壤。\n" NOR);
                set("unit", "盤");
                set("value", 50000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
