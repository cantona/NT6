// Room: /d/fuzhou/jibixiang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "吉庇巷");
        set("long", @LONG
俗呼“急避巷”。宋鄭性之中狀元衣錦還鄉時，曾因以前他落魄而
凌辱過他的人，自感虧心而急避，遂稱“急避巷”。明代以諧音改巷名
為“吉庇巷”，取吉祥如意、庇境安寧之意。
LONG );
        set("exits", ([
                "west" : __DIR__"nanhoujie7",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}