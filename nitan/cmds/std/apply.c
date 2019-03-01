// apply.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int count;
        object ob;
        object *guard;

        if (! arg)
                return notify_fail("你要使用什麼東西？\n");

        if (! objectp(ob = present(arg, me)))
        {
                ob = present(arg, environment(me));

                if (! objectp(ob))
                        return notify_fail("你身上沒有這樣東西，附近也沒有。\n");
        }

        if (! undefinedp(count = ob->query_amount()) && count < 1)
                return notify_fail(ob->name() + "已經用完了。\n");

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

        if( query("can_be_applied", ob) )
        {
                return ob->do_apply(me);
        } else
                return notify_fail("怎麼用" + ob->name() + "？\n");

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : apply <物品>

這個指令可以讓你是用特殊物品，發揮它的功效。
 
HELP );
        return 1;
}