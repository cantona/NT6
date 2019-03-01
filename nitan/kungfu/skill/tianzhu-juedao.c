inherit SKILL;

mapping *action = ({
([      "action" : "$N藏刀內收，一招「開門楫盜」，刀鋒自下而上劃了個半弧，向$n的
$l揮去",
        "force" : 120,
        "dodge" : -10,
        "parry" : 5,
        "damage": 115,
        "lvl" : 0,
        "skill_name" : "開門楫盜",
        "damage_type" : "割傷"
]),
([      "action" : "$N左掌虛托右肘，一招「梅雪逢夏」，手中$w筆直劃向$n的$l",
        "force" : 130,
        "dodge" : -10,
        "parry" : 10,
        "damage": 120,
        "lvl" : 12,
        "skill_name" : "梅雪逢夏",
        "damage_type" : "割傷"
]),
([      "action" : "$N一招「千鈞壓駝」，$w繞頸而過，刷地一聲自上而下向$n猛劈",
        "force" : 140,
        "dodge" : -5,
        "parry" : 5,
        "damage": 125,
        "lvl" : 18,
        "skill_name" : "千鈞壓駝",
        "damage_type" : "割傷"
]),
([      "action" : "$N右手反執刀柄，一招「赤日金鼓」，猛一挫身，$w直向$n的頸中斬
去",
        "force" : 160,
        "dodge" : 5,
        "parry" : 5,
        "damage": 30,
        "lvl" : 24,
        "skill_name" : "赤日金鼓",
        "damage_type" : "割傷",
]),
([      "action" : "$N一招「漢將當關」，無數刀尖化作點點繁星，向$n的$l挑去",
        "force" : 180,
        "dodge" : 10,
        "parry" : 5,
        "damage": 135,
        "lvl" : 30,
        "skill_name" : "漢將當關",
        "damage_type" : "割傷"
]),
([      "action" : "$N雙手合執$w，一招「鮑魚之肆」，擰身急轉，刀尖直刺向$n的雙眼
",
        "force" : 210,
        "dodge" : 15,
        "parry" : 15,
        "damage": 140,
        "lvl" : 36,
        "skill_name" : "鮑魚之肆",
        "damage_type" : "割傷"
]),
([      "action" : "$N一招「旁敲側擊」，手中$w劃出一個大平十字，向$n縱橫劈去",
        "force" : 240,
        "dodge" : 15,
        "parry" : 15,
        "damage": 50,
        "lvl" : 42,
        "skill_name" : "旁敲側擊",
        "damage_type" : "割傷"
]),
([      "action" : "$N反轉刀尖對準自己，一招「長者折枝」，全身一個翻滾，$w向$n攔
腰斬去",
        "force" : 280,
        "dodge" : 20,
        "parry" : 10,
        "damage": 160,
        "lvl" : 48,
        "skill_name" : "長者折枝",
        "damage_type" : "割傷"
]),
([      "action" : "$N一招「赤日炎炎」，$w的刀光仿佛化成一簇簇烈燄，將$n團團圍繞
",
        "force" : 320,
        "dodge" : 10,
        "parry" : 20,
        "damage": 175,
        "lvl" : 54,
        "skill_name" : "赤日炎炎",
        "damage_type" : "割傷"
]),
([      "action" : "$N刀尖平指，一招「大海沉沙」，一片片切骨刀氣如颶風般裹向$n的
全身",
        "force" : 370,
        "dodge" : 5,
        "parry" : 25,
        "damage": 190,
        "lvl" : 60,
        "skill_name" : "大海沉沙",
        "damage_type" : "割傷"
]),
});

int valid_enable(string usage) { return (usage == "blade") || (usage == "parry")
; }

int valid_learn(object me)
{
        if( query("max_neili", me)<600 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的內功火候太淺。\n");
        if ((int)me->query_skill("blade", 1) < 120)
                return notify_fail("你的基本刀法火候太淺。\n");
   
 return 1;
}

mapping query_action(object me, object weapon)
{
int zhaoshu, level;

zhaoshu = sizeof(action)-1;
level   = (int) me->query_skill("tianzhu-juedao",1);

if (level < 60 )
zhaoshu--;
if (level < 55 )
zhaoshu--;
if (level < 50 )
zhaoshu--;
if (level < 40 )
zhaoshu--;
if (level < 30 )
zhaoshu--;
if (level < 20 )
zhaoshu--;
if (level < 10 )
zhaoshu--;

return action[random(zhaoshu)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練天竺絕刀。\n");
        me->receive_damage("qi", 30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianzhu-juedao/" + action;
}