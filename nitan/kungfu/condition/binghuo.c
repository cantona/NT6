// binghuo.c

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if( !living(me) || query_temp("noliving", me) )
                message("vision", me->name() + "打了個嗝，口裏吐出一股藍紅之氣。\n", environment(me), me);
        else
                message("vision", me->name() + "搖頭晃腦地站都站不穩，手心盡是藍紅的斑點。\n", environment(me), me);

        me->apply_condition("binghuo", duration - 1);
        if( !duration ) return 0;
        return 1;
}

string query_type(object me)
{
        return "drunk";
}
