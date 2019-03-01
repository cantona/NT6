// taxue-wuhen.c 踏雪無痕

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$n一式"YEL"「雁落平沙」"NOR"，變招奇速，右足向前踢出，身子已然騰起，輕輕巧巧地落在一旁。\n",
"$n一式"HIW"「玉龍飛起」"NOR"，縱身高躍，半空中一折一轉，已飄身在數丈之外。\n",
"$n一式"HIY"「夏日消融」"NOR"，兩足足跟不動，足尖左磨，身子隨之右轉，卸開了$N這一招。\n",
"$n一式"HIB"「枯鬆倒掛」"NOR"，只見$n身子後仰，雙掌往地下一撐，身子借勢倒射而出，$N便已打$n不著。\n",
"$n一式"HIW"「晴雪飛灘」"NOR"，縱高伏低，東奔西閃，身形飄忽不定，$N手無足措，只得回招自守。\n",
"$n一式"HIW"「冰絲帶雨」"NOR"，突然反手一招，竟然是兩敗俱傷的打法，趁$N手忙腳亂安全脫身。\n",
"$n一式"HIM"「寒江釣雪」"NOR"，不招不架，只微微一側身，$N猶如暴風驟雨般的進攻便即落空。\n",
"$n一式"HIY"「魚龍潛躍」"NOR"，陡然間身形拔起，直沖雲霄，直如鷹隼，幾個盤旋，飄飄盪盪落在數丈之外。\n",
"$n一式"HIW"「踏雪無痕」"NOR"，身形急速旋轉，幾下就劃到數丈之外。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<20 || query("neili", me)<4 )
                return notify_fail("你的體力太差了，不能練踏雪無痕。\n");
        me->receive_damage("qi", 20);
        addn("neili", -4, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1.2; }
mixed valid_damage(object me, object victim, int damage, object weapon)
{
        int ap, dp, level;
        object weapon1=query_temp("weapon", me);
        mapping prepare;
        string result, attack_skill;

        if ( victim->query_skill("taxue-wuhen", 1) < 100
        || !living(victim) )
                return;

        dp = COMBAT_D->skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);
                dp += COMBAT_D->skill_power(victim, "force", SKILL_USAGE_DEFENSE);

        ap = COMBAT_D->skill_power(me, "dodge", SKILL_USAGE_DEFENSE);
        prepare = me->query_skill_prepare();
        if( !prepare ) prepare = ([]);

        if( objectp(weapon1))attack_skill=query("skill_type", weapon1);
        else switch( sizeof(prepare) )
        {
                case 0: attack_skill = "unarmed"; break;
                case 1: attack_skill = (keys(prepare))[0]; break;
                case 2: attack_skill = (keys(prepare))[query_temp("action_flag", me)]; break;
        }

        ap += COMBAT_D->skill_power(me, attack_skill, SKILL_USAGE_ATTACK);

        ap /= 100;
        dp /= 100;

        if ( random(ap+dp) > ap ) {
                result =  "$n身形一晃閃過一邊，手做擲暗器狀，$N心頭一驚，一時有點手忙腳亂！\n";
                result += "$n見有機可趁，立刻對$N發動攻勢！\n" ;

                return ([ "msg" : result, "damage" : -damage ]);
        }
         else if ( random(ap+dp) > ap ) {
                result = HIW "只見$n舉重若輕,以極巧妙身法，身影滿天飛舞，手做擲暗器狀，$N心頭一驚，一時有點手忙腳亂！\n" NOR;
                result += "$n捉緊時機，立刻對$N發動攻勢！\n" ;
                COMBAT_D->do_attack(victim,me,query_temp("weapon", victim));
                addn("jingli", random(-20), victim);

                return ([ "msg" : result, "damage" : -damage ]);
        }
        else if ( random(ap+2*dp) > ap ) {
                result = "$n身形一晃閃過一邊，已然輕易地避開了$N的攻擊。\n" ;

                return ([ "msg" : result, "damage" : -damage ]);
        }
        else if ( random(ap+3*dp) > ap ) {
                result = "$n身形一晃閃過一邊，$N只覺得用力處力道全無。\n";

                return ([ "msg" : result, "damage" : -damage ]);
        }
        else
                return;
}

string perform_action_file(string action)
{
        return __DIR__"taxue-wuhen/" + action;
}

