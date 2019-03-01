// emote.c (Mon  09-04-95)

#include <ansi.h>

inherit F_CLEAN_UP;
 
int main(object me, string str)
{
        string prefix;
        object env;
        mixed info;

        if (me->ban_say())
                return 0;

        env = environment(me);
        if( info=query("no_say", env) )
        {
                if (stringp(info))
                {
                        write(info);
                        return 1;
                }

                write("這個地方不能亂做動作。\n");
                return 1;
        }

        if( query("doing", me) == "scheme" )
        {
                if( query("jing", me)<100 )
                        return notify_fail("你現在的精神不濟，等一會兒吧。\n");
                addn("jing", -50, me);
        }

        if (! str)
        {
                write(CYN"你看起來表情豐富。\n"NOR);
                tell_room(env, CYN + (string)me->name()+
                          "看起來表情豐富。\n" + NOR, me);
                return 1;
        }

        prefix=query("env/no_prefix", me)?"":"~";
        write(CYN "你" + str + "\n" NOR);
        tell_room(env, CYN + prefix + (string)me->name() +
                  str + "\n" NOR, me);
        return 1;
}
 
int help(object me)
{
        write(@HELP
指令格式: emote <動作詞>

這個指令可以讓你表達一個系統沒有預設的動作詞, 系統會將你所輸入
的文字加上你的姓名後顯示給所有在同一個地方的生物看。為了避免造
成困擾, 玩家所輸入的詞句前面會加上 ~ 以供區別。

范例: emote 坐了下來。
你會看見: 你坐了下來。
其他人會看到: ~包子坐了下來。

其中, 包子就是你的名字.

相關指令: semote
HELP );
        return 1;
}