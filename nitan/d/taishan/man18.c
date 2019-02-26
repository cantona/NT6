// Room: /d/taishan/man18.c
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "慢十八盤");
        set("long", @LONG
泰山有三個十八盤之説。自開山至龍門為“慢十八”，再至昇仙坊
為“不緊不慢又十八”，又至南天門為“緊十八”，共計一千六百三十
餘階。你現在正走在慢十八盤上，低頭就看見石階。看着旁邊挑擔上山
的挑夫，頓時自歎不如。
LONG );
        set("exits", ([
                "northup"   : __DIR__"longmen",
                "southdown" : __DIR__"kaishan",
        ]));
        set("objects", ([
                __DIR__"npc/tiao-fu" : 2,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 250);
	set("coor/z", 150);
	setup();
        replace_program(ROOM);
}