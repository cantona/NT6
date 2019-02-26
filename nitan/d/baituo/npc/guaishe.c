//Cracked by Kafei
//lingshe 西域怪蛇
//sdong, 11/19/98

#include <ansi.h>
#include <room.h>

inherit SNAKE;

mapping default_dirs = ([
        "north":        "北",
        "south":        "南",
                  "east":         "東",
        "west":         "西",
        "northup":      "北邊",
                  "southup":      "南邊",
        "eastup":       "東邊",
                  "westup":       "西邊",
        "northdown":    "北邊",
        "southdown":    "南邊",
        "eastdown":     "東邊",
        "westdown":     "西邊",
                  "northeast":    "東北",
                  "northwest":    "西北",
                  "southeast":    "東南",
                  "southwest":    "西南",
                  "up":           "上",
                  "down":         "下",
                  "out":          "外",
                  "enter":        "裏",
]);

void set_owner(object owner);
int do_drive(string arg);
int do_yao(string arg);
int do_stop(string arg);
int random_walk();
void auto_check();
int auto_perform();
void killer_show(object me);
private int is_suitable(object victim, object killer);
void action(object me, object ob);
void setup_skill(object me,object obj);
string long_desc();

void create()
{
        int max,max1;

                  set_name(HIW"怪蛇"NOR, ({ "guai she", "she", "snake" }) );
                  set("unit", "條");
                  set("age", 29);
                  set("long", (: long_desc :));
                  set("attitude", "peaceful");

                  set("auto_follow",0);
                  set("wildness", 90);

                  set("str", 30);
                  set("cor", 30);
                  set("dex", 45);

                  set("combat_exp", 100000);

                  set_temp("apply/attack", 65);
                  set_temp("apply/damage", 56);
                  set_temp("apply/armor", 150);

                        set_skill("dodge", 10);
                        set_skill("parry", 10);
                        set_skill("force", 10);

                  setup();

          set("chat_chance_combat", 50);
          set("chat_msg_combat", ({
                 (: auto_perform :),
          }));

          set("chat_chance", 3);
          set("chat_msg",({
                 (: auto_check :),
          }));
}

string long_desc()
{
                  string desc ;
                  object snake = this_object();

                  desc = HIW"一條全身銀鱗的小蛇，是西域歐陽峯用幾十種最毒的蛇雜交培育出來的，奇毒無比，它正伸出血紅的毒舌盯住你。\n"NOR;

                  if( query("food", snake)<50 )
                         desc += RED"它看起來胃癟癟的，恐怕餓得正慌。\n"NOR;
                  else if( query("food", snake)<100 )
                         desc += "它看起來不是很有精神，恐怕有點餓。\n";
                  else if( query("food", snake)<150 )
                         desc += "它看起來滿活潑的，看來是半飽了。\n";
                  else if( query("food", snake)<200 )
                         desc += "它看起來胃鼓鼓的，看來是快飽了。\n";
                  else
                         desc += HIY"它看起來胃鼓鼓的，似乎吃的太飽撐得簡直快要爆炸了。\n"NOR;

                  return desc;
}

void auto_check()
{
        object me = this_object();
        object here;
        if( !me )return;
        here = environment(me);
        if(!here) return;

        if( !is_busy() && strsrch(base_name(here), "/d/") != -1   )
        {

          if( random(10)==1 )
                        random_walk();
          else if( random(5)==1 )
          {
                                remove_call_out("killer_show");
                                call_out( "killer_show",3+random(15),me );
          }
        }

        remove_call_out("auto_check");
        call_out("auto_check",3);
        return;
}


void init()
{
                  object ob,me = this_object();

                  if( query("id", me) != "guaishe" )
                        me = present( "guai she",environment(this_player()) ) ;

                  add_action("convert","bian");
                  add_action("do_drive","gan");
                  add_action("do_yao","attack");
                  add_action("do_stop","stop");

/*
                  if( interactive(ob = this_player()) &&
                                query("family/family_name", ob) != "歐陽世家" && 
                                random(ob->query_kar() + ob->query_per()) < 30 &&
                                query("combat_exp", ob)>query("combat_exp", me)*9/10 )
                  {
                                remove_call_out("kill_ob");
                                call_out("kill_ob", 1, ob);
                  }
*/

        remove_call_out("auto_check");
        call_out("auto_check",3);
}

