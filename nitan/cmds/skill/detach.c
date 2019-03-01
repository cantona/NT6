// detach.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping family, skills;
        int i;
        string *skname;
        int lvl = 0;

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if (! arg)
                return notify_fail("指令格式：detach <對象>\n");

        if (! (ob = present(arg, environment(me))) ||
            ! ob->is_character())
                return notify_fail("你想和誰斷絕師徒關系？?\n");

        if (! living(ob))
                return notify_fail("你必須先把" + ob->name() + "弄醒。\n");

        if( query("reborn_offer", me) )
                return notify_fail("轉世進程中不可以脫離門派。\n");

        if( query_temp("pending/detach", me) != ob )
        {
                write(HIR "你真的打算和" + ob->name(1) + "說你要離開師門嗎？倘若真"
                      "的離開了，你將會失去所有的高級武功哦！\n" NOR);
                write(YEL "如果你真的下了決心，就請再輸入一次這個命令。\n" NOR);
                set_temp("pending/detach", ob, me);
                me->start_busy(1);
                return 1;
        }

        if (! me->is_apprentice_of(ob))
        {
                if( query("family/family_name", ob) == query("family/family_name", me) )
                {
                    message_vision("\n$N大吃一驚，對$n道：什，什麼？你要脫離師門？"
                                   "這事可得找你師傅去。\n", ob, me);
                    return 1;
                }
        }

        message_vision("\n$N向$n磕了一個頭，道：師父！我... 我想脫離師門。\n", me, ob);
        if( intp(query("family/beggarlvl", me)) && 
            query("family/beggarlvl", me)>0 )
                lvl=query("family/beggarlvl", me);
        set_temp("pending/detach", 1, me);
        tell_object(ob, me->name() + "想脫離師門。\n");
        ob->attempt_detach(me);
        if (lvl) set("gaibang/beggarlvl", lvl, me); 
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : detach|tuoli <對象>
 
這個指令能讓你向你的師傅請求脫離師門，因為一般的大門派不願意接
收判師的人，所以如果你想改投其他門派，最好按照規矩脫離師門，然
而一旦脫離師門，師傅將追回你所有學到的本門秘學，並追回部分其他
武功，知識不會受到任何影響。

請參考相關指令 expell
HELP );
        return 1;
}
