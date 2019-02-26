#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIY "騰龍劍" NOR, ({ "tenglong jian", "tenglong", "jian", "sword" }) );
        set_weight(5800);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIY "一柄鋒利的長劍，劍身宛如流水，隱隱漾着青光。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", "…嗯…這劍倒是口好劍，不過這價錢不好開，我看"
                                 "還是算了吧。");
                set("material", "steel");
                set("wield_msg", HIY "$N" HIY "唰的抽出一柄利劍握在手中，劍"
                                 "身青光盪漾，寒氣逼人。\n" NOR);
                set("unwield_msg", HIY "$N" HIY "空舞了數個劍花，將騰龍寶劍"
                                 "插回腰間。\n" NOR);
                set("stable", 100);
        }
        init_sword(120);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill("sword") < 160)
                return damage_bonus / 2;

        if (me->query_skill_mapped("sword") != "miaojia-jian" &&
            me->query_skill_mapped("sword") != "tianlong-jian")
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 16 + 2);
                return HIY "$N" HIY "手中騰龍劍一顫，漾起層層劍光，頓時將$n"
                       HIY "逼退數步！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return HIY "只聽得破空聲驟響，$N" HIY "手中騰龍劍嵐轉不定，向"
                       "$n" HIY "連刺數劍！\n" NOR;
        }
        return damage_bonus;
}