void set_owner(object owner)
{
        int max, max1;
        object me = this_object();
        if(!owner)return;
        set("owner",query("id", owner));
        set("combat_exp",query("combat_exp", owner));
        set("max_qi",query("max_qi", owner)*3);
        set("qi",query("max_qi", owner)*3);
        set("eff_qi",query("max_qi", owner)*3);
        set("max_jingli",query("max_jingli", owner));
        set("jingli",query("max_jingli", owner));
        set("eff_jingli",query("eff_jingli", owner));
        set("eff_jing",query("eff_jing", owner));
        set("jing",query("jing", owner));
        set("max_jing",query("max_jing", owner));
        set("max_neili",query("max_neili", owner));
        set("neili",query("max_neili", owner));

        max = pow( query("combat_exp")*10.0,0.33333);
        max1 = (int)max;
        set_skill("dodge", max1);
        set_skill("parry", max1 );
        set_skill("force", max1);
        set_skill("claw", max1);
        set_skill("force", max);
        set_skill("hamagong", max);
        map_skill("force", "hamagong");

        if( query("combat_exp", owner)<4000 )
        {
                  set_temp("apply/attack", 35);
                  set_temp("apply/damage", 15);
                  set_temp("apply/armor", 100);
        }
        else if( query("combat_exp", owner)<30000 )
        {
                  set_temp("apply/attack", 45);
                  set_temp("apply/damage", 26);
                  set_temp("apply/armor", 100);
        }
        else if( query("combat_exp", owner)<60000 )
        {
                  set_temp("apply/attack", 45);
                  set_temp("apply/damage", 36);
                  set_temp("apply/armor", 120);
        }
        else if( query("combat_exp", owner)<300000 )
        {
                  set_temp("apply/attack", 55);
                  set_temp("apply/damage", 46);
                  set_temp("apply/armor", 130);
        }
        else
        {
                  set_temp("apply/attack", 65);
                  set_temp("apply/damage", 55);
                  set_temp("apply/armor", 150);
        }
}


void do_leave(object ob)
{
                if( objectp(ob) )
                {
                        if( ob->is_busy() || ob->is_fighting())
                        {
                                message_vision("$N向後一跳，跳出戰圈！\n",ob);
                                if(present("guai she",environment(ob)))
                                  message_vision("$N説道：沒想到老毒物的寶貝玩意還真有兩下子。"+RANK_D->query_self(ob)+"改日再來奉陪！\n",ob);
                                else message_vision("$N説道：哈蛤，老毒物的寶貝玩意到底不是"+RANK_D->query_self(ob)+"的對手！\n",ob);
                        }
                        if(!living(ob))ob->revive(0);
                        message_vision("$N急急忙忙離開了。\n",ob);
                        destruct(ob);
                }
}

void action(object me, object ob)
{
        object owner, here = environment(me);
        if( !me || !ob || !present(query("id", ob),here) )
        {
                do_leave(ob);
                return;
        }

        if( me->is_busy() || ob->is_busy() || ob->is_fighting() || me->is_fighting() || !living(me) || !living(ob) )
        {
                 call_out("action",random(10),me,ob);
                 return;
        }

        if( random(8) == 0 )
        {
                message_vision("\n$N"+HIR"突然一口向$n咬去!\n"NOR, me,ob);
                me->kill_ob(ob);
        }
        else if( query("owner", random(6) != 0 && (owner=present(me),here)) )
        {

                message_vision(HIR"\n$N"+HIR"喝道：老毒物的弟子驅蛇傷人無數，今天"+RANK_D->query_self(ob)+"特來送你們上西天！\n"NOR, ob);
                ob->kill_ob(me);
                ob->kill_ob(owner);
        }
        else if( random(2)==0 )
        {
                message_vision(HIR"\n$N"+HIR"突然向$n"+HIR"發動進攻!\n"NOR, ob,me);
                ob->kill_ob(me);
        }
        else
        {
                message_vision(HIR"\n$N"+HIR"喝道：老毒物的怪蛇害人無數，今天"+RANK_D->query_self(ob)+"誓為民除害！\n"NOR, ob);
                ob->kill_ob(me);
        }

        call_out("action",random(10),me,ob);
}

