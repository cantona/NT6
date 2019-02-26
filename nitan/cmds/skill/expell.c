// expell.c

#include <skill.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;
        string *skname;
        mapping skills;
        int i;

        if( !arg || !ob = present(arg, environment(me)) )
                return notify_fail("你要將誰逐出師門？\n");

        if( !ob->is_character() )
                return notify_fail("開清楚了，它不是人，你逐不動他。\n");

        if( !userp(ob) )
                return notify_fail("你只能開除玩家所扮演的人物。\n");

        if( !ob->is_apprentice_of(me) )
                return notify_fail("這個人不是你的弟子。\n");

        if( query_temp("pending/detach", ob) )
        {
                message_vision("\n$N痛心的對$n説：唉！你若能呆在我" +
                       query("family/family_name", ob)+
                       "，何等有前途？罷了！罷了！\n", me, ob);
        } else
        {
                message_vision("\n$N對着$n説道：從今天起，你再也不是我"
                        +query("family/family_name", me)+"的弟子了，你走吧！\n",
                        me, ob);
        }

        tell_object(ob, "\n你被師父開革出師門了！\n");

        ob->skill_expell_penalty();
        addn("detach/times", 1, ob);
        addn("detach/"+query("family/family_name", ob), 1, ob);
        delete("family", ob);
        set("title", "普通百姓", ob);
        ob->unconcious();

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : expell|kaichu <某人>

這個指令可以讓你開除不成才的弟子，或是請求離開師門的弟子。被開除的
弟子所有本門的祕學都會被追回，而其他除了知識類的以外技能都可能會下
降，這對於一個人物而言是一個「比死還嚴重」的打擊，請你在開除一名弟
子之前務必審慎考慮。

HELP
        );
        return 1;
}