#include <ansi.h>
inherit NPC;

int ask_join();
int ask_box();

void create()
{
        set_name("郭老六", ({ "guo laoliu", "guo", "laoliu", }));
        set("title", HIB"藥王谷"NOR+WHT"管事"NOR);
        set("long", "他是回春堂的帳房先生，負責回春堂的所有帳目。\n" );
        set("gender", "男性");
        set("attitude", "friendly");

        set("age", 60);
        set("shen_type", 1);
        set("str", 17);
        set("int", 16);
        set("con", 18);
        set("dex", 20);
        set("max_qi", 150);
        set("max_jing", 150);
        set("jiali", 10);
        set("combat_exp", 5000);

        set_skill("force", 30);
        set_skill("dodge", 30);
        set_skill("unarmed", 30);
        set_skill("parry", 30);
        set_skill("yaogu-xinfa", 30);
        
        create_family("藥王谷", 3, "弟子");
        set("class", "bonze");

        set("inquiry", ([
                "藥王谷" : "要加入藥王谷，可以ask guo about 加入",
                "join" : (: ask_join :),
                "加入" : (: ask_join :),
                "打工" : (: ask_join :),
                "針灸盒" : (: ask_box :),
                "box" : (: ask_box :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int greeting(object ob)
{
        if( query_temp("work_pass", ob)){
                command("say 谷主正在藥王谷等你，你還不快去！\n");
                return 1; }
        if( query("party/party_name", ob) == "藥王谷" )
        {
                if( (int)ob->query_skill("medical",1)>=40) 
                {
                set_temp("work_pass", 1, ob);
                command("say 這位兄弟你的醫藥口訣大有長進，正是我藥王谷需要的人才！\n");
                command("say 如果你願意可以到藥王谷去，叩見谷主進一步學習。\n");
                return 1;
                }
                
        }
        else {
        switch( random(4) ) {
                case 0:
                        command("bow"+query("id", ob));
                        break;
                case 1:
                        command("nod"+query("id", ob));
                        break;
                case 2:
                        command("hi"+query("id", ob));
                        break;
                case 3:
                        command("welcome"+query("id", ob));
                        break;
                }
        }
}


int ask_join()
{
        mapping party; 
        object me;
        me=this_player();

        if( query("family/family_name", me) == "藥王谷" )
                {
                command("say "+RANK_D->query_respect(me)+
                        "你已經是藥王谷的人了，還要加入什麼？\n");
                return 1; 
                }

        if( query("family/family_name", me) )
                {
                command("say "+RANK_D->query_respect(me)+
                        "你已經有明師指點，還是回去好好吧效忠師門吧！\n");
                return 1; 
                }

        command("ok"+query("id", me));
        command("say 你先在回春堂做事吧，時機成熟了你就可以進入藥王谷了！\n");
        command("recruit"+query("id", me));
        if( query("class", me) != "bonze" )
                set("class", "bonze", me);
        set("title", "回春堂跑堂弟子", me);
        command("say "+RANK_D->query_respect(me)+
                "今後要多多努力幹活啊！\n");
        return 1;
}

int ask_box()
{
        object ob, me;
        me=this_player();

        if( query("family/family_name", me) != "藥王谷"){
                command("say "+RANK_D->query_respect(me)+
                        "你不是藥王谷的弟子，針灸盒不能隨便給你！\n");
                return 1; }

        if( present("zhenjiu he", me) ) {
                command("say "+RANK_D->query_respect(me)+
                        "你現在身上不是有嗎？要哪麼多幹什麼呢？\n");
                return 1; }

        if( (int)me->query_skill("medical",1)<40 ) {
                command("say "+RANK_D->query_respect(me)+
                        "你現在還不會使用針灸盒！\n");
                return 1; }

        ob = new(__DIR__"obj/zhenjiu");
        ob->move(me);

        message_vision(YEL"郭老六給$N一個"+query("name", ob)+"。\n"NOR,me);

        command("say "+RANK_D->query_respect(me)+
                "今後要多多努力啊！\n");
        return 1;
}
