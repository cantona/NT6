//                標準描述長度示例                                   |
// 幻境內人物  其他型
// 包括 教授技能、恢復體力、尋求寶物（有獎勵）
// by naihe  2002-10-29  於茂名

#include <ansi.h>

inherit NPC;

#include "hj_settings/room_amount_hj.h"

string *colors=({
    ""HIR"",
    ""HIY"",
    ""HIG"",
    ""HIC"",
    ""HIW"",
    ""HIM"",
});
// 不要 HIB 顏色的精靈 ：）


int *move_time = ({ 5, 10, 2, 3 });
int *job_times = ({ 5, 10, 10, 3 });


int ask_find();

string me_find_name = "找東西";


void setme( int iii )
{
    string cl = colors[ random( sizeof(colors) ) ];

    if( iii == 99 ) iii = random(4);
    set("iii", iii ); // 此處 iii 為類型標記。

    set_name( cl+"小精靈"NOR, ({"jing ling", "jl", "ling" }) );
    set("msg",cl+"一陣幽香傳來，只見旁邊輕悠悠地飛過來一個小精靈。\n"NOR);

    set("job_times", job_times[ iii ] );

    set("long","這是一個常見於山野的小精靈，只有正常人的手掌大小，模樣甚是可愛。\n");
    set("hj_game/npc","other");

    set("gender","女性");
    set("age",12+random(12));
    set("per",20+random(5));

    set("inquiry",([
        me_find_name : (: ask_find :),
        ]));

    set("no_refresh",1);

    remove_call_out("delete_me");
    remove_call_out("random_move");
    remove_call_out("random_teach");
    remove_call_out("random_heal");
    remove_call_out("random_drop");
    remove_call_out("random_find");

    call_out("do_all_start", 3);
}

void create()
{
    setme( 99 );
    setup();
}

void do_all_start()
{
    if( !environment(this_object()) ) return;

    call_out("delete_me", 240 + random( 60 ) );
    call_out("random_move", 1);

    switch( query("iii") )
    {
        case 0: call_out("random_teach",1); break;
        case 1: call_out("random_heal",1); break;
        case 2: call_out("random_drop",1); break;
        case 3: call_out("random_find",1); break;
    }
}


void delete_me()
{
    message_vision("$N左望望，右望望，忽地就不知飛向何處去了。\n",this_object());
    destruct(this_object());
}

int random_move()
{
    string *dirs=({
"east","west","south","north","northeast","northwest","southeast","southwest"
        });

    if(random(3) == 1 && living(this_object()))
        command(dirs[random(sizeof(dirs))]);

    remove_call_out("random_move");
    call_out("random_move", move_time[ query("iii") ] );
    return 1;
}

void random_teach()
{
    object *inv,target,ob=this_object();
    int i;
    string *skills_ids;
    string *skills_names;

    if( query("job_times") < 1 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",10);
        return;
    }

    if(random(2) == 1)
    {
        inv = all_inventory(environment(ob));
        if(inv && sizeof(inv) > 0)
        {
            target = inv[random(sizeof(inv))];
            if(target->is_character() &&
                   query_temp("huanjing", target) == "start" && 
               living(target) && random(2) == 1)
            {

// 下面開始教這個玩家這項技能 :)

    skills_ids=({"hfzj","hyzj","llzj","ydzj","gszj","fhzj","dhzj","heal"});
    skills_names=({"呼風之技","喚雨之技","落雷之技",
    "引電之技","滾石之技","飛火之技","奪魂之技","恢復之技"});
    i=random(sizeof(skills_ids));

    if( !query_temp("hj_game_skills/"+skills_ids[i], target) )
    {
        command("whisper"+query("id", target)+"我來教你如何運用「"+skills_names[i]+"」的竅門吧！");
        command("whisper"+query("id", target)+"這樣這樣，那樣那樣，明白了嗎？");
        command("smile"+query("id", target));
        addn("job_times", -1, ob);
        set_temp("hj_game_skills/"+skills_ids[i], skills_names[i], target);
        set_temp("hj_game_damages/"+skills_ids[i], 3+random(3), target);
        message_vision(CYN"$N"NOR+CYN"只覺得突然之間靈感驟至，已領悟了「"+skills_names[i]+"」！\n"NOR,target);
    }
    else
    {
        command("whisper"+query("id", target)+"我來教你如何加強「"+skills_names[i]+"」威力的竅門吧！");
        command("whisper"+query("id", target)+"這樣這樣，那樣那樣，明白了嗎？");
        command("pat"+query("id", target));
        addn("job_times", -1, ob);
        if( query_temp("hj_game_damages/"+skills_ids[i], target)<99 )
        {
        addn_temp("hj_game_damages/"+skills_ids[i], 2+random(2), target);
        message_vision(CYN"$N"NOR+CYN"仔細想着，似乎覺得自己「"+skills_names[i]+"」的修為又有所提升了。\n"NOR,target);
        if( query_temp("hj_game_damages/"+skills_ids[i], target)>99 )
            set_temp("hj_game_damages/"+skills_ids[i], 99, target);
        }
        else
        message_vision( CYN"$N"NOR+CYN"哈哈大笑道：“我早已得知其中關竅，不必費心了。”\n"NOR,target);
    }
            }
        }
    }

    if(random(3) == 1) message_vision(CYN"$N"NOR+CYN"四處望了望，「啦啦啦」地哼起了什麼歌兒來。\n"NOR,this_object());
    remove_call_out("random_teach");
    call_out("random_teach",10+random(11));
}


