#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void random_move();
void do_swing();
void set_from_me(object me);
void create()
{
        string *names = ({ "青銅猛□" });

        ::create();
        set_name( names[random(sizeof(names))], ({ "mammoth bronze", "mammoth", "bronze" }));
        set("long", @LONG
這是一個沉睡在皇陵青銅機關獸。身高兩丈有余，四肢極為粗壯，長鼻子左右擺動，
嘴部長出一對彎曲的象牙，如同兩把彎刀，極為鋒利。在東方仙術的作用下，它的行
動雖然遲緩，但力大無窮，長長的象鼻伸縮靈活如意，再加上毛皮刀槍不入，象牙快
如刀刃，端的是極難對付。
LONG);
        set("title", HIR"機關獸" NOR);

        set("str", 150);
        set("con", 150);
        set("dex", 150);
        set("int", 150);
        set("max_qi", 2500000);
        set("max_jing", 1500000);
        set("neili", 2500000);
        set("max_neili", 2500000);
        set("max_jingli", 500000);
        set("attitude", "killer");
        set("auto_perfrom", 1);
        /*
        set("chat_chance", 30);
        set("chat_msg", ({
                (: random_move :)
        }) );
        */
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: do_swing :),
        }) );

        set("combat_exp", 100000000);
        set("death_msg",YEL"\n$N散落成一堆青銅。\n\n"NOR);

        set("rewards", ([
                "exp" : 500,
                "pot" : 120,
                "mar" : 20,
        ]));

        set_temp("apply/attack", 20000);
        set_temp("apply/parry", 20000);
        set_temp("apply/damage", 20000);
        set_temp("apply/unarmed_damage", 20000);
        set_temp("apply/armor", 20000);
        setup();
}

void init()
{
        object me;

        ::init();
        if( !interactive(me = this_player()) ||
            this_object()->is_fighting())
                return;

        set_from_me(me);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

void set_from_me(object me)
{
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        set("jiali", query_skill("force") / 2);
}

void do_swing()
{
        object *enemies,enemy;
        string msg;

        enemies = query_enemy();
        if( !enemies || sizeof(enemies)==0 )
                return;

        msg = BLU"$N口一張，口中已有七心海棠的藥粉,輕輕一吐，一陣無色無味的薄霧向對方飄去。\n"NOR;
        message_vision(msg,this_object());
        foreach( enemy in enemies ) {
                msg = HIY"$n一時大意，已經中了$N的暗算！\n"NOR;
                message_vision(msg,this_object(), enemy);
                enemy->affect_by("poison",
                                  ([ "level" : 1500,
                                     "id":query("id", this_object()),
                                     "name"  : "七心海棠毒",
                                     "duration" : 200 ]));
                tell_object(enemy, HIG "你中了青銅猛□的七心海棠毒。\n");
                enemy->receive_damage("qi",10000+random(10000),this_object());
                COMBAT_D->report_status(enemy);
                if( !enemy->is_busy() && random(2) )
                        enemy->start_busy(2);
        }
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
