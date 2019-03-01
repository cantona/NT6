// Written by Lonely@IsMUD.net (05/21/2009)

#include <ansi.h>
inherit BOSS;

void random_move();
void sp_attack();
void create()
{
        set_name( "金人", ({ "gold man", "gold", "man"}));
        set_color("$HIY$");
        set("long", @LONG
這是秦始皇完成統一大業之後，收繳天下兵器，熔化之後鑄成的一座金人，身高三丈，
重達千石，如同一座巍峨的山峰，聳立在你面前。秦始皇死後，這座金人就作為墓室
的守衛者，數千年來一直守衛著秦陵的內宮。它刀槍不入，力大無窮，觸動機關之後
在東方仙術的作用下赫然使出一套失傳已久的武技，古往今來不知有多少盜墓的好手
栽在它的手上。
LONG );
        set("title", HIY "九大護法" NOR);
        set("attitude", "aggressive");
        set("str", 120);
        set("con", 120);
        set("dex", 30);
        set("int", 30);

        set("max_qi", 50000000);
        set("max_jing", 2500000);
        set("neili", 25000000);
        set("max_neili", 25000000);
        set("max_jingli", 5000000);
        set("jiali", 200000);
        set("level", 180);
        set("combat_exp", 100000000000);
        /*
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        */
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: sp_attack :),
        }));

        set("death_msg", HIY "\n$N散落成一堆青銅。\n\n" NOR);

        set_skill("force", 4500);
        set_skill("zixia-shengong", 4500);
        set_skill("huashan-neigong", 4480);
        set_skill("dodge", 4500);
        set_skill("feiyan-huixiang", 4500);
        set_skill("huashan-shenfa", 4500);
        set_skill("parry", 4520);
        set_skill("sword", 4520);
        set_skill("lonely-sword", 4520);
        set_skill("blade", 4500);
        set_skill("fanliangyi-dao", 4500);
        set_skill("strike", 4480);
        set_skill("hunyuan-zhang", 4480);
        set_skill("cuff", 4480);
        set_skill("poyu-quan", 4480);
        set_skill("literate", 4480);
        set_skill("martial-cognize", 4420);

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "lonely-sword");
        map_skill("blade", "fanliangyi-dao");
        map_skill("sword", "lonely-sword");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        set("rewards", ([
                "exp" : 2000,
                "pot" : 500,
                "mar" : 50,
        ]));
/*
        set("drops", ([
                "RA&LEGEND60" : 100, 
                "RA&LEGEND70" : 50, 
        ]));
*/
        set_temp("apply/attack", 20000+random(10000));
        set_temp("apply/damage",20000+random(10000));
        set_temp("apply/unarmed_damage",20000+random(10000));
        set_temp("apply/armor", 20000+random(10000));
        set_temp("apply/add_weak", 60);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 33);
        set_temp("apply/add_busy", 40);

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        object me;

        ::init();
        if( !interactive(me = this_player()) ||
            this_object()->is_fighting())
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

