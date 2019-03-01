#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "錦繡山河圖" NOR, ({ "shanhe tu", "shanhe", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "萬裡江山，波瀾壯闊，氣勢恢弘磅礡之極");
                set("can_tattoo", ({ "胸口", "後背", }));
                set("tattoo_type", ({ "根骨" }));
                set("tattoo_con", 4);
                set("tattoo_special", "mystery");
                set("tattoo_spcname", "玄黃聚納");
        }
}