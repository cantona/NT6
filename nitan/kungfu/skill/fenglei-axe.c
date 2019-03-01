// fenglei-axe.c 九霄風雷斧 

inherit SKILL;
#include <ansi.h>

string *action_msg = ({
       "$N將$w一擺，先天真氣激盪，第一式『春雷乍響』渾然天成，有若實質的氣勁如利斧般劈向$n" NOR,
       "$w斧勢一變，竟如穿花引蝶般小巧細膩，正是『九霄風雷斧』第九式『陰風藏雨』" NOR,
       "$N大開大闔，第二式『狂風亂雲』閃電般劈向$n" NOR,
       "$N暴喝聲中$w高舉過頭，運勁直劈，第四式『天雷焚城』果然絕無半點花俏" NOR,
       "$w再變，從$N肋下穿出，遙擊$n的$l，第七式『迅雷千幻』讓$n完全無法捉摸來勢" NOR,
       "$N手中$w自左而右劃了一個大弧，$w借第五式『暴風絞沙』這道弧線泛起層層斧影，向$n平推而至" NOR,
       "$N躍至半空，使出第三式『九霄落雷』，手中$w隱挾雷音，織成一道斧網向$n罩去" NOR,
       "$N凝氣守中，$w化大巧為大拙，運勁逼出丈許雪亮斧芒，第六式『疾風驟雨』一斧快似一斧地攻向$n" NOR,
       "$N揮斧由中宮直進，手腕翻處，中途轉向，第八式『旱地雷音』早已變換了數個方位，最終劈向$n的$l" NOR,
       "$w自$N手中彈起，化出一道漂亮的弧線劈向$n，同時左手揮拳直擊，正是威力最大的第十式『風雷齊至』" NOR,
});

int valid_enable(string usage) { return usage == "axe" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("zidian-jin", 1) < 25)
                return notify_fail("你的玄天紫電勁火候太淺。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 180 + random(50),
                "attack": 100 + random(30),
                "dodge" : 100 + random(30),
                "parry" : 100 + random(30),
                "damage_type" : random(2)?"劈傷":"砍傷",
        ]);
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result; 
        
        if (me->query_skill("zidian-jin", 1) < 100
        ||  me->query_skill_mapped("force") != "fenglei-axe"
         || !query_temp("powerup", me )
        ||  damage < 100) return 0;

        if (random(damage / 2) > 50) 
        {
                result = ([ "damage": damage ]);                 
                result += (["msg" : HIR "只見紫芒閃過，$n□血四□，被$N" HIR "斧上聚集的玄天紫電勁所傷！\n" NOR]);
                return result;
        }
}


int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "axe" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練九霄風雷斧。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練九霄風雷斧。\n");               
        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fenglei-axe/" + action;
}
