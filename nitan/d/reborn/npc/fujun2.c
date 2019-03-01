// This program is a part of NITAN MudLIB
// Fujun2.c
// Written by Lonely@NITAN (03/29/2009)

#include <ansi.h>

inherit NPC;

int  ask_offer();
void destroy();
int  do_offer(string arg);
int  do_answer(string arg);
int  do_guess(string arg);
int  do_wager(string arg);

string *valid_types = ({
        "unarmed",
        "cuff",
        "strike",
        "finger",
        "hand",
        "claw",
});

void create()
{
        set_name(BLU "華山府君" NOR, ({ "huashan fujun", "huashan", "fujun" }));
        set("long", "他就是華山府君。\n");
        set("title", HIW "西岳" NOR);
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
                tell_object(me, BLU "華山府君說道：「你還沒有去領取閻王契(contract)，我不會接受你的獻祭請求。」\n" NOR);
                return 1;
        }

        message_vision(CYN "$N" CYN "訝道：「既是身懷閻王契，本府君這便給你一個機會吧。」\n"
                       CYN "$N" CYN "低頭沈吟片刻又道：「轉生非同尋常，非有過人之膽識運氣，不能成此大事，我這便待考驗你一番。」\n"
                       CYN "$N" CYN "續道：「你我以所學之武功作為賭注，我們來豪賭一場如何？」\n" NOR, 
                       this_object(), me); 
                       
        tell_object(me, BLU "華山府君想要與你賭博，你是否同意(answer yes/no)？\n" NOR);
        add_action("do_answer", "answer"); 
                       
        return 1; 
} 

int do_answer(string arg) 
{ 
        object me = this_player(); 
        
        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( arg == "yes" ) { 
                message_vision(BLU "$N" BLU "大笑道：「好好好！果然有過人之膽識！\n"
                               BLU "$N" BLU "掏出一枚銅錢往上一拋，只見銅錢翻轉不止後落入$N" BLU "掌中，隨即便被緊緊蓋住。\n" NOR,
                               this_object(), me);
                tell_object(me, BLU "華山府君道：「拿(wager)一門像樣的技藝出來，然後猜猜(guess)是正面(front)還是反面(back)？猜對三次便算你過關。」\n" NOR);
                set_temp("can_wager", 1, me);
                add_action("do_wager", "wager");   
                add_action("do_guess", "guess");             
        } else if( arg == "no" ) { 
                message_vision(BLU "$N" BLU "大怒道：你連這點膽識都沒有，還想轉世，簡直是痴心妄想！\n" NOR,
                               this_object(), me); 
                remove_call_out("destroy");
                call_out("destroy", 1);
        } else 
                return notify_fail("你要回答什麼？\n"); 
                
        return 1; 
}

int do_wager(string arg)
{
        object me, ob;
        string skill;
        int level;

        me = this_player();

        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( !arg ) return notify_fail("格式：wager skill\n");

        if( !query_temp("can_wager", me) )
                return notify_fail(BLU "華山府君皺眉道：。。。\n" NOR);
        
        if( me->query_skillo(arg, 1) < 3000 )
                return notify_fail(BLU "華山府君皺眉道：「這點小玩意你還是拿回家自己玩吧。」\n" NOR);       
                
        if( !SKILL_D(arg)->valid_enable("parry") && 
            !SKILL_D(arg)->valid_enable("dodge") &&
            !SKILL_D(arg)->valid_enable("throwing") &&
            !SKILL_D(arg)->valid_enable("force")) 
                return notify_fail(BLU "華山府君皺眉道：「你還是拿出一門像樣的技藝吧。」\n" NOR);
        
        message_vision(HIW "$N" HIW "大笑道：“好吧，那我就拿我所學" + to_chinese(arg) + "作為賭注。”\n" NOR, me);
        set_temp("wager", arg, me);

        return 1;
}

