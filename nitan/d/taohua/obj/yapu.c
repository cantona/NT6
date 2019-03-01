//Cracked by Kafei
//yapu.c

#include <ansi.h>

inherit NPC;

void create()
{
        int skill;
        skill = random(60);
        set_name("啞僕", ({ "ya pu","pu", "servant"}) );
        set("gender", "男性");
        set("age", 30);
        set("long",
"這是個桃花島上的傭僕，是個忘恩負義，大姦大惡之徒，
被黃藥師擒住後，割去舌頭，刺聾耳朵，充當廝養.
他又聾又啞，神情木然。\n");
        set("combat_exp", 10000);
        set("shen_type", -1);
        set("attitude", "peaceful");
        set("max_qi", 500);
        set("max_jing", 500);
        set("max_neili", 500);
        set("neili", 500);
        set_temp("apply/armor", 50);        

        set("str", 28);
        set("con", 28);
        set("dex", 28);

        set_skill("cuff", 30+skill);
        set_skill("parry", 30+skill);
        set_skill("force", 30+skill);
        set_skill("dodge", 30+skill);

        setup();

        carry_object("/clone/misc/cloth")->wear();

}
