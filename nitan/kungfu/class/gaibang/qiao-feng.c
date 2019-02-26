// qiao-feng.c

#include <ansi.h>;
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_MANAGER;
string ask_me();

void create()
{
        set_name("喬峯", ({"qiao feng", "feng", "qiao"}));
        set("nickname", "北喬峯");
        set("gender", "男性");
        set("age", 29);
        set("long",
"他就是丐幫第十任幫主，在江湖上與燕子塢的慕容復並稱為「北喬峯，南慕容」。
他身穿一件普通的粗布褂子，腰間用一條麻繩隨便一系。他身高六尺有餘，體格
十分魁梧，長有一張線條粗曠、十分男性化的臉龐，雙目如電，炯炯有神。\n");
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 10);

        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 300);

        set("combat_exp", 3000000);
        set("score", 200000);
        set("shen", 100000);

        set_skill("force", 200);             // 基本內功
        set_skill("huntian-qigong", 200);    // 混天氣功
        set_skill("unarmed", 200);           // 基本拳腳
        set_skill("dodge", 200);                   // 基本躲閃
        set_skill("xiaoyaoyou", 300);        // 逍遙遊
        set_skill("parry", 200);             // 基本招架
        set_skill("strike", 200);            // 基本掌法
        set_skill("dragon-strike", 300);   // 降龍十八掌
        set_skill("hand", 200);              // 基本手法
        set_skill("suohou-hand", 300);       // 鎖喉擒拿手
        set_skill("blade", 200);             // 基本刀法
        set_skill("liuhe-dao", 300);       // 四象六合刀
        set_skill("staff", 200);             // 基本杖法
        set_skill("fengmo-zhang", 300);      // 瘋魔杖法
        set_skill("stick", 200);             // 基本棒法
        set_skill("dagou-bang", 300);        // 打狗棒法
        set_skill("begging", 100);           // 叫化絕活
        set_skill("checking", 100);          // 道聽途説
        set_skill("training", 100);          // 馭獸術
        set_skill("lianhua-zhang",85); // 蓮花掌

        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("hand",  "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "dagou-bang");
        map_skill("stick", "dagou-bang");
        map_skill("staff", "fengmo-zhang");
//        prepare_skill("hand",  "suohou-hand");
        prepare_skill("strike", "dragon-strike");

        set("inquiry",([
                "祕籍"     : (: ask_me :),
                "棒法入門" : (: ask_me :),
        ]));
        set("book_count", 1);
        //set("party/party_name", HIC"丐幫"NOR);
        //set("party/rank", HIR"幫主"NOR);
        //set("party/level", 10);
        create_family("丐幫", 10, "幫主");

        setup();

        carry_object(__DIR__"obj/lvyv_bang")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
//      carry_object(BOOK_DIR"stick_book")->wear();
}

/*
void init()
{
         object ob;
        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_qiecuo","qiecuo");
}


void greeting(object me)
{
               mapping myfam;
        myfam=query("family", me);
        if( (myfam["family_name"] == "丐幫") && (!me->query_skill("huntian-qigong",1)) && (query("combat_exp", me)>500000) )
        {
                command("say 你竟敢放棄本門心法！從我這裏滾出去吧！");
                command("expell"+query("id", me));
        }

}
*/

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        command("sigh");
        command("say 走開，我不收徒。");
        return;

        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<200000 )
        {
                command("say 你的江湖經驗不夠，還是先向各位長老學習吧。");
                return;
        }

        if( query("shen", ob)<30000 )
        {
                command("say 你身為丐幫弟子，竟然不做好事？");
                return;
        }

        if( query("family/beggarlvl", ob)<5 )
        {
                command("say 你在本幫的地位太低，還是先向各位長老學習吧。");
                return;
        }

        if ((int)ob->query_str() < 26)
        {
                command("say 我的武藝以剛猛為主，你膂力不行，還是算了吧。");
                return;
        }

        if (ob->query_skill("force") < 150)
        {
                command("say 你的內功火候還不夠，還是先向各位長老學習吧。");
                return;
        }
        command("nod");
        command("say 我今日便收你為徒，倘若勤懇努力，將來必有一番作為。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "丐幫")
                return RANK_D->query_respect(this_player()) +"與本派毫無瓜葛，我派的武功典籍可不能交給你。";
        if (query("book_count") < 1)
                return "你來晚了，本派的祕籍不在此處。";
        addn("book_count", -1);
        ob = new("/clone/book/stick_book.c");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到棒法入門啦。\n");
        return "好吧，這本「棒法入門」你拿回去好好鑽研。";
}
