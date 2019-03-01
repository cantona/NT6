// Room: /d/wuyi/chadong.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "茶洞");
        set("long", @LONG
茶洞又名玉華洞、升仙洞、碧玉洞，其實不是洞，是一片崢嶸深鎖
的峽谷。三面巖壁環繞，地勢幽深險要，飛瀑噴雪，石洞流水，幽絕塵
寰。清隱巖壁上“茶洞”二字，遒勁有力、韻味深長。這便是“臻山川
精英秀氣所鐘，品具巖骨花香之勝”的武夷巖茶的真正洞天仙府。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "westup"    : __DIR__"tianyoupath1",
                "southwest" : __DIR__"shaibuyan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1370);
        set("coor/y", -4980);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
