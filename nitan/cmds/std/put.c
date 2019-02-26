// put.c

#include <config.h>

inherit F_CLEAN_UP;

int do_put(object me, object obj, object dest);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string target, item;
        object obj, dest, *inv, obj2;
        int i, amount;

        if (! arg) return notify_fail("你要將什麼東西放進哪裏？\n");

        if (sscanf(arg, "%s in %s", item, target) != 2)
                return notify_fail("你要放什麼東西？\n");

        dest = present(target, me);
        if (! dest || living(dest))
                dest = present(target, environment(me));

        if (! dest || living(dest))
                return notify_fail("這裏沒有這樣東西。\n");

        if( query("no_get_from", dest) )
                return notify_fail("還是不要打擾人家了。\n");

        if (sscanf(item, "%d %s", amount, item) == 2)
        {
                if (! objectp(obj = present(item, me)))
                        return notify_fail("你身上沒有這樣東西。\n");

                if (! obj->query_amount())
                        return notify_fail( obj->name() + "不能被分開。\n");

                if (amount < 1)
                        return notify_fail("東西的數量至少是一個。\n");

                if (amount > obj->query_amount())
                        return notify_fail("你沒有那麼多的" + obj->name() + "。\n");
                else
                if (amount == (int) obj->query_amount())
                        return do_put(me, obj, dest);
                else
                {
                        obj->set_amount((int) obj->query_amount() - amount);
                        obj2 = new(base_name(obj));
                        obj2->set_amount(amount);
                        obj2->move(me, 1);
                        return do_put(me, obj2, dest);
                }
        }

        if (item == "all")
        {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                        if (inv[i] != dest)
                                do_put(me, inv[i], dest);
                write("Ok.\n");
                return 1;
        }

        if (! objectp(obj = present(item, me)))
                return notify_fail("你身上沒有這樣東西。\n");
        return do_put(me, obj, dest);
}

int do_put(object me, object obj, object dest)
{
        mixed msg;

        if (! dest->is_container() && ! dest->is_character())
        {
                tell_object(me, dest->name() + "不是容器。你不能把東西放進去。\n");
                return 1;
        }

        if (dest->is_character() &&
            sizeof(filter_array(all_inventory(dest),(:!query("equipped", $1):))) >= MAX_ITEM_CARRIED )
        {
                tell_object(me, dest->name() + "裏面的東西實在"
                            "是太多了，你沒法再放東西了。\n");
                return 1;
        } else
        if (dest->is_container() && sizeof(all_inventory(dest)) >= MAX_ITEM_CARRIED &&
            ! dest->no_limit_amount())
        {
                tell_object(me, dest->name() + "裏面的東西實在"
                            "是太多了，你先好好整理整理吧。\n");
                return 1;
        } else
        if (dest->is_container() && dest->no_limit_amount() &&
            (sizeof(all_inventory(dest)) >= 200 || 
            obj->is_character() || query("unique", obj) || obj->is_no_clone()) || 
            query("money_id", obj) )
        {
                tell_object(me, dest->name() + "裏面不可以放入"
                            "這個東西或者有可能是你的容器裏的東西太多了。\n");
                return 1;
        } else
        if (dest->is_container() &&
            (sizeof(all_inventory(dest)) >= MAX_ITEM_CARRIED || 
            obj->is_character() || query("unique", obj) || obj->is_no_clone()) || 
            query("money_id", obj) )
        {
                tell_object(me, dest->name() + "裏面不可以放入"
                            "這個東西或者有可能是你的容器裏的東西太多了。\n");
                return 1;
        }

        if( !undefinedp(msg=query("no_put", obj)) )
        {
                if (stringp(msg))
                        tell_object(me, msg);
                else
                        tell_object(me, "這個東西不要亂放。\n");
                return 1;
        }

        if( obj == query_temp("is_riding", me) )
        {
                tell_object(me, "你無法把" + obj->name() + "塞進去，你正騎着它呢。\n");
                return 1;
        }

        switch(query("equipped", obj) )
        {
        case "worn": 
                tell_object(me, obj->name() + "必須脱下來才能放進去。\n"); 
                return 1; 
        case "wielded": 
                tell_object(me, obj->name() + "必須解除裝備才能放進去。\n"); 
                return 1; 
        }

        if (obj->is_corpse())
        {
                tell_object(me, "你無法把" + obj->name() + "塞進去。\n");
                return 1;
        }

        if (playerp(obj))
        {
                tell_object(me, "你無法把" + obj->name() + "塞進去。\n");
                return 1;
        }

        if (obj == dest)
        {
                tell_object(me, "嗯... 自己套自己，你的想法比較有趣。\n");
                return 1;
        }

        if (obj->move(dest))
        {
                if (dest->no_limit_amount())
                        dest->save();
                message_vision(sprintf("$N將一%s%s放進%s。\n",
                               query("unit", obj),obj->name(),
                               dest->name()), me);
                return 1;
        }

        // 放回到我的身上來
        if (! environment(obj))
                // 這是分離的物品，沒有分離成功
                obj->move(me, 1);

        return 0;
}

int help(object me)
{
        write(@HELP
指令格式 : put <物品名稱> in <某容器>
 
這個指令可以讓你將某樣物品放進一個容器，當然，首先你要擁有這樣物品。
 
HELP );
        return 1;
}
