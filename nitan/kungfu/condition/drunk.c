// drunk.c

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
        int need_lvl;

        need_lvl = duration + 50;
        if (me != ob)
                need_lvl = need_lvl * 3 / 2;;

        if (need_lvl > me->query_skill("force"))
        {
                if (me == ob)
                {
                        tell_object(me, "你的內功火候尚有欠缺，無法消除醉酒的影響。\n");
                        return -1;
                } else
                {
                        tell_object(me, "你的內功火候尚有欠缺，無法幫助" + ob->name() + "消除醉酒的影響。\n");
                        return -1;
                }
        }

        if (me == ob)
        {
                tell_object(me, "調息以後，你清醒多了，再沒有半點醉酒的感覺。\n");
        } else
        {
                tell_object(me, "你將內力緩緩的輸入到" + ob->name() + "經脈，" +
                            ob->name() + "精神一振。\n");
                tell_object(ob, "你覺得" + me->name() +
                            "將內力輸入你的奇經八脈，你清醒多了，再沒有醉酒的感覺。\n");
        }

        ob->clear_condition("drunk");

        return 1;
}

int update_condition(object me, int duration)
{
        int limit;

        limit = (query("con", me) + query("max_neili", me) / 50) * 2;

        if (duration > limit && living(me))
        {
                me->unconcious();
                return 0;
        } else if (!living(me))
        {
                message("vision", me->name() + "打了個隔，不過依然爛醉如泥。\n",
                        environment(me), me);
        } else if (duration > limit / 2)
        {
                tell_object(me, "你覺得腦中昏昏沉沉，身子輕飄飄地，大概是醉了。\n");
                message("vision", me->name() + "搖頭晃腦地站都站不穩，顯然是喝醉了。\n",
                        environment(me), me);
                me->receive_damage("jing", 10);
        } else if (duration > limit/4)
        {
                tell_object(me, "你覺得一陣酒意上衝，眼皮有些沉重了。\n");
                message("vision", me->name() + "臉上已經略顯酒意了。\n",
                        environment(me), me);
                me->receive_healing("jing", 10);
                me->receive_healing("qi", 15);
        }

        me->apply_condition("drunk", duration - 1);
        if (! duration) return 0;
        return 1;
}