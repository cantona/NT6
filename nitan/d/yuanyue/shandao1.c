// This program is a part of NITAN MudLIB

inherit ROOM;
void create()
{
        set("short", "山道"); 
        set("long", @LONG
到了此處，山勢漸漸平坦些許，已可大致看到不遠的圓月山莊，
那是一棟坐落在山腰上的房子，房子很大，建築得很堂皇。表示房主
一定很有錢。但房子距離小鎮也太遠了些，也太偏僻了些，附近簡直
可說是荒無人煙。
LONG );
        set("outdoors", "wansong");
        set("type","road");
        set("exits",([
                "south": "/d/wudang/sanbuguan",
                "north":__DIR__"shandao2",
        ]) );

        set("coor/x",-590);
        set("coor/y",190);
        set("coor/z",70);
        setup();
        
} 
