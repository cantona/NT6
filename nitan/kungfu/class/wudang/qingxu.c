// guxu.c 清虛

//#include "daozhang.h"
inherit NPC;
//inherit F_MASTER;

string ask_me();

void create()
{
        set_name("清虛道長", ({ "qingxu daozhang", "qingxu" }));
        set("long",
                "他就是俞蓮舟的弟子清虛道長。\n"
                "他今年二十多歲，主管復真觀的雜事。\n"
                "專門在這裡看守本派的各種道經");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 22);
        set("int", 22);
        set("con", 22);
        set("dex", 22);

        set("max_qi", 1800);
        set("max_jing", 900);
        set("neili", 2400);
        set("max_neili", 2400);
        set("jiali", 30);

        set("combat_exp", 70000);
        set("score", 8500);

        set_skill("force", 85);
        set_skill("yinyun-ziqi", 85);
        set_skill("dodge", 80);
        set_skill("tiyunzong", 80);
        set_skill("strike", 85);
        set_skill("wudang-zhang", 85);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("wudang-jian", 80);
        set_skill("taoism", 50);
          set_skill("literate", 50);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        create_family("武當派", 3, "弟子");
        set("class", "taoist");

        set("inquiry", ([
                "道德經" : (: ask_me :),
                "武當派" : "貧道便是武當派弟子，不知這位"+ RANK_D->query_respect(this_player())+"有何見教？",
                "太極劍法" : "嗯……這我不大清楚，你得去問沖虛師兄。",
                "武當劍" : "嗯……武當劍的質地柔韌不足，堅硬易脆，對方如果使用重器械，則不宜與其硬碰硬撞。",
                "兩儀劍法" : "兩儀劍法中有陰有陽，亦剛亦柔，神妙精微無比。",
                "武當兩儀劍" : "兩儀劍法中有陰有陽，亦剛亦柔，神妙精微無比。",
                "繞指柔劍" : "這路劍法我可不會使。",
                "神門十三劍" : "這路劍法我可不會使。",
                "武當長拳" : "拳腳功夫非貧道所長。",
                "綿掌" : "拳腳功夫非貧道所長。",
                "震山掌" : "拳腳功夫非貧道所長。",
                "虎爪絕戶手" : "嗯……曾聽說敝派有這一路武功，但從未見師伯師叔使過。",
                "張三豐" : "敝派創派祖師，近年來常年閉關不出。",
                "張真人" : "敝派創派祖師，近年來常年閉關不出。",
                "宋遠橋" : "那是敝派掌門大師伯。",
                "宋大俠" : "那是敝派掌門大師伯。",
                "俞蓮舟" : "那是二師伯。",
                "俞二俠" : "那是二師伯。",
                "俞岱巖" : "那是三師伯。",
                "俞三俠" : "那是三師伯。",
                "張鬆溪" : "貧道的授業恩師",
                "張四俠" : "貧道的授業恩師",
                "張翠山" : "………那是貧道的五師叔。",
                "張五俠" : "………那是貧道的五師叔。",
                "殷梨亭" : "那是六師叔。",
                "殷六俠" : "那是六師叔。",
                "莫聲谷" : "那是七師叔。",
                "莫七俠" : "那是七師叔。",
                "宋青書" : "好久沒見到宋師哥了，聽說他和莫七叔吵過架，就此再沒回武當過。",
                "沖虛" : "他是貧道的師兄，三代弟子中也就他會使太極劍法。",
                "沖虛道長" : "他是貧道的師兄，三代弟子中也就他會使太極劍法。",
                "谷虛" : "谷虛師兄是三代弟子中的佼佼者，近年來負責在山上主持武當事務。",
                "谷虛道長" : "谷虛師兄是三代弟子中的佼佼者，近年來負責在山上主持武當事務。",
                "清虛道長" : "貧道便是清虛，不知這位"+ RANK_D->query_respect(this_player())+"有何見教？",
                "凌虛" : "凌虛師弟在遇真宮，負責制造香火。",
                "凌虛道長" : "凌虛師弟在遇真宮，負責制造香火。",
                "制香" : "凌虛師弟在遇真宮，負責制造香火。",
                "制香道長" : "凌虛師弟在遇真宮，負責制造香火。",
                "靈虛" : "靈虛師弟在山門，負責接待來客。",
                "靈虛道長" : "靈虛師弟在山門，負責接待來客。",
                "知客" : "靈虛師弟在山門，負責接待來客。",
                "知客道長" : "靈虛師弟在山門，負責接待來客。",
                "成高" : "他是貧道的師侄，以前曾與貧道在西域住過十幾年，現在負責看守榔梅園。",
                "成高道長" : "他是貧道的師侄，以前曾與貧道在西域住過十幾年，現在負責看守榔梅園。",
                "守園" : "他是貧道的師侄，以前曾與貧道在西域住過十幾年，現在負責看守榔梅園。",
                "守園道長" : "他是貧道的師侄，以前曾與貧道在西域住過十幾年，現在負責看守榔梅園。",
                "炸藥" : "嗯……這我不大清楚，你得去問成高師侄。",
                "火藥" : "嗯……這我不大清楚，你得去問成高師侄。",
                "制造炸藥" : "嗯……這我不大清楚，你得去問成高師侄。",
                "制造火藥" : "嗯……這我不大清楚，你得去問成高師侄。",
                "機關" : "貧道曾在西域向當地工匠學過機關削器之術。",
                "機關削器" : "貧道曾在西域向當地工匠學過此術。",
        ]));

        set("book_count", 1);

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}


string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player()) )
            || fam["family_name"] != "武當派")
        {
                return RANK_D->query_respect(this_player()) +
                       "與本派素無來往，不知此話從何談起？";
        }

        if (query("book_count") < 1)
                return "你來晚了，本派的道德真經不在此處。";

        addn("book_count", -1);
        ob = new("/clone/book/daodejing-ii");
        ob->move(this_player());
        return "好吧，這本「道德經」你拿回去好好鑽研。";
}
