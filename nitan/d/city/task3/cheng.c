// cheng.c
#include <ansi.h>
inherit NPC;

int ask_me();
int ask_stop();

void create()
{
        set_name("程藥發", ({ "cheng yaofa", "cheng" , "yaofa"}) );
        set("title", "揚州知府" );
        set("gender", "男性" );
        set("age", 43);
        set("str", 20);
        set("dex", 20);
        set("long", "他就是程藥發，揚州現任知府。\n");
        set("combat_exp", 30000);
        set("shen_type", 0);
        set("attitude", "heroism");

        set_skill("unarmed", 50);
        set_skill("force", 50);
        set_skill("sword", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 15);

        set("neili", 500); 
        set("max_neili", 500);
        set("jiali", 10);
        set("inquiry", ([
                "任務": (: ask_me :),
                "捕快": (: ask_me :),
                "work": (: ask_me :),
                "效力": (: ask_me :),
                "quest": (: ask_me :),
                "揚州府": (: ask_me :),
                "放棄": (: ask_stop :),
                "stop": (: ask_stop :),
        ]) );
        setup();
        carry_object(__DIR__"obj/mangpao")->wear();
        carry_object(__DIR__"obj/zizhuxiao")->wield();
        add_money("silver",30);
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
}
int ask_me()
{
        object ob,me;
        me = this_player();
        if( query("officerlvl", me)<1 )
        {
                command("say 這位"+ RANK_D->query_respect(me)
                        + "若有意為朝廷效力，不妨到簽押房報名！\n");
                return 1;
        }
        command("say 你身為朝廷官員，不能白吃國家俸祿，須得努力工作(work)才是
啊！每次辦差歸來須如實向本府匯報(finish)。");
        return 1;
}
int ask_stop()
{
        object ob,me;
        me = this_player();
        if( !query_temp("bt/working", me) )
        {
                command("say 這位"+ RANK_D->query_respect(me)
                        + "若不願意為朝廷效力，本府也不勉強！\n");
                return 1;
        }
        command("say 你真的沒有抓到罪犯嗎？(answer yes或answer no)");
        set_temp("bt/stop", 1, me);
        return 1;
}
int do_answer(string arg)
{
        object ob,me;
        me = this_player();
        if( !query_temp("bt/stop", me))return notify_fail("什麼？\n");
        if (!arg || (arg !="yes"&&arg !="no"))
        {
                command("say 你吞吞吐吐的在說什麼啊！\n");
                return 1;
        }
        if (arg =="no")
        {                               //113
                command("say 罪犯既已抓到了你還要放棄什麼？\n");
                return 1;
        }
        message_vision (BLU"程藥發不由大怒，拍案而起。\n"NOR,me);
        command("say 大膽！汝身為朝廷官員，食國家俸祿，辦差如此不力，休怪本府無");
        command("say 來啊，與我重責二十大板。");
        message_vision(BLU"四下裡頓時擁出幾個如狼似虎的衙役將"+query("name", me)+"按翻在地。\n"NOR,me);
        delete_temp("bt/stop", me);
        me->apply_condition("bt_stop", 10);
        return 1;
}
