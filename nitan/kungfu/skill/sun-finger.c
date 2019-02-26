// This program is a part of NT MudLIB
// sun-finger.c

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *xue_name = ({
"勞宮穴", "膻中穴", "曲池穴", "關元穴", "曲骨穴", "中極穴", "承漿穴", "天突穴", "百會穴",
"幽門穴", "章門穴", "大橫穴", "紫宮穴", "冷淵穴", "天井穴", "極泉穴", "清靈穴", "至陽穴", });

mapping *action = ({
([      "action" : "$N一式"GRN"「陽關三疊」"NOR"，真氣自指間噴薄而出，連出三指，快如電閃，點向$n的$l",
        "lvl" : 0,
        "skill_name" : "陽關三疊"
]),
([      "action" : "$N身形一轉，一步跨到$n身後。$n急忙轉身，$N又如閃電般躍回，
一式"YEL"「魯陽返日」"NOR"，右手食指疾出，指向$n的$l",
        "lvl" : 20,
        "skill_name" : "魯陽返日"
]),
([      "action" : "$N向左踏出一步，左手輕揚，右手食指挾着雄渾內力疾點$n的$l，
招式光明坦蕩，正是一式"HIW"「陽春白雪」"NOR"",
        "lvl" : 40,
        "skill_name" : "陽春白雪"
]),
([      "action" : "$N身影飄起，一式"MAG"「陽鈎揮天」"NOR"，自上而下，左腳彎曲如鈎，踹向$n的右肩，$n側身相避，$N右手趁勢點向$n的$l",
        "lvl" : 60,
        "skill_name" : "陽鈎揮天"
]),
([      "action" : "只見$N臉上忽地一紅，左手一收，一式"RED"「烈日驕陽」"NOR"，右手食指斜指，向$n的$l點去",
        "lvl" : 70,
        "skill_name" : "烈日驕陽"
]),
([      "action" : "$N左掌斜削，突然間變掌為指，嗤的一聲響，一式"HIM"「丹鳳朝陽」"NOR"，使出一陽指力，疾點$n的$l",
        "lvl" : 90,
        "skill_name" : "丹鳳朝陽"
]),
([      "action" : "$N反身一躍，閃身到$n背後，左膝一屈，右手食指回身一式"BLU"「陰陽交錯」"NOR"，射向$n的後腦",
        "lvl" : 100,
        "skill_name" : "陰陽交錯"
]),
([      "action" : "$N一聲大吼, 一式"HIY"「三陽開泰」"NOR"，用盡全力向$n的$l點去",
        "lvl" : 130,
        "skill_name" : "三陽開泰"
]),
});
mapping *action_staff = ({
([      "action" : "$N嘴角輕笑，提$w平胸，看準時機一杖揮出，激起呼呼風聲，迅猛無比地直插$n$l",
        "force" : 100,
        "dodge" : 15,
        "damage" : 50,
        "lvl" : 0,
        "damage_type" : "刺傷",
]),
([      "action" : "$N左手捏個杖訣，右腕傳動，將一陽指神功化於$w之上，出杖凝重，平平正正地打向$n",
        "force" : 150,
        "dodge" : -10,
        "damage" : 70,
        "lvl" : 20,
        "damage_type" : "內傷",
]),
([      "action" : "只見$N屏息凝神，腳步沉着，杖走刀勢，一式橫劈，砍向$n$l，招式威猛正大",
        "force" : 200,
        "dodge" : 0,
        "damage" : 90,
        "lvl" : 40,
        "damage_type" : "割傷",
]),
([      "action" : "$N腳下步法微變，身隨杖走，端凝自重，極飄逸的一杖向$n擊出，輕靈中卻也不失王者氣象",
        "force" : 250,
        "dodge" : 10,
        "damage" : 120,
        "lvl" : 60,
        "damage_type" : "刺傷",
]),
([      "action" : "$N平推一杖，手中的$w看似漸漸沉重，使動時略比先前滯澀，但實是舉輕若重，威猛之極",
        "force" : 300,
        "dodge" : -15,
        "damage" : 140,
        "lvl" : 80,
        "damage_type" : "刺傷",
]),
});
int valid_enable(string usage)
{
        //return usage == "finger" || usage == "parry" || usage == "staff";
        return usage == "finger" || usage == "parry";
}

int valid_learn(object me)
{
/*
        if( query("gender", me) != "男性" )
                return notify_fail("一陽指乃是純陽玄功，你如何可以修習？\n");

        if( query("str", me)<34 )
                return notify_fail("你的先天膂力孱弱，無法領會一陽指。\n");

        if( query("dex", me)<30 )
                return notify_fail("你的先天身法孱弱，無法修煉一陽指。\n");
*/

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練一陽指必須空手。\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("你的內功火候不夠，無法學一陽指。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力太弱，無法練一陽指。\n");

        if ((int)me->query_skill("finger", 1) < 150)
                return notify_fail("你的基本指法火候不夠，無法學一陽指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("sun-finger", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的一陽指。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的內力不夠練一陽指!\n");

        me->receive_damage("qi", 60);
        addn("neili", -100, me);
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
        int d_e1 = 25;
        int d_e2 = 45;
        int p_e1 = -35;
        int p_e2 = -15;
        int f_e1 = 390;
        int f_e2 = 490;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("sun-finger", 1);
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
                "damage_type" : random(2) ? "刺傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me)
{
  if(me->query_skill("kurong-changong") > 10) return 1.0;
  else return 0.6;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];

        if (victim->is_busy())
                return 0;

        if (damage_bonus < 150)
                return 0;

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                if( (query("neili", me)>300 )
                   && me->query_skill("sun-finger", 1) > 100
                   && ! victim->is_busy())
                {
                        victim->start_busy(3);
                        addn("neili", -50, me);
                        victim->receive_wound("qi", (damage_bonus - 100) / 3, me);

                        if( query("neili", victim) <= (damage_bonus/4+50) )
                                set("neili", 0, victim);
                        else
                                addn("neili", -damage_bonus/4, victim);

                                return HIR "只聽“嗤”的一聲，$n" HIR "被$N" HIR "凌空一指點中" NOR +
                                       HIY + name + NOR + HIR "，真氣不由得一滯。\n" NOR;
                }
        } else
        {
                if( (query("neili", me)>300 )
                   && me->query_skill("sun-finger", 1) > 100
                   && ! victim->is_busy())
                {
                        victim->start_busy(2);
                        addn("neili", -50, me);
                        victim->receive_wound("qi", (damage_bonus - 120) / 3, me);

                        return HIR "只聽“嗤”的一聲，$n" HIR "被$N" HIR "杖端發出的氣勁刺中" NOR +
                               HIY + name + NOR +HIR "，真氣不由得一滯。\n" NOR;
                }
        }

}

string perform_action_file(string action)
{
        return __DIR__"sun-finger/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("yiyang-zhi", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int help(object me)
{
        write(HIC"\n一陽指："NOR"\n");
        write(@HELP

    原為大理段氏獨門招牌武功，當年一燈大師段智興挾此技參與
華山論劍，獲得南帝稱號。後一燈大師用一陽指和重陽真人交換先
天氣功，此技亦流入全真派中。
    可與全真教昊天掌互備。

        學習要求：
                男性
                枯榮禪功或先天氣功80級
                內力700
HELP
        );
        return 1;
}
