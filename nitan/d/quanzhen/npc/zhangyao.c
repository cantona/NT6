// zhangyao.c 掌藥道長

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("掌藥道長", ({"zhangyao"}));
        set("gender", "男性");
        set("age", 28);
        set("class", "quanzhen");
        set("long",
                "這是全真教中的掌管所有藥物的道人。他年紀不大，但看起來\n"
                "顯得少年老成。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 21);
        set("int", 22);
        set("con", 23);
        set("dex", 22);

        set("qi", 600);
        set("max_qi", 600);
        set("jing", 400);
        set("max_jing", 400);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 0);

        set("combat_exp", 30000);
        set("score", 20000);

        set_skill("array", 30);
        set_skill("force", 60);
        set_skill("xiantian-gong", 50);    //先天氣功
        set_skill("sword", 60);
        set_skill("quanzhen-jian", 60);  //全真劍
        set_skill("dodge", 50);
        set_skill("jinyan-gong", 50);   //金雁功
        set_skill("parry", 60);
        set_skill("unarmed", 60);
        set_skill("strike", 60);
        set_skill("haotian-zhang", 50);    //昊天掌
        set_skill("cuff", 60);
        set_skill("chunyang-quan", 50);    //純陽拳
        set_skill("literate", 50);
        set_skill("taoism", 40);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("strike", "haotian-zhang");
        map_skill("cuff", "chunyang-quan");
        prepare_skill("cuff", "chunyang-quan");
        prepare_skill("strike", "haotian-zhang");

        create_family("全真教", 4, "弟子");

        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄門正宗。\n",
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/yellowrobe")->wear();
}

int accept_object(object who, object ob)
{
        object obj,obj1,obj2;
        object me=this_player();

        if( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("你沒有這件東西。\n");

        if( query("name", ob) != HIB"烏龜甲"NOR
                 && query("id", ob) != "fuling" )
                    return notify_fail("掌藥道長搖頭道：這不是配藥的材料。\n");

        if( query("name", ob) == HIB"烏龜甲"NOR )
        {
                if(query_temp("fuling")) {
                        write(MAG"掌藥道長大喜，龜甲和茯苓都有了，這副龜苓膏可煉成了。\n"NOR);
                        obj=new("/clone/medicine/nostrum/guilinggao");
                        obj->move(who);
                        delete_temp("guijia");
                        delete_temp("fuling");
                        if(!(obj2=present("gui jia", this_player())))
                        destruct(obj2);
                        remove_call_out("destroying");
                        call_out("destroying", 1, me, ob);

                        return 1;
                }
                else {
                        if(query_temp("guijia")) {
                                write(YEL"掌藥道長搖了搖頭道：“龜甲我已經有了。”\n"NOR);
                                return 0;
                        }
                        else {
                                set_temp("guijia",1);
                                write(WHT"掌藥道長笑道：龜甲有了，就缺茯苓了。\n"NOR);
                                if(!(obj2=present("gui jia", this_player())))
                                destruct(obj2);
                                remove_call_out("destroying");
                                call_out("destroying", 1, me, ob);
                                return 1;
                        }
                }
        }
        if( query("id", ob) == "fuling" )
        {
                if(query_temp("guijia")) {
                        write(MAG"掌藥道長大喜，龜甲和茯苓都有了，這副龜苓膏可煉成了。\n"NOR);
                        obj=new("/clone/medicine/nostrum/guilinggao");
                        obj->move(who);
                        delete_temp("guijia");
                        delete_temp("fuling");
                        if(!(obj1=present("fuling", this_player())))
                        destruct(obj1);
                        remove_call_out("destroying");
                        call_out("destroying", 1, me, ob);
                        return 1;
                }
                else {
                        if(query_temp("fuling")) {
                                write(YEL"掌藥道長搖了搖頭道：“茯苓我已經有了。”\n"NOR);
                                return 0;
                        }
                        else {
                                set_temp("fuling",1);
                                write(WHT"掌藥道長笑道：茯苓有了，就缺龜甲了。\n"NOR);
                                if(!(obj2=present("fuling", this_player())))
                                destruct(obj2);
                                remove_call_out("destroying");
                                call_out("destroying", 1, me, ob);
                                return 1;
                        }
                }
        }

}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}
void attempt_apprentice(object ob)
{
        command("say 我不收弟子，你去找別的道長吧。");
}
