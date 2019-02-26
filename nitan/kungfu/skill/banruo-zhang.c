// banruo-zhang.c 般若掌

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N前腿踢出，後腿腳尖點地，一式"HIC"「橫空出世」"NOR"，二掌直出，攻向$n的上中下三路",
        "lvl" : 0,
        "skill_name" : "橫空出世"
]),
([      "action" : "$N左掌劃一半圓，一式"HIR"「長虹貫日」"NOR"，右掌斜穿而出，疾拍$n的胸前大穴",
        "lvl" : 12,
        "skill_name" : "長虹貫日"
]),
([      "action" : "$N使一式"HIB"「雲斷秦嶺」"NOR"，右掌上引，左掌由後而上一個甩劈，斬向$n的$l",
        "lvl" : 18,
        "skill_name" : "雲斷秦嶺"
]),
([      "action" : "$N左掌護胸，右拳凝勁後發，一式"HIM"「鐵索攔江」"NOR"，緩緩推向$n的$l",
        "lvl" : 24,
        "skill_name" : "鐵索攔江"
]),
([      "action" : "$N使一式"HIY"「狂風捲地」"NOR"，全身飛速旋轉，雙掌一前一後，猛地拍向$n的胸口",
        "lvl" : 30,
        "skill_name" : "狂風捲地"
]),
([      "action" : "$N合掌抱球，猛吸一口氣，一式"HIW"「懷中抱月」"NOR"，雙掌疾推向$n的肩頭",
        "lvl" : 36,
        "skill_name" : "懷中抱月"
]),
([      "action" : "$N向上高高躍起，一式"HIG"「高山流水」"NOR"，居高臨下，掌力籠罩$n的全身",
        "lvl" : 42,
        "skill_name" : "高山流水"
]),
([      "action" : "$N使一式"CYN"「摘星換鬥」"NOR"，勁氣瀰漫，雙掌如輪，一環環向$n的$l斫去",
        "lvl" : 48,
        "skill_name" : "摘星換鬥"
]),
([      "action" : "$N兩掌上下護胸，一式"HIW"「翻江攪海」"NOR"，驟然化為滿天掌雨，攻向$n",
        "lvl" : 54,
        "skill_name" : "翻江攪海"
]),
([      "action" : "$N一式"HIY"「金剛伏魔」"NOR"，雙手合十，對着$n微微一揖，全身內勁如巨浪般洶湧而出",
        "lvl" : 60,
        "skill_name" : "金剛伏魔"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="yizhi-chan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練般若掌必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法練般若掌。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練般若掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("banruo-zhang", 1))
                return notify_fail("你的基本掌法火候水平有限，無法領會更高深的般若功。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練般若掌。\n");

        me->receive_damage("qi", 65);
        addn("neili", -64, me);
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
        int p_e1 = -10;
        int p_e2 = 20;
        int f_e1 = 250;
        int f_e2 = 350;
        int i, lvl, seq, ttl = sizeof(action);
        string *msg = ({
                "喝道：“吃我一掌！”",
                "雙手合什，説道：“阿彌陀佛！”",
                "説道：“罪過罪過！”這四字一出口，忽地",
                "",
        });

        lvl = (int) me->query_skill("banruo-zhang", 1);
        if( query_temp("sl_perform/san", me) )
        {
                i = me->query_skill("force") + lvl;
                return([
                        "action": HIW"$N"+ msg[random(sizeof(msg))] +"雙掌自外向裏轉了個圓圈，緩緩向$n推了過來。\n"
                                        "$P掌力未到，$n已感胸口呼吸不暢，頃刻之間，$N的掌力如怒潮般洶湧而至！"NOR,
                        "force" : i + random(i),
                        "damage": 300,
                        "dodge" : -100,
                        "parry" : -100,
                        "damage_type" : "瘀傷", ]);
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

void skill_improved(object me)
{
        int level = (int)me->query_skill("banruo-zhang", 1);

        if (level >= 180
        &&  (int)me->query_skill("yizhi-chan", 1) >= 180
         && !query("sl_gift/yzc", me)){
                addn("con", 1, me);
                set("sl_gift/yzc", 1, me);
                tell_object(me, "\n你的一指禪和般若掌學有所成，提高了你的根骨。\n");
        }

        if( !(level % 10) && level >= (int)me->query_skill("force", 1) ) {
                me->improve_skill("force", (level - 5), 1);
                tell_object(me, "\n你在般若掌方面的造詣增進了你的基本內功修為。\n");
        }

        /*
        if( !(level % 10) && level >= (int)me->query_skill("hunyuan-yiqi", 1) ) {
                me->improve_skill("hunyuan-yiqi", (level - 5)/2, 1);
                tell_object(me, "\n你在般若掌方面的造詣增進了你的混元一氣功修為。\n");
        }
        */
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"banruo-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n般若掌："NOR"\n");
        write(@HELP

    少林七十二絕技之一。
    可與一指禪互備。
    般若掌有一招兇猛的絕招，喚做“一拍兩散”。所謂“兩散”，是
指拍在石上，石屑四“散”、拍在人身，魂飛魄“散”。這路掌法就只
這麼一招，只因掌力太過雄渾，臨敵時用不着使第二招，敵人便已斃命，
而這一掌以如此排山倒海般的內力為根基，要想變招換式，亦非人力之
所能。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
