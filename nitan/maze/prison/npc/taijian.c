#include <ansi.h> 
inherit NPC;

object *players = ({});

void set_players(object *ob) {
        players = ob;
}

void add_player(object ob) {
        if(member_array(ob,players)==-1) {
                players += ({ob});
                message_vision(BLU"$N對$n說道：謝謝！\n"NOR,this_object(),ob);
        } else
                message_vision(BLU"$N對$n說道：你已經答應幫忙，你不會反悔吧！\n"NOR,this_object(),ob);
}

object* query_players() {
        players -= ({0});
        return players;
}

void play_sound_0(object speaker,int index);

void create()
{
        set_name("太監", ({ "tai jian","tai", "jian" }) );
        set("gender", "無性" );
        set("age", 40);
        set("str", 50);
        set("con", 30);
        set("dex", 22); 
        set("int", 50);
 
        set("long","他是皇宮內的皇帝身旁非常得寵一個太監。");
        set("max_qi", 8000000);
        set("eff_qi", 480000);        
        set("max_jing", 8500000);
        set("eff_jing",850000);
        set("neili", 8000000);
        set("max_neili", 4500000);
        set("max_jingli", 500000);
        set("combat_exp", 300000000);

        set_skill("force", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("sword", 2000);
        set_skill("unarmed", 2000);
        set_skill("pixie-jian", 2000);        
        set_skill("literate", 2000);
        set_skill("martial-cognize", 2000);
        set_skill("kuihua-mogong", 2000);

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

        prepare_skill("unarmed", "kuihua-mogong");

        set_temp("apply/attack", 3000);
        set_temp("apply/defense", 3000);
        set_temp("apply/damage", 1500);
        set_temp("apply/unarmed_damage", 1500);
        setup();
        
        carry_object("/d/fuzhou/obj/xiuhua")->wield();
        carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
}  

void init()
{       
        object ob; 
        ::init();
        
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_answer", "answer");
        add_action("do_accept", "accept");
        add_action("do_help", "help");
} 

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query_temp("開場白結束") || query_temp("開始說開場白") || query_temp("任務") )
                return;
                
        message_vision(CYN "$N有氣無力地說道：這位" + RANK_D->query_respect(ob) +
                "，你是來為皇宮清除叛逆的嗎？？(answer yes/no)\n" NOR, this_object(), ob);
} 

int do_answer(string arg) {
        if(arg=="yes") {
                if(query_temp("in_speech"))
                        return 0;
                if(present("tape",environment()))
                        return 0;
                set_temp("開始說開場白",1);
                set_temp("in_speech", 1);
                play_sound_0(this_object(),0);
        } else if(arg=="no") {
                message_vision(BLU"$N說道：誰想聽你這個太監廢話！\n",this_player());
        } else
                return notify_fail("你要回答什麼？\n");
        return 1;
}

void play_sound_0(object speaker,int index) {
        if(!environment())
                return;
        if(!speaker)
                return;        
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"太監說道：天牢總管太監總管李蓮英在天牢中鍛煉出一批死士來刺殺聖上......\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"太監說道：由于天牢死士個個都屬于武林人氏，武功高強，所以聖上尋求各位勇士前來幫助。\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"太監說道：你願意為宮廷清理叛逆，鏟除李蓮英嗎？(accept yes/no)\n"NOR);
                        speaker->set_temp("開場白結束",1);
                        break;
                default: 
                        speaker->delete_temp("in_speech");
                        return;

        }
        call_out("play_sound_0",1,speaker,++index);
}

int do_accept(string arg) {
        object ob,*team;
        object me = this_player();
        if(!query_temp("開場白結束"))
                return 0;
        if(query_temp("任務"))
                return 0;
        if(arg=="yes") {                
                delete_temp("開場白結束");
                team = me->query_team();
                if(!team || sizeof(team)==0)
                        team = ({ me });
                set_players(team);
                set_temp("任務", 1);
                ob = new("/maze/prison/npc/obj/key");
                ob->move(me, 1);
                tell_room(environment(),CYN"太監說道：這是進入天牢的鑰匙，現在交給你，希望" + RANK_D->query_respect(me) + 
                        "能完成聖上發布下來的任務。\n" NOR);
                message_vision(HIY "$N" HIY "說罷" HIY "便領著$n" HIY "快步朝地上牢房走去。\n\n" NOR, this_object(), me);
                me->move("/maze/prison/tianlao");
                tell_object(me, CYN + name() + "說道：就是這裡，接下來就看您了。\n"
                        HIC + name() + "說完便急急忙忙趕了回去。\n" NOR);                
        }        
        else if(arg=="no") {
                delete_temp("開場白結束");
                delete_temp("開始說開場白");
                message_vision(BLU"$N說道：沒好處的事情我可不幹！\n",this_player());
        }
        else
                return 0;
        return 1;
}

int do_help(string arg) {
        if(arg!="tai" && arg!="tai jian")
                return 0;
        add_player(this_player());
        return 1;
}
