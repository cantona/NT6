// for feng_npc.c yu_npc.c lei_npc.c dian_npc.c

string *songs3=({
    "親愛的朋友",
    "你可曾聽說過，在遠古的時候",
    "曾有過的古老國度的故事？",
    "那裡有著各樣的神奇的寶物",
    "也有著勤勞而善良的人們",
    "在我所在的地方，",
    me_guodu,
    baowu_name+"、"+baowu_other1+"和"+baowu_other2,
    "將能組成我們最為之著迷的",
    "國之靈物。",
    "我親愛的朋友",
    "如果你能尋得它們",
    "你也將能夠見到那往日的",
    "神秘國度的神秘之光。",
});

int ask_all();
int ask_baowu();

int singing=0;

void sing_song();
int i=0;

string *songs;
object baowu;

void wait_singsong();

string *gem_names=({
    "蠻野族寶物",
    "猛力族寶物",
    "矮妖族寶物",
    "山怪族寶物",
    "巨人族寶物",
});

string *gem_ids=({
    "manye baowu",
    "mengli baowu",
    "aiyao baowu",
    "shanguai baowu",
    "juren baowu",
});



#include "hj_settings/obj_list.h"
#include "hj_settings/room_amount_hj.h"



void create()
{
    set_name("臣民",({"chen min"}));
    set("long","這個人來自古老的"+me_guodu+"，竟不知是人是鬼是神是仙。\n");
    if(random(2) == 1) set("gender","男性");
    else set("gender","女性");
    set("title",me_guodu);
    set("age",20+random(100));
    set("per",18+random(5));
    set("attitude","friendly");
    set("no_refresh",1); // 不會被房間更新。
    set("inquiry",([
        "all": (: ask_all :),
        ask_arg : (: ask_baowu :),
        "寶物" : (:  ask_baowu :),
        ]));
    set("hj_game/npc", me_mark[0]);
    set("host_id","no");
    set("msg", HIW"只見一個人影漸漸清晰，終于憑空出現了一個陌生的人。\n"NOR);

        set("chat_chance", 1);
        set("chat_msg", ({ (: wait_singsong :) }));

    setup();

    remove_call_out("checking");
    remove_call_out("delete_me");
    call_out("checking", 1);
    call_out("delete_me",2400+random(600) ); // 降低遊戲難度，40 - 50分鐘內消失。
// 若七星燈內的設置 deng_time 為 300 的話，這裡需要恢復為 1800+random(600) 。

}

// 如果該NPC的隸屬玩家不存在或已退出遊戲，本NPC清除。
void checking()
{
    object my_host;

    if( !environment( this_object() ) ) return;

    my_host=find_player(query("host_id"));
    if( !my_host || !query_temp("huanjing", my_host) || 
       query_temp("huanjing", my_host) != "start" || 
       !query_temp("hj_hp", my_host) || !query_temp("hj_hp_max", my_host) || 
       query_temp("hj_find_ok", my_host) == "yes" )
    {
        remove_call_out("delete_me");
        call_out("delete_me",5);
    }

    else
    {
        remove_call_out("checking");
        call_out("checking",1);
    }
}

int ask_all()
{
    command("smile");
    command("say 我所知的如山之高，如海之深，你能聽得完麼？");
    return 1;
}

void wait_singsong()
{
    if( singing == 0 )
    {
        remove_call_out("sing_song");
        i=0;
        singing=1;
        if(random(3) == 1) songs=songs1;
        else if(random(3) == 1) songs=songs2;
        else songs=songs3;
        message_vision(CYN"$N"NOR+CYN"微微一笑，輕聲唱起了歌來。\n"NOR,this_object());
        call_out("sing_song",2);
    }
}

void sing_song()
{
    message_vision(CYN"      "+songs[i]+"\n"NOR,this_object());
    i++;

    if( i < sizeof(songs) )
    {
        remove_call_out("sing_song");
        call_out("sing_song",3);
    }
    else
    {
        remove_call_out("song_over");
        call_out("song_over",2);
    }
}

void song_over()
{
    message_vision(CYN"\n$N"NOR+CYN"唱罷，又是微微一笑，似是想起許多往事。\n"NOR,this_object());
    singing=0;
}

void delete_me()
{
    object my_host;

    if( !environment( this_object() ) ) return;

    my_host=find_player(query("host_id"));
    if( my_host && query_temp("huanjing", my_host) == "start" && 
       query_temp("hj_find_ok", my_host) != "yes" )
        tell_object(my_host,HIR"你心中似乎掠過一絲不安，卻又不知道為什麼。\n"NOR);

    message_vision(HIW"$N"HIW"似乎滿心失落地張望了一下，搖了搖頭，忽地消失不見了。\n"NOR,this_object());
    remove_call_out("sing_song");
    destruct(this_object());
}

