// fighter 練功人

#include <ansi.h>

inherit NPC;

void create() { seteuid(getuid()); }

void setup()
{
        set_weight(1000000);
        set("not_living", 1);
        set("fight_times", 0);

        ::setup();

        set_temp("eff_status_msg", "它看起來還可以繼續用來練功。");
}

void unconcious()
{
        message_vision(HIY "□喇一聲，" + name() +
                       "壞了。\n\n" NOR, this_object());
        set("jing", 0);
        set("eff_jing", 0);
        set("qi", 0);
        set("eff_qi", 0);
        set("damaged", 1);
        set_temp("eff_status_msg", HIR " 它已經被打壞了。" NOR);
}

void die()
{
        message_vision(HIR "\n一陣希哩嘩啦的聲音過後，" + name() +
                       "算是徹底的報廢了。\n\n" NOR, this_object());
        destruct(this_object());
}

int accept_fight(object ob)
{
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        string *sname, *mname, *pname;
        int i, temp;
        int max_jing, max_qi, max_neili;
        int scale;
        object env;

        env = environment();
        if( stringp(query("for_family", env)) &&
            query("for_family", env) == query("family/family_name", ob) &&
            query("out_family", ob) )
                return notify_fail("你還是外出歷練吧，不能總呆在這裡。\n");

        if( query("combat_exp", ob) < 12000 )
                return notify_fail("你這點身手還不足以和" + name() + "練功。\n");

        if( is_fighting() )
                return notify_fail("這個" + name() + "正在和人練功呢。\n");

        if( query("damaged") )
                return notify_fail("這個" + name() + "已經被打壞了！\n");

        if( query("fight_times") >= 10 ) {
                unconcious();
                return notify_fail("這個" + name() + "已經被打壞了！\n");
        }

        if( objectp(query("last_fighter")) &&
            query("id", query("last_fighter")) != query("id", ob) )
                return notify_fail("這是" + query("fighter_name") +
                                   "的練功木人！\n");

        set("last_fighter", ob);
        set("fighter_name", ob->name());
        addn("fight_times", 1);
        set_temp("give_potential", 0);

        my = this_object()->query_entire_dbase();

        if( undefinedp(my["scale"]) )
                my["scale"] = 100;

        if( undefinedp(my["max_exp"]) )
                my["max_exp"] = 2000000;

        if( undefinedp(my["max_skill"]) )
                my["max_skill"] = 200;

/* delete and copy skills */

        if( mapp(skill_status = query_skills()) ) {
                skill_status = query_skills();
                sname  = keys(skill_status);

                temp = sizeof(skill_status);
                for (i = 0; i < temp; i++)
                        delete_skill(sname[i]);
        }

        if( mapp(skill_status = ob->query_skills()) ) {
                skill_status = ob->query_skills();
                sname  = keys(skill_status);

                for (i = 0; i < sizeof(skill_status); i++)
                {
                        int sk;

                        sk = skill_status[sname[i]];
                        if( sk > my["max_skill"] )
                                sk = my["max_skill"];
                        set_skill(sname[i], sk);
                }
        }

/* delete and copy skill maps */

        if( mapp(map_status = query_skill_map()) ) {
                mname = keys(map_status);

                temp = sizeof(map_status);
                for (i = 0; i < temp; i++)
                        map_skill(mname[i]);
        }

        if( mapp(map_status = ob->query_skill_map()) ) {
                mname  = keys(map_status);

                for (i = 0; i < sizeof(map_status); i++)
                        map_skill(mname[i], map_status[mname[i]]);
        }

/* delete and copy skill prepares */

        if( mapp(prepare_status = query_skill_prepare()) ) {
                pname  = keys(prepare_status);

                temp = sizeof(prepare_status);
                for (i = 0; i < temp; i++)
                        prepare_skill(pname[i]);
        }

        if( mapp(prepare_status = ob->query_skill_prepare()) ) {
                pname  = keys(prepare_status);

                for (i = 0; i < sizeof(prepare_status); i++)
                        prepare_skill(pname[i], prepare_status[pname[i]]);
        }

        hp_status = ob->query_entire_dbase();

        scale = my["scale"];

        my["str"] = hp_status["str"];
        my["int"] = hp_status["int"];
        my["con"] = hp_status["con"];
        my["dex"] = hp_status["dex"];

        max_jing = hp_status["max_jing"];
        if( max_jing > 7500 ) max_jing = 7500;
        max_qi = hp_status["max_qi"];
        if( max_qi > 1500 ) max_qi = 1500;
        max_neili = hp_status["max_neili"];
        if( max_neili > 1500 ) max_neili = 1500;

        my["max_qi"]     = max_qi    * scale / 100;
        my["eff_qi"]     = max_qi    * scale / 100;
        my["qi"]         = max_qi    * scale / 100;
        my["max_jing"]   = max_jing  * scale / 100;
        my["eff_jing"]   = max_jing  * scale / 100;
        my["jing"]       = max_jing  * scale / 100;
        my["max_neili"]  = max_neili * scale / 100;
        my["neili"]      = max_neili * scale / 100;
        my["jiali"]      = 0;
        my["combat_exp"] = hp_status["combat_exp"];

        if( !undefinedp(my["min_exp"]) &&
            my["combat_exp"] < my["min_exp"] )
                my["combat_exp"] = my["min_exp"];

        if( my["combat_exp"] > my["max_exp"] )
                my["combat_exp"] = my["max_exp"];

        reset_action();

        return 1;
}

int accept_hit(object ob)
{
        if( query("damaged") )
                return notify_fail("這個" + name() + "已經被打壞了！\n");

        if( query("combat_exp", ob) < 12000 )
                return notify_fail("你這點身手還不足以和" + name() + "練功。\n");

        return 1;
}

int accept_kill(object ob)
{
        object me;

        me = this_object();

        if( ob->is_busy() )
                return notify_fail("你現在正忙，沒有時間拆東西。\n");

        if( query("combat_exp", ob) < 12000 )
                return notify_fail("你這點身手還不足以拆掉" + name() + "。\n");

        if( !query("damaged") && query("combat_exp", ob) < query("combat_exp") ) {
                    message_vision("$N撲上去想拆掉$n，結果$n“蓬蓬”幾下"
                               "就把$N撩倒在地。\n", ob, me);
                    ob->start_busy(3);
                    write("這個練功的" + name() + "太強了，你拆不掉它。\n");
                return -1;
        }

        ob->start_busy(2);
        remove_call_out("destroy");
        call_out("destroy", 0, ob, me);

        write("上！\n");
        return -1;
}

int accept_ansuan(object ob)
{
        return notify_fail("一個" + name() + "有什麼好暗算的？\n");
}

// remove kill action
void kill_ob(object ob)
{
        fight_ob(ob);
}

void remove_enemy(object ob)
{
        ::remove_enemy(ob);
        if( ob == query("last_fighter") ) {
                remove_call_out("renewing");
                call_out("renewing", 30 + random(30), ob);
        }
}

void destroy(object ob, object me)
{
        if( !objectp(me) )
            return;

        message_vision("$N撲上去幾下子就把$n給拆了。\n", ob, me);
        destruct(me);
}

void renewing(object ob)
{
        if( !ob || !is_fighting(ob) ) {
                delete("last_fighter");
                delete("figher_name");
        }
}