void random_heal()
{
    object *inv,target,ob=this_object();
    int hp,hp_max;

    if(query("job_times")<1)
    {
        remove_call_out("delete_me");
        call_out("delete_me",10);
        return;
    }

    inv = all_inventory(environment(ob));
    if(inv && sizeof(inv) > 0)
    {
        target = inv[random(sizeof(inv))];
        if(target->is_character() &&
               query_temp("huanjing", target) == "start" && 
           living(target) && query_temp("hj_hp", target)>0 && 
           query_temp("hj_hp_max", target)>0 )
        {

// 下面開始給這個玩家恢復氣息

    if( query_temp("hj_hp", target)<(query_temp("hj_hp_max", target)*8/10) )
    {
        hp=query_temp("hj_hp", target);
        hp_max=query_temp("hj_hp_max", target);

        command("idle2"+query("id", target));
        message_vision("$n"NOR+CYN"對着$N"NOR+CYN"輕輕地念了句什麼，只見$N"NOR+CYN"的臉色頓時大為好轉！\n"NOR,target, ob );
        addn("job_times", -1, ob);
        hp+=30+random(hp_max/10);
        if(hp>hp_max) hp = hp_max;
        set_temp("hj_hp", hp, target);
    }
        }
    }

    if( !random(3) )
        message_vision(CYN"$N"NOR+CYN"四處望了望，「嘻」地笑了一聲。\n"NOR, ob);
    remove_call_out("random_heal");
    call_out("random_heal",5+random(6));
}

void random_drop()
{
    object guo, ob = this_object();

    if(query("job_times")<1)
    {
        remove_call_out("delete_me");
        call_out("delete_me",10);
        return;
    }

    if(random(3) == 1)
    {
        guo = new(__DIR__"hj_obj_other");
        guo->setme(0);
        guo->move(environment(this_object()));
        message_vision(CYN"$N"NOR+CYN"身上忽地掉下一顆小果子！\n"NOR, ob );
        addn("job_times", -1, this_object());
    }

    if(random(3) == 1) message_vision(CYN"$N"NOR+CYN"輕輕地唱道：“採果兒，採果兒，勤勞懇作幹活兒。”\n"NOR, ob );
    remove_call_out("random_drop");
    call_out("random_drop",10+random(11) );
}

void random_find()
{
    int i;
    string *find_names;
    string *find_ids;
    object ob = this_object();

    if(query("job_times")<1)
    {
        remove_call_out("delete_me");
        call_out("delete_me",10);
        return;
    }

    if(!query("me_find_id") && random(5) == 1)
    {

find_names=({"定向水晶","飛翔之石","脱離水晶","迴歸之鏡","祈禱之石","召喚之盒",
"發呆之旗","驅逐之旗","尋人水晶","定位之儀",
"紅色寶石","藍色寶石","綠色寶石",
"呼風之石","喚雨之石","落雷之石","引電之石","滾石之石","飛火之石","奪魂之石","復活之石",
"青銅之劍","靈氣之劍","白銀之劍","盈動之劍","黃金之劍",
"耐力之劍","迅隱之劍","奪魂之劍","必勝之劍","狂風水晶",
"暴雨水晶","落雷水晶","引電水晶","滾石水晶","飛火水晶","奪魂水晶",
});

find_ids=({"dx shuijing","fx zhishi","tl shuijing","hg zhijing","qd zhishi","zh zhihe",
"fd zhiqi","qz zhiqi","xr shuijing","dw zhiyi",
"red baoshi","blue baoshi","green baoshi",
"hufeng shi","huanyu shi","luolei shi","yindian shi",
"gunshi shi","feihuo shi","duohun shi","fuhuo shi",
"qt jian","lq jian","by jian","yd jian","hj jian",
"nl jian","bj jian","dh jian","bs jian","kf sj",
"by sj","ll sj","yd sj","gs sj","fh sj","dh sj",
});

        i=random(sizeof(find_names));
        set("me_find_id",find_ids[i]);
        me_find_name = find_names[i];
        set("inquiry",([
            me_find_name : (: ask_find :),
            ]));
    }

    if(!query("me_find_id") && random(2) == 1)
message_vision(CYN"$N"NOR+CYN"輕輕地唱道：“我尋尋尋，我覓覓覓，怎麼卻不見我要找的東西？”\n"NOR, ob );

    else if(query("me_find_id") && random(2) == 1)
message_vision(CYN"$N"NOR+CYN"輕輕地唱道：“我尋尋尋，我覓覓覓，怎麼卻不見我要找的"+me_find_name+"？”\n"NOR, ob );

    remove_call_out("random_find");
    call_out("random_find",5+random(6));
}

int ask_find()
{
    object find,srl,me = this_player(), ob = this_object();

    if(!query("me_find_id") )
    {
        command("sing");
        return 1;
    }

    find=present(query("me_find_id"),me);
    if(!find)
    {
        command("say 我是要找它呀！如果有人能幫我找找，那該多好呀！");
        command("xixi");
        return 1;
    }
    if( !query("hj_game/obj", find) )
    {
        command("say 哎呀，你帶着的這個不是真的啦！我要找那個真的呀！");
        command("giggle");
        return 1;
    }

    message_vision(CYN"$N"NOR+CYN"拿出一"+query("unit", find)+query("name", find)+NOR+CYN"遞給$n"NOR+CYN"。\n"NOR,me,ob);
    destruct(find);
    command("wa"+query("id", me));
    command("touch");
    srl=new(__DIR__"shenren_ling");
    srl->waiting_delete( 120+random(60) );
    message_vision("$n"NOR+CYN"拿出一"+query("unit", srl)+query("name", srl)+NOR+CYN"遞給了$N"NOR+CYN"。\n"NOR,me,ob);
    srl->move(me);
    command("blush"+query("id", me));
    delete("me_find_id");

    remove_call_out("random_find");
    call_out("random_find",10);
    return 1;
}