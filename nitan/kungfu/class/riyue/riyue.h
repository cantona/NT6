// riyue.h

int permit_recruit(object ob)
{
    object me;

    me = this_object();

    if( query("name", ob) == "東方不敗" || 
        query("name", ob) == "任我行" )
    {
        message_vision("$N勃然大怒：哼！你也敢稱我的諱號？\n",me);
        return 0;
    }

    if( query("detach/日月神教", ob) || 
        query("betrayer/times", ob) )
    {
        message_vision("$N大怒道：我日月神教豈能由你要來便來，要走便走？\n",me);
        return 0;
    }

    return 1;
}
