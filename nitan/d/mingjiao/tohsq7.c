//TOHSQ7.C

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裡是瀑布上方一道窄窄的山樑，渾然天成。石樑上面人工鑿出
一格格階梯。邊上釘了幾棵木樁，繞上粗長的麻繩作為扶手。瀑布在
腳下奔騰而過，山腳下匯成一個深潭。
LONG );
        set("exits", ([
                "north" : __DIR__"hsqmen",
                "south" : __DIR__"tohsq6",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}