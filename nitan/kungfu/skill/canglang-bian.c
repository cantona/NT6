// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;

string *action_msg = ({
        "$N佇立不動，揮動$w，使出一招「大海沉沙」，手中$w緩緩向$n的$l擊去，去勢雖不勁急，\n但鞭勢沉滯，如同壓了幾千斤泥沙一般",
        "$N手持$w中央，一招「海天一線」，$w一端陡然一翻，點向$n前胸，勁風所至，將$n退路封住，\n另一端如靈蛇出洞，疾速卷向$n腳踝",
        "$N冷哼一聲，急催內力，使出一招「巨浪排空」，鞭勢加快，只見十數重鞭影如驚滔駭浪般向$n的$l疾卷而來",
        "$N緩緩轉動手中$w，一式「萬里無波」，手中$w去勢奇慢，不帶絲毫破空之聲，\n但所過之處塵土飛揚，$w上所帶勁風已颳得人撲面生疼",
        "$N身形遊走不定，忽地使出一招「滄海一粟」，$w上風聲大作，剎那間數十條鞭影從四面八方向$n周身要害擊到",
        "$N狂嘯一聲，雙目精光大盛，一招「怒海藍濤」，鞭勢展開，或橫掃直擊，或盤旋翻卷，傾刻間已將$n全身裹住",
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 30)
        {
                return notify_fail("你的碧波神功火候太淺。\n");
        }
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 110 + random(20),
                "attack": 80 + random(10),
                "dodge" : 20 + random(10),
                "parry" : 20 + random(10),
                "damage_type" : random(2)?"鞭傷":"刺傷",
        ]);
}

int practice_skill(object me)
{
        object weapon, where;

        where = environment(me);

        if( !query("guanchao", where) )
                return notify_fail("你練習了一會兒滄浪鞭法，發覺怎麼也不能領會滄浪二字的精粹。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練滄浪鞭法。\n");
        message_vision(HIC"$N面對海潮，徐徐揮鞭，使呼吸與海潮同步，漸漸感覺體內真氣也如海潮澎湃一般無窮無盡。\n"NOR, me);
        addn("neili", random(3), me);
        me->recieve_damage("qi", 50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"canglang-bian/" + action;
}
