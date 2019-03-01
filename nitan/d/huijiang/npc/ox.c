// ox.c
// Last Modified by winder on Sep. 12 2001

inherit NPC;

void create()
{
        set_name("□牛", ({ "mao niu","niu" }) );
        set("race", "走畜");
        set("age", 12);
        set("long", "一頭發怒的公牛，兩個角上微微閃著金光。\n");

        set("str", 25);
        set("cor", 24);
        set("combat_exp",15000);

        set_temp("apply/attack", 15);
        set_temp("apply/armor", 25);
   
        set("chat_chance",5);
        set("chat_msg",({
                "□牛瞪著碗大的眼睛，仔細研究著你。\n",
                "□牛張嘴對天叫了兩聲，你卻沒聽到一點聲音。\n",
        }));
        setup();
}

void die()
{
        message_vision("$N怒哼一聲，一頭撞向山壁，不見了。\n",this_object());
        new(__DIR__"obj/niujiao")->move(environment(this_object()));
        destruct(this_object());
        return;
}