// dingdang.c 丁當

inherit NPC;
string inquiry_yu();

void create()
{
        set_name("丁當", ({ "ding dang","ding"}) );
        set("gender", "女性" );
        set("age", 18);
        set("long", "一個十七八歲的少女，身穿淡綠衫子，一張瓜子臉，秀麗美豔。\n");
        set("shen_type", 1);
        set("combat_exp", 100000);
        set("str", 18);
        set("dex", 22);
        set("con", 25);
        set("int", 35);
        set("per",30);
        set("attitude", "friendly");

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 50);

        set_skill("force", 100);
        set_skill("unarmed", 100);
        set_skill("parry", 100);
        set_skill("dodge", 200);
        set_skill("taiji-shengong", 200);
        set_skill("taiji-quan", 200);
        set_skill("tiyunzong", 500);

        map_skill("force","taiji-shenfong");
        map_skill("unarmed","taiji-quan");
        map_skill("parry","taiji-quan");
        map_skill("dodge","tiyunzong");
        set("chat_change", 1);

        set("chat_msg",({
                "丁當唸叨着: 也不知道我的玉哥哥現在怎麼樣了。\n",
                "丁當暗暗抹了把眼淚。\n",
                "丁當一跺腳，説道: 不行，我要上摩天崖把我的玉哥哥救回來。\n",
                "丁當歎了口氣，説道: 要是有玄鐵令就好了。\n",
        }));
        set("inquiry",([
                "石中玉" : "嗚嗚...他...他是我哥哥...",
                "摩天崖" : "前面這座山就是了，你要小心呀，那個老頭的武功好強呀。",
                "玄鐵令" : "據説是在石破天手裏，真假我就不知道了。",
        ]));

        setup();
        add_money("silver", 5);
}