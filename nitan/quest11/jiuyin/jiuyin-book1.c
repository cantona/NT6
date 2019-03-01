// By Spiderii@ty 天賦系統
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"九陰真經上卷"NOR, ({ "jiuyin zhenjing", "shang juan", "book"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "卷");
                set("long","這是名震江湖之九陰真經的上卷。你可以研讀以下的技能：\n"+
                           "道德經    (daode-jing) \n"
                           "九陰真功  (jiuyin-zhengong) \n"
                           "九陰身法  (jiuyin-shenfa) \n"
                           "玄陰劍法  (xuanyin-jian) \n"
                );
                set("treasure", 1);
                set("unique", 1);
                set("value", 0);
                set("material", "skin");
                set("no_drop", 1);
                set("no_give", 1);
                set("no_get", 1);
                set("no_steal", 1);
        }
}

void init()
{
       add_action("do_study", "read");
       add_action("do_unite", "he");
}

int do_unite(string arg)
{
	object me = this_player();
	object ob;
	if( arg ) return 0;
	if((present("shang juan", me)) && (present("xia juan", me))){
		if(me->query_skill("jiuyin-zhengong", 1) < 200
		 || me->query_skill("jiuyin-shenfa", 1) < 150
		 || me->query_skill("xuanyin-jian", 1) < 150 )
			return notify_fail("你還是將此卷讀熟後再合並九陰真經上、下卷吧。\n");
		message_vision(HIY"$N將九陰真經上、下卷互相對照，重新抄錄了整本九陰真經。\n"NOR,me);
		ob = new(__DIR__"book");
		ob->set("owner",me->query("id"));
		if(!me->query("quest/jiuyin1/owner"))
			log_file("quest/jiuyin",
				sprintf("%s(%s)將九陰真經上、下卷互相對照，抄錄了整本九陰真經。\n",
					me->name(1),
					capitalize(getuid(me))
				),me
			);
		me->set("quest/jiuyin1/owner", 1);
		ob->move(me);
		ob =  present("xia juan", me);
		destruct(ob);
		ob =  present("shang juan", me);
		destruct(ob);
		return 1;
      }
      else
		return notify_fail("你需要上、下卷才能互相對照、參考。\n");
}

