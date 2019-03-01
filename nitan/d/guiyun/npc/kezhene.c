// kezhene.c
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("柯鎮惡", ({ "ke zhene", "ke" }));
        set("title", "江南七俠");
        set("nickname", HIM"飛天蝙蝠"NOR);
        set("long", "他是一個衣衫襤褸的瞎子，右手握着一根粗大的鐵杖。只見他
尖嘴削腮，臉色灰撲撲地，頗有兇惡之態。\n");
        set("gender", "男性");
        set("age", 44);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("shen_type", 1);
        set("per", 12);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        
        set("max_qi", 1500);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 20);
        set("combat_exp", 400000);
        set("score", 6000);

        set_skill("force", 80);
        set_skill("taixuan-gong", 80);
        set_skill("dodge", 80);
        set_skill("lingxu-bu", 80);
        set_skill("unarmed", 80);
        set_skill("changquan", 80);
        set_skill("staff", 80);
        set_skill("juemen-gun", 80);
        set_skill("parry", 80);
        set_skill("throwing", 80);
        set_skill("feixing-shu", 80);

        map_skill("force", "taixuan-gong");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "lingxu-bu");
        map_skill("staff", "juemen-gun");
        map_skill("parry", "juemen-gun");
        map_skill("blade", "feixing-shu");

        set("inquiry", ([
                "郭靖" : "靖兒是我們的乖徒兒！\n",
                "江南七俠" : "七俠可不敢當，我們七兄妹江湖上有個匪號叫江南七怪！\n",
                "江南七怪" : "七怪也是你叫的？！\n",
                "丘處機" : "丘道長豪俠仗義，是條漢子！\n",
                "柯鎮惡" : "就是瞎子我，你要怎的？！\n",
                "朱聰"   : "那是我二弟。\n",
                "韓寶駒"   : "那是我三弟。\n",
                "南希仁"   : "那是我四弟。\n",
                "張阿生"   : "那是我五弟。\n",
                "全金髮"   : "那是我六弟。\n",
                "韓小瑩"   : "那是我七妹。\n",
                "梅超風"   : "這個鐵屍害死我大哥，此仇一定要報。\n",
        ]));

        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
