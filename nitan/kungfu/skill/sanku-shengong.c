// This program is a part of NITAN MudLIB
// biyun-xinfa.c 

inherit FORCE;
int valid_force(string force) { return 1; }       

int query_neili_improve(object me)  
{
        int lvl; 
        lvl = (int)me->query_skill("sanku-shengong", 1); 
        return lvl * lvl * 21 * 15 / 100 / 200; 
}

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_learn(object me)
{        
        if (me->query_skill("force", 1) < 40)
                return notify_fail("你的基本內功太差了。\n");
        if( query("gender", me) == "無性" && me->query_skill("sanku-shengong",1)>49 )
                return notify_fail("唐門不要你這種無根無性的人，你無法領會高深的三苦神功。\n");
              
        return ::valid_learn(me);
}
 
int practice_skill(object me)
{
        return notify_fail("三苦神功只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"sanku-shengong/" + func;
}           
