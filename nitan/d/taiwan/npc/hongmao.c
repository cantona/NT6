// hongmao.c
// Last Modifyed by Ahda on Jan. 4 2002

inherit NPC;


void create()
{
        set_name("紅毛鬼", ({ "hongmao gui", "gui"}));
        set("gender", "男性");
        set("age", random(10) + 30);
        set("str", 25);
        set("dex", 16);
        set("long","入侵我天朝寶島台灣的荷蘭紅毛鬼。他手上端着一支火槍，槍口還冒着青煙。\n");
        set("combat_exp", 25000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 30);
        set_temp("apply/damage", 30);

        setup();
        carry_object(__DIR__"obj/huoqiang")->wield();
        carry_object(__DIR__"obj/xifu")->wield();
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( environment(ob) != environment() ) return;
        say("紅毛鬼抬手就是一槍：砰！槍口一團火焰噴出。\n");
        ob->receive_damage("qi",50);
        ob->receive_wound("qi",50);
}
