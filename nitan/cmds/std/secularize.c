// secularize.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        if( query("class", me) != "bonze" )
                return 0;

        if( stringp(query("family/family_name", me)) && 
            (query("family/family_name", me) == "少林派" || 
            query("family/family_name", me) == "峨嵋派") )
        {
                write("你沒有稟告師長，怎敢擅自還俗？\n");
                return 1;
        }

        if( query_temp("pending/secularize", me) )
        {
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "聽說" + me->name(1) + "厭倦了清貧枯燥的生活，決定還俗。");
                delete("class", me);
                write("你摸了摸腦袋，嘆了口氣，決定回塵世好好享受享受。\n");

                if( stringp(query("purename", me)) )
                        me->set_name();
                return 1;
        }

        set_temp("pending/secularize", 1, me);
        write(YEL "你決定要還俗嗎？這可是大事，如果你下了決心，那就再輸入一次這個命令。\n" NOR);
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: secularize|huansu
 
這個指令讓你放棄無聊的出家生活。

HELP );
        return 1;
}