private int is_suitable(object victim, object killer)
{
                  string *no_kill_list = ({
                                         "mu ren",
                                         "huang zhen",
                                         "juexin dashi",
                                         "fighter dummy",
                                         "du e",
                                         "du nan",
                                         "du jie",
                                         "xie yanke",
                                         "ren woxing",
                                         "yue buqun",
                                         "qiu chuji",
                                         "gao lao",
                                         "ai lao",
                                         "kurong dashi",
                                         "hong qigong",
                                         "zhang sanfeng",
                                         "zuo lengchan",
                                         "ouyang zhan",
                                        "duan jin",
                                        "shaolin sengren",
                                         "seng bing",
                                         "huang yaoshi",
                                         "yideng dashi",
                                         "ma guangzuo",
                                         "black gargoyle",
                                         "white gargoyle",
                                         "da shou",
                                         "tang nan",
                                         "lao chaofeng",
                  });

                  if(  !clonep(victim) || userp(victim)
                         || query("race", victim) != "人類"
                         || query("shen", victim)<0
                         || query("winner", victim )
                        || strsrch(base_name(victim), "/kungfu/skill/") != -1
                        || strsrch(base_name(victim), "/kungfu/class/huashan") != -1
                        || strsrch(base_name(victim), "/clone/") != -1
                        || strsrch(base_name(victim), "/u/") != -1
                        || strsrch(base_name(victim), "/d/xiakedao/") != -1
                        || strsrch(base_name(victim), "/d/city/") != -1
                        || strsrch(base_name(victim), "/d/bwdh/") != -1
                         || query("combat_exp", victim)<query("combat_exp", killer)/15
                         || query("combat_exp", victim)>query("combat_exp", killer)*7/3
                         || member_array(query("id", victim),no_kill_list) != -1 || random(2) == 0 )
                  {
                                         return 0;
                  }
                  return 1;
}

void setup_skill(object me,object obj)
{
        mapping skills;
        string *names;
        int level,i;

        if(!objectp(me) || !objectp(obj) )return;

        if( query("combat_exp", obj)<query("combat_exp", me) )
        {
                set("combat_exp",query("combat_exp",  me)/100*(100+random(60)), obj);
        }

        level=to_int(pow(to_float(query("combat_exp", obj)/100),1/3))*10;
        if(level < 10) level = 10;

        if( query("combat_exp", obj)<4000 )
        {
                level = level/2 + random(level/2);
        }
        else if( query("combat_exp", obj)<30000 )
        {
                level = level/2 + random(level/3);
        }
        else if( query("combat_exp", obj)<60000 )
        {
                level = level/2 + random(level/3);
        }
        else if( query("combat_exp", obj)<300000 )
        {
                level = level/2 + random(level/4);
        }
        else
                level = level/2 + random(level/5);

        skills = obj->query_skills();
        if (mapp(skills))
        {
                names = keys(skills);

                for (i=0; i<sizeof(names); i++)
                {
                    if ( names[i] != "literate" )
                        obj->set_skill(names[i], level);
                    else
                        obj->delete_skill( "literate" );
                }
        }

        call_out("do_leave",60+random(60),obj);
}

void killer_show(object me)
{
  object ob,here;
  object *target_list;
  int i;

  if( !me ) return;
  here = environment(me);

  if(!here)return;
  if( strsrch(base_name(here), "/d/") == -1 ) return;

  if ( query("food") >= 200  )return;

  if( me->is_fighting() ) return;

  target_list = filter_array(livings(), "is_suitable", this_object(), me);
  if( sizeof(target_list) == 0 ) {
                  // try again in 5 secs.
                 call_out("killer_show", 5, me);
                 return;
  }

  do
  {
          i = random(sizeof(target_list));
     if(present(base_name(target_list[i]) + ".c",environment(this_object())))continue;
          ob=new( base_name(target_list[i]) + ".c" );
  }
  while( !objectp(ob) );

  ob->move(here);
  setup_skill(me,ob);
  message_vision("\n$N快步走了過來!\n", ob);

  call_out("action",random(10),me,ob);

  if( random(3) == 1)
  {
          remove_call_out("killer_show");
          call_out( "killer_show",30+random(15),me );
  }
}



