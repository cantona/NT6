// cuihua.c

inherit NPC;

void create()
{
        set_name("苗三斤",({ "miao sanjin","miao"}) );
        set("gender", "男性" );
        set("age", 58);
        set("long", "這是本村的村長，凡是村裏各家各户，老老少少的事他沒有不知道的。\n");

        set("max_qi", 300);
        set("shen_type", 1);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set("combat_exp", 800);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 20);
        set("attitude", "peaceful");
        set("chat_chance",10);
        set("chat_msg",({
                   "村長歎道：翠蘭的爹爹到現在還沒回來，會不會出事啊。\n",
                   "村長自言自語道：天天到那種地方去，早晚要出事的。\n",
        }));

        setup();
        carry_object("/d/city/obj/cloth")->wear();
        carry_object(__DIR__"obj/hanyan");
        add_money("coin", 50);
        set("inquiry", ([
                   "name": "我是苗三斤．因為村裏我酒量最大，所以大家選我當了村長。\n",
                   "here": "此乃桃花村也。\n",
                   "桃花峪": "你問桃花峪啊，那可是個鬼地方，據説山谷裏有瘴氣，進去的人都死了。\n",
        ]) );

}