// xunbu.c
#include <ansi.h>
#define THIEF 3
#define ROBBER 5
#define GO 0
#define BACK 1

inherit NPC;

int direction=GO;

mapping BigWay=([
        "/d/city/yamen":({"south",0}),
        "/d/city/tongsijie":({"east","north"}),
        "/d/city/caohexiaojie":({"east","west"}),
        "/d/city/tongsiqiao":({"east","west"}),
        "/d/city/shilijie4":({"north","south"}),
        "/d/city/shilijie4":({"east","west"}),
        "/d/city/shilijie3":({"north","south"}),
        "/d/city/shilijie2":({"north","south"}),
        "/d/city/shilijie1":({"north","south"}),
        "/d/city/shilijie5":({"north","south"}),
        "/d/city/shilijie6":({"east","south"}),
        "/d/city/shilijie7":({"east","south"}),
        "/d/city/ganquanjie": ({0,"west"}),
        "/d/city/nanmendajie": ({0,"north"}),
        "/d/city/beimendajie": ({0,"south"}),
]);

void create()
{
        string *surname=({"慕容","西門","公孫","上官","南宮","歐陽","司徒",});
        set_name(surname[random(sizeof(surname))]+"巡捕",({"xun bu","police"}));
        set("gender", "男性" );
        set("age", 25);
        set("str", 45);
        set("cor", 50);
        set("cps", 35);
        set("int", 20);
        set("per", 20);
        set("kar", 15);
        set("long",@LONG
巡捕個個身手矯健，強盜、山賊無不聞風喪膽。
LONG );
        set("status","patrol");
        set("CatchWho",0);
        set("combat_exp", 500000);
        set("attitude", "heroism");
        set("chat_chance", 3);
        set("chat_msg", ({
                "巡捕說道：你想幹什麼？還不跟我去府衙受審！？\n",
                "巡捕說道：大膽！居然敢當街拒捕！想造反？\n",
                "巡捕說道：別胡鬧了，還是乖乖的跟我走吧。\n"
        }) );
        set ("inquiry",([
                "bribery":
                        "說哪裡話來，府太爺清貧廉正，我們作手下的豈能辱沒他的名聲？\n收起你的錢吧！\n",
                "salary": "哎，老爺俸銀微薄，我們的年餉自然更少了......\n",
                "money": "說實在的，我也想要錢。但要是讓老爺知道了我收受賄賂(bribery)，\n不死也得扒層皮\n",
        ]));
         set("pursuer",1);
         set_skill("blade", 100);
         set_skill("parry", 90);
         set_skill("dodge", 70);
         setup();
         direction=GO;
         carry_object("/clone/weapon/gangdao")->wield();
         carry_object("/clone/misc/cloth")->wear();
         add_money("silver",30);
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && 
                (int)ob->query_condition("killer")) {
        message_vision( "巡捕對著$N大喝一聲：“大膽刁民，竟敢殺人放火，想置我們與何地？！！” \n", ob );
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}
