#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(YEL "金蛇劍" NOR, ({ "jinshe jian", "jinshe", "jian" }) );
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "只見那劍形狀甚是奇特，整柄劍就如是一條蛇盤\n"
                                "曲而成，蛇尾勾成劍柄，蛇頭則是劍尖，蛇舌伸\n"
                                "出分叉，是以劍尖竟有兩叉。那劍金光燦爛，握\n"
                                "在手中甚是沉重，看來竟是黃金混和了其他五金\n"
                                "所鑄，劍身上一道血痕，發出碧油油的暗光，極\n"
                                "是詭異。。\n" NOR);

                set("unit", "柄");
                set("value", 800);
                // set("no_sell", 1);
                // set("unique", 1);
                set("material", "steel");
                set("wield_msg", HIY "破空而響，金蛇劍已出鞘，$N" HIY "全身涼颼颼地只感寒氣逼人。\n" NOR); 
                set("unwield_msg", HIY "$N" HIY "手一揚，金蛇劍回鞘，四周寒氣頓消。\n" NOR);
                set("stable", 100);
        }
        init_sword(100);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int ap, dp;
        int n;

        ap = me->query_skill("sword");
        dp = victim->query_skill("dodge");

        if (me->query_skill_mapped("sword") != "jinshe-jian" ||
            me->query_skill("jinshe-jian", 1) < 100 ||
            ap / 2 + random(ap) < dp)
                return damage_bonus / 2;

        switch (random(3))
        {
        case 0:
                if (! victim->is_busy())
                      victim->start_busy(me->query_skill("sword") / 10 + 4);
                return HIY "$N" HIY "怒喝一聲，金蛇劍猶如靈蛇一般，蜿蜒遊動，泛起\n淡淡碧綠之光，竟"
                       "將$n" HIY "籠罩在銀光幻影之下。\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return  HIY "$N" HIY "飛身而起，金蛇劍自天而下，猶如靈蛇般地舞動着卷向$n" HIY
                        "周身各處大穴！\n" NOR;

        }
        return damage_bonus;
}