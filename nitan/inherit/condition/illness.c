// illness.c

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
        int need_lvl;
        int need_neili;
        string cname;

        need_lvl = duration + 60;
        need_neili = duration * 10;
        if (me != ob)
                need_lvl = need_lvl * 3 / 2;
        if (me != ob)
                need_neili = need_neili * 3 / 2;

        cname = to_chinese(this_object()->name());
        if (need_lvl > me->query_skill("force"))
        {
                if (me == ob)
                {
                        tell_object(me, "你的內功火候尚有欠缺，無法驅除" + cname +"。\n");
                        return -1;
                } else
                {
                        tell_object(me, "你的內功火候尚有欠缺，無法幫助" + ob->name() + "驅除" + cname + "。\n");
                        return -1;
                }
        }

        if (query("neili", me) < need_neili)
        {
                tell_object(me, "你的內力現在不足，無法施展以驅除" + cname + "。\n");
                return -1;
        }
        addn("neili", -need_neili, me);

        if (me == ob)
        {
                tell_object(me, "調息以後，你舒服多了，感覺" + cname + "被消除了。\n");
        } else
        {
                tell_object(me, "你將內力緩緩的輸入到" + ob->name() + "經脈，" +
                            ob->name() + "精神一振。\n");
                tell_object(ob, "你覺得" + me->name() +
                            "將內力輸入你的奇經八脈，你舒服多了，感覺" + cname + "被消除了。\n");
        }

        ob->clear_condition(this_object()->name());

        return 1;
}