#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIC "藍蝶寶劍" NOR, ({ "landie jian", "landie", "jian" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIC "這是一柄充滿傳説的寶劍，乃由崆峒仙境的藍蝶仙子的眼淚所化，由愛生悲，藍蝶寶劍藴藏着巨大的威力。\n" NOR);
                set("value", 2000);
                set("limit", ([
                         "exp" : 2088888888,
                         //"thborn" : 1,
                         "str" : 700,
                         "dex" : 700,
                         "int" : 700,
                         "con" : 700,
                ]));
                set("material", "steel");
                set("wield_msg", "一道藍色的劍芒閃過，只見劍芒化作一直藍色的蝴蝶，光芒退去$N" HIC "手中卻多了一把寶劍。\n");
                set("unwield_msg", HIC "$N" HIC "一聲長歎，$n化作一縷藍色青煙消失了。\n" NOR);
        }
        init_sword(5000);
        setup();
}
