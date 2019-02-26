//by daidai
#include <ansi.h>
//inherit NPC;
inherit FIGHTER;
#define QUESTJINSHE "quest/金蛇劍法/"

void create()
{
	set_name("温方義", ({ "wen fangyi", "wen", "fangyi" }));
        set("gender", "男性");
        set("title", "温家五老");
        set("long", 
        "他就是温家五老的老二温方義。\n"
        "一個五十來歲的老者，一雙眼睛透出精光。\n");
        set("str", 25);
        set("dex", 25);
        set("con", 25);
        set("int", 25);
        set("per", 25);
        set("shen_type", -1);
        set("unique", 1);

        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("blade", 300);
        set_skill("cuff",300); 
        set_skill("yijin-jing",300);
        set_skill("shaolin-shenfa",300);
        set_skill("wenjia-daofa",300);
        set_skill("wenjia-quan",300);
        set_skill("wuxing-zhen",200);
        
        map_skill("force","yijin-jing");
        map_skill("cuff","wenjia-quan");
        map_skill("blade","wenjia-daofa");
        map_skill("dodge","shaolin-shenfa");
        map_skill("parry","wenjia-quan");
        
      prepare_skill("cuff", "wenjia-quan");

  
        set("combat_exp", 2000000);
        set("max_qi", 30000);
        set("max_jing", 3000);
        set("max_neili", 5000);
        set("eff_jingli",3000);
        set("qi",30000);
        set("jing",3000);
        set("jingli",3000);
        set("neili", 5000);

       setup();  
        
     carry_object(ARMOR_D("cloth"))->wear();
    carry_object("/clone/weapon/blade1")->wield();

}
void init()
{
    object me, ob;  
    int i;    
    ::init();

    ob = this_object();
    if( !query("kill_id", ob))return ;
          me=find_player(query("kill_id", ob));
        if(!me) return;
          if(environment(me)!=environment(ob)) return;
    if( query("setok", ob))return ;
        set("setok", 1, ob);
          ob->copy_state();     
        //根據門派更新npc 的一些狀態
          i=query("max_pot", me);
          if(i<350) i=350;
          i=i-100;      
         ob->set_skills_level(i-random(100)+random(50));
          if( random(2))set("combat_exp",query("combat_exp",  me), ob);
    else set("combat_exp",query("combat_exp",  me)*2/3, ob);
          set("max_neili",query("max_neili",  me), ob);
        set("max_jingli",query("max_jingli",  me), ob);
        set("max_qi",query("max_qi",  me)*3/2, ob);
        set("max_jing",query("max_jing",  me), ob);
                set("neili", query("max_neili")*3/2, ob);
                set("jingli", query("max_jingli")*3/2, ob);
                set("eff_jingli", query("max_jingli")*3/2, ob);
                set("qi", query("max_qi"), ob);
                set("eff_qi", query("max_qi"), ob);
                set("jing", query("max_jing")*3/2, ob);
                set("eff_jing", query("max_jing")*3/2, ob);
                ob->set_skill("wuxing-zhen",200);
                remove_call_out("zhen");
                call_out("zhen",1,ob);
                remove_call_out("dest");
                call_out("dest", 600,ob);
                remove_call_out("do_kill");
                call_out("do_kill",2, me);
}

void zhen(object ob) 
{
   if( !ob ) return;                   
   command("lineup with wen fangshi");
   command("lineup with wen fangda");
   command("lineup with wen fangwu");
   command("lineup with wen fangyi");
   command("lineup with wen fangshan");
   command("lineup form wuxing-zhen");   
   command("lineup with wen fangshi");
   command("lineup with wen fangda");
   command("lineup with wen fangwu");
   command("lineup with wen fangyi");
   command("lineup with wen fangshan");
   call_out("zhen",1,ob);
}
int do_kill(object me)
{
        object ob = this_object();
        if(!me) return 0;
        remove_call_out("checking");
        call_out("checking", 2, me, ob);
        ::do_kill(me);
}

