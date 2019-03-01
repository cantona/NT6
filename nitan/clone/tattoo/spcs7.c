#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + WHT "羊皮碎片" NOR, ({ "sui pian7", "suipian7", "pian7" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一塊羊皮碎片，上面繪有殘缺不全"
                            "的錦繡山河紋樣。\n" NOR);
                set("unit", "塊");
                set("value", 10);
                set("material", "paper");
        }
}

int query_autoload()
{
        return 1;
}
