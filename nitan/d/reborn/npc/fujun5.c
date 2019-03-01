// This program is a part of NITAN MudLIB
// Fujun5.c
// Written by Lonely@NITAN (03/29/2009)

#include <ansi.h>
inherit NPC;

#define MIBAO_QIZHEN    "/d/reborn/obj/mibao"

int  ask_offer();
void destroy();
int  do_offer(string arg);
int  do_answer(string arg);

void create()
{
        set_name(BLU "嵩山府君" NOR, ({ "songshan fujun", "songshan", "fujun" }));
        set("long", "他就是嵩山府君。\n");
        set("title", HIW "中岳" NOR);
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

int ask_offer()
{
        object me, ob;

        me = this_player();
        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( !objectp( ob = present("contract", me) ) ||
            query("owner", ob) != query("id", me)){
                tell_object(me, BLU "嵩山府君說道：「你還沒有去領取閻王契(contract)，我不會接受你的獻祭請求。」\n" NOR);
                return 1;
        }
        
        message_vision(CYN "$N" CYN "訝道：「既是身懷閻王契，本府君這便給你一個機會吧。」\n"
                       CYN "$N" CYN "沈吟片刻又道：「本府君聞得近日在柳綠山莊出了一件密寶奇珍，你在七日之內拿來給本府君瞧瞧。」\n" NOR, 
                       this_object(), me); 
                       
        tell_object(me, BLU "嵩山府君想要與你前往柳綠山莊搜尋密寶奇珍，你是否同意(answer yes/no)？\n" NOR);
        add_action("do_answer", "answer"); 
                       
        return 1; 
} 

int do_answer(string arg) 
{ 
        object me = this_player();

        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( arg == "yes" ) { 
                set_temp("mibao/to_find", 1, me);
                message_vision( BLU "$N" BLU "大笑道：「好，很好！" + RANK_D->query_respect(me) + "還是快去吧！」\n" NOR, 
                                this_object(), me );            
                remove_call_out("destroy");
                call_out("destroy", 1800);
        } else if( arg == "no" ) { 
                message_vision( BLU "$N" BLU "大怒道：「沒用的東西！」\n" NOR,
                                this_object(), me ); 
                remove_call_out("destroy");
                call_out("destroy", 1);
        } else 
                return notify_fail("你要回答什麼？\n"); 
                
        return 1; 
}

int accept_object(object me, object ob) 
{
        if( query("worship", this_object()) != query("id", me) )
                return 0;

        if( !query_temp("mibao/to_find", me) )
                return 0;

        if( !query_temp("mibao/finded", me) )
                return 0;
                
        if (base_name(ob) != MIBAO_QIZHEN) { 
                command("say 你給我這種東西幹什麼？"); 
                return 0; 
        } 
        
        message_vision( BLU "$N" BLU "笑道：「江山代有才人出，果真是閻王契的有緣人！」\n"
                        BLU "$N" BLU "又道：「本府君最重韌力，你必須獻祭(offer)些許內力。」\n" NOR,
                               this_object(), me );
        
        set_temp("can_offer",query("id",  this_object()), me);
        add_action("do_offer", "offer");

        destruct(ob); 
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
                        BLU "嵩山府君點頭道：「如此甚好，我這便記載到閻王契上。」\n" NOR);
                break;
        case(1):
                tell_room(environment(),
                        BLU "只見嵩山府君喃喃有詞，乍時山嵐亂動、雲間溢出光芒，只見一授案飄然而下，其上文房四寶一應俱全。\n" NOR);
                break;
        case(2):
                tell_room(environment(),
                        BLU "嵩山府君提筆揮洒，只見絲絲紫光滲入閻王契上，片刻即成。\n" NOR);
                break;
        case(3):
                tell_room(environment(),
                        BLU "嵩山府君滿意道：「這便成了。本府君功成身退，小友多多保重。」\n" NOR);
                break;
        default:
                tell_room(environment(),
                        BLU "嵩山府君化做一陣清煙消失，轉瞬便已飄渺無蹤。\n授案化做一陣清煙消失，轉瞬便已飄渺無蹤。\n" NOR);

                remove_call_out("destroy");
                destruct(this_object());
                return;
        }
        call_out("do_broadcast", 1, ++index);
}

int do_offer(string arg)
{
        object me, ob;
        string msg;
        string *rec;
        int amount;

        me = this_player();

        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( !arg || sscanf(arg, "%d", amount) != 1)
                return notify_fail("格式：offer 數字\n");

        if( !objectp( ob = present("contract", me) ) ||
                query("owner", ob) != query("id", me) )
                return notify_fail(BLU "嵩山府君說道：「你還沒有去領取閻王契(contract)，我不會接受你的獻祭請求。」\n" NOR);
        
        if( query("offer_songshan", ob) )
                return notify_fail(BLU "嵩山府君說道：「你已經在嵩山獻祭過了，就不用再來獻祭吧。」\n" NOR);
                
        if( !query_temp("can_offer", me) || 
                query_temp("can_offer", me) != query("id", this_object()) )
                return notify_fail(BLU "嵩山府君皺眉道：「你還是先去完成我的條件再來獻祭吧。」\n" NOR);

        if( query("max_neili", me)<1000000 || amount<1000000 )
                return notify_fail(BLU "嵩山府君皺眉道：「這點小玩意你還是拿回家自己玩吧。」\n" NOR);

        if( query("max_neili", me)<amount )
                return notify_fail(BLU "嵩山府君皺眉道：「你沒有那麼深厚的內力。」\n" NOR);
                
        addn("max_neili", -amount, me);
        delete_temp("can_offer", me);
        set("offer/neili", amount, me);
        
        message_vision( HIR "$N" HIR "略一沉思道：「既然如此，為顯誠意，我決定獻祭" + amount + "點最大內力。」\n" NOR, me );
        tell_object(me, BLU "嵩山府君凌空一掏，你忽然覺得自己身上少了什麼。\n" NOR);                  
        msg = HIW + NATURE_D->game_time() + "，" + me->query_idname() + HIW "于嵩山獻祭" + amount + "點最大內力。\n";
        
        rec=query("offer", ob);
        if( ! rec ) rec = ({});
        rec += ({ msg });
        set("offer", rec, ob);
        set("offer_songshan", 1, ob);
        
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
        call_out("destroy", 1800);
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
