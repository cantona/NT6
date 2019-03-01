#include <weapon.h>
#include <ansi.h>

inherit STAFF;

void create()
{
        set_name(NOR + WHT "九環錫杖" NOR, ({ "jiuhuan xizhang", "jiuhuan",
                                              "xizhang", "zhang" }) );
        set_weight(8000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", NOR + WHT "這是一根通體漆黑的錫杖，入手極為沉"
                            "重，非常堅韌，乃少林\n寺歷代相傳的聖物。有雲"
                            "：銅鑲鐵造九連環，九節仙籐永駐顏。\n" NOR);
                set("unit", "根");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "$N" HIW "取出九環錫杖握于手中，霎時"
                                 "金波盪漾，有若七佛隨身。\n" NOR);
                set("unwield_msg", HIW "$N" WHT "微微一笑，將手中的九環錫"
                                 "杖放回包囊。\n" NOR);
                set("stable", 100);
        }
        init_staff(180);
        setup();
}