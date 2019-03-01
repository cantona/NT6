inherit ROOM;

void create()
{
        set("short", "桃園小路");
        set("long", @LONG
眼前豁然開朗，你輕鬆地走在桃園邊的小路上。路上落英繽紛，
一邊是桃樹林，盛開著粉紅的桃花，紅雲一片，望不到邊。還可以看
見蜜蜂「嗡嗡」地在花間飛上飛下忙個不停，間或傳來猿猴的嘰咋聲。
北邊是條環山的黃土路。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "south" : __DIR__"tyroad8",
        ]));
        set("objects", ([
                "/clone/quarry/hou" : 1
        ]));
        set("coor/x", -310);
        set("coor/y", -300);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}