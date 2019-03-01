// lengyue.c 冷月寶刀
#include <weapon.h>

inherit BLADE;

#include <ansi.h>

void create()
{
        set_name(HIG "冷月寶刀" NOR, ({ "moon blade", "blade" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 1000000);
                set("no_sell", "這...這玩藝怪嚇人的...\n");
                set("material", "steel");
                set("long", "這是胡家祖傳的寶刀，冷氣森森，銳利無比。\n" );
                set("wield_msg", HIG "$N" HIG "抓起刀柄，眾人只覺眼前青光一"
                                 "閃，寒氣逼人，$N" HIG "手中已經多了一柄$n"
                                 HIG "，刀光如水，流轉不定。\n" NOR);
                set("unwield_msg", HIW "$N" HIW "彈刀清嘯，心中感慨，將$n"
                                   HIW "插回刀鞘。\n");
        }
        init_blade(180);
        setup();
}
