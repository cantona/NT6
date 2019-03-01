// Room: /qingcheng/xiaoqiao.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "小橋");
        set("long", @LONG
小橋橫跨小溪上。溪水清澈，游魚卵石斑駁可數。橋北面就是
青城建福宮了。青城是道家發軔之處，號道教的“第五洞天”，相
傳東漢張陵在此結廬傳授五斗米道，至今宮闕連綿，傳道嗣法不絕。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "south" : __DIR__"qcroad3",
                "north" : __DIR__"jianfugong",
        ]));

        set("no_clean_up", 0);
        set("coor/x", -8060);
        set("coor/y", -930);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}