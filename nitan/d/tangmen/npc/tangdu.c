// tangdu

inherit NPC;

int give_job();
int give_duyao();

void create()
{
        set_name("唐毒", ({ "tang du", "tang", "du"}));
        set("long", 
"唐毒xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx。\n");
        set("gender", "男性");
        set("age", 25);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 25);
        set("con", 24);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);
        set("shen", 2000);
        set("combat_exp", 100000);
        set("level", 8);
        set("score", 7000);

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

        
        create_family("唐門世家", 3, "弟子");

        set("inquiry", ([
                "job" : ( : give_job  : ),
                "工作": ( : give_job  : ),
                "duyao": ( : give_duyao : ),
                "毒藥": ( : give_duyao : ),
        ]));

        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),  
                (: exert_function, "powerup" :),  
                // ( : command("wield all") : ),
                (: perform_action, "throwing.san" :),                  
        }) );        
        
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);  

        set("duyao", 200);  

        setup();
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));  
        carry_object("/d/tangmen/obj/feidao");
}

int give_job()
{
        object me, du;
        string msg, targ;
        int coun;

        string *tar = ({
                "","蜈蚣","毒蠍子","竹葉青","金環蛇","蝮蛇","千年毒王",
//                "蠍毒","蠍子殼","蠍子尾","蝮蛇毒","蝮蛇膽","蝮蛇皮","青蛇毒","青蛇膽","青蛇皮","金蛇毒","金蛇膽","金蛇皮",
        });

        me = this_player();
        du = this_object();

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                say("唐毒說道:“我現在沒心情給你派活，等我回制毒房再說吧！”\n");
                return 0;
        }

        if( !query_temp("tangmen/du", me) )
                command("say “這裡沒有活能給你幹，你聽誰說的？”");
        else
        {
                if( query_temp("duyao", me) )
                {
                        command("say “你還沒有完成剛才給你的任務呢！”");
                        return 1;
                }
                coun = 1 + random(sizeof(tar));
                if ( coun == sizeof(tar) )
                        coun = ( sizeof(tar) - 1 );
                targ = tar[coun];
                printf("%d/%d\n",coun,sizeof(tar));
                say("唐毒說道:“我這裡正缺一味毒物，快去給我找一只" + targ + "來吧！”\n");
                set_temp("duyao", coun, me);
        }
        return 1;
}

int give_duyao()
{
        object me = this_player();
        object ob;
        
        if ( me->is_busy() )
        {
                command("say 你正忙著呢！\n");
                return 1;
        }

        if( query("family/family_name", me) != "唐門世家" )
        {
                command("say 你不是我唐門中人，我無法給你毒藥！\n");
                return 1;
        } else
        if ( query("duyao") < 1 )
        {
                command("say 我這裡的毒藥已經給完了！\n");
                return 1;
        } else
        {
                command("say 此毒藥含有巨毒，普天之下只有三人能解，千萬要注意不要自己中毒了！\n");
                ob = new("/d/tangmen/obj/duyao");
//                ob->move(this_object(), 1);
//                command("givetangmenqiduto"+query("id", me));
                ob->move(me, 1);
                message_vision("$N對$n點了點頭，道：此毒藥含有劇毒，可要小心使用。\n", this_object(), me); 
                addn("duyao", -1);
                me->start_busy(1);
                return 1;
        }
                

}

int accept_object(object who, object ob)
{
        command("say 要是找到了，就放到儲藏室去吧！給我幹什麼?");
        write("唐毒沖著你揚了揚手中一只墨綠色的蟲子，嘿嘿姦笑了幾聲。\n");
        return 0;
}
