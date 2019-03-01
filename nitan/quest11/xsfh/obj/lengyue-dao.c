// lengyue_dao.c 冷月寶刀
#include <ansi.h>
#include <weapon.h>
inherit BLADE;
inherit F_UNIQUE;
#define QUESTDIR5 "quest/雪山飛狐/寶藏/"
#define QUESTDIR4 "quest/雪山飛狐/武功/"

void create()
{
        set_name( HIB"冷月寶刀"NOR , ({ "lengyue dao","lengyue baodao","baodao","lengyue","blade","dao"}));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIB"刀光如水，在冷月下流轉不定。刀柄上用金絲銀絲鑲著一鉤眉毛彎月。\n"NOR);
                set("value", 1);
                set("unique", 1);
                set("rigidity", 4);
                set("sharpness", 4);
                set("weapon_prop/parry", 4);
                set("wield_maxneili", 1400);
                set("treasure",1);
                set("wield_str", 24);
                set("material", "steel");
                set("wield_msg", HIB"$N緩緩抽刀出鞘，冷森森的一道青光激射而出，眨眼之間，手中已多了一柄寒氣逼人的長刀。\n"NOR);
                set("unwield_msg",HIB"$N將冷月寶刀小心的收起，耀人的寒光沒入刀鞘。\n"NOR);
        }
        init_blade(120);
        setup();
}
void init()
{
	if (environment()==this_player()&&!this_player()->query_condition("killer"))
	{

		add_action("do_yanjiu",({"yanjiu", "研究"}));
		add_action("do_guanzhu",({"guanzhu", "灌注"}));
		add_action("do_search",({"search", "尋找"}));
	}
}
int wield()
{
	  object me = environment();
      object ob = this_object();
	  int i=::wield();
          if(clonep() && i &&  objectp(me) && userp(me) && me->query(QUESTDIR4+"hujiadaofa")&&!me->query_temp(QUESTDIR4+"lengquan"))
	  {
     	   message_vision(HIW"\n$N將"+ob->query("name")+HIW"拿起，突然"+ob->query("name")+HIW"閃出耀眼的白光！\n"NOR,me);
     	   tell_object(me,HIB"突然從刀身傳來一股真力，瞬間你感覺七筋八脈全然貫通一氣。\n"NOR);
           me->set_temp(QUESTDIR4+"lengquan",1);
	   }
	   if(i) return i;
	   else return 0;
}

