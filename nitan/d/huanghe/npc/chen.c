// chen.c
inherit NPC;
#include <ansi.h>;
void create()
{
        set_name( "陳玄風" ,({ "chen xuanfeng", "chen" }));
        set("title", "黑風雙煞");
        set("nickname", HIY"銅屍"NOR);
        set("gender", "男性");
        set("age", 35);
        set("long",
            "此人是黃藥師的二弟子，他濃眉大眼，背厚膀寬，軀體甚是壯健，只是\n"
            "面色微微泛黃。\n");
        set("attitude", "aggressive");
        set("str", 27);
        set("int", 32);
        set("con", 35);
        set("max_qi",2500);
        set("max_jing",1000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 100);
        set("shen",-50000);

        set("combat_exp", 1000000);

        set_skill("claw", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("dodge", 40);
        set_skill("jiuyin-baiguzhao", 90);
        set_skill("bibo-shengong", 90);
        set_skill("anying-fuxiang", 90);

        map_skill("force", "bibo-shengong");
        map_skill("parry", "luoying-shenjian");
        map_skill("dodge", "anying-fuxiang");
        map_skill("claw", "jiuyin-baiguzhao");
        prepare_skill("claw", "jiuyin-baiguzhao");

        create_family("桃花島", 2, "被逐弟子");
        set("inquiry", ([
           "銅屍":     "江湖上的人都這麼叫我的，你怕不怕？哈哈哈哈。",
           "東邪":     "那是我師父的綽號。",
           "西毒":     "那是與家師齊名的高手之一，是個老毒物，住在白駝山。",
           "南帝":     "段王爺已出家當和尚去了，法名叫一燈。",
           "北丐":     "北丐統領中原的丐幫，勢力頗為強大。",
           "洪七公":   "洪七公武功高強，而且教會郭靖那小兒降龍十八掌，可恨！",
           "黃蓉":     "她是我師父的獨女，最是刁蠻任性。",
           "梅超風":   "她是我的師妹，也是我的內室。",
           "陳玄風":   "不就是我麼？你是白痴啊？",
           "黃藥師":   "他是我師父。"]) );
        setup();
        carry_object("/kungfu/class/taohua/obj/bupao")->wear();
}
