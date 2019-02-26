// shenlong.h for join shenlongjiao
#include <ansi.h>

int do_join(string arg)
{
        object me, ob, obj ;
        string men;
        mapping party;

        me = this_object () ;
        ob = this_player () ;

        if (! arg || arg != "shenlongjiao")
                return notify_fail("你要加入什麼組織？\n"); 

        if( query("shen", ob)>0 )
        {
                message_vision("$N對$n大怒道：還想入教？一看你就不是好人! \n",
                               me, ob);
                me->kill_ob(ob); 
                return 1;
        }

        if( query("party", ob) && query("party/party_name", ob) != "神龍教" )
        {
                message_vision("$N搖搖頭，對$n説道：你已經加入"
                               "其他幫會了，不能再入我神龍教。\n",
                               me, ob);
                return 1;
        }

        if( query("party/party_name", ob) == "神龍教" )
        {
                message_vision("$N搖搖頭，對$n説道：你已經"
                               "是我神龍教的人了。\n",
                               me, ob);
                return 1;
        }
        if( query("gender", ob) == "女性")men=HIR"赤";
        else
        {
                switch (random(4))
                {
                case 0 : men=HIG"青"; break;
                case 1 : men=HIW"白"; break;
                case 2 : men=BLU"黑"; break;
                default: men=YEL"黃"; break;
                }
        }
        party = allocate_mapping(5);
        party["party_name"] = "神龍教";
        party["rank"] = men+"龍使"NOR"座下教眾";
        party["level"] = 1;
        party["tasks"] = 0;
        party["enter_time"] = time();
        set("party", party, ob);

        command("smile");
        message_vision("$N對$n説道：你就暫時在" + men +
                       "龍使"NOR + "座下效力吧！\n", me, ob);
        return 1;
}
