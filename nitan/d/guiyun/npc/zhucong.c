// zhucong.c
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("朱聰", ({ "zhu cong", "zhu" }));
        set("title", "江南七俠");
        set("nickname", HIB"妙手書生"NOR);
        set("long", "
他看起來象一箇中年士人，拖着鞋皮，踢踏踢踏的直響，一路打
着哈欠。似笑非笑，擠眉弄眼，一副憊懶神氣，全身油膩，衣冠
不整，滿臉污垢，看來少説也有十多天沒洗臉了，拿着一柄破爛
的油紙黑扇，邊搖邊行。突聽乾笑數聲，聲音甚是刺耳。\n");
        set("gender", "男性");
        set("age", 38);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("shen_type", 1);
        set("per", 19);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        
        set("max_qi", 1200);
        set("max_jing", 500);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 20);
        set("combat_exp", 350000);
        set("score", 6000);

        set_skill("force", 75);
        set_skill("taixuan-gong", 75);
        set_skill("dodge", 75);
        set_skill("lingxu-bu", 75);
        set_skill("unarmed", 75);
        set_skill("changquan", 75);
        set_skill("dagger", 75);
        set_skill("shigu-bifa", 75);
        set_skill("parry", 75);
        set_skill("stealing", 75);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "lingxu-bu");
        map_skill("dagger", "shigu-bifa");
        map_skill("parry", "shigu-bifa");

        set("inquiry", ([
                "郭靖" : "靖兒是我們的乖徒兒！\n",
                "江南七俠" : "七俠可不敢當，我們七兄妹江湖上有個匪號叫江南七怪！\n",
                "江南七怪" : "七怪也是你叫的？！\n",
                "丘處機" : "丘道長豪俠仗義，是條漢子！\n",
                "柯鎮惡" : "那是我大哥。\n",
                "朱聰"   : "就是我了。\n",
                "韓寶駒"   : "那是我三弟。\n",
                "南希仁"   : "那是我四弟。\n",
                "張阿生"   : "那是我五弟。\n",
                "全金髮"   : "那是我六弟。\n",
                "韓小瑩"   : "那是我七妹。\n",
        ]));

        setup();
        carry_object(__DIR__"obj/zheshan")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
