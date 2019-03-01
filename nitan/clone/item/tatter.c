#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(WHT "羊皮碎片" NOR, ({ "sheepskin tatter", "tatter" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", WHT "這是一塊非常古老的羊皮碎片，上面繪有殘缺不全的象形文字圖樣。\n" NOR);
                set("unit", "枚");
                set("value", 500000);
        }
        setup();
}
