// suicide.c

#include <ansi.h>

inherit F_CLEAN_UP;

protected int slow_suicide(object me);
protected int halt_suicide(object me);

int main(object me, string arg)
{
        object *inv;
        int i;
        if (me->is_busy())
                return notify_fail("你上一個動作還沒完成。\n");

        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i]) && ! playerp(inv[i])) continue;
                return notify_fail("你身上還有個大活人呢，想不開也別急呀？\n");
        }

        if (! arg)
        {
                write("You commit suicide.\n");
                return 1;
        }

        if (arg != "-f") 
                return notify_fail("自殺有兩種，您是要永遠死掉(-f)還是重新投胎？\n");

        write("您選擇永遠死掉的自殺方式，這個人物的資料將永遠刪除，請務必\n"
              "考慮清楚，確定的話請輸入您的管理密碼：");
        input_to("check_password", 1, me, 1);
        return 1;
}

protected void check_password(string passwd, object me, int forever)
{
        object link_ob;
        string old_pass;

        link_ob=query_temp("link_ob", me);
        old_pass=query("ad_password", link_ob);
        if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
        {
                write(HIR "密碼錯誤！請注意，自殺必須輸入管理密碼。\n");
                return;
        }

        if (forever)
        {
                tell_object(me, HIR "\n你決定要自殺了，如果三十秒"
                            "鐘內不後悔，就真的永別了。\n\n" NOR);
                set_temp("suicide/time", time(), me);
                set_temp("suicide/last", 0, me);
                set_temp("suicide/from", query_ip_number(me), me);
                me->start_busy((: slow_suicide, me :),
                               (: halt_suicide, me :));
        }
}

protected int slow_suicide(object me)
{
        object link_ob;
        int t;

        if (! objectp(me))
                return 0;

        t=time()-query_temp("suicide/time", me);
        if( t<query_temp("suicide/last", me) )
        {
                delete_temp("suicide/", me);
                return 0;
        }

        if (t < 30)
        {
                if( t-query_temp("suicide/last", me)<5 )
                        return 1;

                tell_object(me, HIR "\n你還有" + chinese_number(30 - t) +
                            "秒鐘仔細考慮(" HIC "halt停止" HIR ")。\n" NOR);
                set_temp("suicide/last", t/5*5, me);
                return 1;
        }

        link_ob=query_temp("link_ob", me);
        if (! link_ob || ! interactive(me)) return 0;

        log_file("static/suicide",
                 sprintf("%s %s commits a suicide from %s\n",
                        log_time(), log_id(me),
                        query_temp("suicide/from", me)));

        seteuid(getuid());
        write("\n好吧，永別了:)。\n\n");

        if( query("mud_age", me)>1800 )
        CHANNEL_D->do_channel(this_object(), "rumor",
                sprintf("%s自殺了，以後你再也看不到這個人了。",
                me->name()));

        tell_room(environment(me), me->name() +
                "在你的面前化作輕煙，漸漸消失了...\n", ({me}));

        UPDATE_D->remove_user(query("id", me), 1);
        return 0;
}

protected int halt_suicide(object me)
{
        tell_object(me, HIG "你打消了尋死的念頭。\n" NOR);
        delete_temp("suicide", me);
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: suicide [-f]
 
如果因為某種原因你不想活了, 你可以選擇自殺.
自殺分兩種:
 
suicide    : 重新投胎
suicide -f : 永遠的除去玩家資料, 系統會要求你
             輸入密碼以確認身份.
 
請慎重選擇 :)
 
HELP );
        return 1;
}
