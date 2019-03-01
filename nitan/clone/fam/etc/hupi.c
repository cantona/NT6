#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "白虎皮" NOR, ({ "tiger skin", "skin" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一張白虎皮，乃制衣極品，世間罕有。\n" NOR);
                set("unit", "張");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
