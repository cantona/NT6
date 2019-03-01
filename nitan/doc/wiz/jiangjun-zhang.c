// jiangjun-zhang.c 裴將軍詩杖法

inherit SKILL;

mapping *action = ({
([      "action":               
"$N手中$w向$n的$l連點三點，正是「裴」字起首三筆！",
        "damage":                100,
        "damage_type":  "挫傷"
]),
([      "action":               
"$N揮起$w，對準$n的$l虛點，自右上角至右下角彎曲而下，正是「如」字草書！",
        "damage":                120,
        "damage_type":  "挫傷"
]),
([      "action":               
"$N橫過$w，寫了個「猛」字，對著$n斜掃過去！",
        "damage":                140,
        "damage_type":  "挫傷"
]),
([      "action":               
"$N大喝一聲，筆法一變寫出個「將」字，$w一挺撞向$n$l！",
        "damage":                160,
        "damage_type":  "挫傷"
]),
([        "action":
"$N身形微轉，$w向著$n的$l橫掃過去，順勢帶出個「龍」字！",
        "damage":                180,
        "damage_type":                "瘀傷",
]),
([        "action":
"$N高高躍起，手中$w劃出個「壯」字，向著$n的$l撞了過來！",
        "damage":                200,
        "damage_type":                "挫傷",
]),
([        "action":
"$N怒喝一聲，手中$w急舞正是個「騰」字，將$n$l罩于杖下！",
        "damage":        250,
        "damage_type":        "內傷",
]),
});

int valid_learn(object me)
{
        if(me->query_skill("xuantian-zhi",1)<20)
                return notify_fail("你的「玄天指法」不夠嫻熟。\n");
        if ((int)me->query_skill("kuihua-xinfa", 1) < 120)
                return notify_fail("你的葵花心法火候不夠。\n");
        if(me->query("max_neili")<50)
                return notify_fail("你的內力修為不夠。\n");
        return 1;
}

int valid_enable(string usage)
{
        return (usage=="staff") || (usage=="parry");
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon = me->query_temp("weapon")) ||
                (string)weapon->query("skill_type") != "staff" )
                return notify_fail("你必須先找一根木杖或者是類似的武器，才能練杖法。\n");

        if((int)me->query("qi") <40)
                return notify_fail("你的體力不夠練這門杖法，還是先休息休息吧。\n");
        me->receive_damage("qi",40);
        return 1;
}
 
