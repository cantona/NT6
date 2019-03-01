// chenglingsu
//modified by tangfeng@SJ 2004

inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR3 "quest/雪山飛狐/解藥篇/"

string ask_jindi();
int ask_jieyao();
int ask_yaofang();
int ask_qixinghaitang();
int ask_hufei();
void destroying(object obj);
void giveyaofang(object me);

void create()
{
       set_name("程靈素", ({ "cheng lingsu", "cheng" }));
       set("nickname", "藥師");
       set("long",
               "她就是藥師程靈素。\n"
               "年紀已僅有二十來歲，但是各種藥理極為精通。\n");
        set("gender", "女性");
       set("age", 21);
       set("attitude", "friendly");
       set("shen", -3000);
       set("str", 29);
       set("int", 27);
       set("con", 26);
       set("dex", 26);

       set("max_qi", 200);
       set("max_jing", 100);
       set("neili", 1000);
       set("max_neili", 1000);
       set("jiali", 10);
       set("combat_exp", 80000);
       set("no_get",1);
       set("no_bark",1);
       set_skill("force", 60);
        set_skill("yinyun-ziqi", 60);
       set_skill("dodge", 60);
       set_skill("jinshe-zhangfa", 60);
       set_skill("tiyunzong", 60);
       set_skill("strike", 60);
       set_skill("jinshe-jianfa", 60);
       set_skill("parry", 60);
       set_skill("sword", 60);
       set_skill("poison", 160);
       set_skill("medicine", 160);
       set_skill("literate", 120);
        map_skill("force", "yinyun-ziqi");
       map_skill("dodge", "tiyunzong");
       map_skill("strike", "jinshe-zhangfa");
       map_skill("parry", "jinshe-jianfa");
       map_skill("sword", "jinshe-jianfa");
       prepare_skill("strike", "jinshe-zhangfa");

       set("inquiry", ([
                "五毒教" : (: ask_jindi :),
                "解藥" : (: ask_jieyao :),
                "藥方" : (: ask_yaofang :),
                "治療" : (: ask_jieyao :),
                "七星海棠" : (: ask_qixinghaitang :),
                "胡斐" : (: ask_hufei :),
                "禁地" : (: ask_jindi :),
                "苗人鳳" : "苗大俠武功高強，倒是其次，多年來興俠仗義尤其佩服！\n",
                "胡一道" : "遼東大俠胡一刀！\n",
       ]));
       setup();
       carry_object("/clone/armor/cloth")->wear();
}
void init()
{
     add_action("do_yes","yes");
     add_action("do_no","no");
}
string ask_jindi()
{
       object applicant;
       object ob;
       int exp;
       applicant=this_player();

        exp=(int)applicant->query("combat_exp",1);
        if(exp<90000)
        return "你就這點功夫，恐怕連五毒教的山也上不去，等幾年在說吧！\n";

        if (  present("jiuxuebiyun dan", this_player()) )
        return "我已經給過你了，為何還要向我要？此藥很難煉制，不要太貪心！\n";

        if( applicant->query("wudu_jiedu") ){
        ob = new(__DIR__"obj/jxdan1");
        ob->move(applicant);
        message_vision("$N獲得一顆九雪碧雲丹。\n",this_player());

        return "你上次答應我的事情還沒做，怎麼又來要？ 程靈素皺了皺眉，
冷冷的說到：“丹到還有一顆，你要就拿去吧。\n";
        }

         applicant->set_temp("marks/程",1);
         return "五毒教的禁地種滿了各種奇花異草，其中大部分具有巨毒，如果一旦隨著
空氣吸入體中，必將中毒而死。如果你想去五毒教，我這裡有顆丹藥可抵制其毒。你如能
進去幫我尋得雪蛛，我願將此藥贈于你，你考慮一下，是否答應(yes)或者不答應(no)我。\n";


}
int do_yes()
{

   object jxdan, me, ob;
   me = this_object();
   ob = this_player();

   if(!ob->query_temp("marks/程")) return 0;
        jxdan = new(__DIR__"obj/jxdan");
   ob->set("wudu_jiedu", 1);
   ob->delete_temp("marks/程");
   jxdan->move(this_player());
   message_vision("$N獲得一顆九雪碧雲丹。\n",this_player());
   message_vision("$N對你微微一笑，說道：祝你此行順利。另外希望你能言而有信。\n",me, this_object());
   return 1;
}
int do_no()
{
   object me = this_player();
   if(!me->query_temp("marks/程")) return 0;
   message_vision("程靈素無奈的一笑，說到，既然你不能答應我的要求，丹藥自然不能給你。\n",me);
   me->delete_temp("marks/程");

   return 1;
}
int accept_object(object who, object ob,object me)
{
	 if(who->query_condition("killer"))
	 {
	   command("shake "+who->query("id"));
     command("say 你目前被官府通緝，我如何敢受"+ob->name()+"！");
	   return 0;
	 }
	 if(ob->query("id")=="qixing haitang" )
   {
   	 command("ah "+(string)who->query("id"));
     if(who->query_temp(QUESTDIR3+"qixinghaitang") && who->query(QUESTDIR3+"start")&& ob->query("owner")==who->query("id"))
     {
     	command("nod "+(string)who->query("id"));
     	command("say 就是它！但是要想制造解藥，還需要一種東西，它就生長在五毒教，一種藍色的藥花。");
     	who->set_temp(QUESTDIR3+"jieyao2",1);
     	who->delete_temp(QUESTDIR3+"qixinghaitang");
     }
     else  command("thank "+(string)who->query("id"));
   }
   else if(ob->query("id")=="lanse yaohua")
   {
   	 command("ah "+(string)who->query("id"));
     if(who->query_temp(QUESTDIR3+"jieyao2") && who->query(QUESTDIR3+"start")&& ob->query("owner")==who->query("id"))
     {
     	command("nod "+(string)who->query("id"));
     	command("say 就是它！稍微等我一下，我馬上就好。\n");
     	tell_object(who,HIC"程靈素開始制起解藥，從程序上看，只要藥物齊全，似乎不是很復雜。\n\n"NOR);
	    tell_room(environment(who),HIC"\n程靈素轉過身，似乎開始制造解藥。\n"NOR, ({ who }));
     	who->set_temp(QUESTDIR3+"getjieyao",1);
     	who->delete_temp(QUESTDIR3+"jieyao2");
     	who->start_busy(4);
      remove_call_out("giveyaofang");
      call_out("giveyaofang",10, who);
     }
     else  command("thank "+(string)who->query("id"));
   }
   else if (ob->query("id") == "xue zhu" )
   {
   	 command("thank " + who->query("id"));
     command("say 你果然言而有信，下次你要再去五毒教來找我吧。\n");
     who->delete("wudu_jiedu");
   }
   else
   {
     command("? "+(string)who->query("id"));
   }
   call_out("destroying", 1, ob);
   return 1;
}
void destroying(object obj)
{
        if(!userp(obj)) destruct(obj);
        return;
}
void giveyaofang(object me)
{
      object obj;
      if(!me) return;

      obj=new("/d/miaojiang/npc/obj/yaofang");
      if(!obj) return;
      if(!me->query_temp(QUESTDIR3+"getjieyao")) return;
	    if(environment(me)!=environment(this_object()))
 	    {
 	    	command("say 人呢？難道不要解藥了？");
       	me->delete_temp(QUESTDIR3+"getjieyao");
 	    	return;
 	    }
     	command("nod "+(string)me->query("id"));
     	command("say 等著急了吧。這是藥方，你可以使用內屋那個藥爐制作。");
      obj->move(me);
      tell_object(me,HIC"程靈素給你一份"+HBCYN"藥方"NOR+HIC"。\n"NOR);
            tell_room(environment(me),HIC"\n程靈素交給"+me->query("name")+"一張紙。\n"NOR, ({ me }));
  	  if(!present("qixing haitang",me))
  	  {
  		  obj=new("/d/miaojiang/npc/obj/qixinghaitang");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一份"+HBCYN"七星海棠"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("lanse yaohua",me))
  	  {
  		  obj=new("/d/miaojiang/npc/obj/lanseyaohua");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一朵"+HBCYN"藍色藥花"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("ren shen",me))
  	  {
  		  obj=new("/clone/medicine/drug/renshen.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一棵"+HBCYN"人參"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("jinyin hua",me))
  	  {
  		  obj=new("/clone/medicine/drug/hua.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一棵"+HBCYN"金銀花"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("zang honghua",me))
  	  {
  		  obj=new("/clone/medicine/drug/zanghonghua.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一朵"+HBCYN"藏紅花"NOR+HIC"。\n"NOR);
  	  }
      return;
}
int ask_yaofang()
{
	object obj,me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("nod "+me->query("id"));
	  command("say 七星海棠，可稱謂天下第一奇草，本身劇毒無比。用這種辦法治療苗大俠也是無奈之舉。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")
      && me->query_temp(QUESTDIR3+"getjieyao"))
  {
  	  if(!present("qixing haitang",me))
  	  {
  		  obj=new("/d/miaojiang/npc/obj/qixinghaitang");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一份"+HBCYN"七星海棠"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("lanse yaohua",me))
  	  {
  		  obj=new("/d/miaojiang/npc/obj/lanseyaohua");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一朵"+HBCYN"藍色藥花"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("ren shen",me))
  	  {
  		  obj=new("/clone/medicine/drug/renshen.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一棵"+HBCYN"人參"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("jinyin hua",me))
  	  {
  		  obj=new("/clone/medicine/drug/hua.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一棵"+HBCYN"金銀花"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("zang honghua",me))
  	  {
  		  obj=new("/clone/medicine/drug/zanghonghua.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程靈素給你一朵"+HBCYN"藏紅花"NOR+HIC"。\n"NOR);
  	  }

  	if(!present("yao fang",me))
  	{
  		obj=new("/d/miaojiang/npc/obj/yaofang");
  		obj->move(me);
      tell_object(me,HIC"程靈素給你一份"+HBCYN"藥方"NOR+HIC"。\n"NOR);
     	command("say 不要再丟了。");
  	}
  	else
  	{
      command("sigh "+me->query("id"));
	    command("say 七星海棠，可稱謂天下第一奇草，本身劇毒無比。用這種辦法治療苗大俠也是無奈之舉。");
	  }
	  return 1;
  }
  command("say 七星海棠，可稱謂天下第一奇草，本身劇毒無比。");
	return 1;
}
int ask_jieyao()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("nod "+me->query("id"));
	  command("say 我想也應該有效地治好苗大俠的病。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"getjieyao"))
  {
	  command("nod "+me->query("id"));
	  command("say 趕快給苗大俠治療去吧。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao2"))
  {
	  command("nod "+me->query("id"));
	  command("say 除了七星海棠，還需要五毒教一種藍色藥花，我們一起找找看。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"qixinghaitang"))
  {
	  command("nod "+me->query("id"));
	  command("say 快把七星海棠給我。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao1"))
  {
	  command("nod "+me->query("id"));
	  command("say 七星海棠正是這主藥之一，可惜被閻基和石萬嗔搶走了。你趕快去找回來吧。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
    tell_object(me,HIC"你著急地將苗大俠病情和症狀轉告給程靈素，應該是斷腸草之毒。\n"NOR);
    tell_room(environment(me),HIC"\n"+me->query("name")+"很著急地和程靈素說了些什麼。\n"NOR, ({ me }));
	  command("nod "+me->query("id"));
	  command("say 苗大俠也是我敬佩的人，我自當盡力。你說這種毒藥的確很兇猛，雖然不是立刻斃命，但是必須使用一種奇草。");
	  command("say 就是劇毒的七星海棠，當年我師傅種植了三棵，只有一顆成熟，可惜被閻基和石萬嗔搶走了。你趕快去找回來吧。\n");
	  me->set_temp(QUESTDIR3+"jieyao1",1);
	  return 1;
  }
	command("?");
	command("sorry");
	return 1;
}
int ask_qixinghaitang()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("nod "+me->query("id"));
	  command("say 七星海棠，可稱謂天下第一奇草，本身劇毒無比。用這種辦法治療苗大俠也是無奈之舉。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")
      && (me->query_temp(QUESTDIR3+"getjieyao")
      ||me->query_temp(QUESTDIR3+"jieyao1")
      ||me->query_temp(QUESTDIR3+"jieyao2")
      ||me->query_temp(QUESTDIR3+"askqixinghaitang"))
      )
  {
	  command("sigh "+me->query("id"));
	  command("say 七星海棠，可稱謂天下第一奇草，本身劇毒無比。用這種辦法治療苗大俠也是無奈之舉。");
	  return 1;
  }
  command("say 七星海棠，可稱謂天下第一奇草，本身劇毒無比。");
	return 1;
}
int ask_hufei()
{
  message_vision(HIC"$N沉默很久道：我不認識這個人......\n"NOR,this_object());
	return 1;
}
