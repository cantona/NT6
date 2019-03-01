// Npc: /kungfu/class/shaolin/qing-yuan.c
// Date: YZC 96/01/19

inherit NPC;

void create()
{
        set_name("清緣比丘", ({
                "qingyuan biqiu",
                "qingyuan",
                "biqiu",
        }));
        set("long",
                "他是一位體格強健的壯年僧人，他身得虎背熊腰，全身似乎藴含\n"
                "着無窮勁力。他身穿一襲白布黑邊袈裟，似乎身懷武藝。\n"
        );


        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 30);
        set("shen_type", 1);
        set("str", 21);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 350);
        set("max_jing", 200);
        set("neili", 350);
        set("max_neili", 350);
        set("jiali", 30);
        set("combat_exp", 5000);
        set("score", 100);

        set_skill("force", 30);
        set_skill("shaolin-xinfa", 30);
        set_skill("dodge", 30);
        set_skill("shaolin-shenfa", 30);
        set_skill("strike", 30);
        set_skill("qianye-shou", 30);
        set_skill("parry", 30);
        set_skill("buddhism", 30);
        set_skill("literate", 30);

        map_skill("force", "shaolin-xinfa");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("strike", "qianye-shou");
        map_skill("parry", "qianye-shou");

        prepare_skill("strike", "qianye-shou");

        create_family("少林派", 40, "弟子");

        set("master_ob",1);
        set("master_ob",1);
        setup();

        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}

void init()
{        
        object ob;

        ::init();
        if( interactive(ob = this_player()) ) {
                remove_call_out("speaking");
                call_out("speaking", 1, ob);
        }
}

void speaking(object ob)
{
        if ( random(5) < 1 ) 
        {        
                switch( random(4) ) {
                case 0:
                       command("say 百年前的一場大火，整個少林寺就除這監牢和北邊的鐘樓沒遭災。唉。。。\n");
                       break;
                case 1:
                       command("say 這裏四周全用鋼汁澆縫的花崗巖給封了起來，你們就是變成蒼蠅也飛不出去！\n");
                       break;
                case 2:
                       command("say 好好呆着別動，等會兒自然會放你們出去，不過你們自己要打架我可不管！\n");
                       break;
                case 3:
                       command("say 嘿，歷年來多少鉅奸大盜都在這裏被關過，北邊牢裏的獄卒就是其中一個。\n");
                       break;
                }
        }
}

