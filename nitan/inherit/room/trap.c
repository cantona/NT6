// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;

#define BUSY        1     // 讓玩家BUSY      
#define TRIP        2     // 讓玩家摔到別的房間   
#define LOSTMAP     3     // 讓迷宮地圖失效       
#define CHANGEMAP   4     // 讓迷宮地圖刷新       
#define WOUND       5     // 讓玩家受傷          

void create()
{
        set("short", "迷宮");
        set("long", @LONG
這是一間寬敞的石屋，四周巨石壘就的牆壁泛出幽幽的青色光芒，兩盞青銅
燈吐出一尺高的火燄，飄忽閃爍，偶然有燈花爆裂的輕響，更令人感到窒息般的
寂靜。地上是丈許見方的青石板舖就，房間中央一塊白色石板格外醒目，上面雕
刻著細密的圖紋，讓人不由自主的想上前查看（mazemap）一番。
LONG );
        setup();
}

void init()
{
        object me, room, next_room;
        int trap;
        object mazeobj;
        int damage;

        room = this_object();  
        if( !(me = this_player()) ) return;
        if( !userp(me) ) return;
        if( !(trap=query("maze/trap", room)))return ;
        mazeobj=get_object(query("mazeobj", room));
            
        switch( trap ) {
        case BUSY:
                message_vision(HIR "\n$N腳下一滑，差點摔個嘴啃泥，好不容易穩住身"
                        "子，才感覺腳踝扭傷了，好痛啊...\n\n" NOR, me);
                me->start_busy(5);
                break;
        case TRIP:
                message_vision(HIR "\n$N一腳踩上了什麼東西，身形再也把持不住，猛"
                        "的向前滑出，只留下一聲驚叫久久回盪...\n\n" NOR, me);
                next_room = mazeobj->trip_maze(room);
                if( objectp(next_room) )
                        me->move(next_room);
                break;
        case LOSTMAP:
                message_vision(HIR "\n$N只聽得腳下一聲喀嚓輕響，忽見到房間中央的"
                        "白色石板閃起一道強光，旋即迅速黯淡下去...\n\n" NOR, me);
                //mazeobj->set_display_map(0);
                break;
        case CHANGEMAP:
                mazeobj->init_maze(room);
                message_vision(HIR "\n$N一腳踩到了什麼東西，急惶惶的把腳收起，卻"
                        "已經聽到陣陣沉悶的聲音從地下響起...\n" NOR 
                        HIR "只見四周光影晃動，整個房間似乎在快速移動，等一切安靜"
                        "下來，周遭景象似乎有所改變。\n\n" NOR, me);
                break;
        case WOUND:
                message_vision(HIR "\n只聽得一聲機括脆響，$N下意識的趕緊避讓，卻"
                        "為時已晚，一支鋼弩不偏不倚正好射中$N。\n" NOR 
                        HIR "$N驚怒交加，傷口處痛徹心扉，終于忍不住連聲哀叫起來。"
                        "\n\n" NOR, me);
                damage=query("max_qi", me);
                damage = damage/10 + random(damage/10) + 1;
                me->receive_wound("qi", damage);
                break;
        default:
                break;
        }
    
        // 把這個房間的陷阱去除
        delete("maze/trap");
        mazeobj->remove_trap(room);
        return;    
}
