// 本文件被 all_room_info_hj.h
// 及 1_room_info_special.h 
// 共同調用。

// naihe 0:33 03-10-21



void reset()
{ 
    ::reset();
    set("no_clean_up", 1); 
}

int block_cmds()
{
    write("幻境裏不允許使用這個指令。關於 hj 裏使用的一些基本指令，請輸入 help hj2003 查詢。\n");
    return 1;
}

int do_look(string arg)
{
    string *orention;

    if( !arg )
        return 0;
    orention=({ "east","west","south","north",
        "northeast","northwest","southeast","southwest"
    });
    if( member_array( arg , orention ) != -1 )
    {
        write("到處都是一片密林，你看不到遠處的情況。\n");
        return 1;
    }
    return 0;
}

int do_get(string arg)
{
    if( !arg || arg != "all")
        return 0;
    write("還是一樣一樣地揀罷。\n");
    return 1;
}

void get_out_here( object me )
{
    if( !me ) return;

    message_vision( HIR"$N"HIR"不知怎麼的闖進了幻境密林裏，一陣奇異的震盪把$N"HIR"拋了出去。\n"NOR,me);
    me->move( __DIR__"room_door_hj" );
    message_vision("一陣莫名的震盪忽來忽逝，$N不知怎麼的就忽地出現在這裏了。\n",me);
}


void full_all( object me )
{
    if( !me )
        return;
    set("jingli",query("max_jingli",  me), me);//只要加些精力給走路時消耗，以及保持餓不死就行了。
    set("food", 50, me);
    set("water", 50, me);
}

int valid_leave(object me, string dir)
{
    string temp;

    if( query_temp("hj_move_busy", me)>1000 )
        return notify_fail("密林裏糾結重重，你無法行走太快。\n");

    temp=query_temp("hj_need_waiting", me);
    if( temp && me->is_busy() )
    {
        switch(temp)
        {
            case "healing":return notify_fail("你正在療傷呢，走不開。\n");
            case "fighting":return notify_fail("你還在戰鬥中，被纏住了走不開。\n");
            default:return notify_fail("你正忙着呢，無法離開。\n");
        }
    }

    if( query_temp("hj_the_orention", me) == dir && random(10) == 1 && 
        !query("hj_game/npc", me) )
    {
        call_out("games_random_move",1, me);
        message_vision( HIR"\n一陣奇異的震盪忽然傳來……\n"NOR, me );
        me->start_busy(2);
        return notify_fail("\n");
    }

    // 走路 busy 方式更改，配合 七星燈 來實現新的效果。
    // 七星燈有將此數值逐秒遞減的函數。
    // 風之國度主動技能效果  走路時忙時較低
    if( !query("hj_game/npc", me) )
    {
        if( query_temp("hj_game_find", me) == "feng" )
            addn_temp("hj_move_busy", (150+random(100)), me);//再增強
        else addn_temp("hj_move_busy", (300+random(200)), me);
    }

    set_temp("hj_the_orention", dir, me);//記錄這一步的方向

    return ::valid_leave(me, dir);
}

void games_random_move( object me )
{
    object rooms;
    string random_rooms;

    if( !me || !environment(me) || environment(me) != this_object() ) return;
    random_rooms=__DIR__"hj_room"+( 2 + random( HJ_ROOM_AMOUNT-1 ));

    tell_room(environment(me),HIR+query("name", me)+HIR"突然憑空消失不見！\n"NOR,({me}));
    rooms=find_object(random_rooms);
    if(!rooms) rooms = load_object(random_rooms);
    if( !rooms ) rooms = this_object();
    this_player()->move(rooms);
    message_vision(HIG"$N"HIG"被一股奇怪的震盪送到了這裏來。\n"NOR,me);
}
