inherit ROOM;

void init()
{
        object me = this_player();

        if(!userp(me))
                return;

        call_out("show_msg", 1, me);
}

void show_msg(object me)
{
        int sk, n;

        if(!me || (environment(me) != this_object()))
                return;

        sk = me->query_skill("dodge", 1);

        if( ((n=query("qi", me)) <= 5) || (sk<40) || (random(10)>(sk-35)) )
        {
                if(n>25) n=25;
                message_vision("$N一個沒站穩，倒栽沖摔了下去。\n", me);
                me->receive_damage("qi",n);
                me->move(__DIR__"lianwu");
                tell_room(environment(me), me->name()+"摔了下來。\n", ({me}));
                return;
        }

        message_vision("$N紮了個馬步，紋絲不動。\n", me);
}

int valid_leave(object ob,string dir)
{
        if(dir != "down")
        {
                ob->receive_damage("qi",20);
        }

        return 1;
}
