#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIG "千蛇纏身圖" NOR, ({ "qianshe tu", "qianshe", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "無數只毒蛇纏繞的圖樣");
                set("can_tattoo", ({ "後背"}));
                set("tattoo_type", ({ "身法" }));
                set("tattoo_dex", 10);
                                set("tattoo_con", -6);
                                set("scborn", 1);
        }
}
