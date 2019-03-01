// item: redcloth.c

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(HIR"紅布"NOR, ({"hong bu", "bu"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", 
"這是一塊紅布，上面寫著一行字道：“把此布交給漁翁。
上山之後將黃色布囊交給小沙彌。”\n");
                set("unit", "塊");
                set("value", 1);
        }
}
