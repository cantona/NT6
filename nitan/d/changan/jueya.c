// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
    set("short", "絕崖");
    set("long",@LONG
眼前一片空曠，腳下是一個深不見底的懸崖，稍一邁步，崖邊的
碎巖就紛紛落了下去，久久都沒聽到回音。
LONG
        );
        set("outdoors","changan");
        set("exits", ([
                "west" :__DIR__"caodi",
        ]));
        set("coor/x", -10610);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}


