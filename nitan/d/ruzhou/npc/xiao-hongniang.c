//土包子(tubaozi)告訴你：woodman@pub.wx.jsinfo.net

// Npc: /d/ruzhou/npc/xiao-hongniang.c 小紅娘  專髮結婚南需知
// by llm 99/06

#include <ansi.h>

inherit NPC;
int ask_marry();
int ask_guest();

void create()
{
        set_name("小紅娘", ({ "xiao hongniang", "hongniang" }));
   set("long","她是一個長得很好看的小姑娘。紮了兩根直直向上的小辮子，顯得愈發地可愛了。\n");
   set("gender", "女性");
   set("age", 16);
   set_skill("unarmed", 20);
   set_skill("dodge", 20);
   set_skill("parry", 20);
   set_temp("apply/attack", 30);
   set_temp("apply/defense", 30);
   set_temp("apply/damage", 5);
   set("combat_exp", 3000);
   set("shen_type", 1);
   set("inquiry", ([
                "結婚"    : (: ask_marry :),
      "婚禮": (: ask_marry :),
      "結婚需知"    : (: ask_marry :),
      "《結婚需知》"    : (: ask_marry :),
      "規則"    : (: ask_marry :),
      "請客"    : (: ask_guest :),
      "邀請"    : (: ask_guest :),
   ]));
   setup();

}
void init()
{
        object me, ob;
        me = this_object();
        ob = this_player();

        ::init();
        if( !ob || environment(ob) != environment() ) return;
          say("小紅娘笑嘻嘻地説道：“到紅娘莊來辦喜事，可得要知道一些規距，如果你想知道的話，可以問我！”\n");
}

int ask_guest()
{
        object me;
        me = this_object();

        if (me->is_busy())
                return notify_fail("小紅娘説道：“你忙完後再和我説話吧！”\n");
        if( this_object()->is_fighting()||me->is_fighting() )
                return notify_fail("小紅娘説道：“現在沒功夫！”\n");
        if( !living(this_object()) )
                return notify_fail("你還是先想辦法把小紅娘救醒吧。\n");
        if( query("gender", me) == "無性" )
                return notify_fail("小紅娘嘻嘻哈哈地肚子都笑痛了：“你要結婚？還要請客，哈哈哈！！！”\n");
        if( (query("age", me)<18) && (query("gender", me) == "男性" )
                 || (query("age", me)<16) && (query("gender", me) == "女性") )
                return notify_fail("小紅娘嘻嘻一笑道：“你和我差不多大，就想結婚請客了？不行的！”\n");
        if( query("class", me) == "bonze" || query("jobname", me) == "taoist" )
                return notify_fail("小紅娘抿嘴一笑道：“你可別拿我開玩笑，出家人怎麼能結婚呢？”\n");
   if( query("couple/have_couple", me) )
           return notify_fail("小紅娘奇道：“您不是已經結過婚了嗎？怎麼還想......”\n");
        write( "小紅娘説：“只有到媒婆那裏交了錢後，就可以讓媒婆幫你放喜鵲請客人了。”\n");
        return 1;
}

int ask_marry()
{
   object ob;
   if( query_temp("marry-book", this_player()) )
                return notify_fail("小紅娘有些不高興了：“你這個人怎麼會這樣，剛剛不是給過你一本了嗎？\n");
   message_vision("小紅娘點點頭，拿出一本《結婚需知》交給$N，説道：“結婚可是一輩子的大事，\n"
   "你一定要仔細看看，不要在拜堂時出洋象，弄得錢也花了，婚也沒結成。”\n",this_player());
   ob=new(__DIR__"obj/marry-book");
   ob->move(this_player());
        addn_temp("marry-book", 1, this_player());
        return 1;
}