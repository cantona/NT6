// qin.c

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("秦教頭", ({ "qin jiaotou", "qin", "jiaotou" }));
        set("long","一個四十多歲的漢子，一看就是個會家子，渾身透著一股英氣。\n");
        set("gender", "男性");
        set("age", 45);
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("claw", 80);
        set_skill("hand", 80);
        set_skill("strike", 80);
        set_skill("finger", 80);
        set_skill("cuff", 80);
        set_skill("blade", 80);
        set_skill("stick", 80);
        set_skill("club", 80);
        set_skill("staff", 80);
        set_skill("sword", 80);
        set_skill("throwing", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);
        setup();

}
int accept_object(object who, object ob)
{
    if( query("combat_exp", who) >= 3500 )
    {
        message_vision("秦教頭望著$N說：你的武功應該歷練江湖才能再長進，不能埋沒
在這裡了。\n", who);
        return 0;
    }
    if( query("money_id", ob) && ob->value() >= 500 )
    {
        set_temp("marks/qin_paied", 1, who);
        message_vision("秦教頭對$N說：好！這位" + RANK_D->query_respect(who) 
+ "想學什麼呢？\n" , who);
        return 1;
    }
    else
        message_vision("秦教頭皺眉對$N說：錢我不在乎。可你也給的也太少了點兒吧？\n", who);
        return 0;
}

int recognize_apprentice(object ob)
{
        if( !query_temp("marks/qin_paied", ob) == 1)return 0;
        return 1;
}
