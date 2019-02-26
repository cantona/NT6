// drink.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string from;
        object from_ob;
        object ob;
        object *guard;
        int search_flag;
        string prefix;
        int need_busy;

        if (! arg)
                return notify_fail("你要喝什麼東西？\n");

        if (sscanf(arg, "%s in %s", arg, from) == 2)
        {
                // 檢查容具
                if (sscanf(from, "all %s", from))
                {
                        if (me->is_busy())
                                return notify_fail("你忙着呢，沒有功夫找東西。\n");

                        search_flag = 0;
                        foreach (from_ob in all_inventory(me))
                        {
                                if (! from_ob->id(from))
                                        continue;

                                if (from_ob->is_character())
                                        continue;

                                if (! present(arg, from_ob))
                                        continue;

                                search_flag = 1;
                                break;
                        }

                        if (! search_flag)
                        {
                                me->start_busy(2);
                                return notify_fail("你翻遍了身上帶的東西，也沒找到想要的。\n");
                        } else
                                need_busy = 3;
                } else
                if (! objectp(from_ob = present(from, me)))
                {
                        from_ob = present(from, environment(me));
                        if( query("env/careful", me) )
                        {
                                if (! objectp(from_ob))
                                        return notify_fail("你身上沒有這個容具。\n");
                                else
                                        return notify_fail("你身上沒有這樣容具，附近的" +
                                                           from_ob->name() + "你又不敢動。\n");
                        }
        
                        if (! objectp(from_ob))
                                return notify_fail("你身上沒有這樣容具，附近也沒有。\n");
                }

                if (from_ob->is_character() && from_ob != me)
                        return notify_fail("你要搶劫啊？\n");
                else
                if (sizeof(all_inventory(from_ob)) < 1)
                        return notify_fail(from_ob->name() + "裏面什麼都沒有啊。\n");
        } else
                from_ob = me;

        if (! objectp(ob = present(arg, from_ob)))
        {
                ob = present(arg, environment(me));
                if( query("env/careful", me) )
                {
                        if (! objectp(ob))
                                return notify_fail("你身上沒有這樣東西。\n");
                        else
                                return notify_fail("你身上沒有這樣東西，附近的" +
                                                   ob->name() + "你又不敢動。\n");
                }

                if (! objectp(ob))
                        return notify_fail("你身上沒有這樣東西，附近也沒有。\n");
        }

        if (me->is_busy())
        {
                write("你上一個動作還沒有完成。\n");
                return 1;
        }

        if( guard=query_temp("guarded", ob) )
        {
                guard = filter_array(guard, (:
                        objectp($1) && present($1, environment($(me))) &&
                        living($1) && ($1 != $(me)) :));
                if (sizeof(guard))
                        return notify_fail(guard[0]->name()
                                + "正守在" + ob->name() + "一旁，防止任何人拿走。\n");
        }

        if( query("only_do_effect", ob) )
        {
                if( !query("can_drink", ob) )
                {
                        write(ob->name() + "怎麼喝？\n");
                        return 1;
                }

                return ob->do_effect(me);
        }

        if( !mapp(query("liquid", ob)) )
                return notify_fail("你不知道怎麼喝" + ob->name() + "... :)\n");

        if (me->is_fighting())
        {
                write("你邊打架邊喝東西也不怕嗆着？\n");
                return 1;
        }

        if( !query("liquid/remaining", ob) )
        {
                write(ob->name()+(query("liquid/name", ob)?
                      "裏的"+query("liquid/name", ob)+"已經被喝得一滴也不剩了。\n":
                      "是空的。\n"));
                if( query("env/auto_drinkout", me) && 
                    environment(ob) != environment(me))
                {
                        message_vision("$N丟下一個$n。\n", me, ob);
                        ob->move(environment(me));
                }
                return 1;
        }

        if( query("water", me)>me->max_water_capacity() )
        {
                write("你已經喝太多了，再也灌不下一滴水了。\n");
                return 1;
        }

        addn("liquid/remaining", -1, ob);
        message_vision("$N拿起" + ob->name() + "咕嚕嚕地喝了幾口" +
                       query("liquid/name", ob)+"。\n",me);
        addn("water", 30, me);

        ob->do_effect();
        if( !query("liquid/remaining", ob) )
        {
                write("你已經將"+ob->name()+"裏的"+query("liquid/name", ob )
                        + "喝得一滴也不剩了。\n");
                ob->clear_effect();
                if( query("env/auto_drinkout", me) && 
                    environment(ob) == me)
                {
                        message_vision("$N丟下一個$n。\n", me, ob);
                        ob->move(environment(me));
                }
                return 1;
        }

        switch(query("liquid/type", ob) )
        {
        case "alcohol":
                me->apply_condition("drunk",
                        (int)me->query_condition("drunk") +
                        query("liquid/drunk_apply", ob));
                break;
        }

        if (! me->is_busy() && need_busy)
                me->start_busy(need_busy);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : drink <容器> [in [all] <包裹>]
 
這個指令可以讓你喝容器裏面的液體。如果你沒有設置變量 careful，
並且你身上沒有帶這種容器就會自動在周圍的環境尋找你指定的容器。

如果你指明瞭 in， 那麼你將從包裹取出容器飲用。倘若你身上沒有
指明的包裹並且沒有設置環境變量 careful 的話， 就會自動在附近
的環境尋找。

如果你指明瞭 all，那麼你將在身上所有指定的包裹中尋找想要的容
器，這需要花費你一段時間。

see also : eat

HELP );
        return 1;
}