inherit ROOM;

void create()
{
        set("short", "玄冥峯");
        set("long", @LONG
這裏便是玄冥峯了，只見四周白雪覆蓋，遠處羣山卻是葱
綠一片。舉目四望，但見不遠處玄冥谷中炊煙了了，偶有猴子
松鼠之類小生靈忽而躍出，而後又隱沒與羣山之間。
LONG );
        set("exits", ([
                "southdown"    : __DIR__"shanlu4",
        ]));

        set("objects", ([
                "/kungfu/class/xuanming/bai" : 1,
        ]));

        set("outdoors", "xuanming");
        setup();
        replace_program(ROOM);
}