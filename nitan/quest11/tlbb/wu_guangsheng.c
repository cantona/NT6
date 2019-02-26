// NPC :wu_guangsheng.c 吳光勝
// By River 98/12
inherit NPC;
#include <ansi.h>

#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
void create()
{
        set_name("吳光勝", ({ "wu guangsheng", "wu", "guangsheng"}));
        set("title","無量劍東宗弟子");              
        set("gender", "男性" );
        set("age", 36);
        set("str", 27);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 15);
   	    set("attitude", "friendly");

        set("max_qi", 1000);
        set("max_jing", 800);
        set("eff_jingli", 800);
        set("neili", 1000);
	      set("qi", 1000);	
        set("max_neili", 1000);      
        set("unique", 1);
        
        set("long","他是無量劍東宗的弟子。\n");
        set("combat_exp", 200000);
        set("shen", 800); 

        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("cuff", 80);
        set_skill("sword", 80);
        set_skill("qiantian-yiyang", 80);   
        set_skill("xiaoyaoyou", 80);
        set_skill("wuliang-jianfa", 80);
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "wuliang-jianfa");
        map_skill("sword", "wuliang-jianfa");
        map_skill("force", "qiantian-yiyang");         

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/dali/wuliang/npc/obj/changpao")->wear();
}
void die()
{
	object me,ob=this_object();
       me=ob->query_temp("last_damage_from");

 if(objectp(me)&& !present("yu guangbiao", environment(me))&& me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query_temp(QUESTDIR1+"jianying") || me->query_temp("marks/xiaoyao/gotowyz")  )
 {
    tell_object(me,HIY"\n這"+ob->name()+"眼見就要喪命，突然開口向你求饒，告訴你關於後山劍影的祕密。\n"NOR);
	  tell_room(environment(me),HIC"\n只見，鬱光標似乎重傷在身，向"+me->query("name")+"似乎討教着什麼。\n"NOR, ({ me }));
	  me->set_temp(QUESTDIR1+"jianying",1);
    tell_object(me,HIY"\n按"+ob->name()+"所説，這後山一個峭崖邊，一塊常見到壁上常出現舞劍的人影，有時是男子，有時是女子，\n"
                       "有時更是男女對使，互相擊刺。玉壁上所顯現的劍法之精，據説極其高明，相傳是仙人使劍。\n"NOR);

    tell_object(me,HIC"\n你聽完"+ob->name()+"之後，還是手下不留情面，雙手一緊，一股內力蓬勃而發。\n"NOR);
	  tell_room(environment(me),HIC"\n吳光勝説完很多之後，然而不知為何，似乎氣血一震，好像失去了什麼似的，慢慢萎靡倒地。\n"NOR, ({ me }));
    message_vision(HIG"$n仰天長歎，為什麼啊，為什麼，$N竟然如此狠心。\n"NOR, me, this_object());
    if(me->query_temp("marks/xiaoyao/gotowyz")) {
    	me->delete_temp("marks/xiaoyao/gotowyz");
       me->delete_temp(QUESTDIR1+"jianying",1);
       me->set("marks/xiaoyao","gotofind");	
    	}
    
  }
	::die();
}
