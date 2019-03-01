// huagu-mianzhang 化骨綿掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N身形微晃，一招"HIB"「長恨深入骨」"NOR"，十指如戟，插向$n的雙肩鎖骨",
        "lvl"   : 0,
        "skill_name" : "長恨深入骨"
]),
([        "action" : "$N出手如風，十指微微抖動，一招"HIB"「素手裂紅裳」"NOR"抓向$n的前胸",
        "lvl"   : 20,
        "skill_name" : "素手裂紅裳"
]),
([        "action" : "$N雙手忽隱忽現，一招"HIB"「長風吹落塵」"NOR"，鬼魅般地抓向$n的肩頭",
        "lvl"   : 40,
        "skill_name" : "長風吹落塵"
]),
([        "action" : "$N左手當胸畫弧，右手疾出，一招"HIB"「明月映流沙」"NOR"，猛地抓向$n的額
頭",
        "lvl"   : 60,
        "skill_name" : "明月映流沙"
]),
([        "action" : "$N使一招"HIB"「森然動四方」"NOR"，激起漫天的勁風，撞向$n",
        "lvl"   : 80,
        "skill_name" : "森然動四方"
]),
([        "action" : "$N面無表情，雙臂忽左忽右地疾揮，使出"HIB"「黯黯侵骨寒」"NOR"，十指\n忽伸忽縮，迅猛無比地襲向$n全身各處大穴",
        "lvl"   : 100,
        "skill_name" : "黯黯侵骨寒"
]),
([        "action" : "$N使出"HIB"「黃沙飄驚雨」"NOR"，驀然遊身而上，繞著$n疾轉數圈，$n正眼花繚亂間，\n$N已悄然停在$n身後，右手劃出一道光圈，接著右手沖出光圈猛抓$n的後背",
        "lvl"   : 120,
        "skill_name" : "黃沙飄驚雨"
]),
([        "action" : "$N突然雙手平舉，$n一呆，正在猜測間，便見$N嗖的一下將雙手\n收回胸前，接著一招"HIB"「白骨無限寒」"NOR"，五指如鉤，直抓向$n的腰間",
        "lvl"   : 140,
        "skill_name" : "白骨無限寒"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="shenlong-bashi"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練化骨綿掌必須空手。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功心法火候不夠，練化骨綿掌會走火入魔。\n");

        if( query("max_neili", me)<250 )
                return notify_fail("你的內力太弱，無法練化骨綿掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("huagu-mianzhang", 1))
                return notify_fail("你的基本掌法火候有限，無法領會更高深的化骨綿掌。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練化骨綿掌。\n");
        if (me->query_skill("huagu-mianzhang", 1) < 60)
                me->receive_damage("qi", 60);
        else
                me->receive_damage("qi", 40);
        addn("neili", -25, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -45;
        int d_e2 = -20;
        int p_e1 = 0;
        int p_e2 = 25;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("huagu-mianzhang", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}

string perform_action_file(string action)
{
        return __DIR__"huagu-mianzhang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("huagu-mianzhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force"))
        {
                victim->receive_wound("qi", damage_bonus, me);
                victim->affect_by("huagu",
                              ([ "level" : lvl + random(lvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 50 + random(lvl / 20) ]));

                return HIB"$n胸腹間氣血翻湧，“哇”的一聲，又是鮮血，又是清水，大口吐了出來。\n" NOR;
        }
}

/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int amount;

        if ((int)me->query_skill("huagu-mianzhang") > 100)
        {
                if (random(damage_bonus) > (int)victim->query_skill("force") / 10
                 && !query_temp("hgmz", victim) )
                {
                        set_temp("hgmz", 1, victim);
                        amount = 5 * damage_bonus/( 1 + victim->query_con()) + 1;
                        amount = amount / 100;
                        addn_temp("apply/str", -amount, victim);
                        victim->start_call_out( (: call_other, __FILE__, "remove_effect",
                                                victim, me, amount :),
                                                (int)me->query_skill("huagu-mianzhang", 1) / 20);

                        return HIB "\n$N登時頭暈目眩，立時便欲嘔吐，喉間“呃呃呃”的不住作聲。\n" NOR;
                }
        }
}

void remove_effect(object victim, object me, int amount)
{
        delete_temp("hgmz", victim);
        addn_temp("apply/str", amount, victim);
        message_combatd(HIB"\n$N胸腹間氣血翻湧，“哇”的一聲，又是鮮血，又是清水，大口吐了出來。\n"NOR, victim);
        if( me )
                victim->receive_wound("qi", amount * 10 + random(amount * 10), me);
        else
                victim->receive_wound("qi", amount * 10 + random(amount * 10));
}
*/

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n化骨綿掌："NOR"\n");
        write(@HELP

    化骨綿掌為蛇島神龍教絕技。可與絕命腿互備。

        學習要求：
                毒龍大法級別不能低于化骨綿掌
                基本內功50
                內力300
HELP
        );
        return 1;
}
