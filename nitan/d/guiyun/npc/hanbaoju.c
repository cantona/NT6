// hanbaoju.c
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("韓寶駒", ({ "han baoju", "han" }));
        set("title", "江南七俠");
        set("nickname", HIY"馬王神"NOR);
        set("long", "他是個又矮又胖的猥瑣漢子，猶如一個大肉團一般。他手短足短，
沒有脖子，一個頭大的出奇，卻又縮在雙肩之中。一個酒糟鼻又
大又圓，就如一隻紅柿子旒在臉上。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("shen_type", 1);
        set("per", 10);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        
        set("max_qi", 1200);
        set("max_jing", 500);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 20);
        set("combat_exp", 300000);
        set("score", 6000);

        set_skill("force", 70);
        set_skill("taixuan-gong", 70);
        set_skill("dodge", 70);
        set_skill("lingxu-bu", 70);
        set_skill("unarmed", 70);
        set_skill("changquan", 70);
        set_skill("whip", 70);
        set_skill("riyue-bian", 70);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "lingxu-bu");
        map_skill("unarmed", "changquan");
        map_skill("whip", "riyue-bian");
        map_skill("parry", "riyue-bian");

        set("inquiry", ([
                "郭靖" : "靖兒是我們的乖徒兒！\n",
                "江南七俠" : "七俠可不敢當，我們七兄妹江湖上有個匪號叫江南七怪！\n",
                "江南七怪" : "七怪也是你叫的？！\n",
                "丘處機" : "丘道長豪俠仗義，是條漢子！\n",
                "柯鎮惡" : "那是我大哥。\n",
                "朱聰"   : "那是我二哥。\n",
                "韓寶駒"   : "就是我了。\n",
                "南希仁"   : "那是我四弟。\n",
                "張阿生"   : "那是我五弟。\n",
                "全金髮"   : "那是我六弟。\n",
                "韓小瑩"   : "那是我七妹。\n",
        ]));

        setup();
        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
