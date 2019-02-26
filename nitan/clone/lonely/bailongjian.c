#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIW "白龍劍" NOR, ({ "bailong jian", "bailong", "jian" }) );
        set_weight(5500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "青鋒長約三尺，劍脊花紋古樸，鋒口隱隱發着銀澤。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "$N" HIW "從背後「唰」的抽出一柄利劍，"
                                 "劍刃在陽光下閃閃生輝。\n" NOR);
                set("unwield_msg", HIW "$N" HIW "將手中白龍劍空舞個劍花，插"
                                 "回劍鞘。\n" NOR);
                set("stable", 100);
        }
        init_sword(150);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("sword") != "rouyun-jian" ||
            me->query_skill("rouyun-jian", 1) < 100)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 10 + 2);
                return HIW "$N" HIW "將手中白龍劍斜斜削出，劍身陡然漾起一道"
                       "白光，將$n" HIW "逼得連連後退！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return HIW "$N" HIW "一聲清嘯，手中白龍劍連舞出七、八個劍花"
                       "，繽紛削向$n" HIW "周身各處！\n" NOR;
        }
        return damage_bonus;
}