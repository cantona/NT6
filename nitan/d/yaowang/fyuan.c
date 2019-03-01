inherit ROOM;

void create()
{
        set("short", "前院");
        set("long", @LONG
這裡是前院的小廣場，用青磚舖就的地面非常整潔。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"gd3",
  "south" : __DIR__"gd2",
  "east" : __DIR__"yanwu",
  "west" : __DIR__"keting",
]));

        set("objects", ([
        "/kungfu/class/yaowang/jiang" : 1,
]));
        set("valid_startroom", 1);
        set("no_fight", 1);
        set("outdoors", "yaowang");
        setup();
//加個post板
}
