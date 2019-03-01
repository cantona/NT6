// fanliangyi-dao.c 反兩儀刀法

#include <ansi.h>

inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N手中$w斜指，一招"HIY"「混沌一破」"NOR"，反身一頓，一刀向$n的$l撩去",
        "lvl"    : 0,
        "skill_name" : "混沌一破",
]),
([        "action" : "$N一招"HIC"「太乙生萌」"NOR"，左右腿虛點，$w一提一收，平刃揮向$n的頸部",
        "lvl"    : 20,
        "skill_name" : "太乙生萌",
]),
([        "action" : "$N展身虛步，提腰躍落，一招"BLU"「兩儀合德」"NOR"，刀鋒化作兩股斬向$n",
        "lvl"    : 40,
        "skill_name" : "兩儀合德",
]),
([        "action" : "$N一招"HIW"「日月晦明」"NOR"，$w大開大闔，自上而下劃出一個大弧，筆直劈向$n",
        "lvl"    : 60,
        "skill_name" : "日月晦明",
]),
([        "action" : "$N手中$w一沉，一招"HIR"「無色無相」"NOR"，雙手持刃攔腰反切，砍向$n的胸口",
        "lvl"    : 80,
        "skill_name" : "無色無相",
]),
([        "action" : "$N揮舞$w，使出一招"HIB"「萬劫不復」"NOR"，上劈下撩，左擋右開，齊齊罩向$n",
        "lvl"    : 100,
        "skill_name" : "萬劫不復",
])
});

int valid_enable(string usage)
{
        return usage == "blade" ||
               usage == "parry" ||
               usage == "array";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<150 )
                return notify_fail("你的內力修為不夠，無法修煉。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候太淺。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練反兩儀刀法。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不足，無法練習反兩儀刀法，\n");

        me->receive_damage("qi", 40);
        addn("neili", -41, me);
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
        int d_e1 = 55;
        int d_e2 = 30;
        int p_e1 = 0;
        int p_e2 = -15;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 50;
        int m_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("fanliangyi-dao", 1);
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
                "damage_type" : "割傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point() { return 1; }
string perform_action_file(string action)
{
        return __DIR__"fanliangyi-dao/" + action;
}
/*
int form_array(object leader)
//int perform(object leader, object target)
{
        object *member,ob, weapon;
        int i,j,n;
        int max,min,skill;

        member = leader->query_team();
        if( sizeof(member) != 2 )
                return notify_fail("反兩儀刀共需兩人，少一個多一個都不行。\n");

        j=sizeof (member);
        for (i=0;i<j;i++)
        {
                ob=member[i];
                if( !ob || !living(ob) || query_temp("noliving", ob) ||
                        !ob->is_character())
                {
                        return notify_fail("你想和誰同使反兩儀刀？\n");
                }
                if( query_temp("array/name", ob) )
                {
                        return notify_fail("已經組成刀陣了。\n");
                }
                if (environment(leader)!=environment(ob))
                {
                        return notify_fail("人數不夠兩人。\n");
                }
                if (!ob->query_skill("fanliangyi-dao",1))
                {
                        return notify_fail(ob->name()+"還不會反兩儀刀法。\n");
                }
                if (ob->is_ghost())
                {
                        return notify_fail("只有陽間的人才能組刀陣。\n");
                }

                if( query("max_neili", ob)<50 )
                        return notify_fail(query("name", ob)+"的內力不夠。\n");

                if( (string)ob->query_skill_mapped("force")!= "zixia-shengong")
                        return notify_fail(query("name", ob)+"沒有使用華山派內功。\n");

                if( !(weapon=query_temp("weapon", ob) )
                         || query("skill_type", weapon) != "blade" )
                        return notify_fail(query("name", ob)+"必須拿把刀做武器。\n");

                if( (int)ob->query_skill("fanliangyi-dao",1)<30)
                        return notify_fail(query("name", ob)+"的反兩儀刀法還不夠熟練。\n");

                if( (string)ob->query_skill_mapped("blade")!="fanliangyi-dao")
                        return notify_fail(query("name", ob)+"必須使用反兩儀刀法。\n");

        }

//get the average array skill of the team
        n=0;
        for (i=0;i<j;i++)
        {
                ob=member[i];
                n+=(int)ob->query_skill("fanliangyi-dao",1);
        }
        n/=2;

//get the difference of the array skill,
//first get the max and mix skill level of the array
        max=member[0]->query_skill("fanliangyi-dao",1);
        min=max;
        for (i=0;i<j;i++)
        {
                skill=member[i]->query_skill("fanliangyi-dao",1);
                if(skill>max)
                        max=skill;
                else if(skill<min)
                        min=skill;
        }

//and the leader is important
        n += leader->query_skill("fanliangyi-dao", 1) * 5;
        n /= max - min + 1;
        for (i=0;i<j;i++)
        {
                ob=member[i];
                set_temp("no_quit", 1, ob);

                set_temp("array/name", "fanliangyi-dao", ob);
                set_temp("array/level", n, ob);

                addn_temp("apply/attack", n, ob);
                addn_temp("apply/defense", n, ob);
                addn_temp("apply/damage", n, ob);
                addn_temp("apply/armor", n, ob);
        }
        message_combatd(HIG"$N率領$N站定兩儀方位，頓時兩人之間顯得渾然天成、毫無破綻。\n" NOR, leader);
        return 1;
}
int dismiss_array(object person)
{
        int i,j,n;
        object *member,ob;

        member = person->query_team();
        j=sizeof(member);
        n=query_temp("array/level", person);
        for (i=0;i<j;i++)
        {
                ob=member[i];
                delete_temp("array", ob);
                addn_temp("apply/attack", -n, ob);
                addn_temp("apply/damage", -n, ob);
                addn_temp("apply/defense", -n, ob);
                addn_temp("apply/armor", -n, ob);
                tell_object(ob,"刀陣解散了\n");
        }
}

//if the leader kills enemy, then all members in the array kill enemy
int array_kill(object leader, object enemy)
{
        object *member, ob;
        int i,j;
        member=leader->query_team();
        j=sizeof(member);

        for(i=0;i<j;i++)
        {
                ob=member[i];
                ob->kill_ob(enemy);
        }

        return 1;
}
int effective_level() { return 120;}
*/
int help(object me)
{
        write(HIC"\n反兩儀刀法："NOR"\n");
        write(@HELP

    反兩儀刀法是華山派功夫，兩儀化四象，四象化八卦，正變八
八六十四招，奇變八八六十四招，正奇相合，六十四再以六十四倍
之，共有四千零九十六種變化。天下武功變化之繁，可說無出其右
了。招數雖多，終究不脫于太極化為陰陽兩儀的道理。陽分太陽、
少陰，陰分少陽、太陰，是為四象。太陽為乾兌，少陰為離震，少
陽為巽坎，太陰為艮坤。乾南、坤北、離東、坎西、震東北、兌東
南、巽西南、艮西北。自震至乾為順，自巽至坤為逆。天地定位，
山澤通氣，雷風相薄，水火不相射，八卦相錯。數往者順，知來者
逆。正兩儀劍法，是自震位至乾位的順；華山派反兩儀刀法，則是
自巽位至坤位的逆。

        學習要求：
                紫霞神功50級
                內力300
HELP
        );
        return 1;
}
