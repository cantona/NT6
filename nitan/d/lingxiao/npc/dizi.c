#include <ansi.h>
inherit NPC;

void create()
{
        set_name("凌宵弟子", ({"lingxiao dizi", "dizi", "lingxiao"}));
        set("gender", "男性");
        set("age", 20);
        set("long", "這是一個凌霄城的普通弟子。\n");
        set("attitude", "peaceful");

        set("str", 30);
        set("con", 30);
        set("int", 30);
        set("dex", 30);
        set("neili", 500);
        set("max_neili", 500);
        set("max_jing", 400);
        set("jing", 400);
        set("max_qi", 800);
        set("qi", 800);
        set("jiali", 20);

        set("combat_exp", 20000);
        set("shen_type", 0);
        set("score", 50000);
        set("chat_chance", 3);
        set("chat_msg", ({
                CYN "一位凌霄弟子小聲說道：聽說老爺子發瘋了，還把封師叔的膀子卸了下來，不知道是真是假。\n" NOR,
                CYN "一位凌霄弟子冷笑道：打起來了好啊，這下子半年一次的論劍也不用開了，免得挨罵。\n" NOR,
                       CYN "一位凌霄城弟子哼了一聲，道：師父一向說我們凌霄城的劍法天下無雙，改天我要讓那些江湖中人見識一下。\n" NOR,
                CYN "一位凌霄城弟子不屑道：老爺子的病是氣出來的，你們不知道吧。\n" NOR,
                CYN "一位凌霄城弟子哼了一聲，道：馬上賞善罰惡使者要來了，我們還是先跑路吧。\n" NOR,
                CYN "一位凌霄城弟子搖搖頭，道：就算賞善罰惡使者來了，只要有人接令牌，我們這些小人物也沒事。\n" NOR,
                       CYN "一位凌霄城弟子打了個哈欠，道：昨天輪到老子守城，差點被冷死。\n" NOR,
                       CYN "一位凌霄城弟子搓了搓手，道：昨天我從師父的櫃子裡偷了瓶參陽玉酒，嘿嘿……真他媽的不錯。\n" NOR,
                       CYN "一位凌霄城弟子看看四周，小聲說道：上次謝煙客來的時候，帶的那個狗雜種，聽說是長樂幫的幫主。\n" NOR,
                       CYN "一位凌霄城弟子擺了個架勢，大聲說：武當少林算什麼！老爺子說了，武林中就我們凌霄城最厲害！\n" NOR,
                       CYN "一位凌霄城弟子掏出一瓶酒，喝了兩口，紅著眼睛說：老爺子是被成師叔祖他們暗算了！我等會就去把他救出來！\n" NOR,
                       CYN "一位凌霄城弟子低聲對另一位弟子說，要想進地牢，就必須先拿到寒玉牌啊。\n" NOR,
                       CYN "一位凌霄城弟子憤憤說道：那個狗雜種，上次竟想對阿繡非禮，要是讓我遇見，哼哼哼！\n" NOR,
        }) );
        set_skill("unarmed", 100);
        set_skill("sword", 100);
        set_skill("force", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("literate", 40);

        setup();
        carry_object("/clone/weapon/changjian")->wield();        
        carry_object("/clone/cloth/cloth")->wear();
}
