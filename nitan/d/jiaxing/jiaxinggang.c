// Room: /d/jiaxing/jiaxinggang.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "嘉興海港");
        set("long", @LONG
這裏是嘉興海港，港內白帆點點，碼頭上停着好多漁船，正要出海
的漁民忙碌地來來往往，一個船老大摸樣的人正在拼命呼喝着在船上做
幫工的漁家孩子。船工是不少，可是一提起桃花島卻個個搖頭。
LONG );
        set("exits", ([
                "west" : __DIR__"nanhu",
        ]));
        set("objects", ([
           //"/d/taohua/npc/laoda": 1,
                "/d/taohua/npc/chuanfu": 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jiaxing");
	set("coor/x", 1210);
	set("coor/y", -1770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}