inherit ROOM;

void create()
{
        set("short", "中州南門");
        set("long", @LONG
到了中州的南城門了。出了城不遠就是一大片的樹林。聽
説南城門外一帶經常有土匪出沒。可在這裏把守的官兵比較多
所以城裏倒也太平無事。
LONG);
        set("outdoors", "zhongzhou");
        set("exits", ([
                  "north" : __DIR__"wendingnan4",
                //"south" : __DIR__"nroad",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/d/city/npc/wujiang" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -9040);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}