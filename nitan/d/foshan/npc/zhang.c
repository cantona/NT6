// zhang.c

inherit NPC;

void create()
{
        set_name("張朝唐", ({ "zhang chaotang", "zhang" }) );
        set("gender", "男性" );
        set("age", 22);
        set("int", 28);
        set("per", 23);
        set("long", 
"這是個飽讀詩書的南洋書生，他一直嚮往中土文化，特來趕考。\n");

        set("attitude", "peaceful");
        set_skill("literate", 40);
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
