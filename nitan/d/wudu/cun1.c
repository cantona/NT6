inherit ROOM;

void create()
{
        set("short", "小村口");
        set("long", @LONG
這裡是桃花江邊的一個小村，村口有幾個農家的小孩正在大樹底
下玩耍。遠遠的升起縷縷炊煙，忙碌了一天的人們開始做飯了。 
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"cun2",
                "west" : __DIR__"jiang2",
        ]));
        set("objects", ([
                 __DIR__"npc/kid": 3,
        ]));
    
        setup();
}