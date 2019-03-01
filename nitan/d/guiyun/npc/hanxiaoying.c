// hanxiaoying.c
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("韓小瑩", ({ "han xiaoying", "han" }));
        set("title", "江南七俠");
        set("nickname", HIR"越女劍"NOR);
        set("long", "她大約十八九歲年紀，身形苗條，大眼睛，皮膚如雪，露出一
頭烏雲般的秀髮。正是江南水鄉的人物。\n");
        set("gender", "女性");
        set("age", 18);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("shen_type", 1);
        set("per", 18);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        
        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 20);
        set("combat_exp", 200000);
        set("score", 6000);

        set_skill("force", 60);
        set_skill("taixuan-gong", 60);
        set_skill("dodge", 60);
        set_skill("lingxu-bu", 60);
        set_skill("unarmed", 60);
        set_skill("changquan", 60);
        set_skill("sword", 60);
        set_skill("yunu-sword", 60);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "lingxu-bu");
        map_skill("unarmed", "changquan");
        map_skill("sword", "yunu-sword");
        map_skill("parry", "yunu-sword");

        set("inquiry", ([
                "郭靖" : "靖兒是我們的乖徒兒！\n",
                "江南七俠" : "七俠可不敢當，我們七兄妹江湖上有個匪號叫江南七怪！\n",
                "江南七怪" : "七怪也是你叫的？！\n",
                "丘處機" : "丘道長豪俠仗義，是條漢子！\n",
                "柯鎮惡" : "那是我大哥。\n",
                "朱聰"   : "那是我二哥。\n",
                "韓寶駒"   : "那是我三哥。\n",
                "南希仁"   : "那是我四哥。\n",
                "張阿生"   : "那是我五哥。\n",
                "全金髮"   : "那是我六哥。\n",
                "韓小瑩"   : "就是我了。\n",
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