int do_drive(string arg)
{
        object env, obj, ob, me = this_player();
        string target_dir, dir, dest, victim;
        mapping exit;

        if (!arg) return notify_fail("你要驅趕什麼？\n");

        if( sscanf(arg, "%s %s", victim, dir) != 2 ) return notify_fail("指令錯誤！\n");


        if( victim == query("id", me))return notify_fail("何必多此一舉？\n");

        if ( victim != "snake" && victim != "guai she" && victim != "she" ) return notify_fail("你要驅趕什麼？\n");

        ob = present(victim, environment(me));

        if (!ob) return notify_fail("這裏並無此人！\n");
        if (!living(ob)) return notify_fail("這不是活物！\n");


        env = environment(me);
        if( !mapp(exit=query("exits", env)) || undefinedp(exit[dir]) )
                return notify_fail("無此方向可去！\n");

        dest = exit[dir];

        if( !(obj = find_object(dest)) )
                                         call_other(dest, "???");
                  if( !(obj = find_object(dest)) )
                                         return notify_fail("無法走！\n");
        if( !wizardp(ob) && query("short", obj) == "巫師休息室" )
                return notify_fail("無法走！\n");

        if( !undefinedp(default_dirs[dir]) )
                                         target_dir = default_dirs[dir];
                  else
                                         target_dir = dir;

        if ( present("shezhang",me) || present("guai shezhang",me))
                message_vision(HIR "$N用蛇杖驅趕$n朝"+target_dir+"走去。\n" NOR, me, ob);
        else
                message_vision( "$N用手勢驅趕$n朝"+target_dir+"走去。\n" , me, ob);


        if( query("owner", ob) != query("id", me) )
        {
                message_vision( "可是$N理都不理。\n" NOR, ob);
                return 1;
        }

        if( random(20) != 0)
        {
                message("vision", HIR "只見"+ob->name()+"乖乖的向"+target_dir+"游過去。\n" NOR, environment(ob), ({ob}));

                if( ob->move(obj) ) {
                        message( "vision", HIR "只見"+ob->name()+"遊了過來。\n" NOR, environment(ob), ({ob}));
                        return 1;
                }
        }
        else
                message_vision( "可是$N理都不理。\n" NOR, ob);

        return 1;
}

int do_yao(string arg)
{
        object env, obj, ob, me = this_player(),snake;
        string target_dir, dir, dest, victim;
        mapping exit;

        if (!arg) return notify_fail("你要驅趕什麼？\n");

        victim = arg;

        if( victim == query("id", me))return notify_fail("怪蛇疑惑地看着你。\n");

        ob = present(victim, environment(me));
        snake = present("guai she",environment(me));

        if (!ob) return notify_fail("這裏並無此人！\n");



        if ( present("shezhang",me) || present("guai shezhang",me))
                message_vision(HIR "$N用蛇杖驅趕蛇朝$n咬去。\n" NOR, me, ob);
        else
                message_vision( "$N用手指了指蛇，又朝$n指去。\n" , me, ob);

//        if (!living(ob)) return notify_fail("這不是活物！\n");



        if( query("owner") != query("id", me) || query("race", ob) != "人類" || query("id", ob) == "guaishe" )
        {
                message_vision( "可是$N理都不理。\n" NOR, snake );
                return 1;
        }

        if ( query("food") >= 200  )
        {
                message_vision( "可是$N吃得太飽了，理都不理。\n" NOR, snake );
                return 1;
        }

        if( query("combat_exp", ob)<query("combat_exp", me)*4/5 )
                return notify_fail("怪蛇只對武功高手感興趣！\n");



        if( random(20) != 0)
        {
                message_vision( HIR "只見$N"+HIW"閃電般的向$n撲擊過去。\n" NOR, snake, ob );
                snake->kill_ob(ob);
                if(random(4)!=0 && living(ob) )
                {
                        message_vision( HIR "$N對着$n"+HIR"冷笑一聲："+RANK_D->query_rude(me)+HIR"居然敢縱蛇傷我，看招！\n" NOR, ob,me );
                        ob->kill_ob(me);
                }
        }
        else
                message_vision( "可是$N理都不理。\n" NOR, snake);

        return 1;
}

