// huangshan.c 黃裳
// Last Modified by winder on Aug. 18 2002

inherit NPC;
string ask_book();
string ask_jing();

void create()
{
        set_name("黃裳", ({ "huang shang", "huang", "shang" }));
        set("long","
　　黃裳，劍浦人，字冕仲、號演山。生卒年不詳。
　　黃裳為書生時，常有魁天下之志。自敍門狀，予家劍潭之濱，鬥牛之
光，上下相照，風雷之信，時有變現。又題黃龍州雲：“看取黃龍沙鬥起， 
滿城風雨入豐年。”元豐四年（1081），郡之譙門，忽為風雷所擊，黃裳
聞之，賦詩道：“風雷昨夜破枯枝，借問天公有意無，莫是卧龍蹤跡困，
放教頭角入亨衢。”次年，黃裳對策，果為天下第一。宋神宗對黃裳之文
章極為喜爰，禮部奏進士，有黃裳名，及進讀試策，前幾位皆不合神宗之
意，神宗等黃裳名出現，但未甲才始聽到，遂親擢為第一。考官因高下失
實被處罰金。
　　黃裳為官清正恬退。政和間（1111—1118），知福州，嘗為禮部侍郎，
遷尚書。當時三舍法實行，黃裳認為“宜近不宜遠，宜少不宜老，宜富不
宜貧，不如遵祖宗科舉之制。”黃裳享年八十七歲，著有《演山集》六十
卷行於世。
    歷史上，黃裳乃一介書生，與武無緣。

");
        set("gender", "男性");
        set("age", 61);
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        
        set("max_jing", 3000);
        set("max_qi", 5000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 50);
        set("combat_exp", 5000000);
        set("score", 60000);
        set("inquiry", ([
                "祕籍" : (: ask_jing :),
                "jing" : (: ask_jing :),
                "book" : (: ask_book :),
                "九陰真經" : (: ask_jing :),
                "萬壽道藏" : (: ask_book :),
        ]));
        set("book_count", 1);
        set("jing_count", 1);
        setup();
}

string ask_book()
{
        mapping fam; 
        object ob, me = this_player();

        if (query("book_count") < 1)
                return "這麼笨重的書，"+RANK_D->query_respect(me)+ "要來又有啥用？";
        if (me->query_skill("taoism",1) < 100)
                return "這部萬壽道藏太過艱深，"+RANK_D->query_respect(me)+ "恐怕讀不懂罷？";
        addn("book_count", -1);
        ob = new(BOOK_DIR"daojing");
        if (ob->violate_unique())
        {
                destruct(ob);
                return "這麼笨重的書，"+RANK_D->query_respect(me)+ "要來又有啥用？";
  }
        ob->move(environment(me));
        command("rumor"+query("name", me)+"拿到萬壽道藏啦。\n");
        tell_room(environment(me), "黃裳轉過身去，從書架上抱下一部大書，堆在地上。\n", ({ob}));
        return "好吧，這部「萬壽道藏」你拿回去好好鑽研。";
}

string ask_jing()
{
        mapping fam; 
        object ob, me = this_player();
        mixed sks;
        string skl;
        
        if (query("jing_count") < 1)
                return "《九陰真經》是我幾十年心血所駐，豈能輕給？";
        if( !query("xkd/skill", me) )
                return "《九陰真經》所載武功博大精深，"+RANK_D->query_respect(me)+ "恐怕讀不懂罷？";
        if( query("kar", me) != query("kar") && !wizardp(me) )
                return "萬事隨緣，學習武功也是這樣的，你看，很不巧，你要的《九陰真經》給人借閲未還。";
        addn("jing_count", -1);
        ob = new(BOOK_DIR"9book");
        if (ob->violate_unique()) 
        {
                destruct(ob);
                return "《九陰真經》是我幾十年心血所駐，豈能輕給？";
        }
        sks=query("xkd/skill", me);
        if (arrayp(sks))
                skl = sks[random(sizeof(sks))];
        else        if (stringp(sks))
                skl = sks;
//        ob->set("skill/name", me->query("xkd/skill") );
        set("skill/name", skl, ob);
        set("skill/exp_required", 1000000, ob);
        set("skill/jing_cost", 50, ob);
        set("skill/difficulty", 50, ob);
        set("skill/min_skill", 300, ob);
        set("skill/max_skill", 350, ob);
        ob->move(me);
        command("rumor"+query("name", me)+"拿到九陰真經原本啦。\n");
        return "這本「九陰真經」你拿去好好鑽研，當有進益。";
}