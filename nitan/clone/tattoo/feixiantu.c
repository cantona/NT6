#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIY "天外飛仙圖" NOR, ({ "feixian tu", "feixian", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "羣仙飛舞的情景");
                set("can_tattoo", ({ "臀部"}));
                set("tattoo_type", ({ "根骨", "悟性", "臂力", "身法" }));
                                set("tattoo_con", 2);
                                set("tattoo_dex", 2);
                                set("tattoo_str", 2);
                                set("tattoo_int", 2);
                                set("scborn", 1);
        }
}
