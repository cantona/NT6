inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("changsheng-jue", 1);
        return lvl * lvl * 15 * 22 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("changsheng-jue", 1);

        if( query("character", me) != "狡黠多變" )
                return notify_fail("你心中暗想：這不過是道家練氣的口訣罷了，哪裡是什麼神功？\n");

        if( query("int", me)<35 )
                return notify_fail("你覺得長生決過于艱深，難以理解。\n");

        if( query("con", me)<31 )
                return notify_fail("依照你的根骨無法修煉長生決。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("你的武學修養沒有辦法理解其中的精神奧義。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("長生決只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"changsheng-jue/" + func;
}
