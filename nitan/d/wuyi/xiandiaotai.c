// Room: /d/wuyi/xiandiaotai.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "仙釣台");
        set("long", @LONG
這裏位於四曲溪北，又稱釣魚台。從水中向上聳立，尖峭的巖鳳，
直插雲天，猶如一個頭戴竹笠、臨溪垂釣的仙翁。“釣仙姜子牙四曲犯
難，拗斷釣竿，誓不垂釣”指的就是這裏。至今巖孔中釣竿仍在。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"shijianshi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1370);
        set("coor/y", -4990);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
