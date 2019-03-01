// Code of ShenZhou
// Room: /d/mingjiao/szchang.c
// Zhangchi 3/00

inherit ROOM;

void create()
{
        set("short", "鑄造場");
        set("long", @LONG
在場子南側有一座高爐，爐口火孔徑不到一尺。一個銳金旗旗下
弟子，身旁放著十余件兵器，目不轉睛地望著爐火，每見爐火變色，
便將已有些成型的兵器放入爐中試探火力。旁有兩個烈火旗下弟子正
賣力地拉扯風箱，但見爐火直竄上來，火燄高達丈許，蔚為奇觀。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "east" : __DIR__"lhqlwch",
]));
        set("objects", ([
                __DIR__"obj/ronglu": 1,
                __DIR__"obj/muzi": 1,
        ]));

        set("cost", 1);

        setup();

}

int valid_leave(object me, string dir)
{
        if( (dir == "north" || dir == "west") && query_temp("gun_making", this_player()) )
               return notify_fail("你正在打造火槍，不能離開這裡！\n");
        return ::valid_leave(this_player(), dir);
}