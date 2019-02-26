// Room: /d/taishan/xitian.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "西天門");
        set("long", @LONG
月觀峯山陰有兩塊巨石壁立如門，有如給人斬削過似的，正是岱頂
的西面出口，稱西天門。明萬曆年間林古度在石門上題“西闕”。鍾惺
在《登泰山記》中頌道：“岱之為天門者三，西天門者石自門焉，真天
門也。”
LONG );
        set("exits", ([
                "southdown" : __DIR__"yueguan",
        ]));
        set("objects", ([
                CLASS_D("taishan")+"/yuqingzi" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 20);
	set("coor/y", 310);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}