// tangbiao

inherit NPC;

int give_job();
int give_anqi();

void create()
{
        set_name("唐鏢", ({ "tang biao", "tang", "biao"}));
        set("long", 
"唐門中所有的絕門鏢法，他都會用。\n");        
        set("gender", "男性");
        set("gender", "男性");
        set("age", 32);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 28);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("max_qi", 8000);
        set("max_jingli", 2500);
        set("max_douzhi", 600);
        set("douzhi", 600);
        set("neili", 4500);
        set("max_neili", 4500);
        set("yanli", 200);
        set("jiali", 120);
        set("combat_exp", 900000);
        set("level", 15);
        set("score", 8000);

        set_skill("force", 80);
        set_skill("throwing", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_skill("literate", 80);
        set_skill("hand", 80);
        set_skill("sword", 80);
        set_skill("boyun-suowu", 80);
        set_skill("biyun-xinfa", 80);
        set_skill("qiulin-shiye", 80);
        set_skill("wuzhan-mei", 80);
        set_skill("tangmen-throwing", 80);
        set_skill("tangmen-poison", 80);
        set_skill("tangmen-medical", 80);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "boyun-suowu");
        map_skill("sword", "wuzhan-mei");        
        map_skill("hand", "boyun-suowu");
        
        prepare_skill("hand", "boyun-suowu");
        
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);  
        
        create_family("唐門世家", 2, "弟子");

        set("inquiry", ([
                "job" : ( : give_job  : ),
                "工作": ( : give_job  : ),
                "anqi": ( : give_anqi : ),
                "暗器": ( : give_anqi : ),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));  
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
}

int give_job()
{
        object me, biao;
        string msg, targ;
        int coun;

        string *tar = ({
                "","鐵礦石",
        });

        me = this_player();
        biao = this_object();

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                say("唐鏢説道:“我現在沒心情給你派活，等我回制鏢房再説吧！”\n");
                return 0;
        }

        if( !query_temp("tangmen/biao", me) )
                command("say “這裏沒有活能給你幹，你聽誰説的？”");
        else
        {
                if( query_temp("biao", me) )
                {
                        command("say “你還沒有完成剛才給你的任務呢！”");
                        return 1;
                }
                coun = 1 + random(sizeof(tar));
                if ( coun == sizeof(tar) )
                        coun = ( sizeof(tar) - 1 );
                targ = tar[coun];
                printf("%d/%d\n",coun,sizeof(tar));
                say("唐鏢説道:“我這裏上好的" + targ + "不多了，你去後山給我找一些來吧！”\n");
                set_temp("biao", coun, me);
        }
        return 1;
}

int give_anqi()
{
        object me = this_player();
        object ob;
        
        if( query("family/family_name", me) != "唐門世家" )
        {
                command("say 你不是我唐門中人，我無法給你七子剛鏢！\n");
                return 1;
        } else
        {
                command("say 此七子剛鏢威力無窮，配合唐門奇毒使用的話，效果更好！\n");
                ob = new("/kungfu/class/tangmen/obj/biao");
//                ob->move(this_object());
//                command("give qizi gangbiao to"+query("id", me));
                ob->move(me, 1);
                return 1;
        }
                
}

int accept_object(object who, object ob)
{
        command("say 要是找到了，就放到儲藏室去吧！給我幹什麼?");
        write("唐鏢衝着你不耐煩的揮了揮手，低着頭接着研究暗器圖譜。\n");
        return 0;
}
