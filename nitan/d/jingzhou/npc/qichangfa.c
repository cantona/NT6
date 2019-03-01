//Edited by fandog, 02/13/2000
#include <ansi.h>;
inherit NPC;

void create ()
{
        set_name("戚長發", ({"qi changfa","qi"}));
        set("nickname", HIB"鐵鎖橫江"NOR);
        set("long", "一個老頭兒，嘴裡咬著一根短短的旱煙管。他滿頭白發、滿臉皺
紋，但眼中神光炯然，凜凜有威。\n");
        set("gender", "男性");
        set("age", 48);
        set("combat_exp", 1000000);
        set("str", 25);
        set("int", 28);
        set("dex", 23);
        set("con", 18);
        set("per", 18);
        set("kar", 26);
  
        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("sword", 120);
        set_skill("parry", 120);
        set_skill("yanfly", 120);
        set_skill("tangshi-jian", 120);
        map_skill("dodge", "yanfly");
        map_skill("parry", "tangshi-jian");
        map_skill("sword", "tangshi-jian");
        setup();
        carry_object("/clone/cloth/male-cloth")->wear();
}

