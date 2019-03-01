// This program is a part of NITAN MudLIB
// Fujun4.c
// Written by Lonely@NITAN (03/29/2009)

#include <ansi.h>

inherit NPC;

int  ask_offer();
void destroy();
int  do_offer(string arg);
int  do_answer(string arg);
int  do_report(string arg);

void create()
{
        set_name(BLU "恆山府君" NOR, ({ "hengshan fujun", "hengshan", "fujun" }));
        set("long", "他就是恆山府君。\n");
        set("title", HIW "北岳" NOR);
        set("gender", "男性");
        set("age", 50);
        set("str", 91);
        set("int", 39);
        set("con", 50);
        set("dex", 62);
        
        set("max_qi", 10000000);
        set("max_jing", 10000000);
        set("max_jingli", 10000000);
        set("jingli", 10000000);
        set("max_neili", 12000000);
        set("neili", 12000000);
        set("jiali", 55000);
        set("combat_exp", 2000000000);
        set("score", 1200000);

        set_skill("force", 2700);
        set_skill("parry", 2700);
        set_skill("dodge", 2700);
        set_skill("sword", 2700);
        set_skill("unarmed", 2700);
        set_skill("pixie-jian", 2700);        
        set_skill("literate", 2700);
        set_skill("martial-cognize", 2700);
        set_skill("kuihua-mogong", 2700);

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

        prepare_skill("unarmed", "kuihua-mogong");

        set("inquiry", ([
                "獻祭"  : (: ask_offer : ),
                "offer" : (: ask_offer : ),
        ])); 
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "sword.bian" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "sword.qiong" :),
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "roar" :),
        }) );
        
        set_temp("apply/attack", 5000); 
        set_temp("apply/armor", 10000); 
        set_temp("apply/damage", 50000); 
        set_temp("apply/unarmed_damage", 50000); 
        set_temp("apply/add_xuruo", 90); 
        set_temp("apply/reduce_xuruo", 100);
        set_temp("apply/add_damage", 100);
        set_temp("apply/reduce_damage", 90); 
        set_temp("apply/reduce_busy", 30); 
        set_temp("apply/add_busy", 10); 
         
        set("auto_perform", 1); 
        // set("bonus", 100000); 

        setup();

        carry_object("/clone/weapon/sword")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_report", "report");
}

int ask_offer()
{
        object me, ob;

        me = this_player();
        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( !objectp( ob = present("contract", me) ) ||
            query("owner", ob) != query("id", me)){
                tell_object(me, BLU "恆山府君說道：「你還沒有去領取閻王契(contract)，我不會接受你的獻祭請求。」\n" NOR);
                return 1;
        }
        
        message_vision(CYN "$N" CYN "訝道：「既是身懷閻王契，本府君這便給你一個機會吧。」\n"
                       CYN "$N" CYN "目射奇光續道：「本府君嗜武如命，近日神功有成，你我打上一架，你若勝了，本府君便準了你的獻祭。」\n" NOR, 
                       this_object(), me); 
                       
        tell_object(me, BLU "恆山府君想要與你切磋，你是否同意(answer yes/no)？\n" NOR);
        add_action("do_answer", "answer"); 
                       
        return 1; 
} 

int do_answer(string arg)
{
        object ob, me = this_player();

        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( arg == "yes" ) { 
                message_vision(BLU "$N" BLU "大笑道：「好好好！你和我的幻象痛痛快快打上一場！」\n" NOR, 
                               this_object(), me);
                ob = new(__DIR__"fujun4-shadow");
                ob->move(environment(me)); 
                set_temp("shadow/to_kill", 1, me);
        } else if( arg == "no" ) { 
                message_vision(BLU "$N" BLU "大怒道：沒有用的東西！」\n" NOR,
                               this_object(), me); 
                remove_call_out("destroy");
                call_out("destroy", 1);
        } else 
                return notify_fail("你要回答什麼？\n"); 
                
        return 1; 
}

int do_report(string arg)
{
        object me, ob;

        me = this_player();
        ob = this_object();

        if( query("worship", ob) != query("id", me) )
                return 0;

        if( !query_temp("shadow/to_kill", me) )
                return notify_fail(BLU "恆山府君皺眉道：「你想要幹什麼？」\n" NOR);

        if( !query_temp("shadow/killed", me) )
                return notify_fail(BLU "恆山府君皺眉道：「你還沒有戰勝我的幻象呀！」\n" NOR);

        message_vision( BLU "$N" BLU "笑道：「果然很有誠意，果真是閻王契的有緣人！」\n"
                        BLU "$N" BLU "又道：「本府君最重神兵之技，你必須獻祭(offer)一門兵器技能。」\n" NOR,
                        ob, me);
        delete_temp("shadow", me);
        set_temp("can_offer",query("id",  ob), me);
        add_action("do_offer", "offer");
        return 1;
}

