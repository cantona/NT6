#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "九儀天尊圖" NOR, ({ "tianzun tu", "tianzun", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪着些紋樣。");
                set("unit", "張");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "九儀天尊座於八寶蓮花上，周身仙霞繚繞，似幻似真");
                set("can_tattoo", ({ "胸口", "後背", }));
                set("tattoo_type", ({ "悟性", "根骨" }));
                set("tattoo_int", 2);
                set("tattoo_con", 2);
                set("tattoo_special", "divine");
                set("tattoo_spcname", "移經易脈");
        }
}