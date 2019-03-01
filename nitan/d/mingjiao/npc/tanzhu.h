// tanzhu.h for join mingjiao 

#include "mingjiao.h"

int do_join(string arg)
{
        object me, ob, obj;
        mapping family;

        me = this_object () ;
        ob = this_player () ;

        if( !arg || arg!="mingjiao" )
                return notify_fail("你要加入什麼組織？\n"); 
           if( query_temp("have_letter", ob) || present("tuijian xin1",ob) )
           {
                command("say 好啊。");
                command("heihei "+query("id", ob));
                return 1;
        }
        if( !mapp(family=query("family", ob)) || 
            !query("family/family_name", ob) )
           {
                message_vision("$N點點頭，對$n說道：好，你到昆侖山總舵去找接引使，他會讓你入教的。\n",me,ob);
                message_vision("$N交給$n一封推薦信。\n", me, ob);
                set_temp("have_letter", 1, ob);
                obj=new("/d/mingjiao/obj/tuijianxin-1");
                obj->move(ob);
                return 1;        
        }
           if( family["family_name"] != "明教" )
        {
                message_vision("$N搖搖頭，對$n說道：你已經加入其他門派了，不能再入我光明聖教。\n",me,ob);
                return 1;
        }
        else
                message_vision("$N搖搖頭，對$n說道：你已經是我明教的人了。\n",me,ob);
        return 1;
}
