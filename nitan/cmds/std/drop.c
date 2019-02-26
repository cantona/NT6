// drop.c

#include <config.h>

inherit F_CLEAN_UP;

int do_drop(object me, object obj, int raw);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj, *inv, obj2;
        int i, amount;
        mixed info;
        string item;

        if (! arg)
                return notify_fail("你要丟下什麼東西？\n");

        if (sscanf(arg, "%d %s", amount, item) == 2)
        {
                if (! objectp(obj = present(item, me)))
                        return notify_fail("你身上沒有這樣東西。\n");

                if( info=query("no_drop", obj) )
                        return notify_fail(stringp(info) ? info : "這樣東西不能丟棄。\n");

                if (! obj->query_amount())
                        return notify_fail( obj->name() + "不能被分開丟棄。\n");

                if (amount < 1)
                        return notify_fail("東西的數量至少是一個。\n");

                if (amount > obj->query_amount())
                        return notify_fail("你沒有那麼多的" + obj->name() + "。\n");
                else if (amount == (int)obj->query_amount())
                        return do_drop(me, obj, 0);
                else
                {
                        obj->set_amount((int)obj->query_amount() - amount);
                        obj2 = new(base_name(obj));
                        obj2->set_amount(amount);
                        if (! do_drop(me, obj2, 0))
                        {
                                obj2->move(me);
                                return 0;
                        }
                        return 1;
                }
        }

        if (arg == "all")
        {
                inv = all_inventory(me);
                for(amount = 0, i = 0; i < sizeof(inv); i++)
                {
                        if (! living(me)) break;
                        amount += do_drop(me, inv[i], 1);
                }

                if (! amount)
                {
                        write("你什麼都沒有丟掉。\n");
                        return 1;
                }

                message("vision", me->name() + "丟下了一堆東西。\n",
                        environment(me), ({ me }));
                write("丟完了。\n");
                return 1;
        }

        if (! objectp(obj = present(arg, me)))
                return notify_fail("你身上沒有這樣東西。\n");

        do_drop(me, obj, 0);
        return 1;
}

int do_drop(object me, object obj, int raw)
{
        mixed no_drop;
        object riding;

        if( obj == (riding=query_temp("is_riding", me)) )
        {
                message_vision("$N從$n背上飛身跳下。\n", me, riding);
                delete_temp("is_riding", me);
                delete_temp("is_rided_by", obj);
                obj->move(environment(me));
                return 1;
        }

        if( no_drop=query("no_drop", obj) )
                return notify_fail(stringp(no_drop) ? no_drop : "這樣東西不能隨意丟棄。\n");

        if( no_drop=query("no_drop", environment(me)) )
                return notify_fail(stringp(no_drop) ? no_drop : "這裏東西丟棄下去也看不見。\n");

        switch(query("equipped", obj) )
        {
        case "worn":
                tell_object(me, obj->name() + "必須脱下來才能丟掉。\n");
                return 0;

        case "wielded":
                tell_object(me, obj->name() + "必須解除裝備才能丟掉。\n");
                return 0;
        }

        if (! obj->is_character() &&
            ! obj->can_combine_to(environment(me)) &&
            sizeof(filter_array(all_inventory(environment(me)),
                                (: ! $1->is_character() :))) > MAX_ITEM_IN_ROOM)
        {
                tell_object(me, "這裏東西太多了，你亂丟恐怕" + obj->name() + "就找不到了。\n");
                return 0;
        }

        if (obj->move(environment(me)))
        {
                if (obj->is_character() && obj->query_weight() > 20000)
                        message_vision("$N將$n從背上放了下來，躺在地上。\n", me, obj);
                else
                {
                        if (! raw)
                                message_vision(sprintf("$N丟下一%s$n。\n",
                                                       query("unit", obj)),me,obj);
                        else
                                write("你丟下了一"+query("unit", obj)+
                                      obj->name() + "\n");

                        if( !obj->is_character() && !query("value", obj) && !obj->value() )
                        {
                                write("因為這樣東西並不值錢，所以人們並不會注意到它的存在。\n");
                                destruct(obj);
                        }
                }
                return 1;
        }

        return 0;
}

int help(object me)
{
        write(@HELP
指令格式 : drop <物品名稱> | all
 
這個指令可以讓你丟下你所攜帶的物品.
 
HELP );
        return 1;
}