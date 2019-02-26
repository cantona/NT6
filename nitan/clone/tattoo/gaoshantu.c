#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "高山流水圖" NOR, ({ "gaoshan tu", "gaoshan", "tu" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "高山流水的景象");
                set("can_tattoo", ({ "左臂"}));
                set("tattoo_type", ({ "精力上限" }));
                                set("tattoo_addneili", -3000);
                                set("tattoo_addjingli", 600);
                                set("scborn", 1);
        }
}
