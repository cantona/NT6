// Npc: /d/guiyun/npc/lugy.c
// Last Modified by winder on Jul. 9 2001

inherit NPC;

// string ask_yao1();
string ask_yao2();

object ob = this_object();
void create()
{
        set_name("陸冠英", ({"lu guanying", "lu", "guanying"}) );
        set("long", "他身穿熟羅長袍，背厚膀寬，軀體壯健。\n");
        set("gender", "男性" );
        set("nickname", "歸雲莊少莊主" );
        set("age", 27);
        set("attitude", "peaceful");
//        set("apprentice",1);
        set("str",25);
        set("int",25);
        set("con",27);
        set("dex",26);
        set("max_qi", 1000);
        set("max_jing", 450);
        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 30);
        set("combat_exp", 70000);

        set_skill("force", 50);
        set_skill("bibo-shengong", 50);
        set_skill("dodge", 50);
        set_skill("anying-fuxiang", 40);
        set_skill("parry", 60);
        set_skill("strike", 40);
        set_skill("luoying-shenzhang", 35);
        set_skill("leg", 40);
        set_skill("xuanfeng-tui", 30);
        set_skill("sword", 60);
        set_skill("yuxiao-jianfa", 50);
        set_skill("taoism", 20);
        set_skill("literate", 60);
        set_skill("qimen-wuxing", 80);

        map_skill("force", "bibo-shengong");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "luoying-shenzhang");
        map_skill("leg", "xuanfeng-tui");
        map_skill("parry", "luoying-shenzhang");
        map_skill("sword", "yuxiao-jianfa");
        prepare_skill("strike", "luoying-shenzhang");

        set("rank_info/respect", "少莊主");
        set("shen_type", 1);
        set("shen", 200);
        create_family("桃花島", 3, "弟子");
        set("class", "fighter");
        set("yao", 10);   

        set("inquiry", ([
                "name": "在下陸冠英，是這裏的少莊主。",
                "rumors": "聽説蒙古兵又要南侵了，唉！",
                "here": "這裏是歸雲莊，你隨便轉轉吧，累了請到客房休息。",
                "東邪": "那是師祖呀，，蒙他老人家恩准，我才能跟父親學藝。",
                "黃藥師": "那是師祖呀，，蒙他老人家恩准，我才能跟父親學藝。",
                "桃花島": "聽説是師祖住的地方，可惜沒有去看過。",
                "陸乘風": "是我的父親，找他老人家有什麼事嗎？",
                "陸冠英": "不敢，就是在下。",
                "歸雲莊": "這裏是花了我父親無數心血才建起來的，與別的莊院相比如何？",
                "太湖": "就在莊前不遠，是一個煙波浩淼的大湖。",
                "藥" : "爹爹讓我保管靈藥，桃花島弟子可以到我這裏領取。",
//                "三才聚精丹": (: ask_yao1 :),
                "六壬集氣丸": (: ask_yao2 :),
                "九花玉露丸":         "九花玉露丸煉製奇難無比，我這裏可沒有! ",
        ]) );

        setup();

        carry_object("/clone/misc/cloth.c")->wear();
}

string ask_yao1()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "桃花島" )
                return RANK_D->query_respect(ob) + "與本派素無來往，不知此話從何談起？";

        if (ob->query_condition("jingli_drug") > 0 )
                return RANK_D->query_respect(ob) + "你不是剛吃過藥嗎，怎麼又來要了？靈藥多吃有害無宜，過段時間再來吧。";

        if( query("max_jingli", ob)<200 )
                return RANK_D->query_respect(ob) + "功力不夠，靈藥多吃有害無宜，過段時間再來吧。";

        if (present("sancai dan", ob))
                return RANK_D->query_respect(ob) + "你現在身上不是有顆藥丸嗎，怎麼又來要了？真是貪得無厭！";

        if (query("yao") < 1) return "對不起，藥已經發完了，新的還未煉出。";
   
        new("/d/taohua/obj/sancai-dan")->move(ob);

        addn("yao", -1);

        message_vision("$N獲得一顆三才聚精丹。\n", ob);
        return "好吧，此藥練之不易，對練武之人大有好處，你要小心收藏好了。";
}

string ask_yao2()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "桃花島" )
                return RANK_D->query_respect(ob) + "與本派素無來往，不知此話從何談起？";

        if (ob->query_condition("medicine") > 0 )
                return RANK_D->query_respect(ob) + "你不是剛吃過藥嗎，怎麼又來要了？靈藥多吃有害無宜，過段時間再來吧。";

        if( query("max_neili", this_player())<400 )
                return RANK_D->query_respect(ob) + "功力不夠，靈藥多吃有害無宜，過段時間再來吧。";

        if (present("liuren wan", ob))
                return RANK_D->query_respect(ob) + "你現在身上不是有顆藥丸嗎，怎麼又來要了？真是貪得無厭！";

        if (query("yao") < 1) return "對不起，藥已經發完了，新的還未煉出。";

         if( query("max_neili", ob) >= (ob->query_skill("force")*8+query("combat_exp", ob)/1000) )
                     return RANK_D->query_respect(ob) + "此藥已經難以在幫助你提高內力修為了！";
        new("/clone/medicine/liuren-wan")->move(ob);

        addn("yao", -1);

        message_vision("$N獲得一顆六壬集氣丸。\n", ob);
        return "好吧，此藥練之不易，對練武之人大有好處，你要小心收藏好了。";
}

