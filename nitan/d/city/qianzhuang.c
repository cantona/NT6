// Room: /city/qianzhuang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "錢莊");
        set("long", @LONG
錢家開的錢莊，在中原可算是最老字號和信譽最好的錢莊了，已
有幾百年的歷史，在全國各地都有分號。它發行的銀票信譽極好，通
行大江南北。錢莊中央有一半人多高的紅木櫃台，櫃枱上面掛着一塊
牌子 (paizi)。戴着小眼鏡的錢老闆正坐在櫃枱後面看他的帳本，似
乎並沒有注意到你進來。
LONG );
	set("exits", ([
		"east" : "/d/city/beidajie1",
	]));
	set("item_desc", ([
		"paizi" : @TEXT
     本錢莊提供以下服務：
      存錢        deposit或者cun
      取錢        withdraw或者qu
      錢幣兑換    convert或者duihuan
      查帳        check或者chazhang
      轉帳        transfer或者zhuanzhang
TEXT
	]) );

	set("objects", ([
		"/d/city/npc/qian" : 1
	]));
        set("no_fight", 1);
	set("coor/x", -10);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}