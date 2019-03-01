// tianshi.c 李天師
// Modified by haiyan

#include <ansi.h>
inherit NPC;

mixed ask_ghost();
string ask_fail();
int accept_object(object me, object ob);

void create()
{
        set_name("李天師", ({ "li tianshi", "li", "tianshi" }));
        set("long", "這是一位仙風道骨的法師，身上的道袍上畫著一些驅魔符號。\n");
        set("nickname", HIY"鎮妖真人"NOR);
        set("gender", "男性");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 20);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 5000);
        set("max_jing", 500);
        set("neili", 3000);
        set("max_neili", 3000);

        set("combat_exp", 800000);
        set("score", 1000);

        set_skill("force", 200);
        set_skill("wudang-xinfa", 200);
        set_skill("dodge", 200);
        set_skill("strike", 200);
        set_skill("wudang-zhang", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("wudang-jian", 200);
        set_skill("taoism", 300);

        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        set("inquiry", ([
                "job"   : (: ask_ghost :),
                "捉鬼"  : (: ask_ghost :),
                "失敗"  : (: ask_fail :),
                "fail"  : (: ask_fail :),
                "桃木劍": "桃木劍是捉鬼的必備之物，自己去做一把好了。",
        ]));

        setup();
        carry_object("/clone/cloth/dao-cloth")->wear();
        carry_object("/d/taohua/obj/taojian")->wield();
}

#include "dirs.h"
#include "gui.h"

mixed ask_ghost()
{
      string *kp, p, room;
      object me, ob, ghost;
      int dam;
      me = this_player();

      if( query("family/family_name", me) != "武當派" && 
          query("family/family_name", me) != "全真教" )
           return "這位" + RANK_D->query_respect(me) + "也有捉鬼的本事嗎？";

      if (me->query_skill("taoism", 1) < 50)
           return "還是算了吧！你這點道行只怕給鬼捉了。";

      if( query("combat_exp", me)>400000 )
           return "你身手那麼高，這種小事怎麼敢勞你動手！";

      if( query_temp("gui/shougui", me) )
           return "剛才不是讓你去捉鬼了嘛？怎麼又回來了？";

      kp = keys(dirs);
      p = kp[random(sizeof(kp))];
      room = dirs[p][random(sizeof(dirs[p]))];
      if( wizardp(me) )  tell_object(me,sprintf("<鬼出現在 %s 地點>\n",room));

      dam = me->query_skill("taoism", 1) + random(10) - random(10);
      ghost = new(gui[random(sizeof(gui))] );
      ghost->move(room);
      set_temp("player",query("id",  me), ghost);
      set_temp("born_time", time(), ghost);
      set_temp("damage", dam*2/5, ghost);
      ghost->set_skill("claw", dam);

      tell_object(me, this_object()->name() + "對你道：據說最近" +
                  p + "常有" + ghost->name() + "出沒，附近居民"
                  "深受其害。你去把它收了吧。\n");
      message("vision", this_object()->name() + "在" + me->name() + "耳邊吩咐著什麼，" +
              me->name() + "一邊聽，一邊不住地點頭。\n", environment(me), me);
      ob = new("/d/wudang/quest/obj/fuzhi");
      ob->move(this_object());
      command("givefuzhito"+query("id", me));
      tell_object(me, this_object()->name() + "繼續道：" + ob->name() +
                  "可以讓鬼魂現身，可別弄丟了。\n");
      message_vision("$n對$N說道：快動身吧，多加小心。\n", me, this_object());
      set_temp("gui/shougui", 1, me);
      return 1;
}

string ask_fail()
{
      object me = this_player();

      if( !query_temp("gui/shougui", me) )
           return "我沒有給你什麼任務啊？";

      if (present("fu zhi", me))
          destruct(present("fu zhi", me));
      delete_temp("gui/shougui", me);
      delete_temp("gui/base", me);
      command("sigh"+query("id", me));
      addn("weiwang", -random(20), me);
      if( query("weiwang", me)<0)set("weiwang", 0, me);
      tell_object(me, HIR"你的江湖威望降低了！\n"NOR);
      return "你不能幹，我只好請別人去了！";
}


int accept_object(object me, object ob)
{
    int base, exp, pot;
    if( !me || environment(me) != environment() ) return 0;
    if ( !objectp(ob) ) return 0;
    if ( !present(ob, me) ) return notify_fail("你身上沒有這樣東西。");
    if( query("id", ob) == "fuzhi" )
    {
         if( !query_temp("gui/finish", me) )
         {
             command("sneer"+query("id", me));
             command("say 想蒙騙本天師嗎？");
             addn("weiwang", -random(50), me);
             if( query("weiwang", me)<0)set("weiwang", 0, me);
             tell_object(me, HIR"你的威望降低了！\n"NOR);
             return 1;
         }

         base=query_temp("gui/base", me);
         exp = base + random(base/2);
         pot = exp/3 + random(exp/3);
         if( query("potential", me) >= me->query_potential_limit())pot=1;
         message_vision("$n對$N點了點頭：不錯，不錯。\n", me, this_object());
         tell_object(me, HIG "通過這次□煉，你獲得了" + chinese_number(exp) +
                     "點經驗和" + chinese_number(pot) + "點潛能。\n" NOR);
         tell_object(me, HIC"你對道學心法有了新的領悟！\n"NOR);
         me->improve_skill("taoism", me->query_int()*2);
         addn("combat_exp", exp, me);
         addn("shen", exp/2+random(exp/2), me);
         addn("potential", pot, me);
         delete_temp("gui/base", me);
         delete_temp("gui/shougui", me);
         delete_temp("gui/finish", me);
         destruct(ob);
         return 1;
    }
    else
    {
        command("say 你給我這種東西幹什麼？");
        return 0;
    }
}
