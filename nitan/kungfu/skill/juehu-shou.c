// juehu-shou.c -
// updated by Lonely

inherit SKILL;

mapping *action_msg = ({
        "$N一式「老牛拉車」，以掌化爪，五指如鈎，兩眼瞪得通紅，直逼$n的襠部",
        "$N四肢貼地，頭部底垂，看似已無力進攻，突然四肢用力一扒已竄到$n跨下，兩手猛的上戳，好一式「精疲力盡」",
        "$N兩手高高舉起，運掌如風，一式「壯士斷腕」，閉眼就朝$n的下體砍去",
        "$N一躍而起，直往$n的雙肩落下，雙腿盤住$n的頸部，一扭腰，雙手成關門之勢，往$n的襠部狠狠拍去，正是一式「落葉歸根」",
        "$N使一式「空前絕後」，身形一分為二，四隻手掌有如熊掌般朝$n的後腰和襠部拍去",
        "$N全身關節啪啪作響，面如白紙，一式「斷子絕孫」，無數鷹爪抓向$n全身要害，瞬間無數鷹爪又合為一爪直往$n的襠部抓落",
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練虎抓絕户手必須空手。\n");
                
        if ((int)me->query_skill("taiji-shengong", 1) < 40)
        
                return notify_fail("你的太極神功火候不夠，無法學虎抓絕户手。\n");
                
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練虎抓絕户手。\n");
                
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(20),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2)?"抓傷":"瘀傷",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練虎抓絕户手。\n");
        me->receive_damage("qi", 25);
        addn("shen", -10, me);
        addn("neili", -10, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"juehu-shou/" + action;
}

