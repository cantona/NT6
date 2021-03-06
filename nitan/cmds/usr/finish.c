// quest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

        if (! arg || arg == "")
                return notify_fail("你要向誰領取任務獎勵？\n");
        
        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("這裏沒有這個人，你怎麼領獎勵？\n");

        if (! living(ob))
                return notify_fail("你還是等" + ob->name() +
                                   "醒了再説吧！\n");

        if (me->is_fighting())
                return notify_fail("專心打你的架！\n");

        if (me->is_busy())
                return notify_fail("你還是有空了再和" + ob->name() +
                                   "談這些問題吧！\n");

        if (ob->is_fighting())
                return notify_fail("你還是等" + ob->name() +
                                   "打完架再説吧！\n");

        if (ob->is_busy())
                return notify_fail(ob->name() +
                                   "正忙着呢，沒功夫理你。\n");

        notify_fail(ob->name() + "望着你呵呵的傻笑。\n");
        return ob->ask_finish(me);
}

int help(object me)
{
        write(@HELP
指令格式 : defend  這個指令可以用來向你的門派的掌門或世家長輩
領取任務。
HELP );
        return 1;
}