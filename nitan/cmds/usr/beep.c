// beep.c

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        object obj;
        string no_tell, can_tell;

        if( (query("jing", me)<50) && (!wizardp(me)) )
                return notify_fail("你現在精神不佳，歇會吧。\n");

        if (me->is_busy()) 
                return notify_fail("你現在正忙着呢。\n");
 
        if (! arg || arg == "")
                return notify_fail("你是打算呼叫誰？\n");

        if( arg == query("id", me) )
                return notify_fail("你打算呼叫自己？\n");

        obj = find_player(arg);

        if (! obj || ! me->visible(obj)) 
                return notify_fail("沒有這個人。\n");

        no_tell=query("env/no_tell", obj);

          if (wizardp(obj)
               && query("env/invisible", obj )
              && wiz_level(obj) >= wiz_level(me))
                return notify_fail("沒有這個人。\n");

        if (! wizardp(me) && (no_tell == "all" || no_tell == "ALL" ||
            is_sub(query("id", me),no_tell)) )
        {
                can_tell=query("env/can_tell", obj);
                if( !is_sub(query("id", me),can_tell) )
                        return notify_fail("這個人不想聽你羅嗦啦。\n");
        }

        message_vision(HIC "$N" HIC "弄出一陣刺耳的聲響～～～～～\n" NOR, me);
        tell_object(obj, HIW "只聽「叮叮叮叮」響個不停，原來是" + me->query_idname(1) +
                         HIW "有事找你。\n" BEEP BEEP NOR);

        call_out("do_beep", 1, obj);
        call_out("do_beep", 2, obj);
        call_out("do_beep", 3, obj);
        call_out("do_beep", 4, obj);

        if (! wizardp(me))
        {
                me->start_busy(2); 
                me->receive_damage("jing", 50);
        }
        return 1;
}

int do_beep(object obj)
{
        if (! obj) return 1;
        // tell_object(obj, BEEP);
        tell_object(obj, "\a", 0);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：beep <某人>

只要念出這段傳音咒，你想呼叫的人的音箱內便會有提示音發出。

HELP);
        return 1;
}
