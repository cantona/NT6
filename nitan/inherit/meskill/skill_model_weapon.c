int valid_learn(object me)
{
        object weapon;
        string creater;

        if( (int)me->query("max_neili") < 50 )
                return notify_fail("你的內力不夠，沒有辦法練"+SKILL_CH_NAME+"。\n");
        if (!objectp(weapon = me->query_temp("weapon")) ||
                (string)weapon->query("skill_type") != SKILL_BASE_NAME)
                return notify_fail("你使用的武器不對。\n");
        creater = this_object()->owner();
        if (userp(me) &&
        me->query("id")!=creater && 
        me->query("couple/couple_id")!=creater)
        return notify_fail("不能向其他玩家學習自創的武功。\n");
        return 1;
}
int valid_enable(string usage)
{
        return usage==SKILL_BASE_NAME || usage=="parry";
}
int practice_skill(object me)
{
        object weapon; 
        string skname=explode(__FILE__,"/")[<1][0..<3];
        int lvl = me->query_skill(skname,1);
        int i=sizeof(action);
        int qicost;
        int nlcost;
        
        qicost = (M_E1 + M_E2)/10;
        nlcost = (F_E1 + F_E2)/15;
        if (!objectp(weapon = me->query_temp("weapon")) ||
                (string)weapon->query("skill_type") != SKILL_BASE_NAME)
                return notify_fail("你使用的武器不對。\n");        
        if( (int)me->query("qi") < qicost )
                return notify_fail("你的體力不夠了，休息一下再練吧。\n");
        if( (int)me->query("neili") < nlcost )
                return notify_fail("你的內力不夠了，休息一下再練吧。\n");
        me->receive_damage("qi", qicost);
        me->add("neili", -nlcost);
        if (lvl>=action[i-1]["lvl"]+20)
                return notify_fail("這一招你已經練到頂了，該鑽研鑽研新的招式了。\n");
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
        int d_e1 = D_E1;
        int d_e2 = D_E2;
        int p_e1 = P_E1;
        int p_e2 = P_E2;
        int f_e1 = F_E1;
        int f_e2 = F_E2;
        int m_e1 = M_E1;
        int m_e2 = M_E2;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill(SKILL_EN_NAME, 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割傷" : "刺傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__+SKILL_EN_NAME+"/" + action;
}
int help(object me)
{
        write(HIC"\n"+SKILL_CH_NAME+"："NOR"\n");
        write(@HELP
SKILL_HELP
HELP
        );
        return 1;
}