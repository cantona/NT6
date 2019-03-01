// wang.c
inherit NPC;
#include <ansi.h>;

void create()
{
        set_name("王語嫣", ({ "wang yuyan","wang","yuyan" }) );
        set("gender", "女性" );
        set("title", HIM"蔓陀山莊小姐"NOR );
        set("age", 16);
        set("long", 
"王語嫣秀美的面龐之上，端莊中帶有稚氣，隱隱含著一絲憂色。
見你注目看她不覺低頭輕嘆。只聽得這輕輕一聲嘆息。霎時之間，
你不由得全身一震，一顆心怦怦跳動，心想：“這一聲嘆息如此
好聽，世上怎能有這樣的聲音？”聽得她唇吐玉音，更是全身熱
血如沸！
待見到她左手食指如一根蔥管，點在右手雪白嬌嫩的手背之上，
突覺喉頭幹燥，頭腦中一陣暈眩，忍不住沒話找話問道：“姑……
姑娘，你叫什麼名字？”\n");
        set("shen_type", 1);
        set("combat_exp", 1000000);
        set("per", 30);
        set("str", 20);
        set("dex", 18);
        set("con", 19);
        set("int", 20);
        set("attitude", "friendly");
        set("max_qi", 1000);
        set("max_jing", 800);
        set("neili", 100);
        set("max_neili", 100);
        set("score", 800);

        set_skill("force", 10);
        set_skill("dodge", 100);
        set_skill("lingbo-weibu", 100);
        set_skill("unarmed", 10);
        set_skill("sword", 10);
        set_skill("parry", 10);
        map_skill("dodge", "lingbo-weibu");
        set("inquiry",([
                "曼陀山莊" : "這裡就是曼陀山莊。\n",
                "琅繯玉洞" : "玉洞在潮聲洞的一個支洞裡，你的武功有點基礎了就可以去那裡找了。\n",
                "還施水閣" : "光復大燕就那麼重要麼？\n",
                "王語嫣"   : "你也知道我的名字？\n",
                "南慕容"   : "表哥和丐幫喬幫主齊名，合稱“南慕容北喬峰”！\n",
                "慕容復"   : "你、你有我表哥的消息麼？\n",
                "王夫人"   : "就是公子爺的舅媽，曼陀山莊的莊主！\n",
                "阿朱"     : "那小妮子只大我一歲，整天就喜歡扮別人玩。\n",
                "阿碧"     : "那小妮子只大我一歲，整天就喜歡扮別人玩。\n",
                "鄧百川"   : "你問鄧大哥啊？他在他青風莊上呢。\n",
                "公冶乾"   : "公冶二哥把信鴿傳書一編碼，就沒幾個人讀得懂了。\n",
                "包不同"   : "包三哥最愛抬槓了，你見了他還是閉嘴的好。\n",
                "風波惡"   : "風四哥最是豪爽了，他從不與人計較什麼。\n",
        ]) );
        setup();
        carry_object(__DIR__"obj/ou_cloth")->wear();
}
