// zhenwu-jian.c 真武劍
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>;
#include <weapon.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIC"真武劍"NOR, ({ "zhenwu jian", "sword", "jian" }));
        set_weight(50000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long","此劍劍鞘銅綠斑斕，以銅絲嵌著兩個篆文：“真武”。\n乃是創派之祖張三豐所用佩劍，向來是武當派鎮山之寶。\n");
                set("value", 10000);
                set("material", "steel");
                set("weapon_prop/per", 8);
                set("wield_msg", "$N「唰」的一聲抽出$n。劍面流紋如水，澹然如鏡。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(180);
        setup();
}
mixed weapon_hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if( query("shen", me)<0 || query("shen", victim)>0 )
                return - damage_bonus / 2;

        if( query("shen", me) == 0 || query("shen", victim) == 0 )
                return 0;
        if (me->query_skill_mapped("force") != "taiji-shengong")
                return 0;

        if (me->query_skill_mapped("sword") != "taiji-jian" ||
            me->query_skill("taiji-jian", 1) < 100)
                // only increase damage
                return damage_bonus / 3;

        switch (random(4))
        {
        case 0:
                if (!victim->is_busy())
                {
                victim->start_busy(me->query_skill("sword") / 100 + 1);
                return HIC "$N" HIC "跨前一步，手中的" NOR + HIY "真武劍" NOR
                       + HIC "幻化成無數圓圈，向$n" HIC "逼去，劍法細密之極。\n"
                       "$n" HIC "大吃一驚，不知如何抵擋，只有連連後退！\n" NOR;
                }
        case 1:
                n = me->query_skill("sowrd");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                n=query("eff_jing", victim);
                n /= 2;
                victim->receive_damage("jing", n, me);
                victim->receive_wound("jing", n / 2, me);
                return random(2) ? HIY "$N" HIY "一聲長吟，手中的真武劍化作一"
                                   "道長虹，“唰”的掃過$n" HIY "而去！\n" NOR:
                                   HIY "$N" HIY "突然大聲喝道：“邪魔外道，還"
                                   "不受死？”手中真武劍" HIY "忽的一抖，$n"
                                   HIY "登時覺得眼花繚亂！\n" NOR;
        }

        // double effect
        return damage_bonus;
}