int do_study(string arg)
{
      int cost, my_skill;
      object me=this_player();
      object where = environment(me);

      if (!arg) return notify_fail("你要讀什麼？\n");

      if(me->is_busy())
          return notify_fail("你現在正忙著呢。\n");

      if(where->query("sleep_room")|| where->query("no_fight"))
          return notify_fail("這裡你不能讀書。\n");

      if( me->is_fighting() )
          return notify_fail("你無法在戰鬥中專心下來研讀新知！\n");

      if(! me->query("quest/jiuyin1/pass"))
          return notify_fail("你從哪裡偷來的九陰真經，無法研讀。\n");

      if( this_object()->query("owner") != me->query("id"))
          return notify_fail("你從哪裡偷來的九陰真經，無法研讀。\n");

      if( !me->query_skill("literate", 1) )
          return notify_fail("你是個文盲，先學點文化(literate)吧。\n");

      if((int)me->query("potential") < 1 )
          return notify_fail("你的潛能已經用完了，再怎麼讀也沒用。\n");

      if((int)me->query("combat_exp") < 1000000 )
          return notify_fail("你的實戰經驗不足，再怎麼讀也沒用。\n");

      if( me->query_int() < 40 )
          return notify_fail("以你目前的領悟能力，還沒有辦法學這個技能。\n");

      cost = 40 * ( 1 + ( 35 - (int)me->query("int"))/20 );
      if (cost < 20) cost = 20;
      
      if( me->query("neili") < cost * 2 + 300)
          return notify_fail("你的內力不夠，無法領會這個技能。\n");

      me->set_temp("last_damage_from", "研讀高深武功，熬盡心機累");
      switch (arg) {
        case "jiuyin-zhengong":
          my_skill = me->query_skill("jiuyin-zhengong", 1);
          if( my_skill >= 200)
              return notify_fail("你覺得這經書上所寫的已經太淺了，不能學到什麼東西。\n");
          if( my_skill >= me->query_skill("daode-jing",1))
              return notify_fail("你道德經太淺，不能學到什麼東西。\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("也許是缺乏實戰經驗，你對經書上面所說的東西總是無法領會。\n");
          else
              write("你研讀著有關九陰真功的技巧，似乎有些心得。\n");
        //天賦“領悟大師”影響效果：  by spiderii@ty ..lsxk想法太過變態了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你經過轉世重修後，領悟到了武技萬變不離其宗的道理，瞬間領悟到了九陰真功的精華所在。\n"NOR);
            me->set_skill("jiuyin-zhengong",200);
            }
          me->improve_skill("jiuyin-zhengong", ((int)me->query_skill("literate", 1)/5 + 1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          if(me->query_skill("jiuyin-zhengong",1) < 200)
               me->add("potential", - random(2));
          break;             
        case "jiuyin-shenfa":
          my_skill = me->query_skill("jiuyin-shenfa", 1);
          if( my_skill >= 150)
              return notify_fail("你覺得這經書上所寫的已經太淺了，不能學到什麼東西。\n");
          if( my_skill >= me->query_skill("daode-jing",1))
              return notify_fail("你道德經太淺，不能學到什麼東西。\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("也許是缺乏實戰經驗，你對經書上面所說的東西總是無法領會。\n");
          else
              write("你研讀著有關九陰身法的技巧，似乎有些心得。\n");
        //天賦“領悟大師”影響效果：  by spiderii@ty ..lsxk想法太過變態了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你經過轉世重修後，領悟到了武技萬變不離其宗的道理，瞬間領悟到了九陰身法的精華所在。\n"NOR);
            me->set_skill("jiuyin-shenfa",150);
            }
          me->improve_skill("jiuyin-shenfa", ((int)me->query_skill("literate", 1)/5+1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          if(me->query_skill("jiuyin-shenfa",1) < 150)
               me->add("potential", - random(2));
          break;
        case "xuanyin-jian":
          my_skill = me->query_skill("xuanyin-jian", 1);
          if( my_skill >= 150)
              return notify_fail("你覺得這經書上所寫的已經太淺了，不能學到什麼東西。\n");
          if( my_skill >= me->query_skill("daode-jing",1))
              return notify_fail("你道德經太淺，不能學到什麼東西。\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("也許是缺乏實戰經驗，你對經書上面所說的東西總是無法領會。\n");
          else
              write("你研讀著有關玄陰劍法的技巧，似乎有些心得。\n");
        //天賦“領悟大師”影響效果：  by spiderii@ty ..lsxk想法太過變態了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你經過轉世重修後，領悟到了武技萬變不離其宗的道理，瞬間領悟到了玄陰劍法的精華所在。\n"NOR);
            me->set_skill("xuanyin-jian",150);
            }

          me->improve_skill("xuanyin-jian", ((int)me->query_skill("literate", 1)/5+1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          if(me->query_skill("xuanyin-jian",1) < 150)
               me->add("potential", - random(2));
          break;
         case "daode-jing":
              my_skill = me->query_skill("daode-jing", 1);
          write("你研讀著道德經，似乎有些心得。\n");
          me->improve_skill("daode-jing", ((int)me->query_skill("literate", 1)/5+5) );
          me->receive_damage("jing", cost );
          if(me->query_skill("daode-jing",1)>150)
               me->add("potential", - random(2));
          if(me->query_skill("daode-jing",1)>200)
               me->add("potential", - random(2));
          if(me->query_skill("daode-jing",1)>250)
               me->add("potential", - random(3));
          if(me->query_skill("daode-jing",1)>300)
               me->add("potential", - random(3));
          break;
      }
      return 1;
}

