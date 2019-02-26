#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(HIW "銀索" NOR + HIY "金鈴" NOR,({ "yinsuo jinling", "suo", "ling",
                                                    "yinsuo", "jinling" }) );
        set_weight(1300);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "一根銀色的長索，隱隱流動着金屬的光"
                            "澤，看上去很是堅韌。長索的一端繫着兩個"
                            "金鈴。\n" NOR);
                set("unit", "把");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "$N" HIW "輕輕的從懷裏取出一根"
                                 "銀色的長索握在手中。\n" NOR); 
                set("unwield_msg", HIW "$N將手中銀索" NOR + HIY "金"
                                 "鈴" NOR + HIW "回腰間，天地又漸漸"
                                 "放出光芒。\n" NOR);
                set("stable", 50);
        }
        init_whip(150);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("whip") != "yinsuo-jinling" ||
            me->query_skill("yinsuo-jinling", 1) < 100)
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("whip") / 10 + 2);
                return HIY "$N" HIY "一聲嬌喝，手中的" NOR + HIW "銀索"
                       NOR + HIY "金鈴幻出漫天鞭影，直點$n" HIY "而去！"
                       HIR "\n$n" HIR "稍一遲疑，只覺全身一麻，已被$N"
                       HIR "這招點中要穴。\n" NOR;

        case 1:
                n = me->query_skill("whip");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return  HIY "$N" HIY "一聲清嘯，手中" NOR + HIW "銀索"
                        NOR + HIY "金鈴宛如蛟龍通天，鋪天蓋地襲向$n"
                        HIY "！\n" NOR;
        }
        return damage_bonus;
}
