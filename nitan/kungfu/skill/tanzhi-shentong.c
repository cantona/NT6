// tanzhi.c 彈指神通

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
string *xue_name = ({
        "勞宮穴","膻中穴","曲池穴","關元穴","曲骨穴","中極穴","承漿穴","天突穴","百會穴",
        "幽門穴","章門穴","大橫穴","紫宮穴","冷淵穴","天井穴","極泉穴","清靈穴","至陽穴",
});

string *action_finger = ({
        "$N中指微屈，突然彈出，一式「指點江山」，一縷勁風直襲$n的$l",
        "$N左掌在身前一劃，右手突然穿出，中指微彈，「如來神指」！直襲$n的$l",
        "$N右臂揮動，中指連彈，在身前劃了一道弧線，正是「一衣帶水」，划向$n的前胸",
        "$N躍起在半空，雙手急揮，中指連彈，「彈指驚雷」鋪天蓋地般向$n湧去",
});

string *action_throwing = ({
        "$N中指微屈，突然彈出，一式「指點江山」，$w破空之聲甚厲，直襲$n的$l",
        "$N左掌在身前一劃，右手突然穿出，中指微彈，「如來神指」！$w呼嘯着直襲$n的$l",
        "$N右臂揮動，中指連彈，數個$w在身前劃了一道弧線，正是「一衣帶水」，划向$n的前胸",
        "$N躍起在半空，雙手急揮，中指連彈，「彈指驚雷」彈出鋪天蓋地的$w，向$n湧去",
});
mapping *action = ({
([      "action" : "$N右指劃了個半圈，一式"CYN"「劃天裂地」"NOR"自上而下划向$n的全身",
        "lvl" : 0,
        "skill_name" : "劃天裂地"
]),
([      "action" : "$N左掌護胸，一招"BLU"「我心悠悠」"NOR"，右指欲舉無力指向$n的額頭",
        "lvl" : 10,
        "skill_name" : "我心悠悠"
]),
([      "action" : "$N雙手齊出，一式"YEL"「千夫所指」"NOR"，疾指向$n的$l",
        "lvl" : 20,
        "skill_name" : "千夫所指"
]),
([      "action" : "$N仰天一歎，一招"RED"「彈指人生」"NOR"，雙手幻出重重指影，點向$n的$l",
        "lvl" : 30,
        "skill_name" : "彈指人生"
]),
([      "action" : "$N一式"GRN"「笑指天南」"NOR"，左掌蓄式，右指彈出一縷指風點向$n的$l",
        "lvl" : 40,
        "skill_name" : "笑指天南"
]),
([      "action" : "$N用出"HIY"「擎天一指」"NOR"，蓄集全身力氣，一指點向$n的$l",
        "lvl" : 50,
        "skill_name" : "擎天一指"
]),
});

