inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "極北寒玉" NOR, ({"jibei hanyu", "jibei", "hanyu", "yu"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "極地萬年寒冰凝結而成，散發出雪一般的光澤。\n" NOR);
                set("unit", "塊");
                set("value", 15000);
        }
        
        setup();
        // move("/d/lingxiao/yudong");
}

int query_autoload()
{
        return 1;
}
