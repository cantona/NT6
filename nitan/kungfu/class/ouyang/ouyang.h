// ouyang.h

int permit_recruit(object ob)
{
        object me = this_object();

        if( query("name", ob) == "歐陽鋒" || 
            query("name", ob) == "歐陽克" )
        {
                message_vision("$N大怒：我操！你起這個名字是什麼意思啊？\n",
                               this_object());
                return 0;
        }

/*
        if( query("born_family", ob) != "歐陽世家" && !query("reborn/times", ob) )
        {
                message_vision("$N對$n道：你不是我們歐陽家的人，我怎能收你為徒？\n",
                               me, ob);
                return 0;
        }
*/

        if( query("detach/歐陽世家", ob) || 
            query("betrayer/times", ob) )
        {
                message_vision("$N搖搖頭對$n說：你反復無常，我不能收你為徒！\n",
                               me, ob);
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != query("family/family_name", me) )
        {
                message_vision("$N對$n道：你雖然是歐陽家的人，但你入了其他門派，我不能收你為徒！\n",
                               me, ob);
                return 0;
        }

        return 1;
}
