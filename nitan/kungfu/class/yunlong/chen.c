// chen.c 陳近南

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "yunlong.h"
int ask_tuihui();
mixed ask_me();
string ask_me1();

void create()
{
        set_name("陳近南", ({ "chen jinnan", "chen","jinnan" }));
        set("title", HIR "天地會"HIM"總舵主"NOR );
        set("nickname", HIC "英雄無敵" NOR);
        set("long",
                "\n這是一個文士打扮的中年書生，神色和藹。\n"
                "他就是天下聞名的天地會總舵主陳近南，\n"
                "據説十八般武藝，樣樣精通。\n"
                "偶爾向這邊看過來，頓覺他目光如電，英氣逼人。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 45);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 120);
        set("combat_exp", 2000000);
        set("score", 500000);
        set_skill("literate", 600);

        set_skill("force", 600);
        set_skill("dodge", 600);
        set_skill("unarmed", 600);
        set_skill("parry", 600);
        set_skill("claw", 600);
        set_skill("blade", 600);
        set_skill("wuhu-duanmendao", 600);
        set_skill("sword", 600);
        set_skill("yunlong-jian", 600);
        set_skill("whip", 600);
        set_skill("yunlong-bian", 600);
        set_skill("houquan", 600);
        set_skill("yunlong-xinfa", 600);
        set_skill("yunlong-shengong", 600);
        set_skill("yunlong-shenfa", 600);
        set_skill("ningxue-shenzhao", 600);

        map_skill("dodge", "yunlong-shenfa");
        map_skill("force", "yunlong-shengong");
        map_skill("unarmed", "houquan");
        map_skill("parry", "ningxue-shenzhao");
        map_skill("claw", "ningxue-shenzhao");

        prepare_skill("claw","ningxue-shenzhao");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "claw.ji" :),
                (: exert_function, "recover" :),
        }) );

        create_family("雲龍門",1, "開山祖師");
        set("book_count", 1);
        set("inquiry", ([
                "天地會" :  "只要是英雄好漢，都可以入我天地會(join tiandihui)。",
                "入會" :  "還不快快如天地會一同反清復明。",
                "反清復明" : "去棺材店和回春堂仔細瞧瞧吧！\n",
                "暗號"     : "敲三下！\n",
                "切口"     : "敲三下！\n",
                "絕招" : (: ask_me :),
                "絕技" : (: ask_me :),
                "疾電" : (: ask_me :),
                "凝血神爪" : (: ask_me :),
                "雲龍劍譜" : (: ask_me1 :),
                "退會" : (: ask_tuihui :),
                "tuihui"   : (: ask_tuihui :),
        ]) );

        set("master_ob", 5);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_join","join");
}

int ask_tuihui()
{
        object ob;
        ob=this_player();

        if( query("party/party_name", ob) != "天地會" )
        {
                message_vision("陳近南笑了笑，對$N説道：你還沒"
                               "加入我天地會呢，退什麼退？\n", ob);
                return 1;
        }
        command("look "+query("id", ob));
        command("sigh ");
        command("say 反清復明，就要堅貞志士，你去吧! ");
        delete("party", ob);
        delete("rank", ob);
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/ningxue-shenzhao/ji", me) )
                return "你真會開玩笑，會了還來找我。";

/*
        if( !query("story/shenzhao", me) )
                return "你打聽這個幹嘛？";
*/

        if( query("shen", me)<1000000 )
                return "習武之人最重一個“俠”字，俠義方面你還做得不夠！";

        if (me->query_skill("ningxue-shenzhao", 1) < 250)
                return "你的凝血神爪還不到家，要多練練！";

        message_vision(HIY "$n" HIY "點了點頭，變掌為爪，"
                       "隨意揮灑而出，雙爪頓時幻出漫天爪影，"
                       "氣勢恢弘無比。\n" NOR,
                       me, this_object());
        command("nod");
        command("say 你可明白了？");
        tell_object(me, HIC "你學會了「疾電」這一招。\n" NOR);
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 500000);
        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 500000);
        if (me->can_improve_skill("ningxue-shenzhao"))
                me->improve_skill("ningxue-shenzhao", 500000);
        set("can_perform/ningxue-shenzhao/ji", 1, me);
        return 1;
}

string ask_me1()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "雲龍門")
                return RANK_D->query_respect(this_player())+ "與本派素無來往，不知此話從何談起？";
        if (query("book_count") < 1)
                return "你來晚了，本派的雲龍真經不在此處。";
        addn("book_count", -1);
        ob = new("/clone/book/yljianpu");
        ob->move(this_player());
        return "好吧，這本「雲龍劍譜」你拿回去好好鑽研。";
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("yunlong-shengong", 1) < 50)
        {
                command("say 我雲龍神功乃內家武功，最重視內功心法。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否還應該在雲龍神功上多下點功夫？");
                return;
        }
        if( query("weiwang", ob)<60 )
        {
                command("say 我雲龍門武功天下無敵，凡入我門，\n必闖蕩江湖，行俠仗義，為天下蒼生謀福利。\n");
                command("say " + RANK_D->query_respect(ob) +
                        "是否應該先出去闖一闖，做幾件驚天動地的大事？");
                return ;
        }
        if( query("shen", ob)>0 && query("shen", ob)<5000){
                command("say 學武之人，德義為先，功夫的高低倒還在其次，未練武，要先學做人。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return ;
        }
        if( query("weiwang", ob)<80 )
        {
                if( query("shen", ob)<0 )
                command("say "+ RANK_D->query_respect(ob) +"雖然是邪派中人，但也還做了些好事。\n");
                command("chat 我天地會所作所為，無一不是前人所未行之事。\n");
                command("chat 萬事開創在我，駭人聽聞，物議沸然，又何足論？\n");
                command("chat 今天就收了你吧！！\n");
                command("chat 想不到我一身驚人藝業，今日終於有了傳人，哈哈哈哈！！！！\n");
                message_vision(HIC "$N的江湖威望提高了！\n" NOR,this_player());
                set("weiwang", 80, ob);
        }
        command("recruit "+query("id", ob));
        if( (!query("class", ob)) || (query("class", ob) != "fighter") )
                set("class", "fighter", ob);
}

#include "/kungfu/class/yunlong/tiandihui.h"
