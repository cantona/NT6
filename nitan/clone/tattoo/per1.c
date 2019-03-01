#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "燕尾蝶圖騰" NOR, ({ "yanweidie tu", "yanweidie", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 1500);
                set("material", "paper");
                set("tattoo_long", "一只燕尾蝶");
                set("can_tattoo", ({ "臉部" }));
                set("tattoo_type", ({ "容貌" }));
                set("tattoo_per", 3);
        }
}