// Room: /d/fuzhou/huangxiang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "黃巷");
        set("long", @LONG
晉永嘉年間(307─312)中原黃姓人家避亂入閩，落戶在此，故稱黃
巷。唐代黃璞返隱歸居這裡。黃巢軍入福州，因聞黃璞的大名，命令兵
士“滅炬而過”。巷內歷代多住儒林學士，人文薈萃。清代知府林文英，
榜眼林枝春、巡撫李馥、楹聯大師樑章鉅、進士陳壽棋、趙新等，都曾
居巷內。樑章鉅五十八歲時，引疾歸田，住的就是黃璞的舊居，他在宅
內建的小樓，取名黃樓，旁辟假山池館，頗有江南園林風韻。
LONG );
        set("exits", ([
                "west" : __DIR__"nanhoujie4",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}