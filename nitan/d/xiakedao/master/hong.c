// sample master.c code

inherit NPC;
inherit F_MASTER;
#include <ansi.h>;
void consider();

void create()
{
        set_name("洪七公", ({"hong-qigong", "hong", "qigong"}));
        set("nickname", CYN"北丐"NOR);
        set("gender", "男性");
        set("age", 75);
        set("long", 
                "他就是丐幫第十七任幫主，號稱“北丐”的洪七公老爺子。\n");
        set("attitude", "peaceful");
        set("class", "beggar");
        
        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("chat_chance", 1);
        set("chat_msg", ({
                "洪七公歎了口氣道：“唉……何時能再吃到蓉兒做的「叫化雞」啊……”\n",
                "洪七公説道：“俗話説「吃在江南」，所以老叫化特地跑來揚州看看。”\n",
                "洪七公喃喃道：“我們丐幫的「降龍十八掌」是天下最霸道的掌法。”\n",
//                (: random_move :),
        }));
//        set("inquiry", ([
//                "青竹林" : "東北西北東西北。\n",
//                "丐幫" : "東北西北東西北。\n",
//                "拜師" : "你可以去東城門的我幫總舵拜魯有腳。\n",
//        ]));

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 300);
        set("max_jing", 300);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 300);
        
        set("combat_exp", 1000000);
        set("score", 200000);
        set("shen", 100000);
         
        set_skill("force", 150);             // 基本內功
        set_skill("huntian-qigong", 150);    // 混天氣功
        set_skill("unarmed", 180);           // 基本拳腳
        set_skill("xianglong-zhang", 180);   // 降龍十八掌
        set_skill("dodge", 150);                   // 基本躲閃
        set_skill("xiaoyaoyou", 150);        // 逍遙遊
        set_skill("parry", 150);             // 基本招架
        set_skill("staff", 150);             // 基本棍杖
        set_skill("dagou-bang", 150);        // 打狗棒法
        set_skill("begging", 100);           // 叫化絕活
        set_skill("checking", 100);          // 道聽途説
        
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("staff", "dagou-bang");
        
        create_family("丐幫", 17, "幫主");
        setup();
        
        carry_object("/kungfu/class/gaibang/obj/yuzhu_zhang");
}