int do_stop(string arg)
{
        object env, obj, ob, me = this_player();
        string target_dir, dir, dest, victim;
        mapping exit;

        if (!arg) return notify_fail("你要驅趕什麼？\n");

        victim = arg;


        ob = present(victim, environment(me));

        if (!ob) return notify_fail("這裏並無此物！\n");

        if ( present("shezhang",me) || present("guai shezhang",me))
                message_vision(HIR "$N用蛇杖示意$n停下來。\n" NOR, me,ob);
        else
                message_vision( "$N用手指示意$n停下來。\n" , me, ob);

        if( query("owner", ob) != query("id", me) )
        {
                message_vision( "可是$N理都不理。\n" NOR, ob);
                return 1;
        }


        if( random(20) != 0)
        {
                message("vision", HIR "只見$N乖乖地縮回來，不咬了。\n" NOR, ob );
                ob->remove_all_killer();
        }
        else
                message_vision( "可是$N理都不理。\n" NOR, ob);

        return 1;
}

int convert(string arg)
{
        object me = this_player();
        object target;
        object ob,snake = present("guai she",environment(me));

        if (arg != "guai she" && arg != "she" && arg != "snake" || !snake ) return 0;
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不能化蛇為杖。\n");

        if( !(ob=present("guai shezhang",me)) ) return notify_fail("蛇杖在哪兒？\n");

        if( query("jingli", me)<50)return notify_fail("你的精力不足。\n");

        message_vision("$N左手持怪蛇杖伸到$n面前，右手對着$n做着奇怪的手勢，口中唸唸有詞。\n",
                me,snake);

        addn("jingli", -20, me);

        if( query("food", snake)<200 )
                return notify_fail("怪蛇還沒餵飽，不肯進蛇杖。\n");

        if( query("snake", ob) >= 2)return notify_fail("蛇杖上已有兩條蛇了，怪蛇擠不上去！\n");

        message_vision("$N"+HIW"看了看$n，突然似箭一般躍起，準確地落在蛇杖上，盤了起來。\n"NOR,
                snake,me);
        if( query("bt/job", me) != 0){
                if( (query("bt/exp", me)+query("bt/pot", me)+query("bt/lvl", me)) != 0 )
                delete("bt", me);
        }
        addn("poison_applied", me->query_skill("poison",1)/2, ob);
        addn("snake", 1, ob);

        target = snake->select_opponent();
        if(target)do_leave(target);
        destruct(snake);

        return 1;
}

int random_walk()
{
                  mapping exits, doors;
                  string *dirs, dir, last_room, this_room;
                  object there,here = environment(),snake=this_object();
                  object env, ob, me = this_player();
                  string dest, victim;
                  mapping exit;


                  if( !objectp(here) || !mapp(exits=query("exits", here)) )
                  {
                                if(snake)
                                {
                                        if(!living(snake))snake->revive(0);
                                                message_vision("$N在地上找了一個縫鑽了進去，不見了。\n",snake);
                                                destruct(snake);
                                }
                                return 0;
                  }

                  //if( is_fighting() || is_busy() || query("jingli") < query("max_jingli") / 2 )return 0;

                  dirs = keys(exits);

                  if( mapp(doors = here->query_doors()) ) {
                                         dirs += keys(doors);
                  }

                  if( sizeof(dirs) == 0 )
                  {
                                if(snake)
                                {
                                        if(!living(snake))snake->revive(0);
                                                message_vision("$N在地上找了一個縫鑽了進去，不見了。\n",snake);
                                                destruct(snake);
                                }
                                return 0;
                  }

                  dir = dirs[random(sizeof(dirs))];
                  if( stringp(last_room = query_temp("last_room"))
                  &&  sizeof(dirs) > 1 && exits[dir] == last_room ) {
                                         dirs -= ({dir});
                                         dir = dirs[random(sizeof(dirs))];
                  }

                  if( mapp(doors) && !undefinedp(doors[dir])
                  && (doors[dir]["status"] & DOOR_CLOSED) )
                  {
                        return 0;
                  }


        if( !mapp(exit=query("exits", here)) || undefinedp(exit[dir]) )
                return notify_fail("無此方向可去！\n");


                  there = find_object( exit[dir] );
                  if( there )
                        {
                                message_vision("$N蜿蜒地向"+default_dirs[dir]+"遊了過去。\n",snake);
                                this_object()->move(there);
                                message_vision("$N蜿蜒地遊了過來。\n",snake);
                                all_inventory(here)->follow_me(this_object(), dir);
                        }
                  else return 0;

                  set_temp("last_room", this_room);

                  return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object owner;
        object here = environment(me);
        int exp, pot, lvl;

        if ( query("food") >= 200  )
        {
                return random_walk();
        }


        if( (owner=present(query("owner", me),here)) )
        {

                exp = 4 + random(6 );
                if( query("combat_exp", me)>6400000)exp=exp/2;
                pot = 2 + random(4);
                if( query("combat_exp", me)>6400000)pot=pot/2;
                lvl = 3 + random(4);
                owner->improve_skill("training", lvl);
                addn("combat_exp", exp, owner);
                addn("potential", pot, owner);
                addn("bt/lvl", lvl, owner);
                addn("bt/exp", exp, owner);
                addn("bt/pot", pot, owner);
                if( query("potential", owner)>owner->query_potential_limit() )
                        set("potential", owner->query_potential_limit(), owner);
                addn("food", random(10), me);
                victim->receive_damage("qi",1,owner);
        }

        victim->affect_by("bt_poison",
                ([ "level" : 300,
                   "id":query("id", me),
                   "duration" : 20 ]));
}

