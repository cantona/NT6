#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(NOR + YEL "紫金八卦刀" NOR,({ "bagua dao", "bagua", "dao", "blade" }) );
        set_weight(4600);
        if (clonep())
                destruct(this_object());
        else {
                set("long", YEL "這是一柄厚背薄刃，紫金所鑄的八卦刀，刀柄上"
                            "刻著一個“商”字。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", "這不是商劍…商爺的東西嗎？小的還想多活幾年"
                               "，你還是換個地方典當吧。\n");
                set("material", "steel");
                set("wield_msg", YEL "$N" YEL "一聲清嘯，「唰」地一聲抽出紫"
                                 "金八卦刀，刀身光澤流動，煞為稱奇。\n" NOR);
                set("unwield_msg", YEL "$N" YEL "輕哼一聲，將手中紫金八卦刀"
                                   "插回背後。\n" NOR);
                set("stable", 100);
        }
        init_blade(120);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("blade") != "bagua-dao" ||
            me->query_skill("bagua-dao", 1) < 100)
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 10 + 2);
                return YEL "$N" YEL "一聲大喝，手中紫金八卦刀按照八卦方位連"
                       "連斬出，劃出一道道金芒，逼得$n" YEL "連連後退！\n"
                       NOR;

        case 1:
                n = me->query_skill("blade");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return YEL "$N" YEL "手中紫金八卦刀按照八卦方位連連斬出。$n"
                       YEL "頓見周圍刀影重重向自己聚攏，甚難抵擋！\n" NOR;
        }
        return damage_bonus;
}