int do_guess(string arg)
{
        object me, ob;
        
        me = this_player();
        ob = this_object();
                
        if( !query_temp("wager", me) )
                return 0;
                
        if( !arg || (arg != "front" && arg != "back"))
                return 0;       
        
        message_vision(HIW "$N" HIW "接著道：“我賭銅板是 " + arg + " 向上。”\n" NOR, me);  
        if( random(10) < 5 ) {
                message_vision(HIW "$N" HIW "將手掌攤開，銅板是正面(front)向上。\n" NOR, ob, me);
                if( arg == "front" ) {
                        addn_temp("guess/win", 1, me);
                        if( query_temp("guess/win", me)<2 )
                                message_vision(BLU "$N" BLU "道：「你勝了一趟。」\n" NOR, ob, me);
                        else if( query_temp("guess/win", me) == 2 )
                                message_vision(BLU "$N" BLU "道：「不錯不錯，你勝了兩趟。」\n" NOR, ob, me);
                        else {
                                message_vision(BLU "$N" BLU "笑道：「江山代有才人出，果真是閻王契的有緣人！」\n"
                                               BLU "$N" BLU "又道：「本府君最重手上功夫，你必須獻祭(offer)一門空手武技。」\n" NOR, 
                                               ob, me);
                                delete_temp("can_wager", me);
                                delete_temp("wager", me);
                                delete_temp("guess", me);
                                set_temp("can_offer",query("id",  ob), me);
                                add_action("do_offer", "offer");
                        }
                } else {
                        message_vision(BLU "$N" BLU "笑道：「看來你運氣不佳啊，沒事，我們再來！」\n" NOR, ob, me);
                        me->set_skill(query_temp("wager", me),200);
                        delete_temp("wager", me);
                        tell_object(me, BLU "華山府君凌空一掏，你忽然覺得自己身上少了什麼。\n" NOR);                        
                }
        } else {
                message_vision(HIC "$N" HIC "將手掌攤開，銅板是反面(back)向上。\n" NOR, ob, me);
                if( arg == "back" ) {
                        addn_temp("guess/win", 1, me);
                        if( query_temp("guess/win", me)<2 )
                                message_vision(BLU "$N" BLU "道：「你勝了一趟。」\n" NOR, ob, me);
                        else if( query_temp("guess/win", me) == 2 )
                                message_vision(BLU "$N" BLU "道：「不錯不錯，你勝了兩趟。」\n" NOR, ob, me);
                        else {
                                message_vision(BLU "$N" BLU "笑道：「江山代有才人出，果真是閻王契的有緣人！」\n"
                                               BLU "$N" BLU "又道：「本府君最重手上功夫，你必須獻祭(offer)一門空手武技。」\n" NOR, 
                                               ob, me);
                                delete_temp("can_wager", me);
                                delete_temp("wager", me);
                                delete_temp("guess", me);
                                set_temp("can_offer",query("id",  ob), me);
                                add_action("do_offer", "offer");
                        }
                } else {
                        message_vision(BLU "$N" BLU "笑道：「看來你運氣不佳啊，沒事，我們再來！」\n" NOR, ob, me);
                        me->set_skill(query_temp("wager", me),200);
                        delete_temp("wager", me);
                        tell_object(me, BLU "華山府君凌空一掏，你忽然覺得自己身上少了什麼。\n" NOR);                        
                }                
        }      
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
                        BLU "華山府君點頭道：「如此甚好，我這便記載到閻王契上。」\n" NOR);
                break;
        case(1):
                tell_room(environment(),
                        BLU "只見華山府君喃喃有詞，乍時山嵐亂動、雲間溢出光芒，只見一授案飄然而下，其上文房四寶一應俱全。\n" NOR);
                break;
        case(2):
                tell_room(environment(),
                        BLU "華山府君提筆揮洒，只見絲絲紫光滲入閻王契上，片刻即成。\n" NOR);
                break;
        case(3):
                tell_room(environment(),
                        BLU "華山府君滿意道：「這便成了。本府君功成身退，小友多多保重。」\n" NOR);
                break;
        default:
                tell_room(environment(),
                        BLU "華山府君化做一陣清煙消失，轉瞬便已飄渺無蹤。\n授案化做一陣清煙消失，轉瞬便已飄渺無蹤。\n" NOR);

                remove_call_out("destroy");
                destruct(this_object());
                return;
        }
        call_out("do_broadcast", 1, ++index);
}

int do_offer(string arg)
{
        object me, ob;
        string skill, msg;
        string *rec;
        int i, level, unarmed;

        me = this_player();

        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( !arg || sscanf(arg, "%s %d", skill, level) != 2 )
                return notify_fail("格式：offer skill level\n");

        if( !objectp( ob = present("contract", me) ) ||
                query("owner", ob) != query("id", me) )
                return notify_fail(BLU "華山府君說道：「你還沒有去領取閻王契(contract)，我不會接受你的獻祭請求。」\n" NOR);

        if( query("offer_huashan", ob) )
                return notify_fail(BLU "華山府君說道：「你已經在華山獻祭過了，就不用再來獻祭吧。」\n" NOR);
                
        if( !query_temp("can_offer", me) || 
                query_temp("can_offer", me) != query("id", this_object()) )
                return notify_fail(BLU "華山府君皺眉道：「你還是先去完成我的條件再來獻祭吧。」\n" NOR);

        if( me->query_skillo(skill, 1) < 3000 || level < 3000 )
                return notify_fail(BLU "華山府君皺眉道：「你獻祭的技能等級必須達到3000級！」\n" NOR);

        if( me->query_skillo(skill, 1) < level )
                return notify_fail(BLU "華山府君皺眉道：「你這門技能沒有這麼高的等級。」\n" NOR);
        
        unarmed = 0;
        for( i=0; i<sizeof(valid_types); i++ ) {
                if( SKILL_D(skill)->valid_enable(valid_types[i]) ) {
                        unarmed = 1;
                        break;
                }
        }                
        if( !unarmed ) return notify_fail(BLU "華山府君皺眉道：「你還是先獻祭個空手技能吧。」\n" NOR);

        me->add_skill(skill, -level); 
        delete_temp("can_offer", me);
        set("offer/"+skill, level, me);
        
        message_vision( HIR "$N" HIR "略一沉思道：「既然如此，為顯誠意，我決定獻祭" + to_chinese(skill) + level + "級。」\n" NOR, me );
        tell_object(me, BLU "華山府君凌空一掏，你忽然覺得自己身上少了什麼。\n" NOR);                      
        msg = HIW + NATURE_D->game_time() + "，" + me->query_idname() + HIW "于華山獻祭" + to_chinese(skill) + level + "級。\n";
        
        rec=query("offer", ob);
        if( ! rec ) rec = ({});
        rec += ({ msg });
        set("offer", rec, ob);
        set("offer_huashan", 1, ob);
        
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
        call_out("destroy", 1200);
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
