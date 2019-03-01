 //yitian.c
 //倚天劍
 //PLZW 2003-12-22
 
#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(NOR + WHT "倚天劍" NOR, ({ "yitian jian", "yitian", "jian", "sword" }) );
        set_weight(10000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", NOR + WHT "這便與天下至尊的屠龍寶刀並稱的倚天劍。\n"
                            "相傳其中藏有曠世的大秘密。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？");
                set("material", "steel");
                set("wield_msg", HIW "只聽「嗖」的一聲破空聲響，號稱天下第一"
                             "神兵的倚天劍已被$N" HIW "握于手中。\n" NOR);
                set("unwield_msg", HIW "$N" HIW "將倚天劍插回腰間，天地又漸漸"
                             "放出光芒。\n"NOR);
                set("stable", 100);
        }
        init_sword(250);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("qi",query("str", me)*4,me);
        victim->receive_wound("qi",query("str", me)*4,me);
        return WHT "倚天劍攜著刺骨風聲劃破天際，$n"
               WHT "只覺全身力氣竟一絲絲隨著劍鋒湧出。\n" NOR;
}

