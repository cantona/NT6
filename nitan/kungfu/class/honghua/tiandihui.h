// tiandihui.h for join tiandihui
#include <ansi.h>;

int do_join(string arg)
{
        object me, ob, obj ;
        string tang;
        mapping party;

        me = this_object () ;
        ob = this_player () ;

        if (! arg || arg != "tiandihui")
                return notify_fail("你要加入什麼組織？\n"); 

        if( query("weiwang", ob)<20 )
        {
                message_vision(HIR "$N" HIR "對$n" HIR "道：想入會？你的江湖"
                               "威望太低，天地會都是敢作敢為的好漢！\n" NOR,
                               me, ob);
                return 1;
        }

        if( query("shen", ob)<0 )
        {
                message_vision(HIR "$N" HIR "對$n" HIR "大怒道：還想入會？"
                               "一看你就是個大漢奸! \n"NOR, me, ob);
                set_leader(this_player());
                remove_call_out("kill_ob");
                me->kill_ob(ob); 
                return 1;
        }

        if( query("party", ob) && 
            query("party/party_name", ob) != "天地會" )
        {
                message_vision("$N搖搖頭，對$n説道：你已經加入其他幫"
                               "會了，不能再入我天地會。\n", me, ob);
                return 1;
        }

        if( query("party/party_name", ob) == "天地會" )
        {
                message_vision("$N搖搖頭，對$n説道：你已經是我"
                               "天地會的人了。\n",me,ob);
                return 1;
        }

        switch (random(10))
        {
                case 0 : tang=HIG"青木堂"; break;
                case 1 : tang=HIG"赤火堂"; break;  //古至中
                case 2 : tang=HIW"西金堂"; break;
                case 3 : tang=BLU"玄水堂"; break;
                case 4 : tang=YEL"黃土堂"; break;
                case 5 : tang=HIG"蓮花堂"; break;  //蔡德忠
                case 6 : tang=HIG"洪順堂"; break;  //方大洪
                case 7 : tang=HIW"家後堂"; break;  //馬超興
                case 8 : tang=BLU"參太堂"; break;
                default: tang=YEL"宏化堂"; break;  //李
        }
        party = allocate_mapping(5);
        party["party_name"] = "天地會";
        party["rank"] = tang + NOR"會眾";
        party["level"] = 1;
        party["tasks"] = 0;
        party["enter_time"] = time();
        set("party", party, ob);

        command("smile");
        message_vision("$N對$n説道：你就暫時在" + tang + NOR +
                       "效力吧！\n", me, ob);
        if( query("weiwang", ob)<50 )
        {
                set("weiwang", 50, ob);
                message_vision(HIC "$N的江湖威望提高了！\n" NOR, this_player());
                return 1;        
        }
        return 1;
}
