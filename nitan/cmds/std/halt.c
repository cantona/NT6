// halt.c

#define SCHEME_CMD      "/cmds/usr/scheme"
#define TRIGGER_CMD     "/cmds/usr/trigger"

int main(object me, string arg)
{
        object ob;

        if( query("doing", me) == "scheme" )
        {
                // 執行計劃中，終止
                write("你決定中止計劃。\n");
                SCHEME_CMD->cancel_schedule(me);
                if (! me->is_busy())
                        return 1;
        }

        if( query("doing", me) == "trigger" )
        {
                write("你決定中止觸發練功。\n");
                TRIGGER_CMD->cancel_trigger(me);
                if (! me->is_busy())
                        return 1;
        }

        if (me->is_busy() && ! intp(me->query_busy()))
        {
                me->interrupt_me(me);
                return 1;
        } else
        if (me->is_fighting())
        {
                me->remove_all_enemy(0);
                message_vision("$N身行向後一躍，跳出戰圈不打了。\n", me); 
                if (objectp(ob = me->query_competitor()) &&
                    ! ob->is_fighting(me))
                {
                        ob->win();
                        me->lost();
                }
                return 1;
        }
        else
        if (me->is_busy())
                return notify_fail("你現在停不下來。\n");
        else
                return notify_fail("你現在不忙。\n");

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : halt

中止你目前正在做的事情，比如打坐、吐納或者是某些工作。如果
你和別人正在動手，則這條命令會讓你停手，當然前提是對方並不
想殺死你，否則使用這條命令沒有效果。

如果你正在和人比武或是接受挑戰而且並不是見生死方式，則該命
令即作為認輸處理。

其他相關指令: accept, fight, hit, scheme

HELP );
        return 1;
}