inherit ROOM;

void create()
{
        set("short", "玄冥峰");
        set("long", @LONG
這裡便是玄冥峰了，只見四周白雪覆蓋，遠處群山卻是蔥
綠一片。舉目四望，但見不遠處玄冥谷中炊煙了了，偶有猴子
鬆鼠之類小生靈忽而躍出，而後又隱沒與群山之間。
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