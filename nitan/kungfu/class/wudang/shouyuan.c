// shouyuan.c 守園道長

//#include "daozhang.h"
inherit NPC;
//inherit F_MASTER;

void create()
{
        set_name("成高道長", ({ "chenggao daozhang", "chenggao", "daozhang", "shouyuan" }));
        set("nickname", "守園道長");
        set("long","他是凌虛的師侄，劍術算不得很精，但年輕之時，曾在西域住過十幾年，\n懂得善制炸藥，現今是看守榔梅園的道長。\n");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "taoist");
        set("str", 21);
        set("int", 21);
        set("con", 21);
        set("dex", 21);

        set("max_qi", 600);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 30);
        set("combat_exp", 30000);
        set("score", 4000);

        set_skill("force", 50);
        set_skill("taiji-shengong", 40);
        set_skill("dodge", 50);
        set_skill("tiyunzong", 40);
        set_skill("unarmed", 50);
        set_skill("taiji-quan", 50);
        set_skill("parry", 50);
        set_skill("sword", 50);
        set_skill("wudang-jian", 40);
        set_skill("wudang-quan", 40);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        set("inquiry", ([
                "name" : "貧道道號成高，負責看守榔梅園，不知這位"+RANK_D->query_respect(this_player()) +"有何見教？",
                "武當" : "貧道便是武當派弟子，不知這位"+ RANK_D->query_respect(this_player())+"有何見教？",
                "武當派" : "貧道便是武當派弟子，不知這位"+ RANK_D->query_respect(this_player())+"有何見教？",
                "劍法" : "本門劍法貧道尚未練到家，不敢妄加評論。",
                "太極劍" : "嗯……這個我不大清楚。",
                "太極劍法" : "嗯……這個我不大清楚。",
                "武當劍" : "武當劍？",
                "武當劍法" : "本門劍法貧道尚未練到家，不敢妄加評論。",
                "兩儀劍法" : "兩儀劍法的劍招一陰一陽，一剛一柔，必須二人同使。",
                "武當兩儀劍" : "兩儀劍法的劍招一陰一陽，一剛一柔，必須二人同使。",
                "繞指柔劍" : "這路劍法貧道沒能學會。",
                "神門十三劍" : "這路劍法貧道沒能學會。",
                "武當長拳" : "拳腳功夫非貧道所長。",
                "綿掌" : "拳腳功夫非貧道所長。",
                "震山掌" : "拳腳功夫非貧道所長。",
                "虎爪絕戶手" : "嗯……聽說敝派好像是有這一路武功，不過貧道不大清楚。",
                "張三豐" : "敝派創派祖師，近年來常年閉關不出，我也未見過幾次。",
                "張真人" : "敝派創派祖師，近年來常年閉關不出，我也未見過幾次。",
                "宋遠橋" : "那是敝派掌門。",
                "宋大俠" : "那是敝派掌門。",
                "俞蓮舟" : "那是敝派的前輩。",
                "俞二俠" : "那是敝派的前輩。",
                "俞岱巖" : "那是敝派的前輩。",
                "俞三俠" : "那是敝派的前輩。",
                "張鬆溪" : "那是敝派的前輩。",
                "張四俠" : "那是敝派的前輩。",
                "張翠山" : "那是敝派的前輩，可是貧道未得有緣一見。",
                "張五俠" : "那是敝派的前輩，可是貧道未得有緣一見。",
                "殷梨亭" : "那是敝派的前輩。",
                "殷六俠" : "那是敝派的前輩。",
                "莫聲谷" : "那是敝派的前輩，就在這附近的南巖。",
                "莫七俠" : "那是敝派的前輩，就在這附近的南巖。",
                "宋青書" : "宋師叔？好久都未曾見過了。",
                "沖虛" : "沖虛道長是貧道的師伯，劍法上的造詣已是出神入化，在眾師伯師叔中無人可及。",
                "沖虛道長" : "沖虛道長是貧道的師伯，劍法上的造詣已是出神入化，在眾師伯師叔中無人可及。",
                "谷虛" : "谷虛師伯負責在山上主持武當事務。",
                "谷虛道長" : "谷虛師伯負責在山上主持武當事務。",
                "清虛" : "清虛道長是貧道的師叔，曾與貧道一同在西域住過十幾年。",
                "清虛道長" : "清虛道長是貧道的師叔，曾與貧道一同在西域住過十幾年。",
                "凌虛" : "凌虛師叔在遇真宮。",
                "凌虛道長" : "凌虛師叔在遇真宮。",
                "制香" : "凌虛師叔在遇真宮。",
                "制香道長" : "凌虛師叔在遇真宮。",
                "靈虛" : "靈虛師叔在山門，負責接待香客。",
                "靈虛道長" : "靈虛師叔在山門，負責接待香客。",
                "知客" : "靈虛師叔在山門，負責接待香客。",
                "知客道長" : "靈虛師叔在山門，負責接待香客。",
                "成高" : "貧道便是成高，負責看守榔梅園，不知這位"+RANK_D->query_respect(this_player()) +"有何見教？",
                "成高道長" : "貧道便是成高，負責看守榔梅園，不知這位"+RANK_D->query_respect(this_player()) +"有何見教？",
                "守園" : "這位"+ RANK_D->query_respect(this_player()) +"太客氣了，看守榔梅園的事還是我一人來做吧。",
                "守園道長" : "貧道道號成高，負責看守榔梅園，不知這位"+RANK_D->query_respect(this_player()) +"有何見教？",
                "炸藥" : "貧道曾在西域學過制造炸藥之術。",
                "火藥" : "貧道曾在西域學過制造炸藥之術。",
                "制造火藥" : "制造火藥？"+ RANK_D->query_respect(this_player())+"是想制造炸藥吧？",
                "制造炸藥" : "炸藥威力過於巨大，造難用險，不知這位"+RANK_D->query_respect(this_player()) +"問來做甚？",
                "機關" : "這你得去問清虛師叔。",
                "機關削器" : "這你得去問清虛師叔。",
        ]));

        create_family("武當派", 4, "弟子");

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}
