// Room: /d/taishan/jin18.c
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "緊十八盤");
        set("long", @LONG
你爬在緊十八盤上，抬頭只能看到前面的人的鞋底，低頭穿襠則只
見到後面人的發頂。在這裡每走十來步便要稍一休息。西崖上有巨巖懸
空，側影佛頭側枕，高鼻禿頂，慈顏微笑，名迎客佛。
　　十八盤巖層陡立，在不足兩裡地內升高近一裡。明人賦《十八盤》
詩：“拔地五千丈，沖霄十八盤。徑從窮處見，天向隙中觀。重累行如
畫，孤懸峻若竿。生平饒勝具，此日骨猶寒。”
LONG );
        set("exits", ([
                "northup"   : __DIR__"nantian",
                "southdown" : __DIR__"shengxian",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 290);
	set("coor/z", 190);
	setup();
        replace_program(ROOM);
}