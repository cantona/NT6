// wash.c

#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string target;
        object dest;
        string msg;
        int remain;

        if (!arg)
                return notify_fail("你要洗什麼？\n");

        target = arg;

        if( !query("resource/water", environment(me)) )
                return notify_fail("這裡沒水，你怎麼洗？\n");

        if (me->is_busy())
                return notify_fail("先忙玩了你的事情再洗吧！\n");

        if (me->is_fighting())
                return notify_fail("你還是打完了架再洗吧！\n");

        if (target == "hand" || target == "me")
        {
                // washing me
                dest = me;
        } else
        {
                dest = present(target, me);
                if (! dest) dest = present(target, environment(me));
                if (! dest)
                        return notify_fail("這裡沒有這樣東西。\n");

                if (dest->is_character())
                {
                        if (dest != me)
                        {
                                dest->force_me("chat*rascal"+query("id", me));
                                return notify_fail("你要給人家" + dest->name() +
                                                   "洗澡？\n");
                        }
                        // daub on me
                } else
                if( !mapp(query("armor_prop", dest)) && 
                    !mapp(query("weapon_prop", dest)) )
                {
                        return notify_fail("那既不是武器，也不是防具，"
                                           "你有什麼好清洗的？\n");
                }
        }

        if( remain=query_temp("daub/poison/remain", dest) )
        {
                if (remain > 10000)
                        msg = "，只見洗完的水變得腥臭無比，令人掩鼻。\n";
                else
                if (remain > 4000)
                        msg = "，就見那水忽的變了顏色，碧汪汪的，氣味古怪。\n";
                else
                if (remain > 1000)
                        msg = "，清水隨即色變，散發出一種難聞的氣味。\n";
                else
                        msg = "，洗後水的顏色變得有點不對。\n";
        } else
                msg = "。\n";

        delete_temp("daub", dest);
        if (dest == me)
        {
                message_vision("$N好好的洗了洗手" + msg, me);
                return 1;
        }

        if( query("equipped", dest) == "worn" )
        {
                function f;

                if (! REMOVE_CMD->do_remove(me, dest))
                        return 0;

                if (! dest || ! me)
                        return 1;

                message_vision("$N將脫下來的$n好好的洗了洗" + msg, me, dest);
                dest->washed(120 + random(120));
                return 1;
        }

        message_vision("$N拿出$n，好好的洗了洗" + msg, me, dest);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : wash <武器> | <防具> | hand

這個指令可以讓你將武器、防具好好沖洗一下，以清除上面的毒。當然沒有
毒清洗它也不是什麼壞事。
HELP
    );
    return 1;
}