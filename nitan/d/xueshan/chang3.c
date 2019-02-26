inherit ROOM;

void create()
{
        set("short", "武場");
        set("long", @LONG
 這裏是雪山寺的小練武場，樹着好多木樁和沙袋，僧人們日常均
在此刻苦習武。往南走就是大練武場，許多雪山弟子在那裏練功。
LONG );
        set("outdoors", "xueshan");

        set("exits", ([
                "north" : __DIR__"houyuan",
                "south" : __DIR__"chang",
        ]));

        setup();
        replace_program(ROOM);
}