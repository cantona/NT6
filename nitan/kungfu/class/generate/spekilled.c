// person used in quest

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

#define WAITING                  1
#define ATTACKING                2
#define OVER                     3
#define GO_CMD                   "/cmds/std/go"

void random_move();
int  leave();
int  is_stay_in_room()  { return 1; }
mapping fam_info;

int filter_listener(object ob)
{
        if( query("env/no_story", ob))return 0;
        return 1;
}

void create()
{
        ::create();
        set("gender", "男性");
        set("age", 30 + random(30));
        set("long", "");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("scale", 150);
        set("no_get", 1);

        set_temp("apply/armor", 100);
        set_temp("apply/damage", 100);
        set_temp("born_time", time());
        set_temp("dest_time", 1800 + time());

        add_money("gold", 30 + random(60));

        fam_info = query("fam_info");

        if (clonep()) keep_heart_beat();
}

void set_from_me(object me)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();

        if (my["max_qi"] > 10000)
                my["max_qi"] = 10000;

        if (my["max_jing"] < my["max_qi"] / 2)
                my["max_jing"] = my["max_qi"] / 2;

        if (my["max_jing"] > 6000)
                my["max_jing"] = 6000;

        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];

        exp=query("combat_exp", me)*11/10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);

        my["jiali"] = query_skill("force") / 2;

}

int accept_fight(object ob)
{
        command("say 我可沒興趣陪你玩，快給我滾開。");
        return 0;
}

int accept_hit(object ob)
{
        command("say 等我辦完正事再來收拾你！");
        return 0;
}

int accept_kill(object ob)
{
        object *t;
        object *our;
        object killer;

        if (! living(this_object()))
                return 1;

        fam_info = query("fam_info");

        // 檢查是否處於正在攻打狀態
        if ("/adm/daemons/story/familywar"->query_status() != ATTACKING)
        {
                if( query("family/family_name", ob) == fam_info["family"] )
                {
                      command("say 哼！我目前有要事要辦，等下再來取你性命。");
                      return notify_fail("看來，別人不屑與你交手。\n");
                }
                else 
                {
                      command("heng");
                      return notify_fail("看來，別人不屑與你交手。\n");
                }
        }
        else
        {       // 只接受組隊的玩家
                if (! pointerp(t = ob->query_team()) || ! sizeof(t) || sizeof(t) < 2)
                {
                      command("say 我從不和單槍匹馬的人交手。");
                      return notify_fail("看來，別人不屑與你交手。\n");
                }

                message_vision(HIW "$N" HIW "大聲叫道：“兄弟們，大家一起上啊，殺了$n" HIW "這" +
                               RANK_D->query_rude(this_object()) + "！”\n" NOR, ob, this_object());

                foreach(killer in t)
                {
                      if (objectp(killer) && 
                          living(killer) && ! killer->is_fighting(this_object()))
                               killer->kill_ob(this_object());

                }

                our = filter_array(all_inventory(environment()), (: objectp($1) &&
                                                                 ! wizardp($1) &&
                                                                 environment($1) &&
                                                                 query("team_num", $1) && 
                                                                 living($1) &&                  
                                                                 ! playerp($1) :));               
               killer = 0;
               foreach(killer in our)
               {
                      if (objectp(killer) && 
                          living(killer) && ! killer->is_fighting(ob))
                               killer->kill_ob(ob);
               }
        }

        return 1;
}

int accept_ansuan(object ob)
{
        return notify_fail("那人警惕性好高，你難以下手。\n");
}

int accept_touxi(object ob)
{
        return notify_fail("那人警惕性好高，你難以下手。\n");
}