void do_broadcast(int index)
{
        if( !environment() )
                return;

        switch (index)
        {
        case(0):
                tell_room(environment(),
                        BLU "恆山府君點頭道：「如此甚好，我這便記載到閻王契上。」\n" NOR);
                break;
        case(1):
                tell_room(environment(),
                        BLU "只見恆山府君喃喃有詞，乍時山嵐亂動、雲間溢出光芒，只見一授案飄然而下，其上文房四寶一應俱全。\n" NOR);
                break;
        case(2):
                tell_room(environment(),
                        BLU "恆山府君提筆揮洒，只見絲絲紫光滲入閻王契上，片刻即成。\n" NOR);
                break;
        case(3):
                tell_room(environment(),
                        BLU "恆山府君滿意道：「這便成了。本府君功成身退，小友多多保重。」\n" NOR);
                break;
        default:
                tell_room(environment(),
                        BLU "恆山府君化做一陣清煙消失，轉瞬便已飄渺無蹤。\n授案化做一陣清煙消失，轉瞬便已飄渺無蹤。\n" NOR);

                remove_call_out("destroy");
                destruct(this_object());
                return;
        }
        call_out("do_broadcast", 1, ++index);
}

int do_offer(string arg)
{
        object me, ob, weapon;
        string skill, msg;
        string *rec;
        int level;

        me = this_player();

        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( !arg || sscanf(arg, "%s %d", skill, level) != 2 )
                return notify_fail("格式：offer skill level\n");

        if( !objectp( ob = present("contract", me) ) ||
                query("owner", ob) != query("id", me) )
                return notify_fail(BLU "恆山府君說道：「你還沒有去領取閻王契(contract)，我不會接受你的獻祭請求。」\n" NOR);

        if( query("offer_hengshan", ob) )
                return notify_fail(BLU "恆山府君說道：「你已經在恆山獻祭過了，就不用再來獻祭吧。」\n" NOR);
                
        if( !query_temp("can_offer", me) || 
                query_temp("can_offer", me) != query("id", this_object()) )
                return notify_fail(BLU "恆山府君皺眉道：「你還是先去完成我的條件再來獻祭吧。」\n" NOR);

        if( me->query_skillo(skill, 1) < 2000 || level < 2000 )
                return notify_fail(BLU "恆山府君皺眉道：「這點小玩意你還是拿回家自己玩吧。」\n" NOR);

        if( me->query_skillo(skill, 1) < level )
                return notify_fail(BLU "恆山府君皺眉道：「你這門技能沒有這麼高的等級。」\n" NOR);
        
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(BLU "恆山府君皺眉道：「你先把你的兵器裝備上再說。」\n" NOR);
                    
        if( me->query_skill_mapped(query("skill_type", weapon)) != skill )
                return notify_fail(BLU "恆山府君皺眉道：「你還是先把這個技能激發到兵器技能上吧。」\n" NOR);

        me->add_skill(skill, -level); 
        delete_temp("can_offer", me);
        set("offer/"+skill, level, me);
        
        message_vision( HIR "$N" HIR "略一沉思道：「既然如此，為顯誠意，我決定獻祭" + to_chinese(skill) + level + "級。」\n" NOR, me );
        tell_object(me, BLU "恆山府君凌空一掏，你忽然覺得自己身上少了什麼。\n" NOR);                  
        msg = HIW + NATURE_D->game_time() + "，" + me->query_idname() + HIW "于恆山獻祭" + to_chinese(skill) + level + "級。\n";
        
        rec=query("offer", ob);
        if( ! rec ) rec = ({});
        rec += ({ msg });
        set("offer", rec, ob);
        set("offer_hengshan", 1, ob);
        
        do_broadcast(0);
        return 1;
}

void destroy()
{
        message_vision( BLU "$N化做一陣清煙消失，轉瞬便已飄渺無蹤。\n" NOR,
                        this_object() );
        destruct(this_object());
        return;
}

void start_borrowing()
{
        remove_call_out("destroy");
        call_out("destroy", 900);
}

varargs void die(object killer)
{
        object me = this_object();

        me->full_self();
        return;
}

void unconcious()
{
        object me = this_object();

        me->full_self();
        return;
}

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}
