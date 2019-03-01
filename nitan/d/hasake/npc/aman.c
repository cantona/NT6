// aman.c

inherit NPC;

void create()
{
        set_name("阿曼", ({ "aman" }) );
        set("gender", "女性" );
        set("age", 18);
        set("long", "最美麗的哈薩克姑娘,身形裊娜,面目姣好, 眼光中閃爍著笑意。\n");
        set("shen", 200);
        set("combat_exp", 1000);
        set("str", 16);
        set("dex", 18);
        set("con", 12);
        set("int", 24);
        set("per", 39);
        set("attitude", "friendly");
        set("inquiry", ([
            "蘇普" : "嘻嘻，不告訴你。\n",            
            "車爾庫" : "他是我阿爹，和蘇魯克大叔一樣是草原上的英雄呢！\n",
        ]) );
        setup();
        add_money("silver", 5);
        carry_object(__DIR__"obj/qun")->wear();
}
