// nuerhai.c

inherit NPC;

#include <ansi.h>;
void create()
{
        set_name("努兒海", ({ "nu erhai", "nu" }));
        set("title", HIM"西夏一品堂"HIG"接引使"NOR);
        set("gender", "男性");
        set("age", random(10) + 20);
        set("str", 25);
        set("dex", 16);
        set("per", 13);
        set("long", "一個身形極高、鼻子極大，聲音陰陽怪氣的漢子。\n");

        set("combat_exp", 100000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set_skill("unarmed", 80);
        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 50);

        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);

        setup();
        carry_object("/d/city/npc/obj/tiejia")->wear();
}

void init()
{
        object me,ob;
        me = this_object () ;
        ob = this_player () ;
        ::init();
        add_action("do_join","join");
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me, ob);
        }
}

string ask_me()
{
        return "誠招天下豪傑。你想加入我一品堂(join yipintang)嗎？";
}

int do_join(string arg)
{
        object ob;
        mapping party;

        ob = this_player () ;
        if( !arg || arg!="yipintang" )
                return notify_fail("努兒海問道：“你要加入什麼組織？”\n");
           if( query("yipin/joined", ob) )
                return notify_fail("努兒海奇怪地説道：“你開什麼玩笑？你已經是堂中人了。”\n");
           if( query("combat_exp", ob)<1000 )
                return notify_fail("努兒海哈的一聲大笑起來：“我們只要江湖中的成名英雄。你算什麼材料？”\n");
        command("gongxi"+query("id", ob));
        message_vision("努兒海衝着$N笑道：“那好，咱們現在就是一殿之臣，一家人了！”\n",ob);
        set("yipin/joined", 1, ob);
        return 1;
}
