// Room: /d/nanyang/beimen.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;
void create()
{
        set("short","北城門");
        set("long",@LONG
這裏是南陽北門。南陽古稱宛城，東邊是桐柏山、北面是伏牛山，
西靠秦嶺。當年張繡大敗曹操於此，典韋便戰死城外。“唱戲的腔，做
菜的湯”，這裏的風味也甚有名氣。
LONG);
        set("exits",([
                "north"  : __DIR__"yidao3",
                "south"  : __DIR__"dajie2",
        ]));
        set("objects",([
                "/d/city/npc/bing" : random(2)+1,
        ]));
        set("outdoors","nanyang");
	set("coor/x", -6940);
	set("coor/y", 790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}