// menggudog.c
// Last Modified by winder on May. 25 2001

inherit NPC;
void create()
{
        set_name("獒犬", ({ "dog" }) );
        set("race", "走獸");
        set("age",8);
        set("long", "威猛的獒犬,脖子上掛了帶刺的頸圈。\n");
        set("str", 32);
        set("combat_exp", 20000);
        set("chat_chance", 6);
        set("chat_msg", ({
                "獒犬嘴角搭拉下兩長條唾液。\n",
                "獒犬嘴角慢慢的裂開來，露出鋒利的犬牙。\n",
        }));
        set_temp("apply/attack",30);
        set_temp("apply/armor",30);
        setup();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob=this_player())&&!is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting",1,ob);
        }
}
void greeting(object ob)
{
        if (!ob||environment(ob)!=environment()) return;
        if( query("short", environment()) == "察合台營帳" )
        {
                message_vision("$N露出白色獠牙，向$n衝去.\n",this_object(),ob);
                kill_ob(ob);
                return;
        }
        return;
}