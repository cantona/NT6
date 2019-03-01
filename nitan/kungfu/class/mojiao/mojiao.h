// mojiao.h

int permit_recruit(object ob)
{
        object me;

        me = this_object();

        if( query("detach/魔教", ob) || 
            query("betrayer/times", ob) )
        {
                message_vision("$N大怒道：我魔教豈能由你要來便來，要走便走？\n",me);
                return 0;
        }

        return 1;
}
