// Room: /qingcheng/songfengguan.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "上清殿");
        set("long", @LONG
這裡是鬆風觀主殿。殿中陳設奢華，顯見青城派財力不菲。正中的
三清座像也塑得極為精致，顯微著著，甚有神韻。殿側兩壁掛著幾柄舊
劍和一些青城派獨門兵器，想來都是本派前輩名宿們當年斬妖除魔時所
佩神兵，供奉于此激勵後代弟子。
LONG );
        set("valid_startroom", 1);
        set("exits", ([
                "south" : __DIR__"caochang",
                "north" : __DIR__"garden",
        ]));
        set("objects", ([
                __DIR__"npc/hou" : 1,
                CLASS_D("qingcheng") + "/first" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8080);
        set("coor/y", -830);
        set("coor/z", 90);
        setup();
        "/clone/board/qingcheng_b"->foo();
        replace_program(ROOM);
}
