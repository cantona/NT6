inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裡是院內的練武場，黃土場地上擺放著一些練功的石鎖，沙袋。
一個小頭目正在指導弟子練武。 
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"dating",
                "south" : __DIR__"nanyuan",
                "west" : __DIR__"damen",
                "north" : __DIR__"beiyuan",
        ]));
    
        setup();
        replace_program(ROOM);
}