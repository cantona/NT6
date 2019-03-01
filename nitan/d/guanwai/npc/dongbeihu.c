// dongbeihu.c
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("東北虎", ({ "dongbei hu", "tiger","hu" }) );
        set("race", "野獸");
        set("age", 20);
        set("long", @LONG
一隻矯捷的斑斕猛虎，形體巨大，狀極威猛，雄偉極了。


    ("`-''-/").___..--''"`-.
     `@_ @ )   `-.  (  *  ).`-.__.`)
     (_Y_.)'  ._   )  `._ `. ``-..-'
      _..`--'_..-_/  /--'_.' ,'
    (il),-''  (li),'  ((!.-'


LONG);
        set("attitude", "aggressive");
        set("shen_type", -1);

        set("limbs", ({ "虎頭", "虎身", "前爪", "後爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 50000);

        set_temp("apply/attack", 200);
        set_temp("apply/defense", 300);
        set_temp("apply/armor", 100);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "老虎在浚巡，嚇得你大氣都不敢出。\n",
                "老虎仰天長嘯，聲震山谷，黃葉紛墜。\n",
        }) );
}

void init()
{       
        object ob; 

        ob = this_player();
        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( ob->query_dex()<30 && !query_temp("owner", this_object()) )
        {
                message_vision( "只見發起一陣狂風。
只聽得亂樹背後撲地一聲響，跳出一隻吊睛白額大蟲來。
那大蟲又餓，又渴，把兩隻爪在地上略按一按，和身望你一撲，從半空裏攛將下來。\n",ob);
                message_vision("$N這一下沒有躲開，為虎所傷暈了過去。\n\n",ob);
                ob->receive_wound("qi",30);
                ob->receive_damage("qi",30);
                ob->start_busy(2);
                this_object()->kill_ob(ob);
        }
}

