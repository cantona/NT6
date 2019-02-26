#include <ansi.h>
inherit NPC;

int ask_me();
int ask_ok();

void create()
{
        set_name("姜小鐵", ({ "jiang xiaotie", "jiang", "xiaotie" }) );
        set("title", HIB"藥王谷"NOR+WHT"管事"NOR);
        set("long", "他是回春堂的管事，負責回春堂的雜役。\n" );
        set("gender", "男性" );
        set("age", 17);
        set("combat_exp", 10000);
        set("attitude", "friendly");

        set("inquiry", ([
                "job" : (: ask_me :),
                "ok" : (: ask_ok :),
        ]));

        setup();
        add_money("silver", 5);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int greeting(object ob)
{
        int i=(query("eff_qi", ob)*100)/query("max_qi", ob);

        if( query("party/party_name", ob) == "藥王谷"){
                command("say 這位兄弟辛苦了，快請進！\n");
                return 1;}

        if (i<=30) {
                command("wa"+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"，你受了重傷啊！快請到裏面讓藥王谷醫師給你看看吧！\n");
                return 1;}

        if (i<=60) {
                command("look"+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"，你傷得不輕啊！快請到裏面療傷吧！\n");
                return 1;}

        if (i<=90) {
                command("pat"+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"，你受了點傷！到裏面買包藥服下就沒事了！\n");
                return 1;}

        else {
        switch( random(4) ) {
                case 0:
                        command("bow"+query("id", ob));
                        break;
                case 1:
                        command("nod"+query("id", ob));
                        break;
                case 2:
                        command("hi"+query("id", ob));
                        break;
                case 3:
                        command("welcome"+query("id", ob));
                        break;
                }
        }
}

int ask_me()
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "藥王谷"){
                command("say 你不是這裏的夥計，這種活怎麼能讓你幹呢？\n");
                return 1; }
        if( query_temp("work_pass", me)){
                command("say 不是讓去見谷主了嗎？\n");
                return 1; }

        if( (int)me->query_skill("medical",1)>=40 ) {
                command("say 你不需要幹這種活的！\n");
                return 1; }

        if( !query_temp("renwu_name", me)){
                ob = new(__DIR__"obj/saoba");
                ob->move(me);
                message_vision(YEL"遲未給了$N一支掃把。\n"NOR, me);
        switch ( random(7) ) {
        case 0 :
                set_temp("renwu_name", "休息室", me);
                command("say 你去打掃(dasao)一下休息室吧！\n");
                return 1;
        case 1 :
                set_temp("renwu_name", "北廳", me);
                command("say 你去打掃(dasao)一下北廳吧！\n");
                return 1;
        case 2 :
                set_temp("renwu_name", "正廳", me);
                command("say 你去打掃(dasao)一下正廳吧！\n");
                return 1;
        case 3 :
                set_temp("renwu_name", "庭院", me);
                command("say 你去打掃(dasao)一下庭院吧！\n");
                return 1;
        case 4 :
                set_temp("renwu_name", "回春堂", me);
                command("say 你去打掃(dasao)一下大門吧！\n");
                return 1;
        case 5 :
                set_temp("renwu_name", "內屋", me);
                command("say 你去打掃(dasao)一下內屋吧！\n");
                return 1;
        case 6 :
                set_temp("renwu_name", "南廳", me);
                command("say 你去打掃一下南廳吧！\n");
                return 1;
                }
        }
        else {
                command("say 你先把活幹完吧！\n");
                return 1;
        }
}

int ask_ok()
{
            object money, me;
          int amount, i,exp,pot;
          exp = 25+random(5);
          pot = 5+random(5);
        me = this_player();
        amount = random(3);
        i = random(20);
        if( query_temp("renwu_wancheng", me) >= 100){
                delete_temp("renwu_wancheng", me);
                delete_temp("renwu_name", me);
                if ( present("saoba", me) ) {
                        message_vision ("$N放下手中的掃把。\n", me);
                        destruct(present("saoba", me));
                        money = new ("/clone/money/silver");
                        money->move(me);
                        money->add_amount(amount);
                          addn("combat_exp", exp, me);
                          addn("potential", pot, me);
                          command("say 好！幹得不錯，這是賞你的！\n");
                                tell_object(me, HIC "你獲得了" + chinese_number(exp) + "點" 
                                 "經驗和" + chinese_number(pot) + "點潛能。"
                                 "\n" NOR);
                        if(i=1) {addn("max_jingli",1,me);} 
                } else { 
                        command("hmm"+query("id", me));
                        command("say 真沒用，讓你幹活，你把工具都丟了！\n");
                        }
        } else {
                command("say 你趕快去把活幹完啊！\n");
                }
        return 1;
}
