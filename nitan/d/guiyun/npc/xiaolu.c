// xiaolu.c

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("陸冠英", ({ "lu guanying", "lu" }));
        set("long", "
他是歸雲莊少莊主陸冠英。他肩寬背闊，軀體甚是壯健，
但行動之間温文爾雅，謙恭有禮，一派世家子弟風範。
傳聞他就是太湖羣盜的首領，不知是真是假。\n");
        set("gender", "男性");
        set("age", 21);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("shen_type", 1);
        set("per", 26);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        
        set("max_qi", 600);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 20);
        set("combat_exp", 150000);
        set("score", 6000);

        set_skill("force", 50);
        set_skill("bibo-shengong", 50);
        set_skill("dodge", 50);
        set_skill("anying-fuxiang", 50);
        set_skill("parry", 50);
        set_skill("sword", 50);
        set_skill("yuxiao-jianfa", 50);

        map_skill("force", "bibo-shengong");
        map_skill("dodge", "anying-fuxiang");
        map_skill("sword", "yuxiao-jianfa");
        map_skill("parry", "yuxiao-jianfa");

        set("inquiry", ([
                "歸雲莊" : (: ask_me :),
        ]));

        set("book_count", 1);
        create_family("桃花島", 3, "弟子 歸雲莊少莊主");
        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

init()
{
        add_action("do_decide", "decide");
}

/*
void attempt_apprentice(object ob)
{
        if (ob->query_dex() < 20)
        {
           command("say 我派武功講究輕靈巧捷。");
           command("say 這位"+RANK_D->query_respect(ob)+"可能是白來歸雲莊一趟了。");
           return;
        }
        if( query("shen", ob)<0 )
        {
           command("say 我派在江湖中立身尚正，"+ RANK_D->query_respect(ob)+"請回吧。");
           return;
        }
        if( query("gender", ob) == "無性" )
        {
           command("say 師祖最討厭不男不女的東西了，這位"+RANK_D->query_respect(ob)+"趕快請吧。");
           return;
        }
        if( query("class", ob) == "bonze" )
        {
           command("say 師祖最愛非僧抑道了，這位"+RANK_D->query_respect(ob)+"還是請回吧。");
           return;
        }
        if (ob->query_skill("literate",1) <= 10)
        {
           command("say 桃花島只收讀書人作弟子，這位"+RANK_D->query_respect(ob)+"是否去讀點書再來。");
           return;
        }
        command("smile");
        command("say " + RANK_D->query_respect(ob) + "入我門下，需努力不墮。");
        command("recruit "+query("id", ob));
}
*/


string ask_me()
{
        object me = this_player();
        set_temp("guiyun/decide", 1, me);

        if( query("family/family_name", me) != "桃花島" )
           return "歸雲莊就是在下居處，如果"+RANK_D->query_respect(me)+"有意(decide)，我可修書一封代為引薦。\n";
        command("say 這位"+ RANK_D->query_respect(me)
               + "來得正好，這裏正有馬車要回莊辦事，就讓他們送你一程吧。\n");
//      message_vision(HIC"陸冠英一招手，一輛馬車駛過來停在門前。\n$N急忙鑽進車中，只聽一陣清脆的鞭響，馬車絕塵而去。\n\n"NOR,me);
//        ob = load_object("/d/guiyun/dayuan");
//        ob = find_object("/d/guiyun/dayuan");
//        message("vision", "遠處一輛馬車急駛而來，車門一開"+me->query("name")+"從裏面鑽了出來。\n", ob);
//            tell_object(me, "只聽車把勢説道：這位"+ RANK_D->query_respect(me) + "已經到了，請下車吧。\n"NOR );
        me->move("/d/guiyun/dayuan");           
}

int do_decide()
{
        object ob, me;
        me = this_player();
        if( !query_temp("guiyun/decide", me) )
        {
                message_vision("$N對$n奇怪地説道：你要決定幹嘛？\n", this_object(), me);
                return 1;
        }
        delete_temp("guiyun/decide", me);
        ob = new(__DIR__"obj/xin");
        ob->move(me);
        message_vision("$N雙手抱拳，道：有勞少莊主費心了。\n", me);
        message_vision("$N説道：好！\n", this_object());
        message_vision("$N給$n一封書信。\n", this_object(), me);
        message_vision("$N説道：這位"+RANK_D->query_respect(me) + "請先到敝莊盤恆數日，以後再圖相敍。\n", this_object());
        return 1;
}
