// changxiang.c

inherit NPC;

void create()
{
        set_name( "常翔", ({"chang xiang", "chang", "changxiang"}) );
        set( "title", "媚香院龜奴" );
        set( "gender", "男性" );
        set( "age", 33 );
        set( "str", 26 );
        set( "dex", 25 );         
        set( "per", 26 );
        set( "attribute", "heroism" );
        set( "long", @LONG
一個高大威猛的漢子，鬱悶的一人坐在一旁。看他的樣子是該笑傲江湖的
人，不知為何要在此幹這等差事。
LONG
        );
        set( "max_qi", 500 );
        set( "max_jing", 500 );
        set( "attitude", "heroism" );
        set( "combat_exp", 50000 );
        set("inquiry", ([
                "陸麗仙" : "不要問我，我是看門的。\n",
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
                "常翔道：小姐多才多藝，自己做了幾個謎語，可惜沒人能猜中！\n",
                "常翔道：小姐才貌雙絕，可恨我愚魯不能和她同賞(enjoy)琴韻！\n",
        }) );
        set_skill("parry", 80);
        set_skill("blade", 80);
        set_skill("dodge", 80);
        set_skill("wuhu-duanmendao", 80);
        map_skill("blade", "wuhu-duanmendao");
        map_skill("parry", "wuhu-duanmendao");
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/male-cloth")->wear();
}

int accept_object(object me, object ob)
{
        int val, money;
        val = ob->value();
        money=(8+2*query("lu_sing", me))*1000;
        if ( val >= money )
        {
                write("常翔對你點了點頭，示意你可以走了。\n");
                delete("lu_sing", me);
                return 1;
        }
        if ( val > 0 )
        {
                command("look"+query("id", me));
                write("常翔面無表情的説道：我告訴過你要交多少錢的。\n");
        }
        return 0;
}

