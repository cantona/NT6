// Room: /u/zqb/tiezhang/lx.c

inherit ROOM;

void create()
{
        set("short", "瀘溪");
        set("long", @LONG
這裏是湘西的一個小鎮。雖然此地地處偏僻，但這裏來往的行人仍然很
多。西面是一間供人休息打尖的小客店。西南方四十里處，就是此處有名的
猴爪山。
LONG        );
        set("outdoors", "tiezhang");
        set("exits", ([ /* sizeof() == 3 */
                "southwest" : __DIR__"road-1",
                "northeast" : "/d/henshan/hsroad6",
                "west" : __DIR__"kedian",
        ]));

        setup();
        replace_program(ROOM);
}