// Room: /u/zqb/tiezhang/lx.c

inherit ROOM;

void create()
{
        set("short", "瀘溪");
        set("long", @LONG
這裏是湘西的一個小鎮。雖然此地地處偏僻，但這裏來往的行人
仍然很多。西面是一間供人休息打尖的小客店。西南方四十里處，就
是此處有名的猴爪山。
LONG );
        set("outdoors", "tiezhang");
        set("exits", ([ /* sizeof() == 3 */
                "north" : __DIR__"hunanroad2",
        ]));
/*
        set("objects", ([
                CLASS_D("misc") + "/qiuqianren" : 1,
        ]));
*/
        set("coor/x", -3600);
        set("coor/y", -180);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}