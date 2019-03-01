// This program is a part of NT MudLIB
// qishang-quan.c 七傷拳

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N氣凝如山，一式「金戈鐵馬」，雙拳蓄勢而發，擊向$n的$l",
        "lvl" : 0,
        "skill_name" : "金戈鐵馬"
]),
([        "action" : "$N身形凝重，勁發腰背，一式「木已成舟」，緩緩向$n推出",
        "lvl" : 10,
        "skill_name" : "木已成舟"
]),
([        "action" : "$N步伐輕靈，兩臂伸舒如鞭，一式「水中撈月」，令$n無可躲閃",
        "lvl" : 20,
        "skill_name" : "水中撈月"
]),
([        "action" : "$N身形躍起，一式「火海刀山」，雙拳當空擊下，勢不可擋",
        "lvl" : 30,
        "skill_name" : "火海刀山"
]),
([        "action" : "$N身形一矮，一式「土載萬物」，兩拳自下而上，攻向$n",
        "lvl" : 40,
        "skill_name" : "土載萬物"
]),
([        "action" : "$N身形一轉，一式「陰風慘慘」，攻向$n的身前身後",
        "lvl" : 48,
        "skill_name" : "陰風慘慘"
]),
([        "action" : "$N移形換位，步到拳到，一式「陽光普照」，四面八方都是拳影",
        "lvl" : 54,
        "skill_name" : "陽光普照"
]),
([        "action" : "$N長嘯一聲，向前踏出一步，雙拳中宮直進，一式「七者皆傷」，驟然擊向$n的前胸",
        "lvl" : 60,
        "skill_name" : "七者皆傷"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("練七傷拳必須空手。\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的內功火候不夠，無法學七傷拳。\n");

        if ((int)query("max_neili", me) < 1800)
                return notify_fail("你的內力修為不夠，無法練七傷拳。\n");

        if ((int)me->query_skill("cuff", 1) < 120)
                return notify_fail("你的基本拳法火候不夠，無法練七傷拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("qishang-quan", 1))
                return notify_fail("你的基本拳法水平還不夠，無法領會更高深的七傷拳。\n");

        return 1;
}

int practice_skill(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("你的必須空手才能練習。\n");
        if ((int)query("qi", me) < 60)
                return notify_fail("你的體力太低了。\n");
        if ((int)query("neili", me) < 70)
                return notify_fail("你的內力不夠練七傷拳。\n");
        /*
        if ((int)me->query_skill("qishang-quan",1) % 20 == 0 &&
                (int)me->query_skill("qishang-quan",1) < 200)
                return notify_fail("你的七傷拳到了關鍵火候，怎麼練都無法領悟。\n");
        */
        me->receive_damage("qi", 50);
        addn("neili", -60, me);
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
        int d_e1 = 5;
        int d_e2 = 30;
        int p_e1 = -50;
        int p_e2 = -5;
        int f_e1 = 250;
        int f_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("qishang-quan", 1);
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
                "damage_type" : "瘀傷",
        ]);
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string msg;
        mixed result;
        int lvl;
        int flvl;

        lvl  = me->query_skill("qishang-quan", 1);
        flvl = query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (random(lvl) > 80 && (int)query("neili", me) > 300)
        {
                victim->affect_by("qs_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ]));
                result = ([ "damage" : damage_bonus ]);
                addn("neili", -200, me);

                switch(random(7))
                {
                case 0 :
                        msg = MAG"$N凝神定氣，使出七傷拳總訣中的「"HIR"損心訣"MAG"」，雙拳一股剛猛之力向$n擊去。\n"NOR;
                        break;
                case 1 :
                        msg = HIB"$N深吸一口氣，左拳再使出七傷拳總訣中的「"HIR"傷肺訣"HIB"」，雙拳飄忽不定，$n頓時感覺一股陰柔之力迎面而來。\n"NOR;
                        break;
                case 2 :
                        msg = HIC"$N右拳接著使出七傷拳總訣中的「"HIR"摧肝腸訣"HIC"」，雙拳剛中有柔，向$n擊去。\n"NOR;
                        break;
                case 3 :
                        msg = HIG"$N凝神定氣，使出七傷拳總訣中的「"HIR"藏離訣"HIG"」，雙拳柔中有剛，打出一股內縮之力！向$n擊去。\n"NOR;
                        break;
                case 4 :
                        msg = HIY"$N凝神定氣，使出七傷拳總訣中的「"HIR"精失訣"HIY"」，雙拳勢如雷霆，將力道直向$n送去。\n"NOR;
                        break;
                case 5:
                        msg = HIM"$N凝神定氣，使出七傷拳總訣中的「"HIR"意恍惚訣"HIM"」，向$n送出一股橫出之力。\n"NOR;
                        break;
                case 6:
                        msg = HIR"$N大喝一聲，須發俱張，使出「七傷總訣」，左右雙拳連續擊出，威猛無儔，打向$n。\n"NOR;
                        break;
                }
                msg += HIW"$n只覺得$N這一拳之中共有七股不同勁力，變幻百端，猶豫間已被這股力道籠罩全身，頓時身受嚴重的內傷。\n" NOR;
                result += ([ "msg" : msg ]);
                return result;
        }
}

void skill_improved(object me)
{
        object *ob;
        int i, skill;
        skill = me->query_skill("qishang-quan", 1);

        if (query("max_neili", me) < skill * 15 && skill < 200)
        {
                switch(random(5)){
                case 0 :
                        tell_object(me, HIR"你肩頭雲門穴突然一陣輕微隱痛，是肺脈傷了！\n"NOR);
                        addn("max_neili", -random(100), me);
                        break;
                case 1 :
                        tell_object(me, HIR"你腿上無裡穴突然酸痛難當，是肝脈傷了！\n"NOR);
                        addn("combat_exp", -random(7000), me);
                        break;
                case 2 :
                        message_vision(HIR"$N心脈練傷，突然狂性大發、無法抑制了！\n"NOR, me);
                        me->set_skill("qishang-quan", skill - 1);
                        break;
                case 3 :
                        tell_object(me, HIR"你上臂青靈穴突然一時麻癢難當，是心脈傷了！\n"NOR);
                        addn("max_neili", -random(100), me);
                        break;
                case 4 :
                        tell_object(me, HIR"你突然覺得體內陰陽二氣串行金木水火土五行，無法抑制了！\n"NOR);
                        me->set_skill("qishang-quan", skill-2);
                        break;
                }
                // me->unconcious();
        }
}

string perform_action_file(string action)
{
        return __DIR__"qishang-quan/" + action;
}

int help(object me)
{
        write(HIC"\n七傷拳："NOR"\n");
        write(@HELP

    七傷拳，拳出必傷。是崆峒派的不傳之秘，但後來謝遜為報家
仇，從崆峒派手中盜出《七傷拳譜》，從而練成。名為七傷，實則
為每出一拳可以有七種不同內勁，使人不知如何與之相抗。

                    ┌──────────┐
                    │    七傷拳總訣      │
                    │  五行之氣調陰陽，  │
                    │  損心傷肺摧肝腸，  │
                    │  藏離精失意恍惚，  │
                    │三焦齊逆兮魂魄飛    │
                    └──────────┘

        學習要求：
                只能向謝遜學習
                內力200
HELP
        );
        return 1;
}