//檢查，quest過程不允許死亡
int checking(object me, object ob)
{
        int ret =  ::checking(me,ob);
        if(!ret) return 0;
        remove_call_out("checking");
        call_out("checking", 1, me, ob);
  if( !living(me) && living(ob) && query("jing", ob)>0 && query("jingli", ob)>0 && query("qi", ob)>0){
                remove_call_out("checking");
                tell_room(environment(me), HIB"\n"+me->name()+"眼看就是不敵，突然一股勁風襲來，五行陣一頓出現一道間隙，"+me->name()+"順勢闖出温家堡莊。\n"NOR);
                me->move("/d/xiangyang/ncx3");
                tell_room(environment(me), HIB"\n一個身影突然飛來，待你仔細看來，原來是"+me->name()+"，只見"+me->name()+"突然一頓，竟然昏倒在地。\n"NOR);
                me->delete_tem(QUESTJINSHE+"start_kill");
                delete_temp(QUESTJINSHE+"kill", me);
                delete_temp(QUESTJINSHE+"kill_5wen", me);
                delete_temp(QUESTJINSHE+"have_kill", me);
                set("qi", 100, me);
                set("jing", 100, me);
                set("jingli", 100, me);
        log_file("quest/FEIHU",sprintf("%s紀錄：%s(%s)金蛇劍法失敗。經驗%d。\n",ob->name(1),me->name(1),query("id", me),query("combat_exp", me)));
    tell_room(environment(ob), ob->name()+"哼了一聲：“快追！”\n");
                destruct(ob);
                return 1;
        }
 if( !me || me->is_ghost() || query("eff_qi", me)<query("max_qi", me)/15 || query("qi", me)<query("max_qi", me)/20 || environment(me) != environment(ob)){
                remove_call_out("checking");
                remove_call_out("do_lost");
                call_out("do_lost",0);
                return 1;
        }
   if(!me->is_fighting(ob)){remove_call_out("do_kill");  call_out("do_kill",1,me);}
}
void do_lost()
{
        object me,ob;
        ob = this_object();
        if(!ob) return;
        me=present(query("kill_id", ob),environment(ob));
        if( !me)me=find_player(query("kill_id", ob));
        if(me)
        {
                delete(QUESTJINSHE+"start_kill", me);

                delete_temp(QUESTJINSHE+"kill", me);
                delete_temp(QUESTJINSHE+"have_kill", me);
                delete_temp(QUESTJINSHE+"kill_5wen", me);

        log_file("quest/FEIHU",sprintf("%s紀錄：%s(%s)金蛇劍法失敗。經驗%d。\n",ob->name(1),me->name(1),query("id", me),query("combat_exp", me)));
        }
  tell_room(environment(ob), ob->name()+"哼了一聲：“就這點本事啊！”\n");
        destruct(ob);
}

void dest(object ob)
{
  if(!ob) return;
  tell_room(environment(ob), HIR+"\n"+ob->name()+"哼了一聲，點子厲害，我們撤~~~~~~~\n"NOR);
        destruct(ob);
}
void die()
{
        object me,ob=this_object();
        
        if( query("kill_id", ob) )
        {
                me=present(query("kill_id", ob),environment(ob));
                if( !me)me=find_player(query("kill_id", ob));
                if(!me) return 0;
      if( query_temp(QUESTJINSHE+"start_kill", me) )
      { 
                if( !query_temp(QUESTJINSHE+"kill", me) )
                {
                  addn_temp(QUESTJINSHE+"kill_5wen", 1, me);
                  if( query_temp(QUESTJINSHE+"kill_5wen", me) == 5 )
                  {
                    set(QUESTJINSHE+"over", 1, me);
                    set_temp(QUESTJINSHE+"have_kill", 1, me);
                    delete_temp(QUESTJINSHE+"kill_5wen", me);
                  }
                }
            }
  }
        command("disapp");
    
        ::die();
}

