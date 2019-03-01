// eat.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int count;
        string from;
        object from_ob;
        object ob;
        object *guard;
        int search_flag;
        string prefix;
        int need_busy;

        if (! arg)
                return notify_fail("你要吃什麼東西？\n");

        prefix = "";
        need_busy = 0;
        if (sscanf(arg, "%s in %s", arg, from) == 2)
        {
                // 檢查容容具
                if (sscanf(from, "all %s", from))
                {
                        if (me->is_busy())
                                return notify_fail("你忙著呢，沒有功夫找東西。\n");

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
                        return notify_fail(from_ob->name() + "裡面什麼都沒有啊。\n");

                prefix = "從" + from_ob->name() + "中";
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

        if (! undefinedp(count = ob->query_amount()) && count < 1)
                return notify_fail(ob->name() + "已經吃完了。\n");

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
                if( me->query_condition("killer") && query("no_fight", environment(me)) )
                        return notify_fail("被通緝期間無法在安全區食用" + ob->name() + "。\n");

                return ob->do_effect(me);
        } else
        {
                if( !query("food_remaining", ob) )
                        return notify_fail(ob->name() + "已經沒什麼好吃的了。\n");

                if (me->is_fighting())
                {
                        write("你邊打架邊吃東西也不怕弄壞了胃！\n");
                        return 1;
                }
 
                if( query("material", ob) == "plant" )
                {
                        message_vision("$N把$n塞進嘴裡，嚼了幾口吞下肚。\n",
                                       me, ob);
                        destruct(ob);
                        return 1;
                }

                if( query("food", me)>me->max_food_capacity() )
                {
                        write("你已經吃太飽了，再也塞不下任何東西了。\n");
                        return 1;
                }
        
                addn("food",query("food_supply",  ob), me);
        
                set("base_value", 0, ob);
                addn("food_remaining", -1, ob);
                ob->do_effect(me);
                if( query("food_remaining", ob)<1 )
                {
                        message_vision("$N將剩下的" + ob->name() + "吃得幹幹凈凈。\n", me);
                        ob->clear_effect();
                        if (! ob->finish_eat())
                                destruct(ob);
                } else 
                {
                        message_vision("$N" + prefix + "拿出" +
                                       ob->name() + "咬了幾口。\n", me);
                }
        }

        if (! me->is_busy() && need_busy)
                me->start_busy(need_busy);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : eat <食物> | <丹藥> [in [all] <包裹>]
 
這個指令可以讓你吃食物。如果你沒有設置環境變量 careful，並且
你身上沒有帶這種食物就會自動在周圍的環境尋找你指定的食物。

如果你指明了 in， 那麼你將從包裹取出食物食用。倘若你身上沒有
指明的包裹並且沒有設置環境變量 careful 的話， 就會自動在附近
的環境尋找。

如果你指明了 all，那麼你將在身上所有指定的包裹中尋找想要的食
物，這需要花費你一些時間。

see also : drink
 
HELP );
        return 1;
}