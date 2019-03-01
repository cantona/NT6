// apprentice.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, old_app;
        mapping family, ob_family, skills;
        int i;
        string *skname;

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if (! arg)
                return notify_fail("指令格式：apprentice | bai [cancel]|<對象>\n");

        if (query("reborn_offer", me))
                return notify_fail("轉世過程中無法拜師。\n");

        if (arg == "cancel")
        {
                old_app=query_temp("pending/apprentice", me);
                if( !objectp(old_app) )
                        return notify_fail("你現在並沒有拜任何人為師的意思。\n");
                write("你改變主意不想拜" + old_app->name() + "為師了。\n");
                tell_object(old_app, me->name() + "改變主意不想拜你為師了。\n");
                delete_temp("pending/apprentice", me);
                return 1;
        }

        if (! (ob = present(arg, environment(me))) ||
            ! ob->is_character())
                return notify_fail("你想拜誰為師？\n");

        if (! living(ob))
                return notify_fail("你必須先把" + ob->name() + "弄醒。\n");

        if (ob == me)
                return notify_fail("拜自己為師？好主意....不過沒有用。\n");

        if (ob->is_baby())
                return notify_fail("拜孩子為師？好主意....不過沒有用。\n");

        if (me->is_apprentice_of(ob))
        {
                message_vision("$N恭恭敬敬地向$n磕頭請安，叫道：「師父！」\n", me, ob);
                return 1;
        }

        if( !mapp(ob_family=query("family", ob)) )
                return notify_fail(ob->name() + "既不屬於任何"
                                   "門派，也沒有開山立派，不能拜師。\n");

        if (playerp(ob))
                return notify_fail("... 現在不能拜玩家為師 :)\n");

        family=query("family", me);
        if (mapp(family) && stringp(family["master_name"]) &&
            ob_family["family_name"] == family["family_name"] &&
            ob_family["generation"] >= family["generation"])
                return notify_fail(ob->name() + "嚇了一跳，忙道：“這可不敢當，不敢當。”\n");

        // betrayer ?
        if (mapp(family) && stringp(family["family_name"]) &&
            family["family_name"] != ob_family["family_name"] &&
            query_temp("pending/betrayer", me) != ob )
        {
                if( query("reborn_offer", me) )
                        return notify_fail("轉世進程中不可以判師。\n");
                write(HIR "你是打算判師嘛？這很可能遭到嚴厲懲罰的哦。\n" NOR
                      "如果你下了決心，就再輸入一次這條命令。\n");
                set_temp("pending/betrayer", ob, me);
                return 1;
        }

        // If the target is willing to recruit us already, we do it.
        if ((object)query_temp("pending/recruit", ob) == me)
        {
                if (mapp(family) && stringp(family["family_name"]) &&
                    family["family_name"] != ob_family["family_name"])
                {
                        message_vision(
                                "$N決定背叛師門，改投入$n門下！！\n\n"
                                "$N跪了下來向$n恭恭敬敬地磕了四個響頭，叫道：「師父！」\n\n",
                                me, ob);
                        set("weiwang", 0, me);
                        addn("betrayer/times", 1, me);
                        delete("quest", me);
                        delete_temp("quest", me);
                        if (stringp(family["family_name"]))
                                addn("betrayer/"+family["family_name"], 1, me);
                } else
                        message_vision(
                                "$N決定拜$n為師。\n\n"
                                "$N跪了下來向$n恭恭敬敬地磕了四個響頭，叫道：「師父！」\n\n",
                                me, ob);
                ob->recruit_apprentice(me);
                delete_temp("pending/recruit", ob);

                tell_object(ob, "恭喜你新收了一名弟子！\n");
                printf("恭喜您成為%s的第%s代弟子。\n",
                        query("family/family_name", me),
                        chinese_number(query("family/generation", me)));
                return 1;

        } else
        {
                old_app=query_temp("pending/apprentice", me);
                if (ob == old_app)
                        return notify_fail("你想拜" + ob->name() +
                                           "為師，但是對方還沒有答應。\n");
                else
                if (objectp(old_app))
                {
                        write("你改變主意不想拜" + old_app->name() + "為師了。\n");
                        tell_object(old_app, me->name() + "改變主意不想拜你為師了。\n");
                }

                message_vision("$N想要拜$n為師。\n", me, ob);
                set_temp("pending/apprentice", ob, me);
                if (userp(ob))
                {
                        tell_object(ob, YEL "如果你願意收" + me->name() +
                                    "為弟子，用 recruit 指令。\n" NOR);
                } else
                        ob->attempt_apprentice(me);
                return 1;
        }
}


int help(object me)
{
        write(@HELP
指令格式 : apprentice|bai [cancel]|<對象>

這個指令能讓你拜某人為師，如果對方也答應要收你為徒的話，就會
立即行拜師之禮， 否則要等到對方用 recruit 指令收你為弟子才能
正式拜師。

請注意你已經有了師父，又背叛師門投入別人門下，則很有可能導致
原有門派的人的追殺，一旦失手，則所有的特殊武功都將被別人廢掉，
基本武功減半。

如果對你的師父使用這個指令，會變成向師父請安。

拜同門的師父不能拜比自己輩分低的或是和自己輩分相同的人。

請參考相關指令 expell、recruit
HELP );
        return 1;
}
