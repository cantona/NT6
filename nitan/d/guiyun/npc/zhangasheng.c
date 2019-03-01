// zhangasheng.c
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("張阿生", ({ "zhang asheng", "zhang" }));
        set("title", "江南七俠");
        set("nickname", HIW"笑彌陀"NOR);
        set("long", "一人身材魁梧，少說也有二百五六十斤，圍著一條長圍裙，全
身油膩，敞開衣襟，露出毛茸茸的胸膛，袖子卷得高高的，手
臂上全是寸許長的黑毛，腰間皮帶上別著柄尺來長的尖刀，瞧
模樣是個殺豬宰羊的屠夫。\n");
        set("gender", "男性");
        set("age", 28);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("shen_type", 1);
        set("per", 18);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        
        set("max_qi", 1200);
        set("max_jing", 500);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 20);
        set("combat_exp", 250000);
        set("score", 6000);

        set_skill("force", 65);
        set_skill("taixuan-gong", 65);
        set_skill("dodge", 65);
        set_skill("lingxu-bu", 65);
        set_skill("unarmed", 65);
        set_skill("changquan", 65);
        set_skill("blade", 65);
        set_skill("hujia-daofa", 65);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "lingxu-bu");
        map_skill("unarmed", "changquan");
        map_skill("blade", "hujia-daofa");
        map_skill("parry", "hujia-daofa");

        set("inquiry", ([
                "郭靖" : "靖兒是我們的乖徒兒！\n",
                "江南七俠" : "七俠可不敢當，我們七兄妹江湖上有個匪號叫江南七怪！\n",
                "江南七怪" : "七怪也是你叫的？！\n",
                "丘處機" : "丘道長豪俠仗義，是條漢子！\n",
                "柯鎮惡" : "那是我大哥。\n",
                "朱聰"   : "那是我二哥。\n",
                "韓寶駒"   : "那是我三哥。\n",
                "南希仁"   : "那是我四哥。\n",
                "張阿生"   : "就是我了。\n",
                "全金發"   : "那是我六弟。\n",
                "韓小瑩"   : "那是我七妹。\n",
        ]));

        setup();
        carry_object(__DIR__"obj/jiandao")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
