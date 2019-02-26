// qiulin-shiye.c 秋林拾葉

inherit SKILL;

string *dodge_msg = ({
        "只見$n略一低頭，形似彎腰拾葉，輕而易舉的躲過$N這一招。\n",
        "但是$n目光流轉，雙肩微動，腳步輕移已避開了$N的攻擊。\n",
        "然而$n微微移步向前，彷彿直走中宮卻又飄忽不定，$N的攻勢全部落空。\n"
        "但是$n身形如竹葉飛舞，隨風繞着$N的出招飄動，好像要擊中，卻若無物。\n",
        "可是$n身隨意轉，彷彿閒庭散步，人卻已在數丈以外，閃過了這一招。\n",
        
        });

int valid_enable(string usage) 
{ 
        return (usage == "dodge") || (usage == "move"); 
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的體力太差了，不能練秋林拾葉。\n");
        me->receive_damage("qi", 30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qiulin-shiye/" + action;
}
