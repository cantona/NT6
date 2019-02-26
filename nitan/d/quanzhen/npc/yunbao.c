// yunbao.c 雲豹

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("雲豹", ({ "yun bao", "bao" }) );
        set("race", "走獸");
        set("gender", "雌性");
        set("age", 5);
        set("long", @LONG
這是一隻艾葉花皮的雲豹，它的毛皮極為雄美、厚實。
LONG);
        set("attitude", "aggressive");
        set("shen_type", -1);

        set("combat_exp", 30000);
        set("neili",800);
        set("jiali",100);
        set("max_neili",800);
        set("jingli",500);
        set("max_jingli",500);

        set_temp("apply/attack", 20000);
        set_temp("apply/defense", 30000);
        set_temp("apply/armor", 1000);

        setup();
}

void die()
{
        object ob, corpse;
        message_vision("$N發出震天動地的一聲大吼，轟地倒在地上，死了！\n", this_object());
        if( objectp(corpse = CHAR_D->make_corpse(this_object())) )
        ob = new("/clone/medicine/vegetable/baotai");
        ob->move(corpse);

        corpse->move(environment(this_object()));
        destruct(this_object());
}
