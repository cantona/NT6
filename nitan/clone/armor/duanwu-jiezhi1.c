
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIC "十周年﹒端午﹒龍戒" NOR, ({ "duanwu longjie", "longjie" }));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", HIC "這是由炎黃十周年暨端午節發放的戒指，其散發著迷人的綠光，折射出一條青龍之像。\n" NOR);
                set("value", 100);
                set("material", "gold");
                set("armor_prop/dex", 10);
                set("armor_prop/str", 10);
                set("armor_prop/int", 10);
                set("armor_prop/con", 10);
                set("armor_prop/damage", 500);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
