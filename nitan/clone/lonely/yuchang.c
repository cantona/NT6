#include <ansi.h>
#include <weapon.h>

inherit DAGGER;

void create()
{
        set_name(NOR + WHT "魚腸劍" NOR, ({"yuchang jian", "yuchang", "jian", "dagger"}));
        set_weight(2500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "柄");
                set("long", WHT "一柄古樸沉重的短匕首，匕脊上刻有「" HIY "魚腸"
                            NOR + WHT "」二字。\n" NOR);
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", WHT "$N" WHT "從兜裏掏出一柄匕首，空氣中頓時沁"
                                 "出一絲寒氣。\n" NOR);
                set("unwield_msg", WHT "$N" WHT "手中的魚腸劍一轉，眨眼間已然不"
                                 "見影蹤。\n" NOR);
                set("stable", 100);
        }
        init_dagger(140);
        setup();
}