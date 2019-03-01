inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條被人走出來的小山路，雖然不寬卻是夠一輛馬車
通行。小路順著山中較為平坦地帶緩緩向西伸展。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                "west" : __DIR__"xingxing1",
                "east" : __DIR__"guandao3",
        ]));

        setup();
        replace_program(ROOM);
}