int unequip()
{
	  object me = environment();
  	  int i=::unequip();
          if(clonep() && objectp(me) && userp(me)  && me->query_temp(QUESTDIR4+"lengquan") && i )
           me->delte_temp(QUESTDIR4+"lengquan");
	   if(i) return i;
	   else return 0;
}
int do_yanjiu(string arg)
{
     	object me, obj;
     	me = this_player();
            obj = this_object();
     	if(me->is_busy()) return 0;
     	if(!me->query(QUESTDIR5+"start")) return 0;
     	if(me->query("neili") < 200)  return notify_fail("你內力不夠。\n");
     	if(!present("baozang tu",me)) return notify_fail("一把破刀你研究什麼？\n");
        if( ! arg || (arg != "lengyue baodao"&& arg != "baodao"&& arg != "lengyue"))
                return notify_fail("你要研究什麼？\n");
        if(me->query_temp(QUESTDIR5+"yanjiu_ok"))
     			return notify_fail("你已經發現刀身上的脈路，你可以嘗試對照藏寶圖！\n");
     	if(me->query(QUESTDIR5+"time")&&time()-me->query(QUESTDIR5+"time")<84600)
     			return notify_fail("你感覺全身氣血翻騰，看來剛才的研究已經大傷你的精神！\n");
     	if(me->query(QUESTDIR5+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR5+"combat_exp")<500000)
     			return notify_fail("你感覺全身氣血翻騰，看來以你當前的功力無法繼續研究！\n");

	   me->start_busy(1);
       message_vision(HIC"$N將"+this_object()->name()+HIC"翻來覆去地研究著！\n"NOR, me);
       me->add("neili", -150);
       me->add_temp(QUESTDIR5+"yanjiu",1);
      if(me->query_temp(QUESTDIR5+"yanjiu")>6)
      {
      	me->set(QUESTDIR5+"time",time());
      	me->set(QUESTDIR5+"combat_exp",me->query("combat_exp"));
      	tell_object(me,YEL"你發現"+obj->name()+YEL"刀身上刻有著數條脈路，似乎和藏寶圖可以對照。\n"NOR);
		tell_object(me,YEL"你感覺全身氣血翻騰，看來剛才的研究只怕已經大傷你的精神！\n"NOR);
      	me->set_temp(QUESTDIR5+"yanjiu_ok",1);
      	me->delete_temp(QUESTDIR5+"yanjiu");
      }
     	return 1;
}
int do_guanzhu(string arg)
{
     	object me, obj;
     	string force;

     	me = this_player();
     	obj = this_object();
     	if(me->is_busy()) return 0;
     	if(!me->query(QUESTDIR5+"start")) return 0;
        if( ! arg || (arg != "lengyue baodao"&& arg != "baodao"&& arg != "lengyue"))
                return notify_fail("你要幹什麼？\n");
        if(me->query_temp(QUESTDIR5+"guanzhu_ok"))
     			return notify_fail("你已經灌注了內力，刀身上的脈路更加清晰！\n");
        if(!stringp(force = to_chinese(me->query_skill_mapped("force"))))
      		return notify_fail("你沒有激發內功如何灌注內力！\n");
     	if(me->query("neili") < 200)  return notify_fail("你內力不夠。\n");

		message_vision(HIC"$N默運"+force+HIC"，慢慢地將內力灌注到"+obj->name()+HIC"中，突然"+obj->name()+HIC"閃出耀眼的白光！\n"NOR, me);
        tell_object(me,HIY"你仔細觀察"+obj->name()+HIY"，發現脈路更加清晰。\n"NOR);
     	me->add("max_neili", -10);
     	tell_object(me,HIB"只是，你感到有些內力不適，怕是這次灌注已經大傷你的內功修為。\n"NOR);
     	me->set_temp(QUESTDIR5+"guanzhu_ok",1);
	    me->start_busy(2);
     	return 1;
}
int do_search()
{
     object me, obj;
     me = this_player();
     if(!me->query(QUESTDIR5+"start")) return 0;
     if(!present("baozang tu",me)) return 0;
     if(!me->query_temp(QUESTDIR5+"map_where")) return 0;
     if(me->is_busy()) return 0;
     if(me->is_fighting()) return 0;
     if(me->query_temp(QUESTDIR5+"search_ok"))
     	return notify_fail("你已經發現找到藏寶地址了！\n");
     if((string)file_name(environment(me))!=me->query_temp(QUESTDIR5+"map_where"))
	    return notify_fail(HIW"你繞著"+environment(me)->query("short")+HIW"走了一圈，這裡沒有寶藏！\n"NOR);
     me->start_busy(2);
     if(random(2)) message_vision(HIW"$N繞著"+environment(me)->query("short")+HIW"走來走去，仔細觀察著什麼！\n"NOR, me);
	 else message_vision(HIW"$N似乎發現"+environment(me)->query("short")+HIW"一些什麼特別的地方，繞著"+environment(me)->query("short")+HIW"走來走去！\n"NOR, me);
     me->add_temp(QUESTDIR5+"search",1);

      if(me->query_temp(QUESTDIR5+"search")==4||me->query_temp(QUESTDIR5+"search")==8)
      {
      	me->set(QUESTDIR5+"time",time());
      	me->set(QUESTDIR5+"combat_exp",me->query("combat_exp"));
      	obj=new("/d/xingxiu/baozang/npc/gaoshou");
      	obj->set("kill_id",me->query("id"));
        obj->set("fight_id",me->query("id"));
      	if(me->query_temp(QUESTDIR5+"search")==4) obj->set("title",HIB"黑風寨三當家"NOR);
      	else obj->set("title",HIB"黑風寨寨主"NOR);
      	obj->move(environment(me));
        message_vision(HIC"突然從角落裡跳出一個人，$n對著$N嚷道：“我就是"+obj->query("title")+HIC"，趕快離開"+environment(me)->query("short")+HIC"。”\n"NOR, me,obj);
      	if(me->query_temp(QUESTDIR5+"search")==8)
      	{
      	    obj=new("/d/xingxiu/baozang/npc/gaoshou");
      	    obj->set("kill_id",me->query("id"));
            obj->set("fight_id",me->query("id"));
      	    obj->set("title",HIB"黑風寨二當家"NOR);
      	    obj->move(environment(me));
            message_vision(HIC"跟著又出來一個人，竟然是"+obj->query("title")+HIC"$N，嚷道：“我們老大的話，沒聽清楚？小子找死。”\n"NOR, obj);
            log_file("quest/FEIHU", sprintf("%s(%s)尋找寶藏的過程中遇到黑風寨寨主。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
      	}
      }
      if(me->query_temp(QUESTDIR5+"search")==12)
      {
      	me->set(QUESTDIR5+"time",time());
      	me->set(QUESTDIR5+"combat_exp",me->query("combat_exp"));
        tell_object(me,YEL"你發現"+environment(me)->query("short")+YEL"似乎正合乎刀身上刻的脈路，你心念一動走到"+environment(me)->query("short")+YEL"的一個角落。\n"NOR);
      	message_vision(HIY"$N意外地發現一個可以通向地下的通道。\n"NOR, me);
        message("channel:rumor", HIW"【謠言】"HIG + "傳說在"+environment(me)->query("short")+HIG"，有人找到闖王寶藏的進口！\n"NOR,users() );
        log_file("quest/FEIHU", sprintf("%s(%s)尋找寶藏成功。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
        if( !environment(me)->query("exits/down") ) {
           environment(me)->set("exits/down","/d/xingxiu/baozang/tiantan");
           call_out("close_path", 30,environment(me));
        }
      	me->set_temp(QUESTDIR5+"search_ok",1);
      	me->delete_temp(QUESTDIR5+"search");
      }
     	return 1;
}
void close_path(object ob)
{
        if( !ob->query("exits/down") ) return;
        message("vision",HIR"一陣風吹過，一切都有如往昔，剛才的一切如夢如幻！\n"NOR,ob);
        ob->delete("exits/down");
}
