inherit ROOM;

void create()
{
        set("short", "山道"); 
        set("long", @LONG
你走在去圓月山莊的山道上，一抬頭，又可看見幾個或是蜈蚣狀，
或是老鷹狀的風箏高高飛舞在藍天白雲中。山風徐徐，白雲悠悠，不
覺感覺悠閒自得。往北面探頭望去，已可隱約看見圓月山莊的銅漆大
門。
LONG );
        set("outdoors", "wansong");
        set("type","road");
        set("exits",([
                "north":__DIR__"damen",
                "south":__DIR__"shandao1",
        ]) );
        

        set("coor/x",-590);
        set("coor/y",180);
        set("coor/z",60);
        setup();
} 
