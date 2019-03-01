// duanyun-bian.c 斷雲鞭法

#include <ansi.h>

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action":"$N一招"HIR" 聚火 "NOR",手揚鞭起，手中$w將$n團團圍住，內力一吐，鞭圈勻速縮小。",
        "force":query("max_neili", this_player())/4,
        "dodge":        -10,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "聚火",
        "damage_type":  "內傷"
]),
([      "action":"$N左手虛幻，右手$w一招"HIC" 起光 "NOR",手中$w由似一條青龍迅速擊向$n。",
        "force":query("max_neili", this_player())/4,
        "dodge":        5,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "起光",
        "damage_type":  "刺傷"
]),
([      "action":"$N騰空而起，手中$w舞成圓環，一招"HIB" 招雨 "NOR"壓向$n,令$n無處可躲。",
        "force":query("max_neili", this_player())/4,
        "dodge":        10,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "招雨",
        "damage_type":  "內傷"
]),
([      "action":"$N力貫鞭梢，一招"HIR" 動雷 "NOR"，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "force":query("max_neili", this_player())/4,
        "dodge":        -5,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "動雷",
        "damage_type":  "淤傷"
]),
([      "action":"$N往前一縱, 但見$N身形一轉，一招"HIC" 移電 "NOR"，手中$w如鬼魅一般，神不知鬼不覺地襲向$n的$l！",
        "force":query("max_neili", this_player())/4,
        "dodge":        -10,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "移電",
        "damage_type":  "刺傷"
]),
([      "action":"$N手持$w,力貫鞭稍，一招"HIR" 剪虹 "NOR"手中$w猶如彩虹般擊向$n,已將$n籠罩於鞭下。",
        "force":query("max_neili", this_player())/4,
        "dodge":        -20,
        "damage":query("shen", this_player())/2500,
        "skill_name":  "剪虹",
        "damage_type":  "刺傷"
]),
([      "action":"$N左手虛晃，右腳突然向前邁出，一招"CYN" 止風 "NOR"，右手$w如同鬼魅一般無聲無息的刺向$n!",
        "force":query("max_neili", this_player())/4,
        "dodge":        0,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "止風",
        "damage_type":  "刺傷"
]),
([      "action":"$N向前縱出，身體飛過$n頭頂，一招"HIW" 斷雲 "NOR"手中$w擊向$n的$l",
        "force":query("max_neili", this_player())/4,
        "dodge":        100,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "斷雲",
        "damage_type":  "內傷"
]),
([      "action":"$N手中$w晃出滿天鞭影，一招"HIB" 遮月 "NOR"虛虛實實的鞭影，鋪天蓋地的擊向$n",
        "force":query("max_neili", this_player())/4,
        "dodge":        50,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "遮月",
        "damage_type":  "淤傷"
]),
([      "action":"$N一招"YEL" 掩日 "NOR"手中$w形似蛟龍又似飛蝗,密不透風的罩向$n！",
        "force":query("max_neili", this_player())/4,
        "dodge":        40,
        "damage":query("shen", this_player())/2500,
        "skill_name" : "掩日",
        "damage_type":  "淤傷"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
        object weapon;
        int lvl = (int)me->query_skill("qingyun-bian", 1);
        int t = 1, j;
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不足，沒有辦法練青雲鞭法, 多練些內力再來吧。\n");

        if ((int)me->query_skill("shaolin-xinfa", 1) < 80)
                return notify_fail("你的少林心法火候太淺。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練鞭法。\n");
        if(lvl<=100)
        {
                if( lvl>10 && query("shen", me)<t*100 )
                        return notify_fail("你的正氣太低了。\n");
        }
        else
        {
                if( query("shen", me)<(11100+(lvl-100)*1000) )
                        return notify_fail("你的正氣太低了。\n");
        }
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("qingyun-bian", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練青雲鞭法。\n");
        me->receive_damage("qi", 5);
        return 1;
}

string perform_action_file(string action)
{
        if ( this_player()->query_skill("qingyun-bian", 1) >= 50 )
                return __DIR__"qingyun-bian/" + action;
}

