// jiaofu.c

inherit NPC;

void create()
{
        set_name("腳夫", ({ "jiao fu", "fu" }) );
        set("gender", "男性" );
        set("age", 20+random(15));
        set("long",
                "這是個老實巴交的中年人，專門幫人挑東西，長得膀闊腰圓，一身肌肉。\n");
        set("combat_exp", random(10000));
   set("str", 25);
   set("dex", 22);
   set("con", 20);
   set("int", 15);
        set("attitude", "heroism");

        setup();
   carry_object("clone/misc/cloth")->wear();
}