// tangyao

inherit NPC;

int give_job();
int give_yao();

void create()
{
        set_name("唐藥", ({ "tang yao", "tang", "yao"}));
        set("long",
"唐門二代弟子，在唐門地位頗高。\n");
        set("gender", "男性");
        set("age", 55);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1500);
        set("max_douzhi", 500);
        set("douzhi", 500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("yanli",200);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("level", 15);
        set("shen",3000);
        set("score", 7000);

        set_skill("force", 180);
        set_skill("throwing", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("literate", 180);
        set_skill("hand", 180);
        set_skill("sword", 180);
        set_skill("boyun-suowu", 180);
        set_skill("biyun-xinfa", 180);
        set_skill("qiulin-shiye", 180);
        set_skill("wuzhan-mei", 180);
        set_skill("tangmen-throwing", 180);
        set_skill("tangmen-poison", 180);
        set_skill("tangmen-medical", 180);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        
        prepare_skill("hand", "boyun-suowu");
        
        create_family("唐門世家", 2, "弟子");

        set("inquiry", ([
                "job" : ( : give_job  : ),
                "工作": ( : give_job  : ),
                "散花天雨": ( : give_yao : ),
        ]));

        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);          

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));   
}

int give_job()
{
        object me;

        me = this_player();

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                say("唐藥說道:“我現在沒心情給你派活，等我回制藥房再說吧！”\n");
                return 0;
        }

        if( !query_temp("tangmen/yao", me) )
                command("say “這裡沒有活能給你幹，你聽誰說的？”");
        else
        {
                if( query_temp("yao", me) )
                {
                        command("say “你還沒有完成剛才給你的任務呢！”");
                        return 1;
                }
                write("唐藥說道:“我這裡正缺一味草藥，快去藥圃給我找(zhao)一株草藥(yao)來吧！”\n");
                set_temp("yao", 1, me);
        }
        return 1;
}

int give_yao()
{
        object me = this_player();
        object ob;
        
        if( query("family/family_name", me) != "唐門世家" )
        {
                command("say 你不是我唐門中人，我無法給你散花天雨！\n");
                return 1;
        } else
        {
                command("say 此散花天雨威力無窮，配合唐門奇毒使用的話，世上沒有對手！\n");
                ob = new("/kungfu/class/tangmen/obj/san");
//                ob->move(this_object());
//                command("givesanhuatianyuto"+query("id", me));
                ob->move(me, 1);
                message_vision("$N對$n點了點頭。\n", this_object(), me); 
                return 1;
        }
                
}

int accept_object(object who, object ob)
{
        command("say 要是找到了，就放到儲藏室去吧！給我幹什麼?");
        write("唐藥沖著你搖了搖頭，然後又小心翼翼的反弄著一株碧綠色的藥草。\n");
        return 0;
}
