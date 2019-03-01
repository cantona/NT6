// diyun 狄雲

inherit NPC;

void create()
{
        set_name("狄雲", ({ "di yun", "diyun"}));
        set("long", "他英武剛正，有一股豪邁之氣。\n");
        set("gender", "男性");
        set("age", 25);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 20);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
}