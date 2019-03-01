// pour.c

inherit F_CLEAN_UP;

int do_effect(string type, mixed para);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string item, target;
        object obj, dest;
        function f;

        if (! arg)
                return notify_fail("你要下什麼毒？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再想怎麼害人吧！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if (sscanf(arg, "%s in %s", item, target) != 2)
                return notify_fail("你要往哪裡下毒？\n");

        dest = present(target, me);
        if (! dest) return notify_fail("這裡沒有這樣東西。\n");

        if (! objectp(obj = present(item, me)))
                return notify_fail("你身上沒有這樣東西。\n");

        if( !stringp(query("poison_type", obj)) )
                return notify_fail("這不是毒藥啊。\n");

        if( !query("can_pour", obj) )
                return notify_fail("這種毒藥不能溶在水裡。\n");

        if( query("liquid/remaining", dest)<1 )
        {
                tell_object(me, "裡面一點喝的都沒有是不能下毒的。\n");
                return 1;
        }

        message("vision", sprintf("%s將一些東西偷偷放進%s，搖了一搖。\n",
                me->name(), dest->name()), environment(me), ({ me }));

        message("vision", sprintf("你將一%s%s偷偷放進%s，搖了一搖。\n",
                query("unit", obj),obj->name(),dest->name()),me);

        
        f = bind((: call_other, __FILE__, "do_effect",
                    query("poison_type", obj),
                    query("poison", obj):),dest);
        dest->apply_effect(f);
        if (obj->query_amount() > 1)
                obj->add_amount(-1);
        else
                destruct(obj);
        return 1;
}

int do_effect(string type, mixed para)
{
        object me = this_player();
        mapping p;

        if (! objectp(me))
                return 1;

        if (mapp(para))
        {
                p = allocate_mapping(4);
                p["level"] = para["level"];
                p["id"]    = para["id"];
                p["name"]  = para["name"];
                p["duration"] = para["duration"] / 2 +
                                random(para["duration"] / 2);
                me->affect_by(type, p);
        } else
        {
                int old;
                if (intp(para) && intp(old = me->query_condition(type)))
                        me->apply_condition(type, para + old);
                else
                        me->apply_condition(type, para);
        }

        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : pour <毒藥> in <容器>
 
這個指令可以讓你將某樣毒品放進一個容器，當然，首先你要擁有這樣物品。
容器裡有喝的東西。
HELP
    );
    return 1;
}