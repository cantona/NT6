// l襄陽保衛戰，哲別專用弓

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIW "大漠之鷹" NOR, ({ "damo bow", "bow", "damo", "gong" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "張");
                set("long", HIW "一張用黃金打造的長弓，上面雕刻著一只飛翔的鷹，此弓產自大漠，乃神弓。\n");
                set("value", 80000);
                set("accuracy", 100000);   // 準確度，幾乎100%命中
        }
        setup();
}

