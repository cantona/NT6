// finit.h
#include <ansi.h>
#define A_TIME 60

string * weapon_msg = ({
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/chuidutong",
        "/d/city/task2/obj/sheerkou",
});

void init()
{
        remove_call_out("do_check");
        call_out("do_check",1);
        remove_call_out("do_wait");
        call_out("do_wait",A_TIME);
}

void do_check()
{
        object me = this_object();
        object ob;

        remove_call_out("do_check");
        if (! living(me) || me->fighting() )
        {
                call_out("do_check",1);
        }
        else
        {
                if( !ob = present("biao tou",environment(me)))
                {
                        call_out("do_check",1);
                }
                else
                {
                        command("shot"+query("id", ob));
                        addn("combat_num", 1, ob);
                        message_vision(HIW"\n$N大喊道：保鏢的兔崽子，納命來吧！\n"NOR,me);
                        remove_call_out("do_sha");
                        call_out("do_sha",1);
                }
        }
}

void do_wait()
{
        object ob;
        object me = this_object();

        remove_call_out("do_wait"); 
        if (me->is_fighting() || !living(me) )
        {
                call_out("do_wait",A_TIME);
        }
        else
        {
                message_vision("$N說道：風緊！風緊！大爺先走了！\n$N一陣哄向遠處逃了開去。\n",this_object());
                destruct(me);
        }
}

void do_sha()
{
        object me = this_object();
        object cart,ob, weapon;
        string wmsg;

        remove_call_out("do_sha");
        if (! living(me) || me->fighting() )
        {
                message_vision("$N咬牙切齒地對著天空大叫：“賊老天！”\n",me);

                call_out("do_sha",1);
        }
        else
        {
                if( ob = present("biao tou",environment(me)))
                {
                        wmsg = weapon_msg[random(sizeof(weapon_msg))];
                        weapon = new(wmsg);
                        weapon->move(me);
                        message_vision(HIW"\n$N沖著$n大喊道：你還不死！！看我的手段！\n"NOR,me, ob);
                        command("shot"+query("id", ob));
                        addn("combat_num", 1, ob);
                        call_out("do_sha",1);
                }
                else
                {
                        message_vision("$N說道：大功告成！大爺先走了！\n$N一陣大哄向遠處飛馳而去。\n",me);
                        if ( cart = present("cart",environment(me)))
                        destruct(cart);
                        destruct(me);
                }
        }
}

