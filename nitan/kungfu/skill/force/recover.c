// recover.c

int exert(object me, object target)
{
        int n, q;

        if (me != target)
                return notify_fail("你只能用內功調勻自己的氣息。\n");

        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠。\n");

        q=query("eff_qi", me)-query("qi", me);
        if (q < 10)
                return notify_fail("你現在氣力充沛。\n");
        n = 100 * q / me->query_skill("force");
        if( query("special_skill/self", me) )
                n = n * 7 / 10;
        if( query("breakup", me) )
                n = n * 7 / 10;
        if (n < 20)
                n = 20;
        if( query("neili", me)<n )
        {
                if (q > 1000000)
                        q=q/n*query("neili", me);
                else
                        q=q*query("neili", me)/n;

                n=query("neili", me);
        }

        addn("neili", -n, me);
        if (q < 1) q = 1;
        me->receive_heal("qi", q);
        
        message_vision("$N深深吸了幾口氣，臉色看起來好多了。\n", me);

        if( me->is_fighting() && !query("special_skill/self", me))me->start_busy(1);
        
        return 1;
}