int valid_enable(string usage) { return usage == "finger" || usage == "throwing" || usage == "parry"; }
int valid_combine(string combo) { return combo=="lanhua-shou"; }
int double_attack() { return 1; }
int valid_learn(object me)
{
        object weapon;

        if( query("int", me)<28 )
                return notify_fail("你若有所悟，然而總是有點不明白。\n");

        if( weapon=query_temp("weapon", me) )
                if( query("skill_type", weapon) != "throwing" )
                        return notify_fail("學彈指神通必須空手或手持暗器。\n");

        if( query("max_neili", me) >= 1000)return 1;

        if ((int)me->query_skill("bibo-shengong", 1) < 70)
                return notify_fail("你的碧波神功火候不夠，無法學彈指神通。\n");

        if (me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("修習彈指神通必須有碧波神功配合。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力太弱，無法練彈指神通。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( weapon=query_temp("weapon", me) )
                if( query("skill_type", weapon) != "throwing" )
                        return notify_fail("練彈指神通必須空手或手持暗器。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練彈指神通。\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);

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
        int d_e1 = -50;
        int d_e2 = -30;
        int p_e1 = -30;
        int p_e2 = -10;
        int f_e1 = 300;
        int f_e2 = 400;
        int i, lvl, seq, ttl;
        lvl = (int) me->query_skill("tanzhi-shentong", 1);
        if (random(lvl) > 100 && me->query_skill("force") > 120
         && query("neili", me)>200 )
        {
                addn("neili", -50, me);
                if (! weapon)
                        return ([
                                "action": HBRED "$N一聲斷喝，只聽“嗤嗤”之聲連響，無數道勁風從四面八方襲向$n" NOR,
                                "damage": 160,
                                "force" : 400,
                                "attack": 200,
                                "dodge" : -100,
                                "parry" : -100,
                                "damage_type": "刺傷",
                        ]);
                else
                        return ([
                                "action":HBRED"$N一聲斷喝，只聽“嗤嗤”之聲連響，無數"+query("name", weapon)+HBRED"從四面八方襲向$n"NOR,
                                "damage": 260,
                                "damage": 300,
                                "attack": 200,
                                "dodge" : -100,
                                "parry" : -100,
                                "damage_type": "刺傷",
                                "post_action": (:call_other, WEAPON_D, "throw_weapon":)
                ]);
        }
        if( weapon )
                ttl = sizeof(action_throwing);
        else
                ttl = sizeof(action_finger);

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        if( weapon )
        return ([
                "action"      : action_throwing[seq],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "刺傷" : "瘀傷",
        ]);
        else
        return ([
                "action"      : action_finger[seq],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "刺傷" : "瘀傷",
        ]);
}

string perform_action_file(string action)
{
        return __DIR__"tanzhi-shentong/" + action;
}

mixed hit_ob(object me, object victim, int damage)
{
        string name, weapon;
        mixed result;
        name = xue_name[random(sizeof(xue_name))];

        //if (victim->is_busy()) return 0;

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                if( (query("neili", me)>200) && me->query_skill("tanzhi-shentong",1)>100
                 && query("max_neili", me)>1200 )
                {
                        if( !victim->is_busy() )
                                victim->start_busy(3);
                        addn("neili", -30, me);
                        if( query("neili", victim) <= (damage/2+30) )
                                set("neili", 0, victim);
                        else
                                addn("neili", -damage/2+30, victim);
                        return HIR "$N突然伸指，連點$n"HIC"「"+name+"」"HIR"，$n臉色陡然變得蒼白，內息直泄！\n" NOR;
                }
        } else
        {
                if( (query("neili", me)>200) && me->query_skill("tanzhi-shentong",1)>60 )
                {
                        if( !victim->is_busy() )
                                victim->start_busy(2);
                        addn("neili", -30, me);
                        result = ([ "damage" : damage ]);
                        result += ([ "msg" : HIR "$n被$N的暗器打中"HIC"「"+name+"」"HIR"，內息大亂！\n" NOR]);

                        return result;
                }
        }

}

int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

        if( objectp(weapon=query_temp("weapon", me)) )
                if( query("skill_type", weapon) != "throwing" )
                        return 0;

        lvl = me->query_skill("tanzhi-shentong", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping prepare;
        string attack_skill;
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("tanzhi-shentong", 1) < 100
         || !living(me) || query_temp("weapon", me) )
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("tanzhi-shentong", 1);

        if( objectp(weapon=query_temp("weapon", ob)) )
                attack_skill=query("skill_type", weapon);
        else
        {
                prepare = ob->query_skill_prepare();
                if (! prepare) prepare = ([]);
                else if (sizeof(prepare) == 0)  attack_skill = "unarmed";
                else if (sizeof(prepare) == 1)  attack_skill = (keys(prepare))[0];
                else if( sizeof(prepare) == 2)attack_skill=(query_temp("action_flag", keys(prepare))[ob)];
        }
        attack_skill = ob->query_skill_mapped(attack_skill);

        if (ap / 2 + random(ap) < dp && stringp(attack_skill))
        {
                result = ([ "damage": -damage ]);
                // 去掉所有的傷害寫法
                if( objectp(weapon=query_temp("weapon", ob)) )
                {
                        result += (["msg" : HIC "$n" HIC "伸指一彈，嗤的一聲輕響，一股細細的勁力激射出去，"
                                                "登時將" + weapon->name() + HIC"上所附內勁盡數抵銷，"
                                                        "化解了這招" + to_chinese(attack_skill) + "。\n" NOR]);
                }
                else    result += (["msg" : HIC "$n" HIC "伸指一彈，嗤的一聲輕響，一股細細的勁力激射出去，"
                                "這「彈指神通」與$N的「" + to_chinese(attack_skill) + "」鬥了個旗鼓相當，"
                                        "誰也沒能傷誰。\n" NOR]);
                return  result;
        }
}

*/


int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n彈指神通："NOR"\n");
        write(@HELP

    東海桃花島主黃藥師的成名絕技。
    可與蘭花拂穴手互備。

        學習要求：
                碧波神功20級
                內力100
HELP
        );
        return 1;
}
