// noclone.c

int is_no_clone() { return 1; }

object check_clone()
{
        object me;

        me = this_object();
        if( clonep(me) ) {
                destruct(me);
                return 0;
        }

        if( !stringp(query("startroom", me)) )
                return this_object();

        me->move(query("startroom", me));
        if( me->is_character() ) {
                message("vision", me->name() + "走了過來。\n",
                        environment(me));
        }
        return this_object();
}
