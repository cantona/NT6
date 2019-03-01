// /d/gaoli/xingguan
// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "武士行館");
        set("long", @LONG
這裡是行館的大廳，廳中擺著一張杉木圓桌和幾張椅子，桌上是一
套精致的宜興瓷器。對門立著一座玉石屏風，據說是高麗皇帝所賜。
LONG
        );
set("exits", ([
                "east":__DIR__"yudao5",
                "enter":__DIR__"neitang",
        ]));
set("objects", ([
                "/d/gaoli/npc/shi1" : 4,
        ]));
       setup();
     //"/obj/board/party_yj_b.c"->foo();
}        