void sp_attack()
{
        object *enemies, enemy;
        string msg;

        enemies = query_enemy();
        if( !enemies || sizeof(enemies) == 0 )
                return;
        enemy = enemies[random(sizeof(enemies))];
        switch( random(7) ){
                case 6: msg = HIY"$N猛地一跺腳，一道震波從地面傳來，$n頓受重創，撲通摔倒在地。\n"NOR;break;
                case 5: msg = HIY"$N突然向你撲來，死死地將你抱住，$n聽見自己全身的骨骼格格作響，似乎要在這一抱之下化為齏粉"NOR; break;
                case 4: msg = HIY"$N突然高高躍起，巨大的身軀遮天蔽日。你想要施展身法閃躲開來，無奈金人的體積實在太大，\n"
                                 "而墓室中的空間不大，閃躲的余地十分有限，只聽到一聲巨響，你的身軀被金人活活砸入地面\n"NOR; break;
                case 3: msg = HIY"$N雙手突然發出強烈的光芒，令$n睜不開眼，$n感到一陣具痛。片刻後光芒散去，$n赫然發現$N的手中多出一柄巨斧正在滴血，\n"
                                 "$n被$N使出一套失傳已久的古代斧法所傷！\n"NOR; break;
                case 2: msg = HIY"$N雙手突然發出強烈的光芒，令$n睜不開眼，$n感到一陣具痛。片刻後光芒散去，$n赫然發現$N的手中多出一柄巨劍正在滴血，\n"
                                 "$n被$N使出一套失傳已久的古代劍法所傷！\n"NOR; break;
                case 1: msg = HIY"$N雙手突然發出強烈的光芒，令$n睜不開眼，$n感到一陣具痛。片刻後光芒散去，$n赫然發現$N的手中多出一柄巨錘正在滴血，\n"
                                 "$n被$N使出一套失傳已久的古代錘法所傷！\n"NOR; break;
                default: msg = HIY"$N雙手突然發出強烈的光芒，令$n睜不開眼，$n感到一陣具痛。片刻後光芒散去，$n赫然發現$N的手中多出一柄巨刀正在滴血，\n"
                                 "$n被$N使出一套失傳已久的古代刀法所傷！\n"NOR; break;
        }
        message_vision(append_color(msg, HIY),this_object(),enemy);
        enemy->receive_damage("qi",10000+random(10000),this_object());
        COMBAT_D->report_status(enemy);
        if( !enemy->is_busy() )
                enemy->start_busy(2);
        return;
}

/*
varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}
*/

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;
        int reduce;

        damage = 5000 + random(5000);
        reduce=query_temp("apply/reduce_fire", ob);
        damage -= damage * reduce / 100;
        if( damage < 0 ) damage = 0;
        ob->receive_damage("qi", damage, me);
        ob->receive_wound("qi", damage, me);
        set("neili",query("max_neili",  me), me);
        return HIY "$N" HIY "全身閃出耀眼的金光，登時令$n"
               HIY "全身有若刀絞。\n" NOR;
}

int random_move()
{
        mapping exits;
        string *dirs, direction, to_go_place, my_birth_place;
        object env;
        string userid,mazeobj;
        int x,y;

        if( !mapp(exits=query("exits", environment())))return 0;

        dirs = keys (exits);
        direction = dirs[random(sizeof(dirs))];
        env = environment(this_object());
        to_go_place=query("exits/"+direction, env);
        //my_birth_place = file_name(this_object());

        //ccommand("say "+to_go_place);
        if( sscanf(to_go_place,"/f/mausoleum/%s/%s/%d/%d",userid,mazeobj,x,y)!=4 )
                return 1;
        command("go " + direction);
        addn_temp("random_move", 1);
        return 1;
}

varargs void die(object killer)
{
        object *obs, env;
        object me, ob, mazeobj;
        int exp, pot, mar;
        int count, finished;
        string owner;
        int password;

        me = this_object();

        if( objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                me->full_self();
                return;
        }

        env = environment(me);
        if( !killer )
                killer = me->query_last_damage_from();

        if( objectp(killer) ) {
                mazeobj = FUBEN_D->query_maze_mainobj(killer);
                if( !query("quest/to_kill/"+name(), mazeobj) )
                        set("quest/to_kill/"+name(), 9, mazeobj);

                count=query("quest/to_kill/"+name(), mazeobj);
                finished=query("quest/killed/"+name(), mazeobj);
                finished++;
                if( finished > count )
                        finished = count;
                set("quest/killed/"+name(), finished, mazeobj);
                owner = FUBEN_D->query_fuben_owner(killer);
                password = 1+random(9);
                set("quest/password/"+finished, password, mazeobj);
                FUBEN_D->tell_fuben("mausoleum",owner,HIW"殺死 "+name()+": "+finished+"/"+count+"。\n密碼 "+password+"\n"NOR);

                /*
                obs = pointerp(killer->query_team()) ?
                                killer->query_team() : ({ killer });
                obs = filter_array(obs, (: environment($1) == $(env) :));

                exp=query("bonus", me);
                pot = exp / 2;
                mar = pot / 2;
                foreach( object user in obs )
                        GIFT_D->bonus(user, ([
                                "exp" : exp, "pot" : pot, "mar" : mar ]));
                */
        }

        return ::die(killer);
}

void unconcious()
{
        object ob;

        if( objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                this_object()->full_self();
                return;
        }

        die();
}
