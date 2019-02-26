inherit ROOM;

void create()
{
        set("short", "中院");
        set("long", @LONG
這裏是藥王谷的內院，寬闊的院子莊嚴肅穆，四周的角落裏
都擺放着各種各樣的藥罐。院子中央東北向擺放着兩排石礅，
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
