// jia.c 

inherit NPC;

void create()
{
        set_name("賈人達", ({ "jia renda", "jia", "renda" }));
        set("gender", "男性");
        set("age", 25);
        set("long", "他就是「青城派」中最為同門不齒、最下達的家伙。\n");

        set("combat_exp", 30000);
        set("shen_type", -1);

        set_skill("sword", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("strike", 30);
        set_skill("unarmed", 30);
        set_skill("force", 30);
        set_skill("bixie-sword", 30);
        set_skill("songfeng-jian", 30);
        set_skill("chuanhua", 30);
        set_skill("wuying-leg", 30);
        set_skill("cuixin-zhang", 30);
        set_skill("qingming-xuangong", 30);
        map_skill("force", "qingming-xuangong");
        map_skill("unarmed", "wuying-leg");
        map_skill("strike", "cuixin-zhang");
        map_skill("dodge", "chuanhua");
        map_skill("parry", "bixie-sword");
        map_skill("sword", "songfeng-jian");
        prepare_skill("unarmed", "wuying-leg");
        prepare_skill("strike", "cuixin-zhang");
        create_family("青城派", 6, "弟子");
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/bluecloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( query("gender", ob) == "女性" )
                say("賈人達嬉皮笑臉道：這位花姑娘身材硬是要得。一張臉蛋嘛，
卻是釘鞋踏爛泥，翻轉石榴皮，格老子好一張大麻皮！\n");
        else say("賈人達白了白眼：格老子的，你這兔兒爺罵誰？\n");
        return;
}
