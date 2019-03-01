// /d/xueshan/dumudian.c
// Summer 9/25/96
#include <ansi.h>
#include <room.h>

inherit ROOM;

nosave string current_id = "";
nosave int current_job = 0;

int introduce_robber(object current_player);
int reset_to_normal();

void create()
{
        set("short", "度母殿");
        set("long", @LONG
 這裏是雪山寺的度母殿，正中五尊大座佛，均為高肉髻、外披袒
右袈裟、結跏趺坐、執手印須弭坐各異。殿內對稱排列四根大柱，上
雕忍冬紋，下刻連珠紋。北壁上供有兩尊金剛像：馬頭明王和閻魔護
法。
LONG );
        set("exits", ([
                                "west" : "/d/xueshan/zoulang1",
                ]));
        set("objects", ([
                "/d/xueshan/npc/zrlama": 1,
                "/d/xueshan/obj/tonggang": 1,
        ]));

        set("cost", 1);
    setup();
}

void reset()
{
        ::reset();
        set("no_clean_up", 1);
}

void init() {
    object challenger, me = this_player();

//    printf("blah blah blah\n");
    if( (query("family/family_name", me) == "雪山寺" || 
          query("family/family_name", me) == "血刀門" )
         && !(current_job)
          && query("combat_exp", me)>2000000){
//        printf("hehehe\n");
        call_out("introduce_robber", random(10)+10, me);
        current_job = 1;
    }
//    printf("current_job = %d\n",current_job);
}

int introduce_robber(object current_player)
{
    object robber;

//    printf("name = %s\n", current_player->query("id"));
        if (!current_player) return 0;
    if( objectp(present(query("id", current_player),this_object())) )
    {
//        printf("test1\n");
        robber = new("/d/xueshan/npc/robber");
//        printf("test2\n");
        robber->setup_robber(query("combat_exp", current_player));
        robber->move(this_object());
//        printf("test3\n");
//        message("vision", "一個"+robber->name(1)+"急急忙忙走了過來。\n", this_object(), robber);
        message_vision(HIC"一個$N急急忙忙走了過來。\n"NOR, robber);
        message_vision(HIR"$N説道：聽説這個銅缸裏存着喇嘛用的酥油，老子今天特地來看看，識相的趕快給我滾開！\n" NOR, robber, current_player);
        robber->start_checking(current_player);
//        printf("test4\n");
    }
    else
    {
        reset_to_normal();
    }
}

int reset_to_normal()
{

   current_job = 0;
   return 1;

}