void die(object killer)
{
        object dob;             // 打暈這個NPC的人
        int n;                  // 可以獎勵的人的數目
        int exp;                // 需要瓜分的經驗
        int pot;                // 需要瓜分的潛能
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的閲歷
        int gongxian;           //
        object *t;              // 殺死我的人的隊伍列表
        object tob;
        int i;

        // 找到殺了我(NPC)或是打暈我的人
        if (! objectp(dob = killer))
                dob = query_defeated_by();

        if (! pointerp(t = dob->query_team())) 
        {
                ::die();
                return;
        }

        if (! sizeof(t))
        {
                ::die();
                return;
        }

        if (objectp(dob))
        {
                exp = 5000 + random(5000);
                pot = 2000 + random(2000);
                weiwang = 3000 + random(6000);
                score = 3000 + random(6000);
                n = sizeof(t);
                if (! n || n < 4)
                {
                       exp /= 5;
                       pot /= 5;
                       weiwang /= 3;
                       score /= 3;
                }

                foreach(tob in t)
                {
                       if (objectp(tob) && living(tob))
                       {

                                if( query("family/family_name", tob) == fam_info["family"] )
                                          gongxian = 100 + random(300);
         
                                else 
                                          gongxian = 0;

                                GIFT_D->delay_bonus(tob,
                                         ([ "exp"      : exp + ((tob == dob) ? 2000 : 0),
                                            "pot"      : pot + ((tob == dob) ? 500 : 0),
                                            "weiwang"  : weiwang + ((tob == dob) ? 1000 : 0),
                                            "score"    : score + ((tob == dob) ? 1000 : 0),
                                            "gongxian" : (n < 4 ? gongxian / 3 : gongxian), 
                                            "prompt"  : (pointerp(t) ? "你的隊伍擊斃" + name() + "之後" :
                                                        "擊斃" + name() + "之後") ]));


                      }
              }

        }
        // 正常死亡
        ::die();

        return;
}

void random_move()
{
        string dir;
        string* route;
        object master;
        object *listeners;

        if (time() > query_temp("dest_time") ||
            "/adm/daemons/story/familywar"->query_status() == OVER)
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("聽説%s在攻打%s之後，從此銷聲匿跡，被江湖中人所遺忘。",
                                              name(), fam_info["family"]));
                log_file("static/killed_die", sprintf("%s %s(%s) vanished because timeout(%d:%d).\n",
                                                      log_time(), name(), query("id"),
                                                      time() - query_temp("born_time"),
                                                      query_temp("dest_time") - query_temp("born_time")));
                destruct(this_object());
                return;
        }

        if ("/adm/daemons/story/familywar"->query_status() == WAITING)
        {
                listeners = filter_array(users(), (: filter_listener :));

                if (query("is_leader") && random(3) == 0)
                         message_vision(HIW "$N" HIW "説道：“弟兄們，不要着急，等下咱們攻入" + 
                                        fam_info["family"] + "，大開殺戒~！”\n" NOR, this_object());
                else if (random(10) == 0)
                         message_vision(HIC "$N" HIC "嚷嚷道：“怎麼首領還不下令攻打" + 
                                        fam_info["family"] + "我都等得不耐煩了！”\n" NOR, this_object());                
   
                return;
        }
        fam_info = query("fam_info");
        route = fam_info["route_list"];

        // 已經走到終點
        if (query("move") >= sizeof(route))
        {

               if (base_name(environment()) == fam_info["tar_room_fi"])
               {
                      if (! this_object()->is_fighting())
                      {

                             CHANNEL_D->do_channel(this_object(), "rumor", 
                                        "聽説神祕組織攻到" + fam_info["family"] + "的" + fam_info["tar_room_nm"] + 
                                        "，" + fam_info["family"] + "自此元氣大傷。\n");

                             "/adm/daemons/story/familywar"->change_status(OVER);
                      }
               }

               return;
        }

        // 按照路由列表移動
        if (stringp(dir = route[query("move")]))
        {
              command("say 兄弟們衝啊，殺得他們落花流水，片甲不留！");
              if (GO_CMD->main(this_object(), dir))addn("move", 1);

              else if (stringp(fam_info["spe_cmds"]))
                           command(fam_info["spe_cmds"]);
              
              else return;
        }
}

void init()
{
        object me = this_player();

        fam_info = query("fam_info");

        if (! living(me) || 
            playerp(me) ||
            query("team_num", me) || 
            query("family/family_name", me) != fam_info["family"] )
                 return;

        if( !"/cmds/std/kill"->main(this_object(),query("id", me)) )
                 kill_ob(me);
}

