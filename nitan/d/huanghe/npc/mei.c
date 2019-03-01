// mei.c
inherit NPC;
#include <ansi.h>;
void create()
{
        set_name( "梅超風" ,({ "mei chaofeng", "mei" }));
        set("title", "黑風雙煞");
        set("nickname", HIB"鐵屍"NOR);
        set("gender", "女性");
        set("age", 32);
        set("long",
            "梅超風是黃藥師唯一的女弟子，本來極受黃藥師疼愛，可惜她與師兄陳玄風\n"
            "暗生情愫，他們偷了《九陰真經下卷》私奔。\n"
            "她面色大概因為久居海島顯得黝黑，模樣卻頗為俏麗。她在桃花弟子中尤精\n"
            "通鞭法。\n");
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
           "鐵屍":     "江湖上的人都這麼叫我的，你怕不怕？哈哈哈哈。",
           "東邪":     "那是我師父的綽號。",
           "西毒":     "那是與家師齊名的高手之一，是個老毒物，住在白駝山。",
           "南帝":     "段王爺已出家當和尚去了，法名叫一燈。",
           "北丐":     "北丐統領中原的丐幫，勢力頗為強大。",
           "洪七公":   "洪七公武功高強，而且教會郭靖那小兒降龍十八掌，可恨！",
           "黃蓉":     "她是我師父的獨女，最是刁蠻任性。",
           "郭靖":     "哼，就是這個小子暗算了我師哥，我絕不會放過他！",
           "楊康":     "康兒是我的徒弟，你見過他麼？",
           "梅超風":   "不就是我麼？你是白痴啊？",
           "陳玄風":   "他是我的師哥，也是我的夫君，可惜被郭靖那小兒暗算了。",
           "黃藥師":   "他是我師父。"]) );
        setup();
        carry_object("/kungfu/class/taohua/obj/bupao")->wear();
}
