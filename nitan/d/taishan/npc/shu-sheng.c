// shu-sheng.c
// Last Modified by winder on Aug. 25 2001

inherit NPC;

void create()
{
        set_name("書生", ({ "shu sheng", "sheng" }) );
        set("gender", "男性" );
        set("age", 22);
        set("int", 28);
        set("long", "這是個飽讀詩書，卻手無縛雞之力的年輕書生。\n");
        set("attitude", "peaceful");
        set_skill("literate", 40);
        setup();
}
