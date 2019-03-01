#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(NOR + CYN "鎮岳尚方" NOR, ({ "zhenyue shangfang", "zhenyue", 
                                              "shangfang", "sword" }));
        set_weight(8000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", NOR + CYN "
此劍乃周昭王瑕在位五十一年以二年歲次壬午，鑄五劍，各投
五岳，銘曰鎮岳尚方，古文篆書，劍長五尺通體流光。劍脊與
劍柄之上還鑄有無數密密麻麻的古篆，似乎與武學有關。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", CYN "$N" CYN "驀地縱聲長嘯，霎時寒"
                                 "芒一閃，一道青光破空劃過，落于$N"
                                 CYN "掌間。\n" NOR);
                set("unwield_msg", CYN "$N" CYN "一聲輕哼，將手中的"
                                   "鎮岳尚方寶劍插入劍鞘。\n" NOR);
                set("skill", ([
                        "name"         : "zhenyue-jue",
                        "exp_required" : 300000,
                        "jing_cost"    : 80,
                        "difficulty"   : 80,
                        "max_skill"    : 149,
                        "min_skill"    : 50
                ]));
                set("stable", 100);
        }
        init_sword(140);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n = me->query_skill("sword");

        if (me->query_skill("sword") < 150)
                return damage_bonus / 2;

        if (me->query_skill_mapped("sword") != "henshan-jian"
           && me->query_skill_mapped("sword") != "zigai-jian"
           && me->query_skill_mapped("sword") != "furong-jian"
           && me->query_skill_mapped("sword") != "shilin-jian"
           && me->query_skill_mapped("sword") != "zhurong-jian"
           && me->query_skill_mapped("sword") != "tianzhu-jian"
           && me->query_skill_mapped("sword") != "wushen-jian")
                return damage_bonus / 2;

        switch (random(14))
        {
        case 0:
                victim->receive_damage("jing", n / 2, me);
                victim->receive_wound("jing", n / 4, me);
                return HIW "$N" HIW "將真氣運于" NOR + CYN "鎮"
                       "岳尚方" HIW "劍身，霎時劍芒暴漲，逼得$n"
                       HIW "連連後退！\n" NOR;
        case 1:
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIR "$N" HIR "手中" NOR + CYN "鎮岳尚方"
                       HIR "青光盪漾，透出一道道寒冷的劍氣直向$n"
                       HIR "而去！\n" NOR;
        }
        return damage_bonus;
}