inherit ROOM;

void create()
{
          set ("short", "中州道");
          set ("long", @LONG
這條筆直的大路是連接南北的交通要道，南面通向神州重
地中州城。向北是條渡口路，通向長江。過了江就是揚州了。
LONG);

          set("outdoors", "zhongzhou");
          set("exits", ([
                  "south" : __DIR__"to_zhongzhou2",
                  "north":__DIR__"dukoulu",
        ]));
        set("coor/x", -150);
        set("coor/y", 50);
        set("coor/z", 10);
        setup();
}