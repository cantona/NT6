// Room: /d/yueyang/langyinting.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "朗吟亭");
        set("long", @LONG
相傳為呂洞賓吟過詩的地方，座落在君山龍口的東側山頭上。與對
樓的岳陽樓和三醉亭遙遙相望。呂洞賓數次遊過岳陽，曾作詩：“朝遊
北越暮蒼梧，袖裏青蛇膽氣粗。三醉岳陽人不識，朗吟飛過洞庭湖。”
飛到君山以後，以泉洗腳，在山高卧，於千夜玩月，為紀念他，就在他
傾酒高吟，醉卧酣眠之處建立了一座兩層的“朗吟亭”。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown"  : __DIR__"shijie2",
                "westdown"  : __DIR__"shijie1",
                "southdown" : __DIR__"xijiaochi",
        ]));
        set("coor/x", -1690);
        set("coor/y", 2290);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}