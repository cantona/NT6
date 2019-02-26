// huyidao.c
#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("胡一刀", ({"hu yidao", "hu", "yidao"}));
        set("gender", "男性");
        set("nickname", "遼東大俠");
        set("age", 35);
        set("long","這人生得當真兇惡，一張黑漆臉皮，滿腮濃髯，頭髮卻又不結辮子，蓬蓬鬆鬆的堆在頭上。他生平只要遇到做壞事的，立時一刀殺了，所以名字叫作胡一刀。\n");
        set("attitude", "peaceful");
        set("no_get", "1");
        set("str", 45);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 17);
        
        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 100);
        set("combat_exp", 190000);
        set("score", 20000);
         
        set_skill("force", 110);             // 基本內功
        set_skill("hujia-daofa", 150);       // 胡家刀法        
        set_skill("blade", 120);             // 基本刀法
        set_skill("hunyuan-yiqi", 120);      // 混元一氣功
        set_skill("dodge", 120);             // 基本躲閃
        set_skill("shaolin-shenfa", 120);    // 胡家身法
        set_skill("parry", 120);             // 基本招架
                
        map_skill("force", "hunyuan-yiqi");
        map_skill("blade", "hujia-daofa");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "hujia-daofa");
        set("book_count",1);
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
//          carry_object(BOOK_DIR"hujia-book");
}
