//long.c

#include <ansi.h>

inherit NPC;
//inherit F_MASTER;

void create()
{
        set_name("龍亦凡", ({ "long", "dragon" }));
        set("long", "他就是天下聞之色變的俠客島島主，號稱“不死神龍”。\n"
                   +"他鬚眉全白，臉色紅潤，有如孩童。看不出他的實際年紀。\n"
                   );
        set("title", "俠客島主");
        set("gender", "男性");
        set("age", 75);
        set("nickname", HIR "不死神龍" NOR);
        set("shen_type",1);
        set("attitude", "peaceful");

        set("str", 30);
        set("int", 29);
        set("con", 30);
        set("dex", 28);

        set("qi", 900);
        set("max_qi", 900);
        set("jing", 900);
        set("max_jing", 900);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);

        set("combat_exp", 1500000);
        set("score", 200000);
        set_skill("force", 170);
        set_skill("unarmed", 100);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("hand",170);
        set_skill("staff", 170);

//      set_skill("yanyangong", 200);
        set_skill("jinwu-blade", 150);
//      set_skill("xiake-zhangfa", 100);
        set_skill("lingxu-bu", 150);

//      map_skill("force", "yanyangong");
        map_skill("dodge", "lingbo-weibu");
//      map_skill("unarmed", "xiake-zhangfa");
//      map_skill("hand", "xiake-zhangfa");
        map_skill("parry", "jinwu-blade");
        map_skill("staff", "jinwu-blade");

        create_family("俠客島",1, "島主");
        set("inquiry",([
           "臘八粥" :   "臘八粥只贈有緣人，不知你是否滿足條件。？\n",
           "銅牌"   :   "我這可沒有這玩藝，你如想要的話，可找別人問一問。\n",
        ]) );

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        add_money("gold",2);
}

void attempt_apprentice(object ob)
{
        message_vision("龍島主拍拍$N的頭，微微搖了搖頭。\n",ob);
//        command("recruit " + ob->query("id"));
        return;
}

int accept_object(object who, object ob)
{
        object obn;
        object room;
        object key;

        if( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("你沒有這件東西。\n");

        if( query("name", ob) != "賞善銅牌" )
        {
              message_vision("我不需要這件東西。\n");
              return 0;
        }
        if( query_temp("own", ob) != query("name", who) )
        {
              message_vision("這不是你的牌子。");
              return 0;
        }
        command("say原來是"+query("name", who)+"大俠"+"歡迎光臨本島。");

        obn=new("/d/xiakedao/obj/labazhou");
        obn->move(who);
        command(" say 這是本島特產臘八粥，外邊可不易喝到，其中最主要的一味是<斷腸蝕骨腐心草>，"
           + "瞧" +  RANK_D->query_respect(who) + "也是有緣之人，快乘熱喝，這樣效力方著。"
          );
        message_vision("龍島主給了你一碗臘八粥",who);
        if( query_temp("zhou", who) == 2 )
        {
             command(" say 看來居士福緣深厚，有機會一睹武林絕技，請進吧！");
             set_temp("zhou", 0, who);
             message_vision("只聽得一陣隆隆的響聲由遠及近。\n", this_player());
             message_vision("只見島主身後的石板緩緩移了開來，露出一條長長的甬道。\n", this_player());
             set("exits/enter", "/d/xiakedao/mishi", environment(who));
             room=environment(who);
             remove_call_out("close");
             call_out("close", 15, room);
             key = new("/d/xiakedao/obj/key");
     message_vision("這是我身後石門的鑰匙，也是俠客島上的憑證，希望你妥善保管，不可隨意丟棄，" +
                    "更不可交付他人，離島時應與歸還。\n", who);
             key->move(who);
             return 1;
        }
        set_temp("zhou", 1, who);
        return 1;
}
void close(object room)
{
        message("vision","轟隆隆的響聲響過之後，石板又合上了。\n", room);
        delete("exits/enter", room);
}
