// nanxiren.c
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("南希仁", ({ "nan xiren", "nan" }));
        set("title", "江南七俠");
        set("nickname", HIG"南山樵子"NOR);
        set("long", "
他是個挑柴模樣的漢子，三十歲上下年紀，一身青布衣褲，腰裏
束了根粗草繩，足穿草鞋，粗手大腳，神情木訥。\n");
        set("gender", "男性");
        set("age", 30);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("shen_type", 1);
        set("per", 15);
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
        set_skill("staff", 70);
        set_skill("juemen-gun", 70);
        set_skill("axe", 70);
        set_skill("duanyun-fu", 70);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "lingxu-bu");
        map_skill("unarmed", "changquan");
        map_skill("staff", "juemen-gun");
        map_skill("parry", "juemen-gun");
        map_skill("axe", "duanyun-fu");

        set("inquiry", ([
                "郭靖" : "靖兒是我們的乖徒兒！\n",
                "江南七俠" : "七俠可不敢當，我們七兄妹江湖上有個匪號叫江南七怪！\n",
                "江南七怪" : "七怪也是你叫的？！\n",
                "丘處機" : "丘道長豪俠仗義，是條漢子！\n",
                "柯鎮惡" : "那是我大哥。\n",
                "朱聰"   : "那是我二哥。\n",
                "韓寶駒"   : "那是我三哥。\n",
                "南希仁"   : "就是我了。\n",
                "張阿生"   : "那是我五弟。\n",
                "全金髮"   : "那是我六弟。\n",
                "韓小瑩"   : "那是我七妹。\n",
        ]));

        setup();
        carry_object(__DIR__"obj/biandan");
        carry_object(__DIR__"obj/axe")->wield();
        carry_object(__DIR__"obj/green_cloth")->wear();
}
