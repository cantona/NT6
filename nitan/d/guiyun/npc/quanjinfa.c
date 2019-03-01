// quanjinfa.c
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("全金髮", ({ "quan jinfa", "quan" }));
        set("title", "江南七俠");
        set("nickname", HIC"鬧市俠隱"NOR);
        set("long", "那人五短身材，頭戴小氈帽，白淨面皮，手裏提了一杆秤，一
個竹簍，似是個小商販。\n");
        set("gender", "男性");
        set("age", 25);
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
        set_skill("club", 65);
        set_skill("zhongping-qiang", 65);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "lingxu-bu");
        map_skill("unarmed", "changquan");
        map_skill("club", "zhongping-qiang");
        map_skill("parry", "zhongping-qiang");

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
                "全金髮"   : "就是我了。\n",
                "韓小瑩"   : "那是我七妹。\n",
        ]));

        setup();
        carry_object(__DIR__"obj/gancheng")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
