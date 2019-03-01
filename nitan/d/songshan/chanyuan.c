// Room: /d/songshan/chanyuan.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "峻極禪院");
        set("long", @LONG
峻極禪院處嵩山絕頂，院中古柏森森，殿上並無佛像。院宇遼闊，
可容千人。往裡就是嵩山派的本院了。
LONG );
        set("exits", ([
                "south" : __DIR__"qianting",
                "north" : __DIR__"zhongmen",
        ]));
        set("objects", ([
                CLASS_D("songshan")+"/fei" : 1,
                CLASS_D("songshan")+"/first" : 1,
        ]));
        set("valid_startroom",1);
        set("coor/x", -20);
        set("coor/y", 870);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
        "/clone/board/songshan_b"->foo();
}