// murong.h

int permit_recruit(object ob)
{
    object me;

    me = this_object();
    if( query("name", ob) == "慕容博" || 
        query("name", ob) == "慕容復" )
    {
        message_vision("$N大怒：哼！你起這個名字算是什麼意思？\n");
        return 0;
    }

/*
    if( query("born_family", ob) != "慕容世家" && !query("reborn/times", ob) )
    {
        message_vision("$N對$n道：你不是我們慕容家的人，師徒就免了吧！\n",
                       me, ob);
        return 0;
    }
*/

    if( query("detach/慕容世家", ob) || 
        query("betrayer/times", ob) )
    {
        message_vision("$N搖搖頭對$n説：你反覆無常，我慕容家不留這種人！\n",
                       me, ob);
        return 0;
    }

    if( query("family/family_name", ob) && 
        query("family/family_name", ob) != query("family/family_name", me) )
    {
        message_vision("$N對$n道：你既然是慕容家的人，卻入了其他門派，實在是大逆不道！\n",
                       me, ob);
        return 0;
    }

    return 1;
}
