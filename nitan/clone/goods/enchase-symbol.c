#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "鑲嵌符" NOR, ({ "enchase symbol", "symbol" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "此符文具有使鑲嵌寶物時候擁有100%成功率。\n" NOR);
                set("unit", "張");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

