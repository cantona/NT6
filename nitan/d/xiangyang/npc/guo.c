// guojing.c 郭靖

#include <ansi.h>

inherit NPC;
int ask_rong();
void create()
{
        set_name("郭靖", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY"北俠"NOR);
        set("gender", "男性");
        set("age", 41);
        set("long", 
                "他就是人稱北俠的郭靖，既是蒙古成吉思汗的金刀駙馬，又是\n"
                "江南七怪、全真派馬鈺道長、「北丐」洪七公和「老頑童」周\n"
                "伯通等人的徒弟，身兼數門武功。\n"
                "他身著一件灰色長袍，體態魁梧，敦厚的面目中透出一股威嚴\n"
                "令人不由得產生一股欽佩之情。\n");
         set("attitude", "peaceful");
        
        set("str", 40);
        set("int", 20);
        set("con", 38);
        set("dex", 25);

//          set("no_get", 1);
        set("chat_chance", 1);
        set("chat_msg", ({
                "郭靖嘆了口氣道：“蒙古兵久攻襄陽不下，一定會再出詭計，蓉兒又不在身邊，這....\n",
                "郭靖說道：“華箏公主近來不知可好，抽空一定要回大漠去看看她。\n",
        }));

        set("inquiry", ([
                "周伯通" : "你見到我周大哥了？他現在可好？\n",
                "老頑童" : "周大哥一貫這樣，沒點正經！\n",
                "洪七公" : "師父除了吃，就是喜歡玩。到處玩，還是為了找吃的。\n",
                "黃藥師" : "那是我泰山大人。他雲遊四海，神龍見首不見尾的。\n",
                "一燈大師" : "在下對大師好生感激。\n",
                "歐陽鋒" : "這個老毒物，害死我六位師父，一待襄陽事了，決不與他幹休。\n",
                "黃蓉"   : "蓉兒是我的愛妻，你問她做甚？\n",
                "蓉兒"   : "蓉兒就是蓉兒了。你問這麼多幹嘛？\n",
                "郭芙"   : "這個女兒，又笨又不聽話。\n",
                "郭襄"   : "襄兒生于亂世，這輩子又多艱厄。但願她能快樂一世。\n",
                "郭破虜" : "那是我的小兒子。\n",
                "楊過"   : "過兒確實有出息。\n",
                "馬鈺"   : "馬道長于我有半師之誼。\n",
                "丘處機" : "邱道長義薄雲天，是真豪傑。\n",
                "柯鎮惡" : "那是我大師父。\n",
                "朱聰"   : "那是我二師父。\n",
                "韓寶駒" : "那是我三師父。\n",
                "南希仁" : "那是我四師父。\n",
                "張阿生" : "那是我五師父。\n",
                "全金發" : "那是我六師父。\n",
                "韓小瑩" : "那是我七師父。\n",
                "丐幫"   : "丐幫英雄幾百年了，守衛襄陽多虧了他們。\n",
                "拜師"   : "現在蒙古人圍攻襄陽，我哪有心情收徒啊！\n",
        ]));

        set("qi", 5200);
        set("max_qi", 5200);
        set("jing", 2600);
        set("max_jing", 2600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 100);
        
        set("combat_exp", 2100000);
        set("score", 200000);
         
        set_skill("force", 240);                // 基本內功
        set_skill("huntian-qigong", 240);        // 混天氣功
        set_skill("strike", 260);                // 基本拳腳
        set_skill("dragon-strike", 260);        // 降龍十八掌
        set_skill("dodge", 200);                // 基本躲閃
        set_skill("jinyan-gong", 200);                // 金雁功
        set_skill("parry", 260);                // 基本招架
        
        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "dragon-strike");
        
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
}
int ask_rong()
{
    object ob;
    ob = this_player();
    if (ob->query_int()>=30)
    {
        set_temp("marks/蓉兒", 1, ob);
        command("say"+query("name", ob)+"，你幫我帶個口信去桃花島吧！\n");
    }
    else
    {
        command("say"+query("name", ob)+"，你打聽這幹嘛？\n");
    }
    return 1;
}
