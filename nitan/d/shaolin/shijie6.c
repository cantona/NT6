inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
這裡是瀑布上方一道窄窄的山樑，渾然天成。石樑上面人工鑿出
一格格階梯。邊上釘了幾棵木樁，繞上粗長的麻繩作為扶手。瀑布在
腳下奔騰而過，在不遠的山腳下匯成一個深潭。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie5",
                "northup" : __DIR__"shijie7",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/jue-yuan" : 1,
        ]));

        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
