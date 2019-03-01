// liumang-shenquan.c 流氓神拳
// By Alf, Last Update 2001.11

// 黑虎掏心 雙風貫耳 葉底偷桃 獨劈華山 二郎擔山 拔草尋蛇 猛虎跳澗

inherit SKILL;

mapping *action = ({
([      "action" : "$N沉腰坐馬，左拳護身，右拳直擊，一招「黑虎掏心」，挾著風聲擊向$n的$l",
        "force" : 120,
        "dodge" : 20,
        "parry" : 20,
        "lvl" : 0,
        "skill_name" : "黑虎掏心",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N搶上一步，雙拳左右掄開，胸前賣個破綻，一招「雙風貫耳」，合擊$n的$l",
        "force" : 140,
        "dodge" : 15,
        "parry" : 15,
        "lvl" : 20,
        "skill_name" : "雙風貫耳",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身形一矮，左拳虛晃$n面門，右掌一個「葉底偷桃」，望準$n的$l狠命一抓",
        "force" : 160,
        "dodge" : 10,
        "parry" : 10,
        "lvl" : 40,
        "skill_name" : "葉底偷桃",
        "damage_type" : "瘀傷",
]),
([      "action" : "$N將身一長，一招「獨劈華山」，呼的一掌去勢奇快，當頭向$n的$l猛劈過去",
        "force" : 180,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 60,
        "skill_name" : "獨劈華山",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N腰桿挺直，腳下前弓後箭，雙掌一錯，使出一招「二郎擔山」，拍向$n的$l",
        "force" : 200,
        "dodge" : -5,
        "parry" : -5,
        "lvl" : 80,
        "skill_name" : "二郎擔山",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N步履一沉，一招「拔草尋蛇」，腳下一個掃堂腿橫掃，同時出拳搗向$n的$l",
         "force" : 210,
        "dodge" : -5,
        "parry" : -10,
        "lvl" : 90,
        "skill_name" : "拔草尋蛇",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N口裡一聲怪吼，雙拳虛握，狀如虎爪，一招「猛虎跳澗」，對準$n的$l抓去",
         "force" : 220,
        "dodge" : -10,
        "parry" : -10,
        "lvl" : 100,
        "skill_name" : "猛虎跳澗",
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練流氓神拳必須空手。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太低，無法練流氓神拳。\n");

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
        level = (int) me->query_skill("liumang-shenquan",1);
        
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]) 
                return action[NewRandom(i, 20, level/5)];
                    
}

int practice_skill(object me)
{
        int lvl = me->query_skill("liumang-shenquan", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        
        me->receive_damage("qi", 30);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liumang-shenquan/" + action;
}

