// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "翠竹園");
        
        set("long", @LONG
『有竹無肉軒』四周就是翠竹園，這裡種滿了竹，每到風清月白
的夏夜，圓月山莊的歷代主人們便會來此，一把竹椅，一壺清茶，聽
那海浪般的竹濤聲，可惜柳若鬆很久已經沒這個興致了，倒是會時常
和他的兄弟們砍竹賣錢換酒，年復一年，翠竹園中的竹子也越來越少。
LONG );
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "south":__DIR__"wuzhuxuan",
        ]) );

        set("coor/x",-610);
        set("coor/y",230);
        set("coor/z",80);
        setup();
} 
 
