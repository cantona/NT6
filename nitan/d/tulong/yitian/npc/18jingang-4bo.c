#include <ansi.h>
inherit NPC;
void create()
{
        set_name("鈸僧", ({ "bo seng", "bo", "seng"}) );
        set("long", "一個禿頂和尚，裸露著上身，肌肉結實。\n"
                    "這便是汝陽王手下的十八金剛之一。\n");
        set("attitude", "heroism");
        set("title", "汝陽王座下十八金剛");
        set("nickname", HIY "四鈸金剛" NOR);
        set("age", 30);
        set("shen_type", -1);

        set("str", 15+random(20));
        set("int", 15+random(20));
        set("con", 15+random(20));
        set("dex", 15+random(20));
        
        set("max_qi", 2000);
        set("max_jing", 800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 80);

        set("combat_exp", 300000+random(300000));
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "blade.poli" :),
                (: exert_function, "powerup" :),
        }) );


        set_skill("force", 140+random(20));
        set_skill("longxiang-gong", 140+random(20));
        set_skill("dodge", 140+random(20));
        set_skill("shenkong-xing", 140+random(20));
        set_skill("cuff", 140+random(20));
        set_skill("yujiamu-quan", 140+random(20));
        set_skill("hammer", 140+random(20));
        set_skill("riyue-lun", 140+random(20));
        set_skill("parry", 140+random(20));
        set_skill("lamaism", 180);

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "riyue-lun");
        map_skill("hammer", "riyue-lun");

        set_temp("apply/attack", 80+random(50));
        set_temp("apply/defense", 80+random(50));
        set_temp("apply/armor", 80+random(50));
        set_temp("apply/damage", 80+random(50));

        setup();

        carry_object("/d/beijing/npc/obj/jiasha")->wear();
        carry_object("/d/tulong/yitian/npc/obj/tongbo")->wield();
}
void init()
{
        object ob;

        ::init();

        ob = this_player();

        command("yi");
        command("say 是誰那麼大膽，居然敢在汝陽王眼皮下撒野！");
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob); 
}
