#include <weapon.h>
#include <music.h>
#include <ansi.h>

inherit SWORD;
inherit MI_QIN;

void create()
{
        set_name(WHT "鐵琴劍" NOR,({ "tieqin jian", "tieqin", "jian", "qin" }) );
        set_weight(12000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", WHT "一具雕有古樸花紋的鐵琴，鐵琴的一端露出一個劍柄。\n" NOR);
                set("unit", "具");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", WHT "$N" WHT "緩緩從懷中鐵琴的琴脊處抽出一柄厚脊"
                                 "薄刃的長劍握在手中。\n" NOR);
                set("unwield_msg", WHT "$N" WHT "微微一笑，將手中的鐵琴劍收回，插"
                                 "入鐵琴中去。\n" NOR);
                set("stable", 100);
        }
        init_sword(110);
        setup();
}

void init()
{
        add_action("play_qin", "play");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("sword") != "kunlun-jian" ||
            me->query_skill("kunlun-jian", 1) < 100)
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 12 + 2);
                return WHT "$N" WHT "一聲斷喝，單手猛然拂過手中鐵琴，鐵琴頓時發出一股尖銳的"
                       "琴音，$n" WHT "只覺頭暈目眩，幾欲昏厥！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return WHT "$N" WHT "一聲冷哼，手中鐵琴劍一振，霎時龍吟驟起，一道劍氣攜著尖"
                       "銳的琴音直射$n" WHT "而去！\n" NOR;
        }
        return damage_bonus;
}