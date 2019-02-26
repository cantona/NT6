#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIR "瑩血蛛絲圖" NOR, ({ "zhusi tu", "zhusi", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "外形奇特蜘蛛吐着血紅色的絲");
                set("can_tattoo", ({ "後背"}));
                set("tattoo_type", ({ "悟性" }));
                set("tattoo_int", 10);
                                set("tattoo_str", -8);
                                set("tattoo_per", -4);
                                set("scborn", 1);
        }
}
