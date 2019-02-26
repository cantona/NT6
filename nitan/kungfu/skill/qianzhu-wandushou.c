// qianzhu-wandushou.c 千蛛萬毒手
// Last Modified by winder on May. 17 2001

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N身形一晃而至，一招"HIB"「小鬼勾魂」"NOR"，雙掌帶着一縷腥風拍向$n的前心",
        "lvl"    : 0,
        "skill_name" : "小鬼勾魂"
]),
([        "action" : "$N身形化做一縷輕煙繞着$n急轉，一招"MAG"「天網恢恢」"NOR"，雙掌幻出無數掌影罩向$n",
        "lvl"    : 20,
        "skill_name" : "天網恢恢"
]),
([        "action" : "$N大喝一聲，一招"BLU"「惡鬼推門」"NOR"，單掌如巨斧開山帶着一股腥風猛劈向$n的面門",
        "lvl"    : 30,
        "skill_name" : "惡鬼推門"
]),
([        "action" : "$N一聲冷笑，一招"HIR"「靈蛇九轉」"NOR"，身形一閃而至，一掌輕輕拍出，手臂宛若無骨，掌到中途竟連變九變，如鬼魅般印向$n的$l",
        "lvl"    : 40,
        "skill_name" : "靈蛇九轉"
]),
([        "action" : "$N側身向前，一招"BLU"「地府陰風」"NOR"，雙掌連環拍出，一縷縷徹骨的寒氣從掌心透出，將$n周圍的空氣都凝結了",
        "lvl"    : 50,
        "skill_name" : "地府陰風"
]),
([        "action" : "$N厲叫一聲，身形忽的蜷縮如球，飛身撞向$n，一招"YEL "「黃蜂吐刺」"NOR"單掌如劍，直刺$n的心窩",
        "lvl"    : 60,
        "skill_name" : "黃蜂吐刺"
]),
([        "action" : "$N一個急旋，飛身縱起，半空中一式"HIB"「毒龍擺尾」"NOR"，反手擊向$n的$l",
        "lvl"    : 70,
        "skill_name" : "毒龍擺尾"
]),
([        "action" : "$N大喝一聲，運起五毒神功，一招"RED"「毒火焚身」"NOR"，剎那間全身毛髮盡綠，一對碧綠的雙爪閃電般的朝$n的$l抓去",
        "lvl"    : 80,
        "skill_name" : "毒火焚身"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="wudu-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練千蛛萬毒手必須空手。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練千蛛萬毒手");
        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練千蛛萬毒手。\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int lvl2;
        int flvl;

        lvl  = me->query_skill("qianzhu-wandushou", 1);
        lvl2 = me->query_skill("duji", 1);
        flvl=query("jiali", me);
        if (lvl + random(flvl) > victim->query_skill("dodge")
                         &&victim->affect_by("qzhu_poison",
                                  ([ "level" : lvl2 + lvl*3 + random(flvl),
                                     "id":query("id", me),
                                    "duration" : lvl / 50 + flvl/50 + random(lvl2 / 50) ])))
        {
                return HIW "$n" HIW "突然面孔扭曲,痛苦不堪,看來是中了千蛛萬毒功的巨毒。\n" NOR;
        }
}
void skill_improved(object me)
{
        if( random(15)<1 && query("per", me)>5 )
        {
                tell_object(me, HIR"你忽然覺得體內毒氣狂竄，面上頓時罩着一層黑氣！\n" NOR );
                addn("per", -1, me);
        }
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
        int d_e1 = -55;
        int d_e2 = -20;
        int p_e1 = 10;
        int p_e2 = 35;
        int f_e1 = 190;
        int f_e2 = 290;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("qianzhu-wandushou", 1);
        if (random(me->query_skill("finger")) > 120 &&
            me->query_skill("force") > 100 &&
            me->query_skill("dodge") > 100 &&
            query("neili", me)>1500){
                addn("neili", -200, me);
                return ([
                "action": HIR "$N眉間黑氣籠罩，牙關緊咬，突然噴出一股香氣，十指又快如鬼魅般點向$n膻中穴！"NOR,
                "force": 560,
                "damage" : 100,
                "damage_type": "瘀傷"]);
        }
           if (random(me->query_skill("finger")) > 80 &&
            me->query_skill("force") > 100 &&
            query("neili", me)>1000){
                addn("qi", -15, me);
                addn("neili", -100, me);
                return ([
                "action": HIR "$N忽然咬破食指，潛用內力將毒素逼入指尖，輕輕彈出，一股內勁直襲$n胸口！"NOR,
                "force": 420,
                 "damage" : 80,
                "damage_type": "瘀傷"]);
        }
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
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        if ( this_player()->query_skill("qianzhu-wandushou", 1) >= 50 )
                return __DIR__"qianzhu-wandushou/" + action;
}

int help(object me)
{
        write(HIC"\n千蛛萬毒手："NOR"\n");
        write(@HELP

    千蛛萬毒手是五毒教的獨門功夫，有獨門修煉方法。靠吸取毒
蟲身上的毒氣來練成毒功，雖然厲害，但毒氣會損壞自己的容貌，
使自己變的醜陋無比。

        學習要求：
                五毒神功20級
                內力100
HELP
        );
        return 1;
}
