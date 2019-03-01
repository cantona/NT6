inherit ROOM;

void create()
{
        set("short", "中院");
        set("long", @LONG
這裡是藥王谷的內院，寬闊的院子莊嚴肅穆，四周的角落裡
都擺放著各種各樣的藥罐。院子中央東北向擺放著兩排石礅，
大概是藥王谷給弟子講學用的。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"yitong",
  "south" : __DIR__"gd5",
  "east" : __DIR__"ssl2",
  "west" : __DIR__"ssl1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
