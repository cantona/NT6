// kill.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj;
        string *killer;
        string callname;

        if (me->is_chatter())
                return 0;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裡不準戰鬥。\n");

        if (! arg)
                return notify_fail("你想殺誰？\n");

        if( !objectp(obj = present(arg, environment(me))) || !me->visible(obj) )
                return notify_fail("這裡沒有這個人。\n");

        if( query_temp("apply/name", me) && userp(obj) )
                return notify_fail("你還是先取下面具吧!\n");

        if( query_temp("apply/shade_vision", obj) )
                return notify_fail("你看不到"+query("name", obj)+"。\n");

        if (! obj->is_character() || obj->is_corpse())
                return notify_fail("看清楚一點，那並不是活物。\n");

        if (obj == me)
                return notify_fail("用 suicide 指令會比較快:)。\n");

        if (arrayp(me->query_team()) &&
            member_array(obj, me->query_team()) != -1)
                return notify_fail("連你自己隊伍中的人也要殺嗎？太不人道了吧！\n");

        if (me->is_fighting(obj) && me->is_killing(query("id", obj)))
                return notify_fail("你正在和人家生死相撲呢。\n");

        if (! me->is_fighting(obj) &&
            query("qi", me)<query("max_qi", me)*3/10 )
                return notify_fail("你現在沒有力氣戰鬥了。\n");

        callname = RANK_D->query_rude(obj);

        if( query("can_speak", obj) )
        {
            if (random(3) > 1)
            message_vision("\n$N對著$n喝道：「" 
                    + callname + "！今日不是你死就是我活！」\n\n", me, obj);
            else
            message_vision("\n$N對著$n喝道：「" 
                    + callname + "！明年今日就是你的忌日！」\n\n", me, obj);
        }

        switch(obj->accept_kill(me))
        {
        case 0:
                return (! objectp(obj));
        case -1:
                return 1;
        default:
        }

        if (userp(me) && userp(obj) && !obj->is_want_kill(query("id", me)) )
                // Recoder the player want to kill another player
                me->want_kill(obj);

        me->kill_ob(obj);
        if (living(obj) && ! userp(obj))
                obj->kill_ob(me);
        else
                obj->fight_ob(me);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : kill <人物>
 
這個指令讓你主動開始攻擊一個人物，並且試圖殺死對方，kill 和 fight 最大的
不同在於雙方將會真刀實槍地打鬥，也就是說，會真的受傷。由於 kill 只需單方
面一廂情願就可以成立，因此你對任何人使用 kill 指令都會開始戰鬥，通常如果
對方是 NPC 的話，他們也會同樣對你使用 kill。

當有人對你使用 kill 指令時會出現紅色的字樣警告你，對於一個玩家而言，如果
你沒有對一名敵人使用過 kill 指令，就不會將對方真的打傷或殺死( 使用法術除
外)。

其他相關指令: hit, fight

有關 fight 跟 kill 的區分請看 'help combat'.
HELP );
        return 1;
}
