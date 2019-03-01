#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIR "武聖奔雷圖" NOR, ({ "wusheng tu", "wusheng", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "武聖練功的圖樣");
                set("can_tattoo", ({ "胸口"}));
                set("tattoo_type", ({ "臂力" }));
                set("tattoo_str", 6);
                                set("addfuzhong", 100000);
                                set("scborn", 1);
        }
}
