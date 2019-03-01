//recruit.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, old_rec;
        mapping family;
        int i;
        string temp;
        int student_num;

        if (! arg) return notify_fail("指令格式：recruit|shou [cancel]|<對象>\n");

        if (arg == "cancel")
        {
                old_rec=query_temp("pending/recruit", me);
                if (! objectp(old_rec))
                        return notify_fail("你現在並沒有收錄任何人為弟子的意思。\n");

                write("你改變主意不想收" + old_rec->name() + "為弟子了。\n");
                tell_object(old_rec, me->name() + "改變主意不想收你為弟子了。\n");
                delete_temp("pending/recruit", me);
                return 1;
        }

        if (! (ob = present(arg, environment(me))))
                return notify_fail("你想收誰作弟子？\n");

        if (ob == me) return notify_fail("收自己為弟子？好主意....不過沒有用。\n");

        if (ob->is_apprentice_of(me))
        {
                message_vision("$N拍拍$n的頭，說道：「好徒兒！」\n", me, ob);
                return 1;
        }

        if( !query("family", me) )
                return notify_fail("你並不屬于任何門派，你必須先加入一個"
                                   "門派，或自己創一\n個才能收徒。\n");

        // If the target is willing to apprentice us already, we do it.
        if ((object)query_temp("pending/apprentice", ob) == me)
        {
                if (! living(ob))
                {
                        message_vision("$N決定收$n為弟子。\n\n"
                                       "不過看樣子$n顯然沒有辦法行拜師之禮。\n\n", me, ob);
                        return 1;
                }

                if( mapp(query("family", ob)) && 
                    stringp(query("family/family_name", ob)) && 
                    query("family/family_name", me) != 
                    query("family/family_name", ob) )
                {
                        message_vision("$n決定判師投入$N門下！！\n\n"
                                       "$n跪了下來向$N恭恭敬敬地磕了四個響頭，"
                                       "叫道：「師父！」\n\n", me, ob);
                        addn("betrayer/times", 1, ob);
                        if( query("family/family_name", ob) )
                            addn("betrayer/"+query("family/family_name", ob), 1, ob);
                } else
                        message_vision("$N決定收$n為弟子。\n\n"
                                       "$n跪了下來向$N恭恭敬敬地磕了四個響頭，"
                                       "叫道：「師父！」\n", me, ob);
        
                me->recruit_apprentice(ob);
                delete_temp("pending/apprentice", ob);
        
                MYGIFT_D->check_mygift(ob, "newbie_mygift/baishi");   
                write("恭喜你新收了一名弟子！\n");
                family=query("family", ob);
                tell_object(ob, sprintf("恭喜您成為%s的第%s代弟子。\n",
                            family["family_name"],
                            chinese_number(family["generation"]) ));
                return 1;
        } else
        {
                old_rec=query_temp("pending/recruit", me);
                if (ob == old_rec)
                        return notify_fail("你想收" + ob->name() + "為弟子，但是對方還沒有答應。\n");
                else
                if (objectp(old_rec))
                {
                        write("你改變主意不想收" + old_rec->name() + "為弟子了。\n");
                        tell_object(old_rec, me->name() + "改變主意不想收你為弟子了。\n");
                }
                set_temp("pending/recruit", ob, me);
                message_vision("\n$N想要收$n為弟子。\n", me, ob);
                tell_object(ob, YEL "如果你願意拜" + me->name() + "為師父，"
                                "用 apprentice 指令。\n" NOR);
                return 1;
        }
}


int help(object me)
{
        write(@HELP
指令格式 : recruit|shou [cancel]|<對象>

這個指令能讓你收某人為弟子, 如果對方也答應要拜你為師的話.

See Also:       apprentice
HELP );
        return 1;
}
