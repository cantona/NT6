#include <ansi.h>
inherit NPC;

void create()
{
        object sword, obj;

        set_name("常金鵬", ({ "chang jinpeng", "chang" }) );
        set("long", "這便是天鷹教朱雀壇的壇主常金鵬。\n"
                    "五十來歲年紀，臉上手上的肌肉凹凹凸凸、盤根錯節。\n");
        set("attitude", "heroism");
        set("title", "天鷹教");
        set("nickname", HIR "朱雀壇壇主" NOR);
        set("combat_exp", 1000000);
        set("age", 52);
        set("str", 100);
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                "常金鵬喝道：惡賊還不放手？\n",
                "常金鵬喝道：惡賊不得無禮！\n",
                (: perform_action, "hammer.poli" :),
        }) );
        set_skill("force", 160+random(50));
        set_skill("longxiang-gong", 160+random(50));
        set_skill("dodge", 160+random(50));
        set_skill("shenkong-xing", 160+random(50));
        set_skill("cuff", 160+random(50));
        set_skill("yujiamu-quan", 160+random(50));
        set_skill("hand", 160+random(50));
        set_skill("dashou-yin", 160+random(50));
        set_skill("parry", 160+random(50));
        set_skill("hammer", 160+random(50));
        set_skill("riyue-lun", 160+random(50));

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "riyue-lun");
        map_skill("hammer", "riyue-lun");

        prepare_skill("hand", "dashou-yin");
        prepare_skill("cuff", "yujiamu-quan");

        set_temp("apply/attack", 80+random(80));
        set_temp("apply/defense", 80+random(80));
        set_temp("apply/armor", 80+random(80));
        set_temp("apply/damage", 80+random(80));

        setup();

        carry_object("/d/tulong/tulong/npc/obj/jiaofu")->wear();
        carry_object("/d/tulong/tulong/npc/obj/hammer")->wield();
//        carry_object("/d/tulong/obj/tulongdao");
        sword = find_object("/d/tulong/obj/tulongdao");
        if( clonep() )
        if (objectp(sword))
        {
               obj = environment(sword);
               /*
               if (objectp(obj))
                      tell_object(obj, HIR"\n一條人影從你眼前一閃而過：" +
                                  "“多謝替老夫取回" NOR + sword->name() + HIR
                                  "，就此謝過，咱們後會有期！”\n\n"NOR);
               */
               if( !objectp(obj) )
                      obj->move(this_object());
        } else 
        {
               sword = load_object("/d/tulong/obj/tulongdao");
               sword->move(this_object());
        }

}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是隻見會場裏黑壓壓的擠滿了人，根本看不清楚。\n");
}

void init()
{
        add_action("do_bi","bi");
        add_action("do_get","get");
        if (this_player())
        {
        remove_call_out("put");
        call_out("put",5);
        }
}

void put()
{
        object obj,obj2;
        obj = present("tulong blade",this_object());
        obj2 = present("ding",environment());

        if (objectp(obj) && objectp(obj2)) 
        {
                obj->move(obj2);
                message_vision(HIC "\n$N哈哈一笑，手一揮，將那屠龍寶刀擲進了烈焰沖天的大鐵鼎中。\n\n" NOR,
                                   this_object());
        }
        obj = present("tulong blade",this_object());
        if (objectp(obj)) destruct(obj);
}

int do_get(string arg)
{
        object obj = this_object();
        string what, where;

        if(!arg)
        return 0;        
        if(sscanf(arg, "%s from %s", what, where) != 2)
        return 0;

        if(where == "ding")
        {
                message_vision(CYN "$N對$n大喝一聲：大膽！竟敢打寶刀的主意！\n" NOR,
                               obj,this_player());

                message_vision(CYN "$N對$n喝道：去死吧。\n" NOR,
                               obj,this_player());

                obj->kill_ob(this_player());
                this_player()->kill_ob(obj);
                return 1;
        }

        return 0;
}

int do_bi()
{
        object obj = this_object();
        message_vision(CYN "$N對$n大喝一聲：比什麼比，去死吧！\n" NOR,
                           obj,this_player());

        obj->kill_ob(this_player());
        this_player()->kill_ob(obj);
        return 1;
}

int accept_fight(object me)
{
        object obj = this_object();
        command("say 他奶奶的，要打架嗎？正合老子心意！\n");
        this_player()->kill_ob(obj);
        kill_ob(me);
        return 1;
}

int accept_hit(object me)
{
        object obj = this_object();
        command("say 他奶奶的，要打架嗎？正合老子心意！\n");
        this_player()->kill_ob(obj);
        kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        object obj = this_object();
        command("say 他奶奶的，要打架嗎？正合老子心意！\n");
        this_player()->kill_ob(obj);
        kill_ob(me);
        return 1;
}

