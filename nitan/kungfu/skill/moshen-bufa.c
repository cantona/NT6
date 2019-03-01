// This program is a part of NITAN MudLIB

inherit SKILL;

string *dodge_msg = ({
        "$n一聲長笑，沖天而起，竟能凌空旋，堪堪避過$N的攻擊，往另一個方向投去！\n",
        "$N攻向$N時，$n看似要凌空迎戰，豈知竟像蝙蝠般旋避開，予人吻合天地大道的感覺。\n",
        "$n身軀後仰，險險避開$N的攻擊，再斜飛而起，往遠處投去，姿態美至極點。\n",
        "$n好像化成一縷沒有重量的輕煙，隨呼呼吹來的輕風飄移晃動，每一刻都不斷變換位置。\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太差了，不能練魔神步法。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠。\n");
        me->receive_damage("qi", 40);
        addn("neili", -40, me);
        return 1;
}