void die()
{
                  object corpse, ling;
                  mixed killer;

                  remove_call_out("checking");

                  if( !living(this_object()) ) revive(1);
                  COMBAT_D->announce(this_object(), "dead");

                  if( objectp(killer = query_temp("last_damage_from"))){
                                         set_temp("my_killer",query("id", killer));
                                         COMBAT_D->killer_reward(killer, this_object());
                                         if( !userp(killer) )
                                                call_out( "do_leave",1 , killer );
                  }

                  ::die();
}

int auto_perform()
{
        object me = this_object();
        object target = me->select_opponent();
        object owner;
        object here = environment(me);
        int damage,bonus;
        int exp, pot, lvl;
    int zero_exp=query("combat_exp", target);
    if ( zero_exp < 1 ) zero_exp = 1;

        if ( !objectp(target)
           || !random(query("combat_exp", me)*2
                       /query("combat_exp", target)+1))return 0;

        if( query("neili", me)<100)return 0;

        if ( query("food") >= 200  )
        {
                return random_walk();
        }

        message_vision("\n$N"+HIW"突然閃電般地躍起，象一條白箭似的射向$n"+HIW"的咽喉。\n"NOR,me,target);

        if( random(query("combat_exp", me))>random(query("combat_exp", target)) || !living(target) )
        {
                        message_vision(HIR"結果$N"+HIR"一口咬住$n"+HIR"的咽喉，猛猛地吸起血來。\n\n"NOR,me,target);
                        damage=random(me->query_skill("force")+me->query_skill("hamagong")+query("jiali", me))*(1+random(3));
                        if(damage > 1000) damage = 1000;
                        if(damage < 100) damage = 100;

                        target->affect_by("bt_poison",
                                ([ "level" : 300,
                                      "id":query("id", me),
                                      "duration" : 20 ]));

                        target->receive_damage("qi", damage,  me);
                        target->receive_wound("qi", random(damage), me);
                        target->start_busy(1+random(2));
                        me->start_busy(2+random(2));
                        addn("neili", -damage/2, me);

                        bonus = damage/20 + random(damage/20);
                        if(bonus > 30) bonus = 30;

                        addn("food", bonus+random(bonus), me);

                        if( (owner=present(query("owner", me),here)) )
                        {
                                exp = bonus + random(bonus);
                                pot = bonus;
                                lvl = 3 + random(7);
                                owner->improve_skill("training", lvl);
                                addn("combat_exp", exp, owner);
                                addn("potential", pot, owner);
                                addn("bt/lvl", lvl, owner);
                                addn("bt/exp", exp, owner);
                                addn("bt/pot", pot, owner);
                                if( query("potential", owner)>owner->query_potential_limit() )
                                        set("potential", owner->query_potential_limit(), owner);
                        }
                        addn("combat_exp", bonus + random(bonus) );
                        addn("potential",bonus );

                        COMBAT_D->report_status(target);
        }
        else
                message_vision(HIG"$N"+HIG"慌忙一閃身，正好躲過$n"+HIG"這一攻擊，不過也被嚇得全身流汗，要知道這怪蛇奇毒無比，咬中了就九死一生。\n"NOR,target,me);

        return 1;
}


