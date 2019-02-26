// /d/gaoli/xingguan
// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "武士行館");
        set("long", @LONG
這裏是行館的大廳，廳中擺着一張杉木圓桌和幾張椅子，桌上是一
套精緻的宜興瓷器。對門立着一座玉石屏風，據説是高麗皇帝所賜。
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
