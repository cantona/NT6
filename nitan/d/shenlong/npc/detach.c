// detach.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, old_app;
        mapping family, skills;
        int i;
        string *skname;

	return  notify_fail("脱離師門請使用指令 tuoli 或 tuoli2 即可！\n");
	
        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if (! arg)
                return notify_fail("指令格式：detach|tuoli [cancel]|<對象>\n");

        if (arg == "cancel")
	{
                old_app=query_temp("pending/deatch", me);
                if( !objectp(old_app) )
                        return notify_fail("你現在並沒有脱離你的師傅的想法。\n");
                write("你改變主意不想脱離師門了。\n");
                tell_object(old_app, me->name() + "改變主意不想脱離師門了。\n");
                delete_temp("pending/detach", me);
                delete_temp("pending/want", me);
                return 1;
        }

        if( !query_temp("pending/want", me) )
        {
                tell_object(me, HIR "\n請注意，一但你脱離師門，將會被廢除掉所有"
                                "的特殊武功。\n" NOR + HIC "如果你下了決心，就"
                                "再輸入一次這條命令。\n" NOR);
                set_temp("pending/want", 1, me);
                return 1;
        }

        if (! (ob = present(arg, environment(me))) ||
            ! ob->is_character())
        {
                delete_temp("pending/want", me);
                write("你想和誰斷絕師徒關係？\n");
                return 1;
        }

        if (ob == me)
        {
                delete_temp("pending/want", me);
                write("你想和自己斷絕師徒關係？\n");
                return 1;
        }

        if (! living(ob))
        {
                delete_temp("pending/want", me);
                write("你必須先把" + ob->name() + "弄醒。\n");
                return 1;
        }

        message_vision(CYN "\n$N" CYN "向$n" CYN "磕了一個頭，説道：師"
                       "父！我…我想脱離師門。\n" NOR, me, ob);

        if (! me->is_apprentice_of(ob))
	{
                if( query("family/family_name", ob) == query("family/family_name", me) )
                {
                        delete_temp("pending/want", me);
                        message_vision(CYN "$N" CYN "大吃一驚，對$n" CYN "道：什"
                                       "…什麼？你要脱離師門？這事可得找你師傅去"
                                       "。\n" NOR, ob, me);
                        return 1;
                } else
		{
                        delete_temp("pending/want", me);
                        message_vision(CYN "$N" CYN "看了看跪在地上的$n" CYN "，"
                                       "冷笑一聲，道：我又不是你師傅，找我做甚？"
                                       "\n" NOR, ob, me);
                        return 1;
		}
        }

        set_temp("pending/detach", 1, me);
        tell_object(ob, me->name() + "想脱離師門。\n");
        ob->attempt_detach(me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : detach|tuoli [cancel]|<對象>
 
這個指令能讓你向你的師傅請求脱離師門，因為一般的大門派不願意接
收判師的人，所以如果你想改投其他門派，最好按照規矩脱離師門，然
而一旦脱離師門，師傅將追回你所有學到的本門祕學，並追回部分其他
武功，知識不會受到任何影響。

請參考相關指令 expell
HELP );
        return 1;
}