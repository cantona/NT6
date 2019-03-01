// daub.c

#include <ansi.h>

inherit F_CLEAN_UP;

// the flag that wether I know there is some poison on the object
#define I_KNOW                  1
#define I_DONT_KNOW             0

void check_poison(object me, object dest, int iknow);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string item, target;
        object obj, dest;

        if (!arg)
                return notify_fail("你要往哪兒塗抹毒藥？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再想怎麼害人吧！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if (sscanf(arg, "with %s", item) == 1)
                target = "hand";
        else
        if (sscanf(arg, "%s with %s", target, item) == 2)
                ;
        else
        if (sscanf(arg, "%s on %s", item, target) == 2)
                ;
        else
                return notify_fail("你要往哪兒塗抹毒藥？\n");

        if (! present("hand", me) && target == "hand" ||
            target == "me")
        {
                // daub on me
                dest = me;
        } else
        {
                dest = present(target, me);
                if (! dest) dest = present(target, environment(me));
                if (! dest)
                        return notify_fail("這裡沒有這樣東西。\n");

                if (dest->is_character())
                {
                        if (dest != me && ! dest->is_corpse())
                        {
                                return notify_fail("你往" + dest->name() +
                                                   "上面塗什麼，找扁啊？\n");
                        }
                        // daub on me
                } else
                if( !mapp(query("armor_prop", dest)) && 
                    !mapp(query("weapon_prop", dest)) )
                {
                        return notify_fail("那既不是武器，也不是防具，"
                                           "你怎麼塗抹毒藥呢？\n");
                }
        }

        if (!objectp(obj = present(item, me)))
                return notify_fail("你身上沒有這樣東西。\n");

        if( !stringp(query("poison_type", obj)) )
                return notify_fail(obj->name() + "不是毒藥啊。\n");

        if( query("poison/name", obj) == "唐門奇毒" && !query("reborn", me) && 
            (!query("family", me) || query("family/family_name", me) != "唐門世家") )
                return notify_fail(obj->name() + "毒性強烈，你必須知曉唐門獨特下毒技巧才能使自己不被傷害。\n");

        if( !query("can_daub", obj) )
                return notify_fail("這種毒藥不能用來塗抹。\n");

        set_temp("daub/who_id",query("id",  me), dest);
        set_temp("daub/who_name",query("name",  me), dest);
        set_temp("daub/poison_name", obj->name(), dest);
        set_temp("daub/poison_type",query("poison_type",  obj), dest);
        set_temp("daub/poison",
                POISON->mixed_poison(query_temp("daub/poison", dest),query("poison", obj)), dest);
        if (dest == me)
        {
                message("vision", sprintf("%s拿出一些東西在自己身上塗來"
                                          "抹去的，不知道在幹什麼。\n",
                                          me->name()), environment(me), ({ me }));
                tell_object(me, HIG "你把" + obj->name() + HIG "塗抹到自己手上。\n" NOR);
                check_poison(me, dest, I_KNOW);
                destruct(obj);
                return 1;
        }

        message("vision", sprintf("%s拿出一些東西塗抹在%s上面。\n",
                                  me->name(), dest->name()),
                          environment(me), ({ me }));
        tell_object(me, HIG "你把" + obj->name() + HIG "塗抹到" + dest->name() + HIG "上。\n" NOR);
        if( query("equipped", dest) == "worn" && 
            query("armor_type", dest) != "hands" && 
            environment(dest) == me)
        {
                // daub on armor that I am wearing
                check_poison(me, dest, I_KNOW);
        }

        if (obj->query_amount() > 1)
                obj->add_amount(-1);
        else
                destruct(obj);
        return 1;
}

// check wether I can sufface the poison
void check_poison(object me, object dest, int iknow)
{
        string name;
        string type;
        mapping p;
        int lvl;

        if (! dest) dest = me;
        name=query_temp("daub/poison_name", dest);
        type=query_temp("daub/poison_type", dest);
        p=query_temp("daub/poison", dest);
        if (! name || ! p || ! type) return;

        if( p["id"] == query("id", me) )
                // The poison is made by me
                return;

        lvl = me->query_skill("force") + query("poison", me) / 2;
        if (lvl < 100 || lvl < (int)p["level"])
        {
                message("vision", HIC "忽然" + me->name() + HIC "眉頭"
                                  "緊縮，神情痛苦，看來是遇到麻煩了。\n" NOR,
                                  environment(me), ({ me }));
                tell_object(me, HIC "忽然你覺得有點不對勁，不好，可能是中毒了。\n" NOR);
                me->affect_by(type, p);
                delete_temp("daub", dest);
                return;
        }

        message("vision", HIC + me->name() + HIC "眉頭"
                          "微微一皺，隨即舒展開來。\n" NOR,
                          environment(me), ({ me }));

        if (p["level"] > 120)
        {
                if (iknow)
                        tell_object(me, HIC "你發現這" + name + HIC "毒性甚"
                                        "是猛烈，幸好內功高深，抵擋得住。\n" NOR);
                else
                        tell_object(me, HIC "你發現這" + dest->name() + HIC "上的" +
                                        name + HIC "毒性甚"
                                        "是猛烈，虧得你內功高深，才幸免無事。\n" NOR);
        } else
        if( !iknow && query_temp("who_id", dest) != query("id", me) )
        {
                tell_object(me, HIC "你發現這" + name + HIC "上面帶毒。\n" NOR);
        }
}

int help(object me)
{
write(@HELP
指令格式 : daub <毒品名稱> on <武器> | <防具> | hand
           daub <武器> | <防具> | [hand] with <毒品名稱>

這個指令可以讓你將某樣毒品塗抹到武器上，防具或是手上，當然，塗抹到
防具或是手上的的毒最好不要使自己中毒。
HELP
    );
    return 1;
}
