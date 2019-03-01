// likuilei.c 李傀儡
// Modified by Winder June 25. 2000
inherit NPC;

#include <ansi.h>

void create()
{
        set_name("李傀儡", ({ "li kuilei", "li" }));
        set("long","他看起來青面獠牙，紅發綠須，形狀可怕之極，直是個妖怪，身穿一件亮光閃閃的錦袍。他一生沉迷扮演戲文，瘋瘋顛顛，于這武學一道，不免疏忽了。\n");
        set("nickname","“函谷八友”戲迷");
        set("gender", "男性");
        set("age", 30);
        set("attitude", "friendly");
        set("class", "scholar");
        set("shen_type", 1);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 38);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 60);
        set("combat_exp", 200000);
        set("score", 50000);

        set_skill("dramaturgy",150);
        set_skill("blade", 30);
        set_skill("ruyi-dao", 30);
        set_skill("force", 30);
        set_skill("dodge", 30);
        set_skill("strike", 30);
        set_skill("parry", 30);
        set_skill("lingbo-weibu", 100);
        set_skill("beiming-shengong",30);
        set_skill("liuyang-zhang", 30);
        map_skill("parry", "ruyi-dao");
        map_skill("strike", "liuyang-zhang");
        map_skill("dodge", "lingbo-weibu");
        map_skill("force", "beiming-shengong");
        map_skill("blade", "ruyi-dao");
        prepare_skill("strike", "liuyang-zhang");
        set("book_count", 1);
        set("env/wimpy", 60);

        create_family("逍遙派", 3, "弟子");
        setup();
        carry_object("/clone/cloth/male-cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
}