int ask_baowu()
{
    object me,tianma_zhishen,ob,obj1,obj2,gem_npc,my_gem,gem_rooms;
    int temp_i;
    string gem_name,gem_id;

    if( !query("room_mark", environment(this_player())) && !wizardp(this_player()) )
        return 0;

    me=this_player();
    ob=this_object();

    if( !query_temp("huanjing", me) || query_temp("huanjing", me) != "start" || 
        !query_temp("hj_hp", me) || query_temp("hj_hp", me)<1 )
        return 0;

    if( singing == 1) 
    {
        write(query("name", ob)+"正在唱歌呢，哪裡有空回答你呀。\n");
        return 1;
    }

    if( query("host_id", ob) != query("id", me) )
    {
        message_vision(CYN"$N"NOR+CYN"微微笑了一笑，卻並不說話。\n"NOR,ob);
        return 1;
    }

    obj1=present(me_mark[1],me);
    obj2=present(me_mark[2],me);


// 玩家要起碼帶上其他兩個組合部分在身上才能繼續
// 而且，必須是自己的寶物才行
// 下調，帶上一個即可

    if(!obj1 && !obj2)
    {
        message_vision(CYN"$N"NOR+CYN"似乎剛說點什麼，忽地想起什麼似的微微笑了一笑，卻又不說話了。\n"NOR,ob);
        return 1;
    }

    if( obj1 && query("host_id", obj1) != query("id", me) )
    {
        command("say 這"+query("name", obj1)+NOR+CYN"並不是你的。你怎麼拿了別人的東西？");
        return 1;
    }

    if( obj2 && query("host_id", obj2) != query("id", me) )
    {
        command("say 這"+query("name", obj2)+NOR+CYN"並不是你的。你怎麼拿了別人的東西？");
        return 1;
    }

    if( !query_temp("hj_find_gem/name", me) || !query_temp("hj_find_gem/id", me) )
    {
        temp_i=random(5);
        if(temp_i >= sizeof(gem_names) )
            temp_i = sizeof(gem_names) -1;
        gem_name = gem_names[temp_i];
        gem_id = gem_ids[temp_i];

        command("say 你若能尋得"+gem_name+"，我將予你我的國度的寶物。");
        set_temp("hj_find_gem/name", gem_name, me);
        set_temp("hj_find_gem/id", gem_id, me);
        command("smile "+query("id", me));

        gem_npc=new(__DIR__"hj_npc_kill");

        set("delete_time_max", 1800, gem_npc);//此帶寶NPC最多半小時後清除
        set("take_gem_npc", "yes", gem_npc);
        set("the_gem_for",query("id",  me), gem_npc);
        gem_npc->setme( temp_i );

        temp_i=1+random( HJ_ROOM_AMOUNT );
        gem_rooms=find_object( HJ_DIR +"hj_room"+temp_i);
        if(!gem_rooms) gem_rooms=load_object( HJ_DIR +"hj_room"+temp_i);
        gem_npc->move(gem_rooms);
        if( query("msg", gem_npc))tell_room(gem_rooms,query("msg", gem_npc));
        else tell_room(gem_rooms,query("name", gem_npc)+"走了過來。\n");
        return 1;
    }

    my_gem=present(query_temp("hj_find_gem/id", me),me);
    if(!my_gem)
    {
        command("say 你還未尋得"+query_temp("hj_find_gem/name", me)+"啊。");
        command("pat "+query("id", me));
        return 1;
    }

// 成功尋到該族寶物
    baowu=new(baowu_dir);
    set("host_id",query("id",  me), baowu);
    baowu->setme( 0 );
    baowu->move(me);

    message_vision(CYN"$N"NOR+CYN"拿出一個"+query("name", my_gem)+NOR+CYN"遞給了"+query("name", ob)+NOR+CYN"。\n",me);
    destruct(my_gem);
    command("idle2");
    message_vision(CYN"$n"NOR+CYN"微微一笑，把一個"+query("name", baowu)+NOR+CYN"遞給了$N"NOR+CYN"。\n"NOR,me,ob);

// 新添物品“幽靈之令”，可在 hj_room1.c 快速得到幽靈武士JOB。

    baowu = new( __DIR__"hj_obj_ylling" );
    set("my_master", me, baowu);
    set("this_time_mark",query_temp("this_time_mark",  me), baowu);
    baowu->set("long",
        query("long", baowu)+"它上面似乎刻著個細細的名字："+query("id", me)+"\n");
    delete("waiting_set", baowu);
    baowu ->move(me);

    message_vision(CYN"$n"NOR+CYN"又拿出了一個"+query("name", baowu)+NOR+CYN"遞給了$N"NOR+CYN"。\n"NOR,me,ob);
    command( "say “近日林中竟有幽靈族人現身，請帶上這個令牌，或有些許幫助。”");
    message_vision(CYN"$N"NOR+CYN"說完，身影突然朦朧，竟然就此消失不見！\n"NOR,ob);
    message_vision(CYN"$N"NOR+CYN"細細思索著，一時間竟然呆住了。\n"NOR,me);
    me->start_busy(10+random(10));   // 此時有極高的忙時，並且有怪物出現要打

    temp_i = 3;
    while( temp_i -- )
    {
        if(random(3))
        {
            baowu = new(__DIR__"hj_npc_kill");
            set("killme_by",query("id",  me), baowu);
            baowu ->move(environment(me));
            message_vision( "$N快步走了過來！\n", baowu);
        }
    }

    singing=1; 
// 這個可以作應急判斷，當這wait delete 的短短一秒裡，可以保証不再執行任何函數 :)
    remove_call_out("sing_song");
    destruct(this_object());
    return 1;
}
